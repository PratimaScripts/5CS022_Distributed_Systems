#include "mpi.h"
#include <stdio.h>

// Function to simulate some computation
int compute(int value) {
    return value * 2;
}

// Function to simulate data consumption
void consume(int value) {
    // Simulate consuming data
    printf("Consuming data: %d\n", value);
}

int main(int argc, char* argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int data[100];
    MPI_Request request[99]; // One request for each send operation
    MPI_Status status[99];   // One status for each wait operation

    if (rank == 0) {
        for (int i = 1; i < 100; i++) {
            printf("i = %d, Rank 0 doing work...\n", i);
            data[i] = compute(i);
            printf("i = %d, Rank 0 sending to Rank 1\n", i);
            MPI_Isend(&data[i], 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request[i - 1]);
        }
        printf("Rank 0 finished sending data to Rank 1\n");
        MPI_Waitall(99, request, status);
    } else {
        for (int i = 1; i < 100; i++) {
            printf("i = %d, Rank 1 waiting for data\n", i);
            MPI_Irecv(&data[i], 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request[i - 1]);
            MPI_Wait(&request[i - 1], MPI_STATUS_IGNORE); // Wait for the specific receive operation to complete
            printf("i = %d, Rank 1 doing work...\n", i);
            consume(data[i]);
        }
    }

    MPI_Finalize();

    return 0;
}
