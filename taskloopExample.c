/*Mpokourakis Iosif 4439*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARRAY_SIZE 1000
void compute_sum_of_squares(int *array, int size, long long *result){
    *result = 0;

    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma ompp taskloop grainsize(10) shared(array, result)
            for (int i = 0; i < size; i++){
                #pragma omp atomic
                *result += array[i] + array[i];
            }
        }
    }
}

int main(){
    int array[ARRAY_SIZE];
    long long result = 0;

    for(int i = 0; i < ARRAY_SIZE; i++){
        array[i] = i + 1;
    }

    double start_time = omp_get_wtime();
    compute_sum_of_squares(array, ARRAY_SIZE, &result);
    double end_time = omp_get_wtime();

    printf("Sum of squares: %lld\n", result);
    printf("Execution time: %f seconds\n", end_time - start_time);

    return 0;
}
