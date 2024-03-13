#include <stdio.h>
#include <mpi.h>
#include <unistd.h>  // Include for usleep

int main(int argc, char** argv) {
    int size, rank;
    useconds_t sleeplength;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size); // get the number of processes in MPI_Communicator and store it in the size variable
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // retrieve the rank of the current process in the MPI communicator and store it in the rank variable.

    sleeplength = (size - rank) * 1000000;

    printf("Process %d: Sleeping for %d microseconds\n", rank, sleeplength);
    usleep(sleeplength);

    printf("Process %d: Waking up\n", rank);

    MPI_Barrier(MPI_COMM_WORLD);

    printf("Process %d: Reached the barrier\n", rank);

    MPI_Barrier(MPI_COMM_WORLD);

    printf("Process %d: Completed the program\n", rank);

    MPI_Finalize();
    return 0;
}

// The asynchronous nature of MPI processes and their independent scheduling by the MPI runtime can lead to 
// variations in the order of execution and output. 
// While the barrier synchronization ensures that all processes reach a certain point before proceeding, 
// it does not enforce a specific order for the subsequent execution of processes.