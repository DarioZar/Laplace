# Laplace equation solver

Solve laplace equation using Jacobi/Gauss-Seidel method.

## C
The C version contains a sequential and a parallel (using `MPI`) version.

```
C
- bin: build directory
- src
    - 2darrays: functions for 2d array handling
    - solvers: implementations of Jacobi and Gauss-Seidel solvers
    - laplace_seq.c: sequential version
    - laplace_mpi.c: parallel version
```

### How to use
0. Requirements: MPI (for the parallel version)
1. Compile using the Makefile
    ```bash
    cd C
    make all
    ```
2. Run the sequential version using
    ```bash
    ./bin/laplace_seq METHOD NX NY TOLERANCE
    ```
    - `METHOD`: use Jacobi solver if 0, Gauss-Seidel if 1
    - `NX` `NY`: number of points in the grid
    - `TOLERANCE`: target max difference for convergence

    Example:
    ```bash
    ./bin/laplace_seq 0 128 128 1e-6
    ```
2. Run the parallel version using
    ```bash
    mpirun -np NUMPROC ./bin/laplace_mpi METHOD NX NY TOLERANCE
    ```
    Command arguments are as above, plus
    - `NUMPROC`: number of processors

    Example:
    ```bash
    mpirun -np 4 ./bin/laplace_mpi 0 128 128 1e-6
    ```
3. The command returns number of iterations and time needed for convergence. The data is in `laplace.dat` and can be plotted using (requires numpy, matplotlib)
    ```bash
    python ../python/plot.py laplace.dat
    ```

## Python
The python version contains a sequential and a parallel version (using `mpi4py`).

### How to use
0. Install all requirements (numpy, mpi4py, matplotlib, numba)
    ```bash
    cd python
    pip install -r requirements.txt
    ```
1. Run the sequential version using
    ```bash
    python laplace_seq.py METHOD NX NY TOLERANCE
    ```
    - `METHOD`
        - `jacobi_seq`: sequential version of Jacobi solver
        - `jacobi_vec`: vectorized version of Jacobi solver using numpy functions
        - `gs_seq`: sequential version of Gauss-Seidel solver
        - `gs_vec`: semi-vectorized version of Gauss-Seidel solver
    - `NX` `NY`: number of points in the grid
    - `TOLERANCE`: target max difference for convergence

    Example:
    ```bash
    python laplace_seq.py jacobi_vec 128 128 1e-6
    ```
2. Run the parallel version using
    ```bash
    mpirun -np NUMPROC python laplace_mpi.py METHOD NX NY TOLERANCE
    ```
    Command arguments are as above, plus
    - `NUMPROC`: number of processors

    Example:
    ```bash
    mpirun -np 4 python laplace_mpi.py jacobi_vec 128 128 1e-6
    ```
2. Run the numba version using
    ```bash
    python laplace_numba.py NX NY TOLERANCE
    ```

    Example:
    ```bash
    python laplace_numba.py 128 128 1e-6
    ```
3. The command returns number of iterations, time needed for convergence and plots the solution.
