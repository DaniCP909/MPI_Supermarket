#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "Cliente.h"
#include "time.h"
#include <unistd.h>

//TAGS
//0 -> peticion cliente (id)
//1 -> caja asignada
//2 -> Liberar caja

void ejecutar_cliente(int rank)
{
    int cliente_id = rank - 1;
    int caja_asignada;
    int prioritario;
    int tiempo;
    srand(rank);
    MPI_Status status;
    while(1){
        prioritario = (rand() % 2);
        if(prioritario){
            tiempo = rand() % 11 + 10;
        }
        else {
            tiempo = rand() % 6 + 5;
        }
        //printf("-----------------------------Enviado mensaje desde %d\n", rank);
        int msg[2] = {prioritario, rank};
        MPI_Send(msg, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
        //printf("[PID%d]Cliente %d hace solicitud a PIZARRA\n", rank, cliente_id);
        MPI_Recv(&caja_asignada, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        for(int i = 0; i < rank; i++)printf("\t");
        printf("[PID%d] CLIENTE %d ENTRANDO en caja %d\n", rank, cliente_id, caja_asignada);
        sleep(tiempo);
        printf("[PID%d] CLIENTE %d SALIENDO DE caja %d\n", rank, cliente_id, caja_asignada);
        MPI_Send(&caja_asignada, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);

        //DUERME SIN ACTIVIDAD ANTES DE ENTRAR A LA COLA
        sleep((rand() % 10) + 10);
    }
}