#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int size, rank, tag, count;
    MPI_Status status;

    int data[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        for (int i = 0; i < size - 1; i++) { // Iterates over all other processes (size - 1) in a loop.
            MPI_Recv(data, 100, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status); // Receive a message from any source with any tag.
            
            // Get the count of the received message. 
            // &status is the pointer to MPI_Status structure that was populated during the call to 'MPI_Recv". 
            // count will contain the number of elements of the specified datatype (in this case, integers) received in the last MPI receive operation.
            
            MPI_Get_count(&status, MPI_INT, &count); 
            
            printf("Received MPI_Get_count: %d int(s) from rank %d with tag %d\n", count, status.MPI_SOURCE, status.MPI_TAG);
        }
    } else {
        tag = rank * 100; // Set tag based on the rank.
        count = abs(rank + rand()) % 100; // Generate a random count value.
        printf("Rank %d: count = %d\n", rank, count); 
        MPI_Send(data, count, MPI_INT, 0, tag, MPI_COMM_WORLD); // Send a message to Rank 0 with the specified count and tag.
    }

    MPI_Finalize();
    return 0;
}


// Rank 2: count = 85
// Rank 3: count = 86
// Rank 1: count = 84
// Received MPI_Get_count: 85 int(s) from rank 2 with tag 200
// Received MPI_Get_count: 86 int(s) from rank 3 with tag 300
// Received MPI_Get_count: 84 int(s) from rank 1 with tag 100