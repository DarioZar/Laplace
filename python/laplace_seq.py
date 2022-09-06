import sys
import time

from solvers import *
from plot import plot

# Command line arguments
method = sys.argv[1]
Nx, Ny = int(sys.argv[2]), int(sys.argv[3])
target = float(sys.argv[4])
if method == "jacobi_vec":
    fun_solve = solve_laplace_vec
elif method == "jacobi_seq":
    fun_solve = solve_laplace_seq
elif method == "gs_vec":
    fun_solve = gs_solve_laplace_vec
elif method == "gs_seq":
    fun_solve = gs_solve_laplace_seq
else:
    print("Unknown method")
    sys.exit(1)

# Global domain
phi  = np.zeros([Nx,Ny], float)
## Boundary conditions
V = 10
phi[:,0] = V

# Solve
delta=1
niter=0
t1 = time.time()
while delta>target:
    delta = fun_solve(phi)
    niter += 1
t2 = time.time()
print(niter, t2-t1)

# Plot
plot(phi,1,1)
