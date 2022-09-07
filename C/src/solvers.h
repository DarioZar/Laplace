/**
 * solvers -- Solvers for the Laplace and Poisson equations
 * 
 * @file solvers.h
 * @author Dario Zarcone
 * @brief solvers -- Solvers for the Laplace and Poisson equations.
 *                   Implements the Gauss-Seidel and Jacobi solvers.
 * 
 */

#include <stdio.h>

double solve_laplace(size_t x, size_t y, double(*)[y]);
double gs_solve_laplace(size_t x, size_t y, double(*)[y]);