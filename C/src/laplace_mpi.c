/**
 * @file laplace_mpi.c
 * @author Dario Zarcone
 * @brief laplace_mpi -- MPI implementation of the Laplace equation solver
 * 
 */

#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#include "2darrays.h"
#include "solvers.h"

int main(int argc, char *argv[]) {
    int rank, size, method;
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

    // MPI init
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /*-- Global domain init --*/
    double (*phi)[Ny] = malloc(sizeof(double[Nx][Ny]));
    double V = 10;
    if (rank == 0){
        init2dArray(Nx, Ny, phi, 0.0);
        // Boundary conditions
        for(i=0;i<Nx;i++){
            phi[i][0] = V;
            //phi[i][Ny-1] = -V;
        }
    }
    /*-- Domain decomposition using MPI scatter --*/
    // 1. Set number of rows to send to each process
    //    last process gets the remaining rows
    int *sendcounts = malloc(sizeof(int)*size);
    int *displs = malloc(sizeof(int)*size);
    for (i=0;i<size;i++){
        sendcounts[i] = (Nx/size)*Ny;
        displs[i] = i*(Nx/size)*Ny;
        if(i==size-1) sendcounts[i] += (Nx%size)*Ny;
    }
    // 2. Set dimensions of local domain, adding ghost rows
    int nx = sendcounts[rank]/Ny;
    nx += (rank==0 || rank==size-1) ? 1 : 2;
    int ny = Ny;
    int ni = (rank==0) ? 0 : 1;
    // 3. Initialize local domain
    double (*local_phi)[ny] = malloc(sizeof(double[nx][ny]));
    init2dArray(nx, ny, local_phi, 0.0);
    // 4. Scatter global domain to local domains
    MPI_Scatterv(phi, sendcounts, displs, MPI_DOUBLE, local_phi[ni], sendcounts[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
    /*-- Solver iterations --*/
    int n_iter = 0;
    double delta = 1.0;
    double local_delta;
    clock_t t1 = clock();
    while(delta>target){
        if(rank>0) {
            MPI_Sendrecv(local_phi[1], ny, MPI_DOUBLE, rank-1, 11,
                         local_phi[0], ny, MPI_DOUBLE, rank-1, 22,
                         MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        if(rank<size-1) {
            MPI_Sendrecv(local_phi[nx-2], ny, MPI_DOUBLE, rank+1, 22,
                         local_phi[nx-1], ny, MPI_DOUBLE, rank+1, 11,
                         MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        local_delta = (*fun_solve)(nx, ny, local_phi);
        n_iter++;
        MPI_Allreduce(&local_delta, &delta, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
    }
    clock_t t2 = clock();
    if (rank == 0){
        printf("%d iterations, %f seconds\n", n_iter, (float)(t2-t1)/CLOCKS_PER_SEC);
    }

    // Gather results and free memory
    MPI_Gatherv(local_phi[ni], sendcounts[rank], MPI_DOUBLE, phi, sendcounts, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    free(local_phi);
    // Save results to file and free memory
    if (rank == 0){
        save2dArray(Nx, Ny, phi, "laplace.dat");
    }
    free(phi);

    MPI_Finalize();
    return 0;
}
