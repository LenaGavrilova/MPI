namespace Task4_2 {
    int main(int argc, char* argv[]) {
        int rank, size;
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        int array[12];
        int block_size = 12 / size + 1;

        if (rank == 0) {
            for (int i = 0; i < 12; ++i) {
                array[i] = i;
            }

            for (int proc = 1; proc < size; ++proc) {
                int send_count = (proc < 12 % size) ? block_size : (block_size - 1);
                MPI_Send(array + proc * (block_size - 1), send_count, MPI_INT, proc, 0, MPI_COMM_WORLD);
            }
        }
        else {
      
            int recv_count = (rank < 12 % size) ? block_size : (block_size - 1);
            MPI_Recv(array, recv_count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

      
        printf("Process %d: ", rank);
        int print_count = (rank < 12 % size) ? block_size : (block_size - 1);
        for (int i = 0; i < print_count; ++i) {
            printf("%d ", array[i]);
        }
        printf("\n");

        MPI_Finalize();
        return 0;
    }
}
