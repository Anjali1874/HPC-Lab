#include <stdio.h>
#include <omp.h>
#define N 200

void run_static(int chunk) {
    double A[N], B[N];
    for(int i=0;i<N;i++) { A[i] = i; }
    double start = omp_get_wtime();
    #pragma omp parallel for schedule(static, chunk)
    for(int i=0;i<N;i++) {
        B[i] = A[i] + 5;
    }
    double end = omp_get_wtime();
    printf("STATIC chunk=%d Time=%f sec\n", chunk, end-start);
}

void run_dynamic(int chunk) {
    double A[N], B[N];
    for(int i=0;i<N;i++) { A[i] = i; }
    double start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic, chunk)
    for(int i=0;i<N;i++) {
        B[i] = A[i] + 5;
    }
    double end = omp_get_wtime();
    printf("DYNAMIC chunk=%d Time=%f sec\n", chunk, end-start);
}

void run_nowait() {
    double A[N], B[N], C[N];
    for(int i=0;i<N;i++) { A[i] = i; }
    #pragma omp parallel
    {
        #pragma omp for nowait
        for(int i=0;i<N;i++) { B[i] = A[i] + 5; }

        #pragma omp for
        for(int i=0;i<N;i++) { C[i] = A[i] * 2; }
    }
    printf("nowait clause demo done.\n");
}

int main() {
    int chunks[] = {1, 5, 10, 50, 100};
    for(int i=0;i<5;i++) run_static(chunks[i]);
    printf("\n");
    for(int i=0;i<5;i++) run_dynamic(chunks[i]);
    printf("\n");
    run_nowait();
    return 0;
}
