// OMP_Master.cpp

/* Лаб. 2, Задание 5
Используя директиву master OpenMP, добиться изменения в параллельной области
локальной переменной лишь в пределах основного (главного) потока.
*/

#include <locale.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	setlocale( LC_ALL, ".ACP" );

	int n;

	#pragma omp parallel num_threads(3) private(n)
	{
		n = 1;

		// Этот код будет исполнен лишь основным потоком
		#pragma omp master
		{
			n = 2;
		}

		printf("Первое значение n: %d\n", n);

		// Барьерная синхронизация потоков
		#pragma omp barrier

		// Этот код будет исполнен лишь основным потоком
		#pragma omp master
		{
			n = 3;
		}

		printf("Второе значение n: %d\n", n);
	}
}
