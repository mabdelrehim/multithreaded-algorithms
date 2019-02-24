//
// Created by mohamed on 16/11/18.
//

#ifndef THREADS_READINPUT_H
#define THREADS_READINPUT_H


/* Global variables */
int** matrixA;
int** matrixB;
int* arr;

int rowsA;
int colsA;
int rowsB;
int colsB;
int arrSize;


/* This function reads an input file from the user containing the input matrices and their
 * sizes
 */
void readMatrixInput();

/* This function reads an input file containing the input array and its size*/
void readArrayInput();

#endif //THREADS_READINPUT_H

