#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, data[4] = {10, 20, 30, 40}, recv;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Scatter(data, 1, MPI_INT, &recv, 1, MPI_INT, 0, MPI_COMM_WORLD);
    recv += 1;
    MPI_Gather(&recv, 1, MPI_INT, data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Gathered data: ");
        for (int i = 0; i < size; i++) printf("%d ", data[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}