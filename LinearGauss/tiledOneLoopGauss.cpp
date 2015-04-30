#include "tiledOuterGauss.h"

double oneLoopParallelGauss(double** a, double* answer, size_t N) {
    makeMainElementNotZero(a, N);
    
	int r1 = 2;
    int r2 = 2;

	int Q1 = N / r1;
	int Q2 = N / r2;
    
    //##########
    double start = omp_get_wtime();
    
    for (int t = 0; t < Q1 + Q2 - 1; ++t) {
#pragma omp parallel for
        for (int j_gl = 0; j_gl < Q2; ++j_gl) {
            int i_gl = t - j_gl;
            tile(i_gl, j_gl, r1, r2, a, N);            
        }
    }
    double finish = omp_get_wtime();
    //##########        

	check(a,answer,N);
	cout << "One loop:\n\tTime spent " << finish - start << " seconds\n";

    return finish - start;
}

