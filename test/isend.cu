#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    float *hostSend = new float[100];
    float *hostRecv = new float[100];
    float *deviceSend, *deviceRecv;
    cudaMalloc(&deviceSend, sizeof(float) * 100);
    cudaMalloc(&deviceRecv, sizeof(float) * 100);

    MPI_Request reqSend, reqRecv;
    MPI_Isend(hostSend, 100, MPI_FLOAT, rank, 0, MPI_COMM_WORLD, &reqSend);
    MPI_Irecv(hostRecv, 100, MPI_FLOAT, rank, 0, MPI_COMM_WORLD, &reqRecv);
    MPI_Wait(&reqSend, MPI_STATUS_IGNORE);
    MPI_Wait(&reqRecv, MPI_STATUS_IGNORE);

    MPI_Isend(deviceSend, 100, MPI_FLOAT, rank, 0, MPI_COMM_WORLD, &reqSend);
    MPI_Irecv(deviceRecv, 100, MPI_FLOAT, rank, 0, MPI_COMM_WORLD, &reqRecv);
    MPI_Wait(&reqSend, MPI_STATUS_IGNORE);
    MPI_Wait(&reqRecv, MPI_STATUS_IGNORE);


    MPI_Finalize();

    delete[] hostSend;
    delete[] hostRecv;
    cudaFree(deviceSend);
    cudaFree(deviceRecv);

    return 0;
}