/**
 * 2darrays -- functions for 2D arrays
 * 
 * @file 2darrays.c
 * @author Dario Zarcone
 * @brief 2darrays -- functions to initialize, print and save 2D arrays
 * 
 */

#include "2darrays.h"

/**
 * @brief Initialize a 2D array with a given value
 * 
 * @param x number of rows
 * @param y number of columns
 * @param array 2D array
 * @param value value to initialize the array with
 */
void init2dArray(size_t x, size_t y, double array[x][y], double value){
    for (size_t i = 0; i < x; i++) {
        for (size_t j = 0; j < y; j++) {
            array[i][j] = value;
        }
    }
}

/**
 * @brief Print a 2D array
 * 
 * @param x number of rows
 * @param y number of columns
 * @param array 2D array
 */
void print2dArray(size_t x, size_t y, double array[x][y]) {
    for (size_t i = 0; i < x; i++) {
        for (size_t j = 0; j < y; j++) {
            printf("%f ", array[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Save a 2D array to a file
 * 
 * @param x number of rows
 * @param y number of columns
 * @param array 2D array
 * @param filename name of the file to save the array to
 */
void save2dArray(size_t x, size_t y, double array[x][y], char *filename) {
    FILE *fp;
    fp = fopen(filename, "w");
    for (size_t i = 0; i < x; i++) {
        for (size_t j = 0; j < y; j++) {
            fprintf(fp, "%f ", array[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}