#include <stdio.h>
#include <omp.h>

int main(void) {
    #pragma omp parallel
    {
        int n = omp_get_num_threads();
        printf("%d",n);
        // printf("Hello, world. Thread %d says hi.\n", omp_get_thread_num());
    }
    return 0;
}
