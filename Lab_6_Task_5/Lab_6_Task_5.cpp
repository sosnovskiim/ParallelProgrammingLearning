// MPI_Probe-c-Bind.cpp

/* Лаб. 6, Задача 5
Разработать параллельную программу, в которой процесс 0 ожидает сообщения
от любого из процессов 1 либо 2 с одним и тем же тегом,
но с разными типами данных. Для анализа структуры сообщения
использовать функции MPI_PROBE (MPI::Comm::Probe).
*/

#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv) {
	MPI_Init(NULL, NULL);

	int Size;
	MPI_Comm_size(MPI_COMM_WORLD, &Size);

	if (Size >= 3){
		int Rank;
		MPI_Comm_rank(MPI_COMM_WORLD, &Rank);

		if (Rank == 1) {
			double DVal = 7.7;
			MPI_Send(&DVal, 1, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD);
		}

		if (Rank == 2) {
			int IVal = 3;
			MPI_Send(&IVal, 1, MPI_INTEGER, 0, 6, MPI_COMM_WORLD);
		}

		if (Rank == 0) {
			double DVal = 0;
			int IVal = 0;

			MPI_Status St;
			MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &St);

			if (St.MPI_TAG == 5) {
				MPI_Recv(&DVal, 1, MPI_DOUBLE, St.MPI_SOURCE, 5, MPI_COMM_WORLD, &St);
				cout << "Process 0 has received from process "
					<< St.MPI_SOURCE << ": DVal = " << DVal << endl;
			}

			if (St.MPI_TAG == 6) {
				MPI_Recv(&IVal, 1, MPI_INTEGER, St.MPI_SOURCE, 6, MPI_COMM_WORLD, &St);
				cout << "Process 0 has received from process "
					<< St.MPI_SOURCE << ": IVal = " << IVal << endl;
			}

			MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &St);

			if (St.MPI_TAG == 5) {
				MPI_Recv(&DVal, 1, MPI_DOUBLE, St.MPI_SOURCE, 5, MPI_COMM_WORLD, &St);
				cout << "Process 0 has received from process "
					<< St.MPI_SOURCE << ": DVal = " << DVal << endl;
			}

			if (St.MPI_TAG == 6) {
				MPI_Recv(&IVal, 1, MPI_INTEGER, St.MPI_SOURCE, 6, MPI_COMM_WORLD, &St);
				cout << "Process 0 has received from process "
					<< St.MPI_SOURCE << ": IVal = " << IVal << endl;
			}
		}
	} else {
		cout << "Program must be executed in at least 3 processes" << endl;
	}

	MPI_Finalize();
}
