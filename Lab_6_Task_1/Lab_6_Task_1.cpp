// MPI_Simpliest-c-Bind.cpp

/* Лаб. 6, Задача 1
Используя стандартные функции MPI, написать программу, в которой
каждый из параллельно работающих процессов печатает свой уникальный
идентификационный номер в коммуникаторе MPI_COMM_WORLD и общее число
процессов в данном коммуникаторе. Сравнить интерфейсы MPI
для C и для C++ («MPI bindings for C» и «MPI bindings for C++»).
*/

#include <iostream>
#include <mpi.h>

using namespace std;

int main(void) {
	int NProc, ProcId;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &NProc);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcId);

	cout << "Total number of processes: " << NProc
		<< ", Process identifier: " << ProcId << endl;

	MPI_Finalize();
}
