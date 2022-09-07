import sys
import time

import numpy as np
import numba as nb

from plot import plot

# nb.njit is a decorator that compiles the function to machine code
@nb.njit(fastmath=True)
def numbaloop(phi, target):
    delta=1
    niter=0
    while delta>target:
        phi1 = (phi[:-2,1:-1] + phi[2:,1:-1] +\
                phi[1:-1,:-2] + phi[1:-1,2:] )/4
        delta = np.abs(phi1-phi[1:-1,1:-1]).max()
        phi[1:-1,1:-1] = phi1
        niter+=1
    return niter


# Command line arguments
Nx, Ny = int(sys.argv[1]), int(sys.argv[2])
target = float(sys.argv[3])

# Global domain
phi  = np.zeros([Nx,Ny], float)

# Compile numba
numbaloop(phi, target)

# Boundary conditions
V = 10
phi[:,0] = V

# Solve
t1 = time.time()
niter=numbaloop(phi, target)
t2 = time.time()
print(niter, t2-t1)

# Plot
plot(phi)


