namespace Task2_1 {
    int main(int argc, char** argv)
    {
        int rank;

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Status status;
        int count;
        int a = 10;
        int b = 12;
        const int SIZE = 15;
        const int PART = 5;

        if (rank == 0) {
            int x[SIZE];
            int y[SIZE];
            int z[SIZE];

            for (int i = 0; i < SIZE; ++i) {
                x[i] = rand() % 100 + 1;
                y[i] = rand() % 100 + 1;
            }

            printf("x: ");
            for (int i = 0; i < SIZE; i++) {
                printf("%d ", x[i]);
            }
            printf("\ny: ");
            for (int i = 0; i < SIZE; i++) {
                printf("%d ", y[i]);
            }
            printf("\n");

            int n = 1;
            for (int i = 0; i < SIZE; i += PART, n++) {
                MPI_Send(&x[i], PART, MPI_INT, n, 10, MPI_COMM_WORLD);
                MPI_Send(&y[i], PART, MPI_INT, n, 10, MPI_COMM_WORLD);
            }

            n = 1;
            for (int i = 0; i < SIZE; i += PART, n++) {
                MPI_Recv(&z[i], PART, MPI_INT, n, 10, MPI_COMM_WORLD, &status);
            }

            printf("z: ");
            for (int i = 0; i < SIZE; i++) {
                printf("%d ", z[i]);
            }
        }
        else {
            MPI_Probe(0, 10, MPI_COMM_WORLD, &status);
            MPI_Get_count(&status, MPI_INT, &count);
            int x[PART];
            int y[PART];
            int z[PART];

            MPI_Recv(&x[0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
            MPI_Recv(&y[0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);

            for (int i = 0; i < count; ++i) {
                z[i] = a * x[i] + b * y[i];
            }
            MPI_Send(&z, count, MPI_INT, 0, 10, MPI_COMM_WORLD);
        }

        MPI_Finalize();
    }
}


namespace Task2_2

int main(int argc, char** argv)
{
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    int count;

    const int SIZE = 10;
    const int PART = 5;

    if (rank == 0) {
        int matrix1[SIZE][SIZE];
        int vector[SIZE];
        int result[SIZE];

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; j++) {
                matrix1[i][j] = i*SIZE+j;
               
            }
        }
        for (int i = 0; i < SIZE; ++i) {
                vector[i] = i;
               
            }
        printf("matrix: \n");
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", matrix1[i][j]);
            }
            printf("\n");
        }
        printf("\nvector: \n");
        for (int i = 0; i < SIZE; ++i) {
                printf("%d ", vector[i]);
            printf("\n");
        }
        printf("\n\n");

        int n = 1;
        for (int i = 0; i < SIZE; i++, n++) {
                MPI_Send(&matrix1[i][0], PART, MPI_INT, n, 10, MPI_COMM_WORLD);
                MPI_Send(&vector[0][0], SIZE, MPI_INT, n, 10, MPI_COMM_WORLD);
        }

        n = 1;
        for (int i = 0; i < SIZE; i++,n++) {
                MPI_Recv(&result[i], PART, MPI_INT, n, 10, MPI_COMM_WORLD, &status);
        }

