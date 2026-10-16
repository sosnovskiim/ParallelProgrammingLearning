// concurrent_vector.cpp

#define _USE_MATH_DEFINES

#include <cmath>
#include <concurrent_queue.h>
#include <concurrent_vector.h>
#include <iostream>
#include <locale.h>
#include <ppl.h>
#include <queue>
#include <time.h>
#include <vector>

const int N1 = 400;
const int N2 = 50;

struct Point
{
	double x, y, f;

	Point(double _x = 0, double _y = 0, double _f = 0)
	{
		x = _x; y = _y; f = _f;
	}
};

static double denominator[N2][N2];

void InitDenominator()
{
	for (int k = 1; k <= N2; k++) {
		double k4 = (double)k * k * k * k;
		for (int j = 1; j <= N2; j++) {
			double j4 = (double)j * j * j * j;
			denominator[k - 1][j - 1] =
				1.0 / ((1.0 + k + j) * std::sqrt(1.0 + k4 + j4));
		}
	}
}

void Func(double x, double y, double& fval, double& gx)
{
	double sinkx[N2], kcoskx[N2], sinjy[N2];

	for (int k = 1; k <= N2; k++) {
		double kx = k * x;
		sinkx[k - 1] = std::sin(kx);
		kcoskx[k - 1] = k * std::cos(kx);
	}
	for (int j = 1; j <= N2; j++) {
		sinjy[j - 1] = std::sin(j * y);
	}

	fval = 0.0;
	gx = 0.0;

	for (int k = 1; k <= N2; k++) {
		double sk = sinkx[k - 1];
		double ck = kcoskx[k - 1];
		for (int j = 1; j <= N2; j++) {
			double d = denominator[k - 1][j - 1];
			double sj = sinjy[j - 1];
			fval += sk * sj * d;
			gx += ck * sj * d;
		}
	}
}

int main() {
	setlocale(LC_ALL, ".ACP");
	InitDenominator();
	double h = 2.0 * M_PI / N1;

	std::vector<Point> PointsVectorSeq;
	double Time = clock();
	for (int k = 0; k < N1; k++) {
		for (int j = 0; j < N1; j++) {
			double x = h * k;
			double y = h * j;
			double fval, gx;
			Func(x, y, fval, gx);
			if (gx >= 0.0) {
				PointsVectorSeq.push_back(Point(x, y, fval));
			}
		}
	}
	Time = (clock() - Time) / CLOCKS_PER_SEC;
	std::cout << "Посл. время для vector: " << Time
		<< " сек., размер = " << PointsVectorSeq.size() << std::endl;

	concurrency::concurrent_vector<Point> PointsVectorPar;
	Time = clock();
	concurrency::parallel_for(0, N1, [&PointsVectorPar, h](int k) {
		for (int j = 0; j < N1; j++) {
			double x = h * k;
			double y = h * j;
			double fval, gx;
			Func(x, y, fval, gx);
			if (gx >= 0.0) {
				PointsVectorPar.push_back(Point(x, y, fval));
			}
		}
	});
	Time = (clock() - Time) / CLOCKS_PER_SEC;
	std::cout << "Парал. время для vector: " << Time
		<< " сек., размер = " << PointsVectorPar.size() << std::endl;
	PointsVectorPar.clear();

	std::queue<Point> PointsQueueSeq;
	Time = clock();
	for (int k = 0; k < N1; k++) {
		for (int j = 0; j < N1; j++) {
			double x = h * k;
			double y = h * j;
			double fval, gx;
			Func(x, y, fval, gx);
			if (gx >= 0.0) {
				PointsQueueSeq.push(Point(x, y, fval));
			}
		}
	}
	Time = (clock() - Time) / CLOCKS_PER_SEC;
	std::cout << "Посл. время для queue: " << Time
		<< " сек., размер = " << PointsQueueSeq.size() << std::endl;

	concurrency::concurrent_queue<Point> PointsQueuePar;
	Time = clock();
	concurrency::parallel_for(0, N1, [&PointsQueuePar, h](int k) {
		for (int j = 0; j < N1; j++) {
			double x = h * k;
			double y = h * j;
			double fval, gx;
			Func(x, y, fval, gx);
			if (gx >= 0.0) {
				PointsQueuePar.push(Point(x, y, fval));
			}
		}
	});
	Time = (clock() - Time) / CLOCKS_PER_SEC;
	std::cout << "Парал. время для queue: " << Time
		<< " сек., размер = " << PointsQueuePar.unsafe_size() << std::endl;
	PointsQueuePar.clear();
}
