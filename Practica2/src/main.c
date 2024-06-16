#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "Pizarra.h"
#include "Cliente.h"
#include <time.h>


int main(int argc, char ** argv)
{
    int rank, size;

    srand (time(NULL));

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        ejecutar_pizarra(rank, size);
    }
    else {
        ejecutar_cliente(rank);
    }


    MPI_Finalize();

    return 0;
}