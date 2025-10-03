#include <stdio.h>
#include <omp.h>
#define N 8

int main() {
    int arr[N] = {1,2,3,4,5,6,7,8};
    int prefix[N];

    // Step 1: Copy input
    for (int i=0;i<N;i++) prefix[i] = arr[i];

    // Step 2: upsweep (reduce phase)
    for(int step = 1; step < N; step *= 2){
        #pragma omp parallel for
        for(int i = step*2-1; i < N; i += step*2){
            prefix[i] += prefix[i-step];
        }
    }

    // Step 3: downsweep (down phase)
    int temp = prefix[N-1];
    prefix[N-1] = 0;
    for(int step = N/2; step >= 1; step /= 2){
        #pragma omp parallel for
        for(int i = step*2-1; i < N; i += step*2){
            int t = prefix[i-step];
            prefix[i-step] = prefix[i];
            prefix[i] += t;
        }
    }

    printf("Prefix Sum:\n");
    for (int i=0;i<N;i++) printf("%d ", prefix[i]);
}
