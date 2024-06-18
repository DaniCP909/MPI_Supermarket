#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "Cliente.h"
#include "Pizarra.h"
#include <time.h>
#include "cola_prioridad/TcolaPrioridad.h"
#include <unistd.h>

void imprimirVector(int * v, int c) {
    printf("[");
    for(int i = 0; i < c; i++) {
        printf("%d", v[i]);
        if(i < (c - 1)) printf(", ");
    }
    printf("]\n");
}

void ejecutar_pizarra(int rank, int size) {
    MPI_Status status;
    int flag;

    // VARIABLES DE CONTROL ------------------------------------------------------
    TColaPrioridad colaPrioridad;
    crearColaPrioridad(colaPrioridad);
    
    // Cajas
    int cajas_ocupadas[N_CAJAS];
    int n_abiertas = 3; // Inicialmente abrir 3 cajas
    int n_ocupadas = 0;

    for(int i = 0; i < N_CAJAS; i++) {
        cajas_ocupadas[i] = 0;
    }
    int caja_liberada;

    // Clientes
    int n_esperando = 0;
    int n_prioritarios = 0;
    // --------------------------------------------------------------------------

    while(1) {
        // Probar si hay mensajes de clientes
        MPI_Iprobe(MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &flag, &status);
        if(flag) {
            int destinatario = status.MPI_SOURCE;
            int msg[2];
            MPI_Recv(&msg, 2, MPI_INT, destinatario, 0, MPI_COMM_WORLD, &status);
            push(colaPrioridad, msg[0], msg[1]);
            n_esperando++;
            if(!msg[0]) n_prioritarios++;
            printf("[MAESTRO] [clientes esperando = %d | cajas abiertas = %d] Ha recibido peticion de cliente %d con prioridad %d (0 = MAX)\n", n_esperando, n_abiertas, msg[1], msg[0]);
        }

        if(n_esperando > 0) {
            int destino;
            int caja_asignada = -1;

            // Asignar la caja de prioridad si hay clientes prioritarios y está libre
            if(n_prioritarios > 0 && !cajas_ocupadas[N_CAJAS - 1]) {
                caja_asignada = N_CAJAS - 1;
            } else {
                // Asignar una de las cajas abiertas
                for(int i = 0; i < n_abiertas; i++) {
                    if(!cajas_ocupadas[i]) {
                        caja_asignada = i;
                        break;
                    }
                }
            }

            // Si no se encontró una caja abierta, esperar a que se libere una
            if(caja_asignada == -1) {
                MPI_Recv(&caja_liberada, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
                printf("[MAESTRO] Se ha liberado la caja %d\n", caja_liberada);
                cajas_ocupadas[caja_liberada] = 0;
                if(caja_liberada != N_CAJAS - 1) n_ocupadas--;
                continue;
            }

            // Asignar cliente a caja
            int esPrioritario = hayClientesMaxPrio(colaPrioridad);
            destino = pop(colaPrioridad);
            cajas_ocupadas[caja_asignada] = 1;
            n_ocupadas++;
            if(esPrioritario) n_prioritarios--;
            n_esperando--;

            printf("[MAESTRO] [clientes esperando = %d | cajas abiertas = %d] Enviando caja %d a proceso %d\n", n_esperando, n_abiertas, caja_asignada, destino);
            imprimirVector(cajas_ocupadas, N_CAJAS);
            MPI_Send(&caja_asignada, 1, MPI_INT, destino, 1, MPI_COMM_WORLD);
        }

        // Ajustar el número de cajas abiertas
        if (n_esperando >= 2 * n_abiertas && n_abiertas < N_CAJAS - 1) {
            n_abiertas++;
        } else if (n_esperando < n_abiertas && n_abiertas > 1) {
            n_abiertas--;
        }
    }
}
