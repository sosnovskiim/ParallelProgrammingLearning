#include <chrono>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <locale.h>
#include <omp.h>

double f(double x, double y, double z) {
    return 1.0 / (2.0 + sin(x * x + y * y + z * z));
}

double compute_A_default(int N, double& time) {
    double h = 1.0 / N;
    double sum = 0.0;
    auto time_start = std::chrono::steady_clock::now();

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++) {
        double x = h * (i + 0.5);
        for (int j = 0; j < N; j++) {
            double y = h * (j + 0.5);
            for (int k = 0; k < N; k++) {
                double z = h * (k + 0.5);
                sum += f(x, y, z);
            }
        }
    }

    auto time_end = std::chrono::steady_clock::now();
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
    time = static_cast<double>(time_ms.count());
    return sum * h * h * h;
}

double compute_A_static(int N, double& time) {
    double h = 1.0 / N;
    double sum = 0.0;
    auto time_start = std::chrono::steady_clock::now();

    #pragma omp parallel for reduction(+:sum) schedule(static)
    for (int i = 0; i < N; i++) {
        double x = h * (i + 0.5);
        for (int j = 0; j < N; j++) {
            double y = h * (j + 0.5);
            for (int k = 0; k < N; k++) {
                double z = h * (k + 0.5);
                sum += f(x, y, z);
            }
        }
    }

    auto time_end = std::chrono::steady_clock::now();
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
    time = static_cast<double>(time_ms.count());
    return sum * h * h * h;
}

double compute_A_dynamic(int N, double& time) {
    double h = 1.0 / N;
    double sum = 0.0;
    auto time_start = std::chrono::steady_clock::now();

    #pragma omp parallel for reduction(+:sum) schedule(dynamic)
    for (int i = 0; i < N; i++) {
        double x = h * (i + 0.5);
        for (int j = 0; j < N; j++) {
            double y = h * (j + 0.5);
            for (int k = 0; k < N; k++) {
                double z = h * (k + 0.5);
                sum += f(x, y, z);
            }
        }
    }

    auto time_end = std::chrono::steady_clock::now();
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
    time = static_cast<double>(time_ms.count());
    return sum * h * h * h;
}

double compute_B_default(int N, double& time) {
    double h = 1.0 / N;
    double sum = 0.0;
    auto time_start = std::chrono::steady_clock::now();

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++) {
        int R = N - i;
        double x = h * i;
        for (int j = -R; j <= R; j++) {
            int r2 = R * R - j * j;
            if (r2 < 0) continue;
            int K = static_cast<int>(std::sqrt(r2));
            double y = h * j;
            for (int k = -K; k <= K; k++) {
                double z = h * k;
                sum += f(x, y, z);
            }
        }
    }

    auto time_end = std::chrono::steady_clock::now();
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
    time = static_cast<double>(time_ms.count());
    return sum * h * h * h;
}

double compute_B_static(int N, double& time) {
    double h = 1.0 / N;
    double sum = 0.0;
    auto time_start = std::chrono::steady_clock::now();

    #pragma omp parallel for reduction(+:sum) schedule(static)
    for (int i = 0; i < N; i++) {
        int R = N - i;
        double x = h * i;
        for (int j = -R; j <= R; j++) {
            int r2 = R * R - j * j;
            if (r2 < 0) continue;
            int K = static_cast<int>(std::sqrt(r2));
            double y = h * j;
            for (int k = -K; k <= K; k++) {
                double z = h * k;
                sum += f(x, y, z);
            }
        }
    }

    auto time_end = std::chrono::steady_clock::now();
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
    time = static_cast<double>(time_ms.count());
    return sum * h * h * h;
}

double compute_B_dynamic(int N, double& time) {
    double h = 1.0 / N;
    double sum = 0.0;
    auto time_start = std::chrono::steady_clock::now();

    #pragma omp parallel for reduction(+:sum) schedule(dynamic)
    for (int i = 0; i < N; i++) {
        int R = N - i;
        double x = h * i;
        for (int j = -R; j <= R; j++) {
            int r2 = R * R - j * j;
            if (r2 < 0) continue;
            int K = static_cast<int>(std::sqrt(r2));
            double y = h * j;
            for (int k = -K; k <= K; k++) {
                double z = h * k;
                sum += f(x, y, z);
            }
        }
    }

    auto time_end = std::chrono::steady_clock::now();
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
    time = static_cast<double>(time_ms.count());
    return sum * h * h * h;
}

int main() {
    setlocale(LC_ALL, ".ACP");

    int max_threads = omp_get_max_threads();
    std::cout << "Используется " << max_threads << " потоков\n" << std::endl;

    int N_values[] = { 1000, 1500, 2000 };

    for (int i = 0; i < 3; i++) {
        int N = N_values[i];
        std::cout << "N = " << N << std::endl;
        double time_default, time_static, time_dynamic;

        double A_default = compute_A_default(N, time_default);
        std::cout << "По умолчанию: A = " << A_default
            << ", время = " << time_default << " мс" << std::endl;

        double A_static = compute_A_static(N, time_static);
        std::cout << "Статическая: A = " << A_static
            << ", время = " << time_static << " мс" << std::endl;

        double A_dynamic = compute_A_dynamic(N, time_dynamic);
        std::cout << "Динамическая: A = " << A_dynamic
            << ", время = " << time_dynamic << " мс" << std::endl;

        std::cout << std::endl;
    }

    for (int i = 0; i < 3; i++) {
        int N = N_values[i];
        std::cout << "N = " << N << std::endl;
        double time_default, time_static, time_dynamic;

        double B_default = compute_B_default(N, time_default);
        std::cout << "По умолчанию: B = " << B_default
            << ", время = " << time_default << " мс" << std::endl;

        double B_static = compute_B_static(N, time_static);
        std::cout << "Статическая: B = " << B_static
            << ", время = " << time_static << " мс" << std::endl;

        double B_dynamic = compute_B_dynamic(N, time_dynamic);
        std::cout << "Динамическая: B = " << B_dynamic
            << ", время = " << time_dynamic << " мс" << std::endl;

        std::cout << std::endl;
    }
}
