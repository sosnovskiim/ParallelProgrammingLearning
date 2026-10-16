// OMP_schedule.cpp

/* Лаб. 3, Задача 5
При помощи опции schedule(static, размер_блока) директивы omp for
проиллюстрировать блочно-циклическое распределение итераций цикла
между потоками в параллельной области. Для имитации вычислений
использовать функцию Sleep(unsigned long).
*/

#include <stdio.h>
#include <omp.h>
#include <locale.h>

#ifdef _WIN32
#include <windows.h>

void sleep(int seconds) {
	Sleep(1000 * seconds);
}

#endif

#define NN 36

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, ".ACP" );

	int i;

	#pragma omp parallel num_threads(4) private(i)
	{
		#pragma omp for schedule(static, 5)
		for (i = 0; i < NN; i++)
		{
			printf(
				"Поток %d выполнил итерацию %d\n",
				omp_get_thread_num(),
				i
			);
			sleep(1);
		}
	}
}
