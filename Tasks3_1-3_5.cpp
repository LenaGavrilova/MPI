namespace Task3_1 {
    const int VECTOR_SIZE = 100;

    int main(int argc, char** argv) {
        int rank, size;
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        double vector[VECTOR_SIZE];

        if (rank == 0) {
            // Заполнение вектора на нулевом процессе
            std::cout << "Vector:\n";
            for (int i = 0; i < VECTOR_SIZE; ++i) {
                vector[i] = rand() % 100 + 1;
                std::cout << vector[i] << " ";
            }
        }

        double local_sum = 0.0;
        double local_norm = 0.0;

        // Размер подвектора для каждого процесса
        int local_size = VECTOR_SIZE / size;

        double local_vector[20];

        // Разделение вектора между процессами
        MPI_Scatter(vector, local_size, MPI_DOUBLE, local_vector, local_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        // Вычисление нормы подвектора
        for (int i = 0; i < local_size; ++i) {
            local_sum += local_vector[i];
        }

        // Суммирование норм подвекторов на нулевом процессе
        MPI_Reduce(&local_sum, &local_norm, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        if (rank == 0) {
            std::cout << "Norm: " << local_norm << std::endl;
        }

        MPI_Finalize();
        return 0;
    }
}

namespace Task3_2 {
    const int VECTOR_SIZE = 100;

    int main(int argc, char** argv) {
        int rank, size;
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        double vector1[VECTOR_SIZE];
        double vector2[VECTOR_SIZE];

        if (rank == 0) {
            // Заполнение векторов на нулевом процессе
            std::cout << "Vector1:\n";
            for (int i = 0; i < VECTOR_SIZE; ++i) {
                vector1[i] = rand() % 100 + 1;
                std::cout << vector1[i] << " ";

            }
            std::cout << "Vector2:\n";
            for (int i = 0; i < VECTOR_SIZE; ++i) {
                vector2[i] = rand() % 100 + 1;
                std::cout << vector2[i] << " ";
            }
        }

        double local_sum = 0.0;
        double local_product = 0.0;

        // Размер подвектора для каждого процесса
        int local_size = VECTOR_SIZE / size;

        double local_vector1[20];
        double local_vector2[20];

        // Разделение векторов между процессами
        MPI_Scatter(vector1, local_size, MPI_DOUBLE, local_vector1, local_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Scatter(vector2, local_size, MPI_DOUBLE, local_vector2, local_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        // Вычисление локального скалярного произведения
        for (int i = 0; i < local_size; ++i) {
            local_product += local_vector1[i] * local_vector2[i];
        }

        // Суммирование скалярных произведений на нулевом процессе
        MPI_Reduce(&local_product, &local_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        if (rank == 0) {
            std::cout << "Result: " << local_sum << std::endl;
        }

        MPI_Finalize();
        return 0;
    }
}
namespace Tasl3_3{
const int MATRIX_SIZE = 100;
const int VECTOR_SIZE = 100;

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double matrix[MATRIX_SIZE][MATRIX_SIZE];
    double vector[VECTOR_SIZE];
    double local_result[MATRIX_SIZE] = { 0 };

    if (rank == 0) {
        // Генерация матрицы и вектора на нулевом процессе
        std::cout << "Matrix:\n";
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            for (int j = 0; j < MATRIX_SIZE; ++j) {
                matrix[i][j] = rand() % 100 + 1;
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Vector:\n";
        for (int i = 0; i < VECTOR_SIZE; ++i) {
            vector[i] = rand() % 100 + 1;
            std::cout << vector[i] << " ";
        }
    }

    // Рассылка вектора всем процессам
    MPI_Bcast(vector, VECTOR_SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Размер подматрицы для каждого процесса
    int local_rows = MATRIX_SIZE / size;

    double local_matrix[20][MATRIX_SIZE];

    // Распределение частей матрицы
    MPI_Scatter(matrix, local_rows * MATRIX_SIZE, MPI_DOUBLE, local_matrix, local_rows * MATRIX_SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Умножение матрицы на вектор
    for (int i = 0; i < local_rows; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            local_result[i] += local_matrix[i][j] * vector[j];
        }
    }

    // Сбор результатов на нулевом процессе
    double global_result[MATRIX_SIZE];
    MPI_Gather(local_result, local_rows, MPI_DOUBLE, global_result, local_rows, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Вывод результата на нулевом процессе
        std::cout << "Resulting vector:" << std::endl;
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            std::cout << global_result[i] << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}
}

namespace Tasl3_4{

const int MATRIX_SIZE = 100;

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int matrix[MATRIX_SIZE][MATRIX_SIZE];
    int local_max = 0;

    if (rank == 0) {
        // Генерация матрицы на нулевом процессе
        std::cout << "Matrix:\n";
        for (int i = 0; i < MATRIX_SIZE; ++i) {
            for (int j = 0; j < MATRIX_SIZE; ++j) {
                matrix[i][j] = i*MATRIX_SIZE+j;
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Размер подматрицы для каждого процесса
    int local_rows = MATRIX_SIZE / size;

    int local_matrix[20][MATRIX_SIZE];
   

    // Распределение частей матрицы
    MPI_Scatter(matrix, local_rows * MATRIX_SIZE, MPI_INT, local_matrix, local_rows * MATRIX_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Вычисление максимума для каждой строки локальной матрицы
    for (int i = 0; i < MATRIX_SIZE; i++) {
        int row_sum = 0;
        for (int j = 0; j< MATRIX_SIZE; j++) {
            row_sum += std::abs(matrix[j][i]);
       
        }
        if (row_sum > local_max) {
            local_max = row_sum;
            std::cout <<"rank"<<rank <<" " << local_max << std::endl;
        }
    }

    // Нахождение максимального значения среди всех процессов
    int global_max = 0;
    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
   
    if (rank == 0) {
        // Вывод результата на нулевом процессе
        std::cout << "Norm of the matrix: " << global_max << std::endl;
    }

    MPI_Finalize();
    return 0;
}

}

const int VECTOR_SIZE = 100;

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int vector[VECTOR_SIZE];

    if (rank == 0) {
        // Генерация вектора на нулевом процессе
        std::cout << "Vector";
        for (int i = 0; i < VECTOR_SIZE; ++i) {
            vector[i] = i*VECTOR_SIZE;
            std::cout << vector[i] << " ";
        }
    }

    // Размер подвектора для каждого процесса
    int local_size = VECTOR_SIZE / size;

    int local_vector[20];

    // Распределение частей вектора
    MPI_Scatter(vector, local_size, MPI_INT, local_vector, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    int local_max_value = 0;
    int local_max_index = 0;
 
   
    // Поиск локального максимума
    for (int i = 0; i < local_size; ++i) {
        if (local_vector[i] > local_max_value) {
            local_max_value = local_vector[i];
            local_max_index = i;
            std::cout << local_max_value << "n\ ";
        }
    }

    // Нахождение глобального максимума и его индекса
    int global_max_value;
    int global_max_index;

    MPI_Reduce(&local_max_value, &global_max_value, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_max_index, &global_max_index, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Вывод локальных максимумов
        for (int i = 0; i < size; ++i) {
            std::cout << "Rank " << i << ": Max value = " << global_max_value << ", Index = " << (i * local_size + global_max_index) << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}
