// parallel_transform.cpp

#define _USE_MATH_DEFINES

#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <list>
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
	const int N = 2000;

    std::vector<double> V(N);
    for (int n = 1; n <= N; n++) {
        V[n - 1] = 100.0 * std::cos((double)n);
    }
    std::vector<double> VP(V);

    double Time = clock();
    std::transform(V.begin(), V.end(), V.begin(), [](double x) { return f(x); });
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Посл. время для vector: " << Time << " сек." << std::endl;

    Time = clock();
    concurrency::parallel_transform(
        VP.begin(), VP.end(), VP.begin(), [](double x) { return f(x); }
    );
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Парал. время для vector: " << Time << " сек." << std::endl;

    std::deque<double> D;
    for (int n = 1; n <= N; n++) {
        D.push_back(100.0 * std::cos((double)n));
    }
    std::deque<double> DP(D);

    Time = clock();
    std::transform(D.begin(), D.end(), D.begin(), [](double x) { return f(x); });
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Посл. время для deque: " << Time << " сек." << std::endl;

    Time = clock();
    concurrency::parallel_transform(
        DP.begin(), DP.end(), DP.begin(), [](double x) { return f(x); }
    );
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Парал. время для deque: " << Time << " сек." << std::endl;

    std::list<double> L;
    for (int n = 1; n <= N; n++) {
        L.push_back(100.0 * std::cos((double)n));
    }
    std::list<double> LP(L);

    Time = clock();
    std::transform(L.begin(), L.end(), L.begin(), [](double x) { return f(x); });
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Посл. время для list:  " << Time << " сек." << std::endl;

    Time = clock();
    concurrency::parallel_transform(
        LP.begin(), LP.end(), LP.begin(), [](double x) { return f(x); }
    );
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Парал. время для list: " << Time << " сек." << std::endl;
}
