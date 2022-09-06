# Plot the data from the C program
import sys
import numpy as np
import matplotlib.pyplot as plt

def plot(phi, Lx, Ly):
    Nx, Ny = phi.shape
    dx, dy = Lx/Nx, Ly/Ny
    fig, ax = plt.subplots(1,1,subplot_kw={'projection':'3d'})
    x,y = np.meshgrid(dx*np.array(range(Nx)), dy*np.array(range(Ny)))
    r,c = int (np.ceil(0.05/dx)), int (np.ceil(0.05/dy))
    p = ax.plot_surface(x,y,phi,cmap="coolwarm", linewidth=0, rstride=r, cstride=c)
    fig.colorbar(p)
    plt.show()

if __name__ == "__main__":
    # Read the data from the file in command line
    phi = np.loadtxt(sys.argv[1])
    # Plot the data in a 3D plot
    plot(phi, 1, 1)
