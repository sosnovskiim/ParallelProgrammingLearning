// OMP_barrier.cpp

/* Лаб. 4, Задача 1
Используя директиву барьерной синхронизации omp barrier,
написать параллельную программу, в которой несколько сообщений
с младшими номерами могут выводиться в произвольном порядке,
но будут гарантированно замыкаться сообщениями со старшим номером.
*/

#include <locale.h>
#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, ".ACP" );

	#pragma omp parallel num_threads(2)
	{
		printf("Сообщение 1\n");
		printf("Сообщение 2\n");
		printf("Сообщение 3\n");
		#pragma omp barrier
		printf("Сообщение 4\n");
	}
}
