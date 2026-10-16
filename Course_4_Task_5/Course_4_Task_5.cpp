// parallel_task_group.cpp

#define _USE_MATH_DEFINES

#include <algorithm>
#include <cmath>
#include <iostream>
#include <locale.h>
#include <ppl.h>
#include <time.h>
#include <vector>

double f(double x) {
    int M = (int)std::max(20.0, 20.0 * std::fabs(x));
    double x2 = x * x;

    std::vector<double> cosk(M + 1), sink(M + 1);
    for (int i = 1; i <= M; i++) {
        cosk[i] = std::cos(i * x);
        sink[i] = std::sin(i * x);
    }

    double s = 0.0;
    for (int k = 1; k <= M; k++) {
        for (int j = 1; j <= M; j++) {
            double c = cosk[k] * cosk[j] - sink[k] * sink[j];
            s += x2 / (x2 + (double)k * k + (double)j * j) * c;
        }
    }
    return s;
}

int main() {
    setlocale(LC_ALL, ".ACP");
    const int N = 1000;

    std::vector<double> X(N);
    std::vector<double> Yseq(N);
    std::vector<double> Ypar(N);

    for (int n = 0; n < N; n++) {
        X[n] = 100.0 * std::cos((double)(n + 1));
    }

    double Time = clock();
    for (int n = 0; n < N; n++) {
        Yseq[n] = f(X[n]);
    }
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Посл. время:  " << Time << " сек." << std::endl;

    Time = clock();
    concurrency::task_group task_group;
    for (int n = 0; n < N; n++) {
        task_group.run([&, n]() { Ypar[n] = f(X[n]); });
    }
    task_group.wait();
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Парал. время: " << Time << " сек." << std::endl;
}
