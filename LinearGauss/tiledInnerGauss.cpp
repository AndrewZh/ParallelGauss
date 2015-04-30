#include "tiledInnerGauss.h"

double tiledInnerParallelGauss(double** a, double* answer, size_t N) {
	makeMainElementNotZero(a, N);

	int r1 = 2;
	int r2 = 2;

	int Q1 = N / r1;
	int Q2 = N / r2;

	//##########
	double start = omp_get_wtime();
	for (int k = 0; k < N - 1; ++k) {
		for (int i_gl = 0; i_gl < Q1; ++i_gl) {
#pragma omp parallel for        
			for (int j_gl = 0; j_gl < Q2; ++j_gl) {
				tile(k, i_gl, j_gl, r1, r2, a, N);  
			}
		}
	}
	double finish = omp_get_wtime();
	//##########        

	check("Inner", a,answer,N, finish - start);
	return finish - start;
}
