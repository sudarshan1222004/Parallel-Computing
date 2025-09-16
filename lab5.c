#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int* arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = (int*) malloc(n1 * sizeof(int));
    int* R = (int*) malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0; j = 0; k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}


void mergeSortSequential(int* arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSortSequential(arr, l, m);
        mergeSortSequential(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mergeSortParallel(int* arr, int l, int r, int depth) {
    if (l < r) {
        int m = (l + r) / 2;

        if (depth <= 0) {
            mergeSortSequential(arr, l, m);
            mergeSortSequential(arr, m + 1, r);
        } else {
            #pragma omp parallel sections
            {
                #pragma omp section
                mergeSortParallel(arr, l, m, depth - 1);

                #pragma omp section
                mergeSortParallel(arr, m + 1, r, depth - 1);
            }
        }

        merge(arr, l, m, r);
    }
}

void generateArray(int* arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100000;
}

void copyArray(int* src, int* dest, int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n = 100000;  
    printf("Sorting %d elements...\n\n", n);

    int* arr_seq = (int*) malloc(n * sizeof(int));
    int* arr_par = (int*) malloc(n * sizeof(int));

    generateArray(arr_seq, n);
    copyArray(arr_seq, arr_par, n);

    double start_seq = omp_get_wtime();
    mergeSortSequential(arr_seq, 0, n - 1);
    double end_seq = omp_get_wtime();

    double start_par = omp_get_wtime();
    mergeSortParallel(arr_par, 0, n - 1, 4);
    double end_par = omp_get_wtime();

    double time_seq = end_seq - start_seq;
    double time_par = end_par - start_par;
    double diff = time_seq - time_par;
    double speedup = time_seq / time_par;

    printf("Sequential Merge Sort Time: %.6f seconds\n", time_seq);
    printf("Parallel Merge Sort Time:   %.6f seconds\n\n", time_par);
    printf("Difference (Sequential - Parallel): %.6f seconds\n", diff);
    printf("Speedup: %.2fx\n\n", speedup);

    printf("Verification: First 20 elements of the sorted array:\n");
    printArray(arr_seq, 20);  

    free(arr_seq);
    free(arr_par);
    return 0;
}
