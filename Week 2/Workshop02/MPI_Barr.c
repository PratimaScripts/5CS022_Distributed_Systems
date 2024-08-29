// Like many other parallel programming utilities, synchronization is an essential tool in thread safety and 
// ensuring certain sections of code are handled at certain points. 
// MPI_Barrier is a process lock that holds each process at a certain line of code until all processes have reached that line in code.

#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main () {
    useconds_t sleeplen;

    int size, rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    sleeplen = (size - rank) * 1000000;
    usleep(sleeplen) ;
    printf("%d\n", rank);
    MPI_Barrier (MPI_COMM_WORLD) ;
    printf("%d\n", rank);
    MPI_Finalize();
    return 0;
}