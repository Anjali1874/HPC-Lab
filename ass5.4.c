#include <stdio.h>
#include <omp.h>
#define N 8

int main() {
    int arr[N] = {1,2,3,4,5,6,7,8};
    int prefix[N];

    // Step 1: Copy input
    for (int i=0;i<N;i++) prefix[i] = arr[i];

    // Step 2: Parallel scan using doubling
    for (int step=1; step<N; step*=2) {
        #pragma omp parallel for
        for (int i=step; i<N; i++) {
            int temp = prefix[i-step] + prefix[i];
            #pragma omp critical
            prefix[i] = temp;
        }
    }

    printf("Prefix Sum:\n");
    for (int i=0;i<N;i++) printf("%d ", prefix[i]);
}
