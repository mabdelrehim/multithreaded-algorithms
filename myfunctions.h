//
// Created by mohamed on 17/11/18.
//

#ifndef THREADS_MYFUNCTIONS_H
#define THREADS_MYFUNCTIONS_H

#include <time.h>

/* global variables*/
int** outputElements; // output in case each element is calculated on a different thread

/* This function will calculate the output matrix using multi-threads
 * if threads = 0 then each element of the output matrix will be calculated on a different thread
 * if threads = 1 then each row of the output matrix will be calculated on a different thread
 * important note readMatrixInput() from readInput.h must be called first
 */
void calculateMatrix(int, clock_t *, clock_t*);

/* This function will do merge-sort on an array using multi-threads
 * important note readArrayInput() from readInput.h must be called first
 */
void multiThreadedMergeSort();

/* prints a matrix */
void printMatrix(int**, int, int);

/* prints an array */
void printArray(int*, int);


#endif //THREADS_MYFUNCTIONS_H
