# Links

[MPI Scatter and Gather](https://mpitutorial.com/tutorials/mpi-scatter-gather-and-allgather/)

MPI_Scatter(
    void*send_data,
    int send_count,
    MPI_Datatype send_datatype,
    void* recv_data,
    int recv_count,
    MPI_Datatype recv_datatype,
    int root,
    MPI_Comm communicator)

An MPI_Scatter call sends data from one rank to all other ranks.

![MPI_Scatter](MPI_Scatter.svg)

MPI_Scatter is blocking and introduces collective synchronization into the program.

After the call, all ranks in the communicator have the one value sent from the root rank, ordered by rank number.

MPI_Gather(
    void*send_data,
    int send_count,
    MPI_Datatype send_datatype,
    void* recv_data,
    int recv_count,
    MPI_Datatype recv_datatype,
    int root,
    MPI_Comm communicator)

An MPI_Gather call sends data from all ranks to a single rank. It is the inverse operation of MPI_Scatter.

![MPI_Gather](MPI_Gather.svg)

MPI_Gather is blocking and introduces collective synchronization into the program.

After the call, the root rank has one value from each other rank in the communicator, ordered by rank number.

<https://enccs.github.io/intermediate-mpi/collective-communication-pt1/>
