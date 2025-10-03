#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrix_add(int n, int threads) {
    double **A, **B, **C;
    A = malloc(n * sizeof(double*));
    B = malloc(n * sizeof(double*));
    C = malloc(n * sizeof(double*));
    for(int i = 0; i < n; i++) {
        A[i] = malloc(n * sizeof(double));
        B[i] = malloc(n * sizeof(double));
        C[i] = malloc(n * sizeof(double));
        for(int j = 0; j < n; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }

    omp_set_num_threads(threads);
    double start = omp_get_wtime();

    #pragma omp parallel for collapse(2)
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];

    double end = omp_get_wtime();

    printf("Size=%d Threads=%d Time=%f sec\n", n, threads, end - start);

    for(int i = 0; i < n; i++) {
        free(A[i]); free(B[i]); free(C[i]);
    }
    free(A); free(B); free(C);
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int threads[] = {1, 2, 4, 8};
    for(int s = 0; s < 5; s++) {
        for(int t = 0; t < 4; t++) {
            matrix_add(sizes[s], threads[t]);
        }
        printf("\n");
    }
    return 0;
}
