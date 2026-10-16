#include <iostream>
#include <iomanip>
#include <cmath>
#include <mpi.h>

double f(double x, double y, double z) {
    return 1.0 / (2.0 + sin(x * x + y * y + z * z));
}

double compute_A_mpi(int N, double& elapsed_ms) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double h = 1.0 / N;
    double local_sum = 0.0;

    int chunk = N / size;
    int remainder = N % size;
    int start_i = rank * chunk;
    int end_i = start_i + chunk;
    if (rank < remainder) {
        start_i += rank;
        end_i = start_i + chunk + 1;
    }
    else {
        start_i += remainder;
        end_i = start_i + chunk;
    }

    for (int i = start_i; i < end_i; ++i) {
        double x = h * (i + 0.5);
        for (int j = 0; j < N; ++j) {
            double y = h * (j + 0.5);
            for (int k = 0; k < N; ++k) {
                double z = h * (k + 0.5);
                local_sum += f(x, y, z);
            }
        }
    }

    double global_sum = 0.0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        return global_sum * h * h * h;
    }
    return 0.0;
}

double compute_B_mpi(int N, double& elapsed_ms) {
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double h = 1.0 / N;
    double local_sum = 0.0;

    int chunk = N / size;
    int remainder = N % size;
    int start_i = rank * chunk;
    int end_i = start_i + chunk;
    if (rank < remainder) {
        start_i += rank;
        end_i = start_i + chunk + 1;
    }
    else {
        start_i += remainder;
        end_i = start_i + chunk;
    }

    for (int i = start_i; i < end_i; ++i) {
        int R = N - i;
        double x = h * i;
        for (int j = -R; j <= R; ++j) {
            int r2 = R * R - j * j;
            if (r2 < 0) continue;
            int K = static_cast<int>(std::sqrt(r2));
            double y = h * j;
            for (int k = -K; k <= K; ++k) {
                double z = h * k;
                local_sum += f(x, y, z);
            }
        }
    }

    double global_sum = 0.0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        return global_sum * h * h * h;
    }
    return 0.0;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        std::cout << "Total number of processes: " << size << "\n" << std::endl;
    }

    int N_values[] = { 1000, 1500, 2000 };

    for (int idx = 0; idx < 3; ++idx) {
        int N = N_values[idx];

        double start_time = MPI_Wtime();
        double A = compute_A_mpi(N, start_time);
        double end_time = MPI_Wtime();
        double elapsed_A_ms = (end_time - start_time) * 1000.0;

        start_time = MPI_Wtime();
        double B = compute_B_mpi(N, start_time);
        end_time = MPI_Wtime();
        double elapsed_B_ms = (end_time - start_time) * 1000.0;

        if (rank == 0) {
            std::cout << "N = " << N << std::endl;
            std::cout << "A = " << A
                << ", time = " << elapsed_A_ms << " ms" << std::endl;
            std::cout << "B = " << B
                << ", time = " << elapsed_B_ms << " ms" << std::endl;
            std::cout << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}
