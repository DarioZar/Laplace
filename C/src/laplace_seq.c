/**
 * @file laplace_seq.c
 * @author Dario Zarcone
 * @brief laplace_seq -- Sequential implementation of the Laplace equation solver
 * 
 */

#include <stdlib.h>
#include <time.h>

#include "2darrays.h"
#include "solvers.h"

int main(int argc, char *argv[]) {
    int method;
    int Nx, Ny, i;
    double target;

    // Pointer to solver function
    double (*fun_solve)(size_t x, size_t y, double(*)[y]);

    // Command line arguments
    method = atoi(argv[1]);
    fun_solve = (method==0)? solve_laplace : gs_solve_laplace;
    Nx = atoi(argv[2]);
    Ny = atoi(argv[3]);
    target = atof(argv[4]);

    /*-- Global domain init --*/
    double (*phi)[Ny] = malloc(sizeof(double[Nx][Ny]));
    double V = 10;
    init2dArray(Nx, Ny, phi, 0.0);
    // Boundary conditions
    for(i=0;i<Nx;i++){
        phi[i][0] = V;
        //phi[i][Ny-1] = -V;
    }

    /*-- Solver iterations --*/
    int n_iter = 0;
    double delta = 1.0;
    clock_t t1 = clock();
    while(delta>target){
        delta = (*fun_solve)(Nx, Ny, phi);
        n_iter++;
    }
    clock_t t2 = clock();
    printf("%d iterations, %f seconds", n_iter, (float)(t2-t1)/CLOCKS_PER_SEC);

    // Save results
    save2dArray(Nx, Ny, phi, "laplace.dat");

    // Free array
    free(phi);

    return 0;
}
