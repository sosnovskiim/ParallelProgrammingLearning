// parallel_sort.cpp

#define _USE_MATH_DEFINES

#include <algorithm>
#include <cmath>
#include <iostream>
#include <locale.h>
#include <ppl.h>
#include <time.h>
#include <vector>

int main() {
	setlocale(LC_ALL, ".ACP");
	const int N = 50000000;

	std::vector<double> X0(N);
	for (int n = 0; n < N; n++) {
		double dn = (double)n;
		double sn = std::sqrt(dn);
		X0[n] = std::cos(dn * sn / (1.0 + sn));
	}
	std::vector<double> X(X0);

    double Time = clock();
    std::sort(X.begin(), X.end());
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Посл. время sort: " << Time << " сек." << std::endl;

    X = X0;
    Time = clock();
    concurrency::parallel_sort(X.begin(), X.end());
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Парал. время parallel_sort: "
        << Time << " сек." << std::endl;

    X = X0;
    Time = clock();
    concurrency::parallel_buffered_sort(X.begin(), X.end());
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "Парал. время parallel_buffered_sort: "
        << Time << " сек." << std::endl;
}
