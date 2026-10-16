// OMP_lock.cpp

/* Лаб. 4, Задача 5
При помощи блокировки (обеспечивается стандартными функциями OpenMP
omp_init_lock, omp_set_lock, omp_unset_lock), добиться того,
чтобы сообщения, печатаемые в разных потоках в параллельной секции,
не перемежались друг с другом. Для имитации вычислений использовать
функцию sleep (Sleep в ОС Windows).
*/

#include <locale.h>
#include <omp.h>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>

void sleep(int seconds) {
	Sleep(1000 * seconds);
}

#endif

omp_lock_t lock;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, ".ACP" );

	int n;

	omp_init_lock(&lock);

	#pragma omp parallel num_threads(4) private(n)
	{
		n = omp_get_thread_num();

		omp_set_lock(&lock);

		printf("Начало закрытой секции, поток %d\n", n);
		sleep(2 + 3 * ((n + 1) % 2));
		printf("Конец закрытой секции, поток %d\n", n);

		omp_unset_lock(&lock);
	}

	omp_destroy_lock(&lock);
}
