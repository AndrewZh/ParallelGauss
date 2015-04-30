#include "linearGauss.h"

double linearGauss(double** a, double* answer, size_t N) {

	makeMainElementNotZero(a, N);
    
    //##########
    double start = omp_get_wtime();
    for (int k = 0; k < N - 1; k++) {
        for (int i = k + 1; i < N; i++) {
            for (int j = k + 1; j < N + 1; j++) {
                a[i][j] = a[i][j] - a[i][k] * a[k][j] / a[k][k];
            }
        }
    }
    double finish = omp_get_wtime();
    //##########        

    check(a, answer, N);
    cout << "Linear:\n\tTime spent " << finish - start << " seconds\n";

    return finish - start;
}
