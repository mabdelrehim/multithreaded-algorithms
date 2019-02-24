//
// Created by mohamed on 17/11/18.
//

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "myfunctions.h"
#include "readInput.h"

void* elementThread(void* param);
void* rowThread(void* param);
void* mergeSortThread(void* param);
void merge(int first_index, int last_index);

/* A struct to hold the row-col parameter for each thread */
struct elementThread {
    int row;
    int col;
};

/* A struct to hold the start, middle, and end parameters for each thread */
struct mergeParam {
    int start;
    int end;
};

void multiThreadedMergeSort() {


    struct mergeParam* param = malloc(sizeof(struct mergeParam));
    param->start = 0;
    param->end = arrSize - 1;

    // create a thread to do the merge sort
    pthread_t sortThread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&sortThread, &attr, mergeSortThread, param);

    // wait for the thread to finish
    pthread_join(sortThread, NULL);

}

void calculateMatrix(int threads, clock_t* start, clock_t* end) {

    // allocate space for the output matrix
    outputElements = malloc(rowsA * sizeof(int*));

    for (int i = 0; i < rowsA; i++) {
        outputElements[i] = malloc(colsB * sizeof(int));
    }

    // calculate each element of the output on a different thread if threads = 0 calculate each row on a thread
    // otherwise
    if (threads == 0) {
        pthread_t threadsArr[rowsA][colsB]; // 2d arr of threads to calculate each element of the output
        *start = clock();
        for (int i = 0; i < rowsA; i++) {
            for (int j = 0; j < colsB; j++) {

                // create the thread that will calculate the current element and pass the row-col parameter
                struct elementThread* index = malloc(sizeof(struct elementThread));
                index->row = i;
                index->col = j;
                pthread_attr_t attr;
                pthread_attr_init(&attr);
                pthread_create(&threadsArr[i][j], &attr, elementThread, index);
                //pthread_join(threadsArr[i][j], NULL);
            }
        }

        for (int k = 0; k < rowsA; k++) {
            for (int i = 0; i < colsB; i++) {
                pthread_join(threadsArr[k][i], NULL);
            }
        }
        *end = clock();



    } else {
        pthread_t threadsArr[rowsA];
        *start = clock();
        for (int i = 0; i < rowsA; i++) {
            // create the thread that will calculate the current element and pass the row-col parameter
            struct elementThread* index = malloc(sizeof(struct elementThread));
            index->row = i;
            index->col = -1;  //the thread will not use that parameter
            //pthread_t pthread;
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            pthread_create(&threadsArr[i], &attr, rowThread, index);
            //pthread_join(threadsArr[i], NULL);
        }
        for (int j = 0; j < rowsA; j++) {
            pthread_join(threadsArr[j], NULL);
        }
        *end = clock();
    }

    printMatrix(outputElements, rowsA, colsB);

}

void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void printArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
}

void* rowThread(void* param) {
    struct elementThread* index = param;
    int sum = 0;
    int commonDimension = colsA;

    for (int i = 0; i < colsB; i++) {
        for (int j = 0; j < commonDimension; j++) {
            sum += matrixA[index->row][j] * matrixB[j][i];
        }
        outputElements[index->row][i] = sum;
        sum = 0;
    }
    pthread_exit(0);
}

void* elementThread(void* param) {

    struct elementThread* index = param;
    int sum = 0;
    int commonDimension = colsA;

    for (int i = 0; i < commonDimension; i++) {
        sum += matrixA[index->row][i] * matrixB[i][index->col];
    }

    outputElements[index->row][index->col] = sum;
    pthread_exit(0);

}

void* mergeSortThread(void* param) {

    struct mergeParam* parameters = param;
    if(parameters->start >= parameters->end)
        pthread_exit(0);

    else if((parameters->end) > (parameters->start)) {

        // merge-sort left half on a thread
        struct mergeParam* parametersLeft = malloc(sizeof(struct mergeParam));
        parametersLeft->start = parameters->start;
        parametersLeft->end = ((parameters->start) + (parameters->end)) / 2;

        //printf("left start:%d left end:%d\n", parametersLeft->start, parametersLeft->end);
        pthread_t leftThread;
        pthread_attr_t attrLeft;
        pthread_attr_init(&attrLeft);
        pthread_create(&leftThread, &attrLeft, mergeSortThread, parametersLeft);



        // merge-sort left half on another thread
        struct mergeParam* parametersRight = malloc(sizeof(struct mergeParam));
        parametersRight->start = (((parameters->end) + (parameters->start)) / 2) + 1;
        parametersRight->end = parameters->end;
        //printf("right start:%d right end:%d\n", parametersRight->start, parametersRight->end);
        //printf("parameter start:%d parameter end:%d\n", parameters->start, parameters->end);
        pthread_t rightThread;
        pthread_attr_t attrRight;
        pthread_attr_init(&attrRight);
        pthread_create(&rightThread, &attrRight, mergeSortThread, parametersRight);



        // wait for the two threads to finish sorting
        pthread_join(leftThread, NULL);
        pthread_join(rightThread, NULL);

        // merge the two sorted halves
        merge(parameters->start, parameters->end);

    }

    pthread_exit(0);

}

void merge(int l, int r) {

    int m = l+(r-l)/2;

    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

}
