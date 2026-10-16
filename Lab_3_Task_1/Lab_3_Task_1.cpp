// Threadprivate.cpp

/* Ћаб. 3, «адача 1
ѕроиллюстрировать тот факт, что, при условии, что количество потоков
в двух параллельных област€х совпадает, т.е. число потоков
не измен€етс€ динамически, одноименные некоторым глобальным переменным
локальные переменные, созданные в параллельной области с использованием
опции threadprivate, сохран€ют свое значение при переходе через
последовательную область и при входе в следующую последовательную область.
*/

#include <locale.h>
#include <omp.h>
#include <stdio.h>

int n;
#pragma omp threadprivate(n)

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, ".ACP" );

	int num;
	n = 1;

	omp_set_dynamic(0);
	omp_set_num_threads(4);

	#pragma omp parallel private(num)
	{
		num = omp_get_thread_num();
		printf("«начение n на нити %d (на входе): %d\n", num, n);

		// ѕрисвоим переменной n номер текущей нити
		n = omp_get_thread_num();
		printf("«начение n на нити %d (на выходе): %d\n", num, n);
	}

	printf("«начение n (середина): %d\n", n);

	#pragma omp parallel private(num)
	{
		num = omp_get_thread_num();
		printf("«начение n на нити %d (ещЄ раз): %d\n", num, n);
	}
}
