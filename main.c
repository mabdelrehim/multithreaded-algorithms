
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include "readInput.h"
#include "myfunctions.h"
#include <semaphore.h>



int main() {

    /* driver code for multithreaded matrix multiplication */

    clock_t start, end;  // start and end times
    double cpu_time_used;

    FILE* fout = fopen("matrix-output.txt", "w");

    readMatrixInput();
    printf("MULTI-THREADED MATRIX MULTIPLICATION\n");
    printf("MATRIX A: \n");
    printMatrix(matrixA, rowsA, colsA);
    printf("\n");
    printf("MATRIX B: \n");
    printMatrix(matrixB, rowsB, colsB);
    printf("\n");
    printf("OUTPUT WHEN EACH ELEMENT IS CALCULATED ON A DIFFERENT THREAD: \n");
    calculateMatrix(0, &start, &end);

    // write the output to the output file
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            fprintf(fout, "%d\t\t", outputElements[i][j]);
        }
        fprintf(fout, "\n");
    }
    cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC; //time taken in seconds

    // write elapsed time of procedure1 to output file
    fprintf(fout, "END1\t\t[%lf seconds]\n\n", cpu_time_used);

    printf("TIME USED: %lf seconds\n", cpu_time_used);
    free(outputElements); //free allocated space after printing the result to reuse

    printf("\n");
    printf("OUTPUT WHEN EACH ROW IS CALCULATED ON A DIFFERENT THREAD: \n");
    calculateMatrix(1, &start, &end);

    // write the output to the output file
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            fprintf(fout, "%d\t\t", outputElements[i][j]);
        }
        fprintf(fout, "\n");
    }
    cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC; //time taken in seconds

    // write elapsed time of procedure2 to output file
    fprintf(fout, "END2\t\t[%lf seconds]\n\n", cpu_time_used);

    printf("TIME USED: %lf seconds\n", cpu_time_used);
    printf("==================================================================\n");


    /* driver code for multithreaded merge sort */
    printf("MULTI-THREADED MERGE SORT\n");
    readArrayInput();
    printf("ORIGINAL ARRAY:\t\t");
    printArray(arr, arrSize);
    //printf("\n%d", arrSize);
    printf("\n");
    multiThreadedMergeSort();
    printf("SORTED ARRAY: \t\t");
    printArray(arr, arrSize);



    return 0;
}

