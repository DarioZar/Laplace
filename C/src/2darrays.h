/**
 * 2darrays -- functions for 2D arrays
 * 
 * @file 2darrays.h
 * @author Dario Zarcone
 * @brief 2darrays -- functions to initialize, print and save 2D arrays
 * 
 */

#include <stdio.h>

void init2dArray(size_t x, size_t y, double(*)[y], double);
void print2dArray(size_t x, size_t y, double(*)[y]);
void save2dArray(size_t x, size_t y, double(*)[y], char*);