#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void) {
    int n;
    printf("Enter number of threads: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid number\n");
        return 1;
    }

    printf("\n-- Sequential output (loop for %d iterations) --\n", n);
    for (int i = 0; i < n; ++i) {
        printf("Seq: Hello %d\n", i);
    }

    printf("\n-- Parallel output (using %d thread(s)) --\n", n);
    omp_set_num_threads(n);
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int tn = omp_get_num_threads();
        #pragma omp critical
        {
            printf("Par: Hello from thread %d out of %d\n", id, tn);
        }
    }

    return 0;
}
