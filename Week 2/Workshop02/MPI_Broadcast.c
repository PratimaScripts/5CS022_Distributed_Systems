#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int rank;

    // Initialize MPI
    MPI_Init(NULL, NULL);

    // Get the rank of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Declare a variable to store the message
    int message = 0;

    // Process 0 (rank 0) broadcasts a message to all other processes
    if (rank == 0) {
        printf("Rank %d is about to start broadcasting\n", rank);
        message = 42; // The value to be broadcasted
    } else {
        printf("Rank %d is about to receive the broadcast\n", rank);
    }

    // MPI_Bcast function is used to broadcast a message from one process to all other processes
    // MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)
    // Parameters:
    //   - buffer: Address of the data to be broadcasted
    //   - count: Number of data elements to be broadcasted
    //   - datatype: Data type of the elements
    //   - root: Rank of the broadcasting process (the root process)
    //   - comm: Communicator (MPI_COMM_WORLD represents all processes)

    MPI_Bcast(&message, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Display messages after the broadcast
    if (rank == 0) {
        printf("Rank %d has finished broadcasting\n", rank);
    } else {
        printf("Rank %d has received the broadcast. Received message: %d\n", rank, message);
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}

// Before Broadcast (Setting the Message):
// In this part of the code, only the process with rank == 0 initializes the message. 
// This ensures that only one process (the root process) sets the value of the message to be broadcasted.

// After Broadcast (Displaying Messages):
// In this part, the condition is used to differentiate between the root process and other processes. 
// The root process prints a message indicating that it has finished broadcasting, 
// while other processes print a message indicating that they have received the broadcast and display the received message.