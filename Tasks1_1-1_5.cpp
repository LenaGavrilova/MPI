#include <mpi.h>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <string>

namespace Task1_1 {
    int main(int argc, char** argv)
    {
        int numtasks, rank;
        
        MPI_Init(&argc, &argv);
        
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

        printf(" Hello, World!");

        MPI_Finalize();

        return 0;
    }

    namespace Task1_2 {
        int main(int argc, char** argv)
        {
            int numtasks, rank;

            MPI_Init(&argc, &argv);

            MPI_Comm_rank(MPI_COMM_WORLD, &rank);

            MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

            printf("Number of process: %d, size: %d\n", rank, num);

            MPI_Finalize();

            return 0;
        }

}

namespace Task1_3 {
    int main(int argc, char** argv)
    {
        int rank;
        int const num = 10;
        int a[num];

        MPI_Status status;

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        if (rank == 0) {

            for (int i = 0; i < num; i++) {

                a[i] = rand();

            }
            MPI_Send(a, num, MPI_INT, 1, 1, MPI_COMM_WORLD);
        }

        if (rank == 1) {
            MPI_Recv(a, num, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
            for (int i = 0; i < num; i++) {
                printf("%d ", a[i]);
            }
        }
        MPI_Finalize();

        return 0;
    }
}

namespace Task1_4 {
    int main(int argc, char** argv)
    {
        int rank;
        int count;
        int const num = 10;
        int a[num];

        MPI_Status status;

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        if (rank == 1) {

            for (int i = 0; i < num; i++) {

                a[i] = rand();

            }
            MPI_Send(a, num, MPI_INT, 0, 1, MPI_COMM_WORLD);
            MPI_Send(a, num, MPI_INT, 2, 1, MPI_COMM_WORLD);
            MPI_Send(a, num, MPI_INT, 3, 1, MPI_COMM_WORLD);
        }
        else {
            MPI_Probe(1, 1, MPI_COMM_WORLD, &status);
            MPI_Get_count(&status, MPI_INT, &count);
            MPI_Recv(&a, count, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);

            for (int i = 0; i < num; i++) {
                printf("%d ", a[i]);
            }

        }
        MPI_Finalize();

        return 0;
    }
}
namespace Task1_5
int main(int argc, char** argv) {
    int rank, numtasks;
    int number;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    number = rank * 10;

    if (rank == 0) {
        int* received_numbers = (int*)malloc(numtasks * sizeof(int));

        MPI_Status status;

        for (int i = 1; i < numtasks; i++) {
            MPI_Recv(&received_numbers[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
        }

        for (int i = 1; i < numtasks; i++) {
            printf("Received number from process %d: %d\n", i, received_numbers[i]);
        }

        free(received_numbers);
    }
    else {

        MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
