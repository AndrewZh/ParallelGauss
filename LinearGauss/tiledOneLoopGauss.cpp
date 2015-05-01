#include "tiledOuterGauss.h"

double oneLoopParallelGauss(double** a, double* answer, size_t N, int r1, int r2) {
	makeMainElementNotZero(a, N);

//	int r1 = 2;
//	int r2 = 2;

	int Q1 = N / r1;
	int Q2 = N / r2;

	//##########
	double start = omp_get_wtime();
	for (int k = 0; k < N - 1; ++k) {
		for (int t = 0; t < Q1 + Q2 - 1; ++t) {
#pragma omp parallel for
			for (int j_gl = 0; j_gl < Q2; ++j_gl) {
				int i_gl = t - j_gl;
				tile(k, i_gl, j_gl, r1, r2, a, N);  
			}
		}
	}
	double finish = omp_get_wtime();
	//##########        

	check("One Loop", a,answer,N, finish - start);
	return finish - start;
}

