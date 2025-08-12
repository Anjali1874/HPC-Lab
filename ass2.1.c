#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main() {
    int n = 5000000; // vector size
    float scalar = 5.0f;
    float *a = (float*)malloc(n * sizeof(float));
    float *b = (float*)malloc(n * sizeof(float));
    if (a == NULL || b == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    // Initialize vector a
    for (int i = 0; i < n; i++)
        a[i] = i * 0.5f;

    double start = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < n; i++)
        b[i] = a[i] + scalar;

    double end = omp_get_wtime();

    printf("Time taken: %f seconds\n", end - start);
    printf("Example result: b[0] = %.2f, b[last] = %.2f\n", b[0], b[n-1]);
    free(a);
    free(b);
    return 0;
}

