#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv){
    int i, c;
    int size, rank;
    int nstart = 1, nfinish = 1000;
    MPI_Init(NULL, NULL); // If you dont' want any command-line argument simply pass null
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Prime numbers between %d and %d are: \n", nstart, nfinish);
    // syntax for(initialize, condition, increment)
    for(i = nstart; i <= nfinish; i++){
        for (c = 2; c <= i; c++){
            if (i % c == 0){
                break;
            }
            if (c = i){
                printf("%s: %d\n", argv[0], i);
            }
        }
    }
    MPI_Finalize();
    return 0;
}
