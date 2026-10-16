// Reduct2.cpp

/* Лаб. 4, Задача 7
Использовать потоки OpenMP (директиву #pragma omp parallel for)
и операцию редукции при ускорении вычисления интегралов
по квадратурной формуле Симпсона.
*/

#define _USE_MATH_DEFINES

#include <chrono>
#include <iostream>
#include <locale.h>
#include <math.h>
#include "Simps.h"

using namespace std;

double My_F(double x) {
	return 1.0 / (1.0 + x * x);
}

int main(void) {
	setlocale(LC_ALL, ".ACP");

	auto time_start = chrono::steady_clock::now();
	double Intgr = Simps(0, 1000000, 1000000000, My_F);
	auto time_end = chrono::steady_clock::now();

	auto ms = chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start);
	cout.precision(8);
	cout << "Время: " << ms.count() << " мс" << endl;
	cout << "Результат: " << Intgr << endl;
	cout << "Проверка: " << M_PI / 2.0 << endl;
}
