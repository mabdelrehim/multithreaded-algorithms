//
// Created by mohamed on 16/11/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "readInput.h"


void readMatrixInput() {


    FILE* f = fopen("matrix-input.txt", "r");

    if (f == NULL) {
        printf("error: cannot read from file");
    } else {

        // get the number of rows and columns in the first 2D array and allocate space accordingly
        fscanf(f, "%d %d\n", &rowsA, &colsA);
        matrixA = malloc(rowsA * sizeof(int*));
        for (int i = 0; i < rowsA; i++) {
            matrixA[i] = malloc(colsA * sizeof(int));
        }

        // fill the first 2D array
        for (int i = 0; i < rowsA; i++) {
            for (int j = 0; j < colsA; j++) {
                fscanf(f, "%d", &matrixA[i][j]);
                getc(f);
            }
        }

        // get the number of rows and columns in the second 2D array and allocate space accordingly
        fscanf(f, "%d %d\n", &rowsB, &colsB);
        matrixB = malloc(rowsB * sizeof(int*));
        for (int i = 0; i < rowsB; i++) {
            matrixB[i] = malloc(colsB * sizeof(int));
        }

        // fill the second 2D array
        for (int i = 0; i < rowsB; i++) {
            for (int j = 0; j < colsB; j++) {
                fscanf(f, "%d", &matrixB[i][j]);
                getc(f);
            }
        }

    }
}

void readArrayInput() {

    FILE* f = fopen("array-input.txt", "r");
    fscanf(f, "%d\n", &arrSize);
    arr = malloc(arrSize * sizeof(int));
    for (int i = 0; i < arrSize; i++) {
        fscanf(f, "%d", &arr[i]);
        getc(f);
    }

}
