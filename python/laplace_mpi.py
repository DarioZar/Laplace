import sys
from mpi4py import MPI
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

# MPI setup
comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

# Global domain
phi  = np.zeros([Nx,Ny], float)
## Boundary conditions
V = 10
phi[:,0] = V
# Domain decomposition
## 1. Set number of rows to send to each process
##    last process gets the remaining rows
nx = phi.shape[0] // size
ni = nx * rank
nf = nx * (rank + 1)
if rank == size-1:
    nx += phi.shape[0] % size
    nf += phi.shape[0] % size
## 2. Setup ghost rows for local domain (padding)
pad = ((0,1) if rank==0 else (1,0) if rank==size-1 else (1,1),(0,0))
## 3. Setup local domain
local_phi = np.pad(phi[ni:nf,:], pad, 'constant', constant_values=((0,0),(0,0)))

# Solve
delta=1
niter=0
t1 = time.time()
while delta>target:
    if rank>0:
        comm.Sendrecv(sendbuf=local_phi[1,:], dest=rank-1, sendtag=11,
                      recvbuf=local_phi[0,:], source=rank-1, recvtag=22)
    if rank<size-1:
        comm.Sendrecv(sendbuf=local_phi[-2,:], dest=rank+1, sendtag=22,
                      recvbuf=local_phi[-1,:], source=rank+1, recvtag=11)
    delta = fun_solve(local_phi)
    delta = comm.allreduce(delta, op=MPI.MAX)
    niter += 1
t2 = time.time()
if rank==0:
    print(niter, t2-t1)

# Gather results to root process
if rank == 0:
    phi[ni:nf,:] = local_phi[:-1,:]
    for r in range(1,size-1):
        comm.Recv(phi[nx*r:nx*(r+1),:], source=r)
    comm.Recv(phi[nx*(size-1):,:], source=size-1)
elif rank == size-1:
    comm.Send(local_phi[1:,:], dest=0)
else:
    comm.Send(local_phi[1:-1,:], dest=0)

if rank == 0:
    plot(phi,1,1)