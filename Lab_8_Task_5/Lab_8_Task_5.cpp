// MPI_NEW_COMM-c-Bind.cpp

/* Лаб. 8, Задача 5
То же самое, что в задаче 3, но разделить процессы в коммуникаторе
на два коммуникатора и выполнить операцию редукции для каждого
из коммуникаторов. В пределах каждого из коммуникаторов
пронумеровать процессы с нуля.
*/

/* Лаб. 8, Задача 3
Использовать стандартные средства MPI, в частности, операцию редукции,
при ускорении вычисления интегралов по квадратурной формуле Симпсона.
*/

#include <iostream>
#include <mpi.h>

using namespace std;

int const N = 8;

void UsrFunc(void *In, void *InOut, int *len, MPI_Datatype *Ty) {
	int *InV = (int *) In;
	int *InOutV = (int *) InOut;

	for (int k = 0; k < (*len); k++)
		InOutV[k] = (InV[k] + InOutV[k]) % 8;
}

int main(int argc, char **argv) {
	int *A = new int[N];

	MPI_Init(NULL, NULL);

	MPI_Op My_Op;
	MPI_Op_create(&UsrFunc, true, &My_Op);

	MPI_Group Gr;
	MPI_Comm_group(MPI_COMM_WORLD, &Gr);

	int Size;
	MPI_Comm_size(MPI_COMM_WORLD, &Size);

	int Rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &Rank);

	MPI_Group New_Group;

	if (Rank < Size / 2) {
		int *Rks = new int[Size / 2];

		for (int k = 0; k < Size / 2; k++) Rks[k] = k;

		MPI_Group_incl(Gr, Size / 2, Rks, &New_Group);

		delete[] Rks;
	} else {
		int *Rks = new int[Size - Size / 2];

		for (int k = 0; k < Size - Size / 2; k++) Rks[k] = k + Size / 2;

		MPI_Group_incl(Gr, Size - Size / 2, Rks, &New_Group);

		delete[] Rks;
	}

	MPI_Comm New_Comm;
	MPI_Comm_create(MPI_COMM_WORLD, New_Group, &New_Comm);
	MPI_Comm_rank(New_Comm, &Rank);

	for (int k = 0; k < N; k++) A[k] = k + Rank;

	if (Rank == 0) {
		int *B = new int[N]; 
		MPI_Reduce(A, B, N, MPI_INT, My_Op, 0, New_Comm);

		for (int k = 0; k < N; k++)
			cout << B[k] << " ";
		cout << endl;

		delete[] B;
	} else {
		MPI_Reduce(A, NULL, N, MPI_INT, My_Op, 0, New_Comm);
	}

	MPI_Comm_free(&New_Comm);
	MPI_Op_free(&My_Op);
	MPI_Finalize();

	delete[] A;
}
