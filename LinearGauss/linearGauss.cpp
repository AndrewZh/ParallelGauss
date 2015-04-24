#include "linearGauss.h"

double linearGauss(double** a, double* answer, size_t N) {
    double* x = new double[N];

    cout << setprecision(2);
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

    x[N - 1] = a[N - 1][N] / a[N - 1][N - 1];
    a[N - 1][N - 1] = 1;
    for (int i = N - 2; i >= 0; i--) {
        x[i] = a[i][N];
        for (int j = i + 1; j < N; j++)
            x[i] -= x[j] * a[i][j] / a[j][j];
        x[i] /= a[i][i];
        a[i][i] = 1;
    }
/*
    cout << endl;
    for (int i = 0; i < N; i++)
        cout << "x[" << i << "] = " << x[i] << "\n";
    cout << endl << endl;
*/
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

    cout << "Linear:\n\tTime spent " << finish - start << " seconds\n";
    delete [] x;

    return finish - start;
}
