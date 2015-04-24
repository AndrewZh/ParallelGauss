#include "tiledOuterGauss.h"

double tiledOuterParallelGauss(double** a, double* answer, size_t N) {
    double* x = new double[N];

    int r1 = 2;
    int r2 = 2;

	int Q1 = N / r1;
	int Q2 = N / r2;
    
    omp_set_num_threads(NUMBER_OF_THREADS);
	makeMainElementNotZero(a, N);
    
    
    //##########
    double start = omp_get_wtime();
#pragma omp parallel for    
    for (int i_gl = 0; i_gl < Q1; ++i_gl) {
        for (int j_gl = 0; j_gl < Q2; ++j_gl) {            
            tile(i_gl, j_gl, r1, r2, a, N);
        }
    }
    double finish = omp_get_wtime();
    //##########        

    x[N - 1] = a[N - 1][N] / a[N - 1][N - 1];
    a[N - 1][N - 1] = 1;
    for (int i = N - 2; i >= 0; i--) {
        x[i] = a[i][N];
        for (int j = i + 1; j < N; j++)
            x[i] -= x[j] * a[i][j] / a[j][j];
        x[i] /= a[i][i];
        a[i][i] = 1;
    }

    bool flag = true;
    for (int i = 0; i < N; ++i) {
        if (abs(x[i] - answer[i]) > 0.00001) {
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << "OK\n";
    } else {
        cout << "ERROR\n";
    }

    cout << "Forward Gauss:\n\tTime spent " << finish - start << " seconds\n";
    delete [] x;

    return finish - start;
}