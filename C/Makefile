CC = gcc
MPICC = mpicc
CC_OPTS = -O3
MKDIR_P = mkdir -p
BDIR = bin
SDIR = src

all: laplace_seq laplace_mpi

laplace_seq: $(SDIR)/laplace_seq.c $(SDIR)/solvers.c $(SDIR)/2darrays.c
	$(MKDIR_P) $(BDIR)
	$(CC) $(CC_OPTS) -o $(BDIR)/laplace_seq $(SDIR)/laplace_seq.c $(SDIR)/solvers.c $(SDIR)/2darrays.c -lm

laplace_mpi: $(SDIR)/laplace_mpi.c $(SDIR)/solvers.c $(SDIR)/2darrays.c
	$(MKDIR_P) $(BDIR)
	$(MPICC) $(CC_OPTS) -o $(BDIR)/laplace_mpi $(SDIR)/laplace_mpi.c $(SDIR)/solvers.c $(SDIR)/2darrays.c -lm

.PHONY: all clean

clean:
	rm -r $(BDIR)
