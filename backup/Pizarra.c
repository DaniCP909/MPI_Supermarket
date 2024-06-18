#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "Cliente.h"
#include "Pizarra.h"
#include <time.h>
#include "cola_prioridad/TcolaPrioridad.h"
#include <unistd.h>

void imprimirVector(int * v, int c){
    printf("[");
    for(int i = 0; i < c; i++){
        printf("%d", v[i]);
        if(i < (c - 1)) printf(", ");
    }
    printf("]\n");
}

void ejecutar_pizarra(int rank, int size)
{
    MPI_Status status;
    int flag;
    
    //VARIABLES DE CONTROL------------------------------------------------------
    TColaPrioridad colaPrioridad;
    crearColaPrioridad(colaPrioridad);
    //cajas
    int cajas_ocupadas[N_CAJAS];
    int n_abiertas = (N_CAJAS / 2);
    int n_ocupadas = 0;
    for(int i = 0; i < N_CAJAS; i++){
        cajas_ocupadas[i] = 0;
    }
    int caja_liberada;
    //clientes
    int n_esperando = 0;
    int id_cliente_actual;
    //--------------------------------------------------------------------------

    
    while(1){
        while(1) {
            MPI_Iprobe(MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &flag, &status);
            int destinatario = status.MPI_SOURCE;
            if(flag){
                printf("CAJAS ABUERTAS: %d | CLIENTES ESPERANDO %d\n", n_abiertas, n_esperando);
                int msg[2];
                MPI_Recv(&msg, 2, MPI_INT, destinatario, 0, MPI_COMM_WORLD, &status);
                for(int i = 0; i < rank; i++)printf("\t");
                printf("[MAESTRO] recibe peticion %d, %d\n", msg[0], msg[1]);
                push(colaPrioridad, msg[0], msg[1]);
                n_esperando++;
            }
            else {
                break;
            }
        }
        while(n_ocupadas < n_abiertas && esColaPrioridadVacio(colaPrioridad)){
            int destino;
            int caja_asignada = -1;
            for(int i = 0; i < n_abiertas; i++){
                if(!cajas_ocupadas[i]){
                    caja_asignada = i;
                    break;
                }
            }
            if(caja_asignada != -1){
                    destino = pop(colaPrioridad);
                    cajas_ocupadas[caja_asignada] = 1;
                    n_ocupadas++;
                    n_esperando--;
                    for(int i = 0; i < rank; i++)printf("\t");
                    printf("[MAESTRO] envia caja %d a ps %d\n", caja_asignada, destino);
                    MPI_Send(&caja_asignada, 1, MPI_INT, destino, 1, MPI_COMM_WORLD);
            }
        }
        MPI_Iprobe(MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &flag, &status);
        int destinatario_caja_liberada = status.MPI_SOURCE;
        if(flag){
            MPI_Recv(&caja_liberada, 2, MPI_INT, destinatario_caja_liberada, 2, MPI_COMM_WORLD, &status);
            cajas_ocupadas[caja_liberada] = 0;
            n_ocupadas--;
        }
        if (n_esperando >= 2 * n_abiertas && n_abiertas < N_CAJAS) {
            n_abiertas++;
        } else if (n_esperando < n_abiertas && n_abiertas > 1) {
            n_abiertas--;
        }
        //MAESTRO SE BLOQUEA SI NO HAY CLIENTES ESPERANDO, hasta que haya uno, lo encola, y vuelve a iterar buscando mas peticiones
        if(n_esperando < 1){
            int msg_aux[2];
            MPI_Recv(&msg_aux, 2, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            push(colaPrioridad, msg_aux[0], msg_aux[1]);
            n_esperando++;
        }
    }

}