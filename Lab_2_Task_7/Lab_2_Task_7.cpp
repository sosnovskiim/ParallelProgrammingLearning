// OMP_Shared.cpp

/* Лаб. 2, Задание 7
При помощи опции shared создать массив, общий для всех потоков
в параллельной области, и в элемент массива, номер которого
совпадает с номером потока, записать номер потока.
*/

#include <locale.h>
#include <omp.h>
#include <stdio.h>

#define NNN 8

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, ".ACP" );

	int i, m[NNN];

	// Заполним массив m нулями и напечатаем его
	printf("Массив m в начале:\n");
	for (i = 0; i < NNN; i++) {
		m[i] = 0;
		printf("%d\n", m[i]);
	}

	#pragma omp parallel num_threads(NNN) shared(m)
	{
		// Присвоим элементу массива m, номер которого
		// совпадает с номером текущий нити, значение номера текущей нити
		int thread_num = omp_get_thread_num();
		m[thread_num] = thread_num;
	}

	// Ещё раз напечатаем массив
	printf("Массив m в конце:\n");
	for (i = 0; i < NNN; i++) printf("%d\n", m[i]);
}
