// OMP_Date.cpp

/* Лаб. 1, Задание 1
Определить, поддерживает ли компилятор C++ стандарт OpenMP,
и, если поддерживает, то распечатать год и месяц принятия стандарта.
*/

#include <iostream>
#include <locale.h>

using namespace std;

int main() {
	setlocale(LC_ALL, ".ACP");

	#ifdef _OPENMP
	cout << "OpenMP поддерживается" << endl;

	int year = _OPENMP / 100;
	int month = _OPENMP % 100;

	cout << "Год принятия стандарта: " << year << endl;
	cout << "Месяц принятия стандарта: " << month << endl;

	#else 
	cout << "OpenMP не поддерживается" << endl;

	#endif
}
