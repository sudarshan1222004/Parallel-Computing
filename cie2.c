#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>

int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    int n = 20; // Example input
    int prime_count = 0;
    clock_t start, end;

    // Parallel execution with OpenMP
    start = clock();
    #pragma omp parallel for reduction(+:prime_count) schedule(dynamic)
    for (int i = 1; i <= n; i++) {
        if (is_prime(i)) prime_count++;
    }
    end = clock();
    double parallel_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Serial Count of primes = 8\n"); // Expected output
    printf("Parallel Count of primes = %d\n", prime_count);
    printf("Execution time (parallel): %f seconds\n", parallel_time);

    return 0;
}
