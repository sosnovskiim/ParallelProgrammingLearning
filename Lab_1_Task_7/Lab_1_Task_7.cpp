// master.cpp

/* Лаб. 1, Задание 7
Распечатать значение умолчанию переменной OMP_DYNAMIC
при помощи функции omp_get_dynamic(). Затем при помощи функции
omp_get_dynamic(int) разрешить динамическую установку числа потоков
в параллельной области и снова распечатать значение переменной OMP_DYNAMIC.
Cоздать параллельную область. При помощи директивы master обеспечить печать
фактического числа потоков OpenMP лишь в главном потоке.
*/

#include <locale.h>
#include <omp.h>
#include <stdio.h>

int main() {
	setlocale(LC_ALL, ".ACP");

	printf("OMP_DYNAMIC = %d\n", omp_get_dynamic());

	omp_set_dynamic(1);

	printf("OMP_DYNAMIC = %d\n", omp_get_dynamic());

	#pragma omp parallel num_threads(128)
	{
		#pragma omp master
		{
			printf(
				"Параллельная область с кол-вом потоков: %d\n",
				omp_get_num_threads()
			);
		}
	}
}
