#include <stdio.h>
#include <omp.h>

int main() {
    long steps = 100000000;
    double step = 1.0 / (double) steps;
    double sum = 0.0;

    double st1 = omp_get_wtime();
    for (long i = 0; i < steps; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    double st2 = omp_get_wtime();

    printf("serial time neeeded : %f\n", st2 - st1);   
    sum = 0.0;

    double start = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for (long i = 0; i < steps; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    double pi = step * sum;
    double end = omp_get_wtime();

    printf("Pi = %.15f\n", pi);
    printf("Time taken: %f seconds\n", end - start);
    return 0;
}
