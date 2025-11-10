#include <stdio.h>
#include <omp.h>

#define SIZE 5
int buffer[SIZE], count = 0;

int main() {
    #pragma omp parallel sections
    {
        #pragma omp section   // Producer
        {
            for (int i = 1; i <= 10; i++) {
                #pragma omp critical
                {
                    if (count < SIZE) {
                        buffer[count++] = i;
                        printf("Produced: %d\n", i);
                    }
                }
            }
        }

        #pragma omp section   // Consumer
        {
            for (int i = 1; i <= 10; i++) {
                #pragma omp critical
                {
                    if (count > 0) {
                        printf("Consumed: %d\n", buffer[--count]);
                    }
                }
            }
        }
    }
    return 0;
}
