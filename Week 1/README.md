# README

To change directory from wsl to windows file system:

```cmd
cd /mnt/c/

cd /mnt/d/
```

If MPI is not installed, we get following error during the compilation:

![MPI not installed](./Distributed%20Systems%20and%20Cloud%20Computing%202024/Before%20Installation.png)

```cmd
sudo apt-get update
sudo apt-get upgrade
sudo apt install mpich
mpirun --version
mpicc -v
```

[Open MPI v1.2.9 documentation](https://www.open-mpi.org/doc/v1.2/)

[Using MPI with C](https://curc.readthedocs.io/en/latest/programming/MPI-C.html#setup-and-hello-world)

[MPI Blocking vs Non-Blocking](https://stackoverflow.com/questions/10017301/mpi-blocking-vs-non-blocking)
