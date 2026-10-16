// Detect_Mode.cpp

/* Ћаб. 2, «адание 1
»спользу€ стандартный вызов OpenMP omp_in_parallel(), разработать функцию,
котора€ измен€ет свою функциональность в зависимости от того,
из какой области Ц последовательной или параллельной Ц она вызываетс€.
*/

#include <locale.h>
#include <omp.h>
#include <stdio.h>

void mode(void) {
	if (omp_in_parallel()) printf("ѕараллельна€ область\n");
	else printf("ѕоследовательна€ область\n");
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, ".ACP");

	mode();

	#pragma omp parallel
	{
		#pragma omp master
		{
			mode();
		}
	}
}
