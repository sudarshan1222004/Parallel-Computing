#include <stdio.h>
#include <omp.h>
#include <math.h>

int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i <= sqrt(num); i++)
        if (num % i == 0) return 0;
    return 1;
}

int main() {
    int n = 20, i, count_serial = 0, count_parallel = 0;
    double start, end, serial_time, parallel_time;

    start = omp_get_wtime();
    for (i = 1; i <= n; i++)
        if (is_prime(i)) count_serial++;
    end = omp_get_wtime();
    serial_time = end - start;

    start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic) reduction(+:count_parallel)
    for (i = 1; i <= n; i++)
        if (is_prime(i)) count_parallel++;
    end = omp_get_wtime();
    parallel_time = end - start;

    printf("Serial Count of primes = %d\n", count_serial);
    printf("Parallel Count of primes = %d\n", count_parallel);
    printf("Execution time (serial): %f seconds\n", serial_time);
    printf("Execution time (parallel): %f seconds\n", parallel_time);
    return 0;
}
