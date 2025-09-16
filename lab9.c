#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, value, sum, prod, max, min;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    value = rank + 1;

    MPI_Reduce(&value, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &prod, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &min, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);

    if (rank == 0)
        printf("Reduce SUM (only root): %d\n", sum);

    printf("Allreduce PROD (rank %d): %d\n", rank, prod);
    printf("Allreduce MAX  (rank %d): %d\n", rank, max);
    printf("Allreduce MIN  (rank %d): %d\n", rank, min);

    MPI_Finalize();
    return 0;
}