%%writefile compute.cu
#include <stdio.h>
#include <cuda_runtime.h>

__global__ void compute(int *d_arr) {
    int tid = threadIdx.x;
    d_arr[tid] = tid * 2;
}

int main() {
    int N = 10;
    int size = N * sizeof(int);
    int h_arr[N];

    int *d_arr;
    cudaMalloc(&d_arr, size);

    compute<<<1, N>>>(d_arr);

    cudaDeviceSynchronize();

    cudaMemcpy(h_arr, d_arr, size, cudaMemcpyDeviceToHost);

    for(int i = 0; i < N; i++)
        printf("h_arr[%d] = %d\n", i, h_arr[i]);

    cudaFree(d_arr);
    return 0;
}


// !nvcc compute.cu -o compute -- compile
// !./compute            -- run