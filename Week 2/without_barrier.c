#include <stdio.h>
#include <mpi.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int size, rank;
    useconds_t sleeplength;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    sleeplength = (size - rank) * 1000000;

    printf("Process %d: Sleeping for %d microseconds\n", rank, sleeplength);
    usleep(sleeplength);

    printf("Process %d: Waking up\n", rank);

    // No MPI_Barrier here

    printf("Process %d: Completed the program\n", rank);

    MPI_Finalize();
    return 0;
}