        printf("Resulting matrix: \n");
        for (int i = 0; i < SIZE; i++) {  
            std::cout << "result[" << i << "] = " << result[i] << std::endl;
        }
    }
    else {
        MPI_Probe(0, 10, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        int matrix1[PART];
        int vector[PART];
        int result[PART];

        MPI_Recv(&matrix1[0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        MPI_Recv(&vector[0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);

        for (int i = 0; i < count; ++i) {
            result[i] += matrix1[i] * matrix2[i];
        }
        MPI_Send(&result, count, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
}
/*

namespace Task2_3

int main(int argc, char** argv)
{
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    int count;

    const int SIZE = 10;
    const int PART = 5;

    if (rank == 0) {
        int matrix1[SIZE][SIZE];
        int matrix2[SIZE][SIZE];
        int result[SIZE][SIZE];

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; j++) {
                matrix1[i][j] = i*SIZE+j;
                matrix2[i][j] = j*SIZE+i;
            }
        }

        printf("matrix1: \n");
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", matrix1[i][j]);
            }
            printf("\n");
        }
        printf("\nmatrix2: \n");
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", matrix2[i][j]);
            }
            printf("\n");
        }
        printf("\n\n");

        int n = 1;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j += PART, n++) {
                MPI_Send(&amatrix1[i][j], PART, MPI_INT, n, 10, MPI_COMM_WORLD);
                MPI_Send(&matrix2[i][j], PART, MPI_INT, n, 10, MPI_COMM_WORLD);
            }
        }

        n = 1;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j += PART, n++) {
                MPI_Recv(&result[i][j], PART, MPI_INT, n, 10, MPI_COMM_WORLD, &status);
            }
        }

        printf("Resulting matrix: \n");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", result[i][j]);
            }
            printf("\n");
        }
    }
    else {
        MPI_Probe(0, 10, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        int matrix1[PART];
        int matrix2[PART];
        int result[PART];

        MPI_Recv(&matrix1[0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        MPI_Recv(&matrix2[0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);

        for (int i = 0; i < count; ++i) {
            result[i] = matrix1[i] * matrix2[i];
        }
        MPI_Send(&result, count, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
}

namespace Task2_4{
int main(int argc, char** argv)
{
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    int count;

    const int SIZE = 10;
    const int PART = 5;

    if (rank == 0) {
        int matrix1[SIZE][SIZE];
        int matrix2[SIZE][SIZE];
        int result[SIZE][SIZE];

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; j++) {
                matrix1[i][j] = i*SIZE+j;
                matrix2[i][j] = j*SIZE+i;
            }
        }

        printf("matrix1: \n");
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", matrix1[i][j]);
            }
            printf("\n");
        }
        printf("\nmatrix2: \n");
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", matrix2[i][j]);
            }
            printf("\n");
        }
        printf("\n\n");

        int n = 1;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j += PART, n++) {
                MPI_Send(&matrix1[i][0], PART, MPI_INT, n, 10, MPI_COMM_WORLD);
                MPI_Send(&matrix2[j][0], PART, MPI_INT, n, 10, MPI_COMM_WORLD);
            }
        }

        n = 1;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j += PART, n++) {
                MPI_Recv(&result[i][j], PART, MPI_INT, n, 10, MPI_COMM_WORLD, &status);
            }
        }

        printf("Resulting matrix: \n");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", result[i][j]);
            }
            printf("\n");
        }
    }
    else {
        MPI_Probe(0, 10, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        int matrix1[PART];
        int matrix2[PART];
        int result[PART];

        MPI_Recv(&matrix1[0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        MPI_Recv(&matrix2[0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);

        for (int i = 0; i < count; ++i) {
            result[i] += matrix1[i] * matrix2[i];
        }
        MPI_Send(&result, count, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
}

namespace Task2_5 {

   int main(int argc, char** argv)
{
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    int count;

    const int SIZE = 10;
   
    const int PART = 5;

    if (rank == 0) {
        int matrix1[SIZE][SIZE];
        int tmatrix1[SIZE][SIZE];

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; j++) {
                matrix1[i][j] = i*SIZE+j;
            }
        }

        printf("Original matrix: \n");
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", matrix1[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        int n = 1;
        for (int i = 0; i < SIZE; i += PART) {
            for (int j = 0; j < SIZE; j += PART, n++) {
                MPI_Send(&matrix1[i][j], PART*PART, MPI_INT, n, 10, MPI_COMM_WORLD);
            }
        }

        n = 1;
        for (int i = 0; i < SIZE; i += PART) {
            for (int j = 0; j < SIZE; j += PART, n++) {
                MPI_Recv(&tmatrix1[i][j], PART*PART, MPI_INT, n, 10, MPI_COMM_WORLD, &status);
            }
        }

        printf("Transposed matrix: \n");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                printf("%d ", tmatrix1[i][j]);
            }
            printf("\n");
        }
    }
    else {
        MPI_Probe(0, 10, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        int matrix1[PART][PART];
        int tmatrix1[PART][PART];

        MPI_Recv(&matrix1[0][0], count, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);

        for (int i = 0; i < PART; i++) {
            for (int j = 0; j < PART; j++) {
                tmatrix1[j][i] = matrix1[i][j];
            }
        }

        MPI_Send(&tmatrix1, count, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
}
