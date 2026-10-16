// MPI_Bandwith_Latency-c-Bind.cpp

/* Ћаб. 7, «адача 1
Ќаписать программу, котора€ определ€ет латентность
(т.е. врем€ на передачу сообщени€ нулевой длины)
и максимально достижимую пропускную способность
коммуникационной среды, а также длину сообщени€,
на которой она достигаетс€.
*/

#include <iostream>
#include <mpi.h>

using namespace std;

int const NMAX = 9000000, NTIMES = 10;
double a[NMAX];

int main(int argc, char **argv) {
	double _2_d20 = pow(2.0, 20);
	int n = 0, lmax = 0;
	double max = 0.0;

	MPI_Init(NULL, NULL);

	int Size;
	MPI_Comm_size(MPI_COMM_WORLD, &Size);

	int Rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &Rank);

	while (n <= NMAX) {
		double time_start = MPI_Wtime();

		for (int i = 0; i < NTIMES; i++) {
			if (Rank == 0) {
				MPI_Status St;
				MPI_Send(a, n, MPI_DOUBLE, 1, 5, MPI_COMM_WORLD);
				MPI_Recv(a, n, MPI_DOUBLE, 1, 5, MPI_COMM_WORLD, &St);
			}

			if (Rank == 1) {
				MPI_Status St;
				MPI_Recv(a, n, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD, &St);
				MPI_Send(a, n, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD);
			}
		}

		double time = (MPI_Wtime() - time_start) / (2 * NTIMES);
		double bandwidth = (8.0 * n / _2_d20) / time;

		if (max < bandwidth) {
			max = bandwidth;
			lmax = 8 * n;
		}

		if (Rank == 0) {
			if (n==0) cout << "Latency: " << time << " s" << endl;
			else cout << 8 * n << " bytes, bandwidth: " << bandwidth << "MB/s" << endl;
		}

		if (n == 0) n=1;
		else n *= 2;
	}

	if (Rank == 0) {
		cout << "Max bandwidth: " << max
			<< " MB/s, length: " << lmax << " bytes" << endl;
	}

	MPI_Finalize();
}
