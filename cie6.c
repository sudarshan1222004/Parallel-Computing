#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int sum = 0;
    int all_sum = 0;

    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get the rank of the current process and total number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Print the rank of each process
    printf("Process rank: %d\n", rank);

    // Using MPI_Reduce to sum ranks at process 0
    MPI_Reduce(&rank, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // At process 0, print the sum
    if (rank == 0) {
        printf("MPI_Reduce result at Process 0: Sum of ranks = %d\n", sum);
    }

    // Using MPI_Allreduce to share the sum of ranks with all processes
    MPI_Allreduce(&rank, &all_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    // Print the result of MPI_Allreduce on all processes
    printf("MPI_Allreduce result at Process %d: Sum of ranks = %d\n", rank, all_sum);

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
