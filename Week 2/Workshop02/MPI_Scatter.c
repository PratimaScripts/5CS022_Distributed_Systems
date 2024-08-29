#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv) {
    int isend[3], irecv;
    int rank, size, i;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        for (i = 0; i < size; i++) 
        isend[i] = i + 1;
    }

    MPI_Scatter(&isend, 1, MPI_INT, &irecv, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("rank = %d: irecv = %d\n", rank, irecv);

    MPI_Finalize();
    return 0;
}

// mpiexec -np 4 ./MPI_Scatter

// The error message "stack smashing detected" usually indicates a buffer overflow or stack corruption in your program. In this case, it may be related to the array isend being too small for the number of processes. Since you are using MPI_Scatter to distribute data from the root process to all other processes, each process expects to receive data of the specified count.

// In your code, the array isend has a size of 3 elements, but you are trying to scatter data to 4 processes. This mismatch can lead to memory corruption.