// parallel_for_each.cpp

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

    std::vector<double> V(N);
    for (int n = 0; n < N; n++) {
        V[n] = 100.0 * std::cos((double)(n + 1));
    }
    std::vector<double> VP(V);

    double Time = clock();
    std::for_each(V.begin(), V.end(), [](double& x) { x = f(x); });
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Посл. время для vector: " << Time << " сек." << std::endl;

    Time = clock();
    concurrency::parallel_for_each(
        VP.begin(), VP.end(), [](double& x) { x = f(x); }
    );
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Парал. время для vector: " << Time << " сек." << std::endl;

    std::deque<double> D;
    for (int n = 1; n <= N; n++) {
        D.push_back(100.0 * std::cos((double)n));
    }
    std::deque<double> DP(D);

    Time = clock();
    std::for_each(D.begin(), D.end(), [](double& x) { x = f(x); });
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Посл. время для deque: " << Time << " сек." << std::endl;

    Time = clock();
    concurrency::parallel_for_each(
        DP.begin(), DP.end(), [](double& x) { x = f(x); }
    );
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Парал. время для deque: " << Time << " сек." << std::endl;

    std::list<double> L;
    for (int n = 1; n <= N; n++) {
        L.push_back(100.0 * std::cos((double)n));
    }
    std::list<double> LP(L);

    Time = clock();
    std::for_each(L.begin(), L.end(), [](double& x) { x = f(x); });
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Посл. время для list: " << Time << " сек." << std::endl;

    Time = clock();
    concurrency::parallel_for_each(
        LP.begin(), LP.end(), [](double& x) { x = f(x); }
    );
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Парал. время для list: " << Time << " сек." << std::endl;
}
