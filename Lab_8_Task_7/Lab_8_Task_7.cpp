// MPI_Datatype-c-Bind.cpp

/* Ћаб. 8, «адача 7
»нформаци€ о частице (предположительно) может включать
следующие данные: три координаты (вещественные числа);
зар€д, кратный зар€ду протона (или электрона Ц целое число);
масса поко€ (вещественное число); дополнительные данные (8 символов).
»спользу€ стандартные средства MPI дл€ создани€ и регистрации
пользовательских типов данных, обеспечить пересылку
и приЄм массива подобных структур.
*/

#include <iostream>
#include <mpi.h>

using namespace std;

struct TParticle {
	double Coords[3];
	int Charge;
	double Mass;
	char Chr[8];
};

int main(int argc, char **argv) {
	TParticle Particle[3];

	MPI_Init(NULL, NULL);

	int Rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &Rank);

	MPI_Datatype TType[4] = { MPI_DOUBLE, MPI_INT, MPI_DOUBLE, MPI_CHAR };
	int BlockLen[4] = { 3, 1, 1, 8 };
	MPI_Aint Disp[4];
	MPI_Aint Base;

	MPI_Get_address(&Particle[0], &Base);
	MPI_Get_address(&(Particle[0].Coords), &Disp[0]);
	MPI_Get_address(&(Particle[0].Charge), &Disp[1]);
	MPI_Get_address(&(Particle[0].Mass), &Disp[2]);
	MPI_Get_address(&(Particle[0].Chr), &Disp[3]);

	for (int k = 0; k < 4; k++) Disp[k] -= Base;

	MPI_Datatype My_Particle;
	MPI_Type_create_struct(4, BlockLen, Disp, TType, &My_Particle);
	MPI_Type_commit(&My_Particle);

	if (Rank == 0) {
		for(int k = 0; k < 3; k++)
			for(int j = 0; j < 8; j++)
				Particle[k].Chr[j] = 0;

		Particle[0].Coords[0] = 1.1;
		Particle[0].Coords[1] = 7.3;
		Particle[0].Coords[2] = 3.7;
		Particle[0].Charge = 1;
		Particle[0].Mass = 7.83;
		Particle[0].Chr[0] = 'P';
		Particle[0].Chr[1] = '1';

		Particle[1].Coords[0] = 1.1;
		Particle[1].Coords[1] = -7.3;
		Particle[1].Coords[2] = 3.7;
		Particle[1].Charge = -1;
		Particle[1].Mass = 1.83;
		Particle[1].Chr[0] = 'P';
		Particle[1].Chr[1] = '2';

		Particle[2].Coords[0] = -1.1;
		Particle[2].Coords[1] = 7.3;
		Particle[2].Coords[2] = -3.7;
		Particle[2].Charge = 0;
		Particle[2].Mass = 7.87;
		Particle[2].Chr[0] = 'P';
		Particle[2].Chr[1] = '3';

		cout << "Process 0 sends the data" << endl;

		for (int k = 0; k < 3; k++) {
			cout << "Particle " << Particle[k].Chr << endl
				<< "Coordinates " << Particle[k].Coords[0] << " "
				<< Particle[k].Coords[1] << " "
				<< Particle[k].Coords[2] << endl
				<< "Mass " << Particle[k].Mass
				<< " Charge " << Particle[k].Charge << endl;
		}

		MPI_Send(&Particle[0], 3, My_Particle, 1, 5, MPI_COMM_WORLD);
	}

	if (Rank == 1) {
		MPI_Status St;
		MPI_Recv(&Particle[0], 3, My_Particle, 0, 5, MPI_COMM_WORLD, &St);

		cout << "Process 1 has accepted the data" << endl;

		for (int k = 0; k < 3; k++) {
			cout << "Particle " << Particle[k].Chr << endl
				<< "Coordinates " << Particle[k].Coords[0] << " "
				<< Particle[k].Coords[1] << " "
				<< Particle[k].Coords[2] << endl
				<< "Mass " << Particle[k].Mass
				<< " Charge " << Particle[k].Charge << endl;
		}
	}

	MPI_Type_free(&My_Particle);
	MPI_Finalize();
}
