// parallel_for.cpp

#include <algorithm>
#include <cmath>
#include <iostream>
#include <locale.h>
#include <ppl.h>
#include <time.h>
#include <vector>

double f(double x) {
    int N = std::max(20, (int)(20.0 * std::fabs(x)));
    double x2 = x * x;
    double s = 0.0;

    for (int k = 1; k <= N; k++) {
        for (int j = 1; j <= N; j++) {
            s += x2 / (x2 + k * k + j * j) * std::cos((k + j) * x);
        }
    }
    return s;
}

int main() {
    setlocale(LC_ALL, ".ACP");
    const int N = 2000;
    std::vector<double> y(N + 1);

    double Time = clock();
    for (int n = 1; n <= N; n++) {
        y[n] = f(100.0 * std::cos((double)n));
    }
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Посл. время: " << Time << " сек." << std::endl;

    Time = clock();
    concurrency::parallel_for(1, N + 1, [&](int n) {
        y[n] = f(100.0 * std::cos((double)n));
    });
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Парал. время: " << Time << " сек." << std::endl;
}
