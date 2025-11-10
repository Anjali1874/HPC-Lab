#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int cmp_asc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void reverse_array(int arr[], int n) {
    #pragma omp parallel for
    for (int i = 0; i < n / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }
}

int main() {
    int n = 5;
    int a[] = {1, 3, 5, 2, 4};
    int b[] = {6, 8, 7, 9, 10};
    int min_scalar_product = 0;

    qsort(a, n, sizeof(int), cmp_asc);
    qsort(b, n, sizeof(int), cmp_asc);
    reverse_array(b, n); // Reverse b in parallel

    #pragma omp parallel for reduction(+:min_scalar_product)
    for (int i = 0; i < n; i++) {
        min_scalar_product += a[i] * b[i];
    }

    printf("Minimum Scalar Product = %d\n", min_scalar_product);
    return 0;
}
