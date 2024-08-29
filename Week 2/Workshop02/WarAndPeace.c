#include <ctype.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "WarAndPeace.txt"
#define ALPHABET_SIZE 26
int main(int argc, char** argv) {
  int rank, size;
  MPI_Status status;
  char* buffer = NULL;
  int letter_count[ALPHABET_SIZE] = {0};
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if (size < 1 || size > 100) {
    if (rank == 0) {
        printf("Error: Number of processes must be between 1 and 100 inclusive.\n");
    }
    MPI_Finalize();
    return 1;  // Exit with error code
  }
  if (rank == 0) {
    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
      printf("Error: Unable to open file.\n");
      MPI_Abort(MPI_COMM_WORLD, 1);
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    buffer = (char*)malloc((file_size + 1) * sizeof(char));
    fread(buffer, sizeof(char), file_size, file);
    fclose(file);
    int chunk_size = file_size / size;
    for (int i = 1; i < size; i++) {
      MPI_Send(&chunk_size, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(buffer + i * chunk_size, chunk_size, MPI_CHAR, i, 0,
               MPI_COMM_WORLD);
    }
    for (int i = 0; i < chunk_size; i++) {
      if (isalpha(buffer[i])) {
        letter_count[tolower(buffer[i]) - 'a']++;
      }
    }
    for (int i = 1; i < size; i++) {
      MPI_Recv(letter_count, ALPHABET_SIZE, MPI_INT, i, 0, MPI_COMM_WORLD,
               &status);
      for (int j = 0; j < ALPHABET_SIZE; j++) {
        letter_count[j] += letter_count[j];
      }
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
      printf("Letter %c: %d\n", 'a' + i, letter_count[i]);
    }
    free(buffer);
  } else {
    int chunk_size = 0;
    MPI_Recv(&chunk_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    buffer = (char*)malloc((chunk_size + 1) * sizeof(char));
    MPI_Recv(buffer, chunk_size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
    for (int i = 0; i < chunk_size; i++) {
        if (isalpha(buffer[i])) {
        letter_count[tolower(buffer[i]) - 'a']++;
      }
    }
    MPI_Send(letter_count, ALPHABET_SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
    free(buffer);
  }
  MPI_Finalize();
  return 0;
}