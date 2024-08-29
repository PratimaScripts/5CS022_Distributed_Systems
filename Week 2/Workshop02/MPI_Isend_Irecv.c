#include "mpi.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	int rank, size;
    int tag, destination, count;
    int buffer; 

    tag = 1234;
    destination = 1; 
    count = 1; 
    MPI_Status status;
    MPI_Request request = MPI_REQUEST_NULL;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 

    if (rank == 0) {
        buffer = 9999;
        MPI_Isend(&buffer, count, MPI_INT, destination, tag, MPI_COMM_WORLD, &request); 
    }

    if (rank == destination) {
        MPI_Irecv(&buffer, count, MPI_INT, 0, tag, MPI_COMM_WORLD, &request); 
    }
    MPI_Wait(&request, &status); 

    if (rank == 0) {
        printf("processor %d sent %d\n", rank, buffer);
    }
    if (rank == destination) {
        printf("processor %d rcv %d\n", rank, buffer);
    }

    MPI_Finalize();

	return 0;
}

// In this example, processor 0 sends the value 9999 to processor 1.

// Keep in mind that this MPI program demonstrates a simple point-to-point communication using non-blocking communication (MPI_Isend and MPI_Irecv). 
// The sender (rank == 0) sends a message to the receiver (rank == destination), and both processes print messages indicating the sending and receiving of the message.