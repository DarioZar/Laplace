/**
 * solvers -- Solvers for the Laplace and Poisson equations
 * 
 * @file solvers.c
 * @author Dario Zarcone
 * @brief solvers -- Solvers for the Laplace and Poisson equations.
 *                   Implements the Gauss-Seidel and Jacobi solvers.
 * 
 */

#include <math.h>
#include "solvers.h"

/**
 * @brief Solve the Laplace equation using the Gauss-Seidel method
 * 
 * @param x number of rows
 * @param y number of columns
 * @param array 2D array
 * @return double maximum error
 */
double gs_solve_laplace(size_t x, size_t y, double phi[x][y]){
    int i,j;
    double diff, maxdiff;
    // Save old array
    double phi_0[x][y];
    for(i=0;i<x;i++){
        for(j=0;j<y;j++){
            phi_0[i][j] = phi[i][j];
        }
    }
    // Update points in a gauss-seidel fashion
    for(i=1;i<x-1;i++){
        for(j=1;j<y-1;j++){
                phi[i][j] = 0.25*(phi[i-1][j]+phi[i+1][j]+phi[i][j-1]+phi[i][j+1]);
            }
        }
    // Calculate maximum difference
    maxdiff = 0;
    for(i=1;i<x-1;i++){
        for(j=1;j<y-1;j++){
            diff = fabs(phi[i][j]-phi_0[i][j]);
            if(diff>maxdiff) maxdiff = diff;
        }
    }
    return maxdiff;
}

/**
 * @brief Solve the Laplace equation using the Jacobi method
 * 
 * @param x number of rows
 * @param y number of columns
 * @param array 2D array
 * @return double maximum error
 */
double solve_laplace(size_t x, size_t y, double phi[x][y]){
    int i,j;
    double diff, maxdiff;
    double phi_new[x][y];
    // Update points
    for(i=1;i<x-1;i++){
        for(j=1;j<y-1;j++){
            phi_new[i][j] = 0.25*(phi[i-1][j]+phi[i+1][j]+phi[i][j-1]+phi[i][j+1]);
        }
    }
    // Calculate maximum difference
    maxdiff = 0;
    for(i=1;i<x-1;i++){
        for(j=1;j<y-1;j++){
            diff = fabs(phi_new[i][j]-phi[i][j]);
            if(diff>maxdiff) maxdiff = diff;
            phi[i][j] = phi_new[i][j];
        }
    }
    return maxdiff;
}