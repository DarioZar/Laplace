import numpy as np

def solve_laplace_vec(phi):
    # Calc the new values of phi excluding the boundary
    phi1 = (phi[:-2,1:-1] + phi[2:,1:-1] +\
            phi[1:-1,:-2] + phi[1:-1,2:] )/4
    # Calc the max difference between the old and new values
    delta = np.abs(phi1-phi[1:-1,1:-1]).max()
    # Update the values of phi
    phi[1:-1,1:-1] = phi1
    # Return the max difference
    return delta

def solve_laplace_seq(phi):
    phi1 = np.empty(phi.shape)
    delta = 0
    # Calc the new values of phi excluding the boundary
    for i in range(1,phi.shape[0]-1):
        for j in range(1,phi.shape[1]-1):
            phi1[i,j] = (phi[i-1,j] + phi[i+1,j] +\
                        phi[i,j-1] + phi[i,j+1])/4
    # Calc the max difference between the old and new values
    # Update the values of phi
    for i in range(1, phi.shape[0]-1):
        for j in range(1, phi.shape[1]-1):
            diff = np.abs(phi1[i,j]-phi[i,j])
            if (diff>delta):
                delta = diff
            phi[i,j] = phi1[i,j]
    # Return the max difference
    return delta

def gs_solve_laplace_vec(phi):
    # Copy the array for max difference calculation
    phi0 = phi.copy()
    # Calc the new values of phi excluding the boundary
    # in a checkerboard pattern
    phi[1:-1:2,1:-1:2] = (phi[:-2:2,1:-1:2] + phi[2::2,1:-1:2] +\
                          phi[1:-1:2,:-2:2] + phi[1:-1:2,2::2])/4
    phi[2:-1:2,2:-1:2] = (phi[1:-2:2,2:-1:2] + phi[3::2,2:-1:2] +\
                          phi[2:-1:2,1:-2:2] + phi[2:-1:2,3::2])/4
    phi[1:-1:2,2:-1:2] = (phi[:-2:2,2:-1:2] + phi[2::2,2:-1:2] +\
                          phi[1:-1:2,1:-2:2] + phi[1:-1:2,3::2])/4
    phi[2:-1:2,1:-1:2] = (phi[1:-2:2,1:-1:2] + phi[3::2,1:-1:2] +\
                          phi[2:-1:2,:-2:2] + phi[2:-1:2,2::2])/4
    # Calc the max difference between the old and new values
    delta = np.abs(phi-phi0).max()
    # Return the max difference
    return delta

def gs_solve_laplace_seq(phi):
    phi0 = phi.copy()
    delta = 0
    # Calc the new values of phi excluding the boundary
    for i in range(1,phi.shape[0]-1):
        for j in range(1,phi.shape[1]-1):
            phi[i,j] = (phi[i-1,j] + phi[i+1,j] +\
                        phi[i,j-1] + phi[i,j+1])/4
    # Calc the max difference between the old and new values
    for i in range(1, phi.shape[0]-1):
        for j in range(1, phi.shape[1]-1):
            diff = np.abs(phi[i,j]-phi0[i,j])
            if (diff>delta):
                delta = diff
    # Return the max difference
    return delta
