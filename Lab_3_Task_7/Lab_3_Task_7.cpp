// OMP_lastprivate.cpp

/* Лаб. 3, Задача 7
Проиллюстрировать возможность использование опции lastprivate
для автоматического присваивания значения локальной переменной
в последней секции всем другим локальным переменным и
одноименной глобальной переменной.
*/

#include <locale.h>
#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, ".ACP");

	int n = 0;

	#pragma omp parallel num_threads(3)
	{
		printf(
			"Значение n до секций в потоке %d: %d\n",
			omp_get_thread_num(),
			n
		);

		#pragma omp sections lastprivate(n)
		{
			#pragma omp section
			{
				n = 1;
			}

			#pragma omp section
			{
				n = 2;
			}

			#pragma omp section
			{
				n = 3;
			}
		}

		printf(
			"Значение n после секций в потоке %d: %d\n",
			omp_get_thread_num(),
			n
		);
	}

	printf("Значение n в последовательной области: %d\n", n);
}
