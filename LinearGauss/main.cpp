#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

#include <omp.h>

using namespace std;
#define N 4

void generateInput(double**& matrix, double*& answer);
void init(double**& matrix);
void clear(double**& matrix);
double linearGauss(double** matrix, double* answer);
double tiledGauss(double** a, double* answer);
void tile(int k, int i_gl, int j_gl, int r1, int r2, double** matrix);
void copyMatrix(double** mat1, double** mat2);

int main() {
    double** working; //[N][N+1];
    double** original;
    double* answer = new double[N];
    cout << setprecision(2);

    ofstream report("results.csv", ios::trunc);
    report << "Size, Linear Gauss, OpenMP(outer)" << endl;

    generateInput(original, answer);
    init(working);
    copyMatrix(original, working);
    
    double linearTime = linearGauss(working, answer);
    report << N << "," << linearTime << ",";

    copyMatrix(original, working);
    double outerTime = tiledGauss(working, answer);
    report << outerTime << endl;

    report.close();
    delete [] answer;
    //cin.ignore();
}

double tiledGauss(double** a, double* answer) {
    double* x = new double[N];

    int r1 = N / 2;
    int r2 = N / 2;

    for (int i = 0; i < N; i++) {
        if (a[i][i] == 0) {
            for (int j = i + 1; j < N; j++)
                if (a[j][i] != 0) {
                    for (int k = 0; k < N; k++) {
                        double p = a[i][k];
                        a[i][k] = a[j][k];
                        a[j][k] = p;

                    }
                    double p = a[i][N];
                    a[i][N] = a[j][N];
                    a[j][N] = p;
                    break;
                }
        }
    }
    
    //##########
    double start = omp_get_wtime();
    for (int i_gl = 0; i_gl < N / r1; ++i_gl) {
        for (int j_gl = 0; j_gl < N / r2; ++j_gl) {
            for (int k = 0; k < N - 1; ++k) {
                tile(k, i_gl, j_gl, r1, r2, a);
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

    cout << endl;
    for (int i = 0; i < N; i++)
        cout << "x[" << i << "] = " << x[i] << "\n";
    cout << endl << endl;

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

void tile(int k, int i_gl, int j_gl, int r1, int r2, double** matrix) {
    int start_i = max(k+1, 1+i_gl * r1);
    int finish_i = min(1+r1*(1 + i_gl), N);
    int start_j = max(k+1, 1 + j_gl * r2);
    int finish_j = min(1+r2 * (1 + j_gl), N+1);

    cout << "k = " << k << endl
            << "i = [" << start_i << ", " << finish_i << "]" << endl
            << "j = [" << start_j << ", " << finish_j << "]" << endl;
   
    for (int i = start_i; i < finish_i; ++i) {               
        double coef = matrix[i][k] / matrix[k][k];
        for (int j = start_j; j < finish_j; ++j) {
            matrix[i][j] = matrix[i][j] - matrix[k][j] * coef;
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "*******\n\n";
}

double linearGauss(double** a, double* answer) {
    double* x = new double[N];

    cout << setprecision(2);
    for (int i = 0; i < N; i++) {
        if (a[i][i] == 0) {
            for (int j = i + 1; j < N; j++)
                if (a[j][i] != 0) {
                    for (int k = 0; k < N; k++) {
                        double p = a[i][k];
                        a[i][k] = a[j][k];
                        a[j][k] = p;

                    }
                    double p = a[i][N];
                    a[i][N] = a[j][N];
                    a[j][N] = p;
                    break;
                }
        }
    }

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

    cout << endl;
    for (int i = 0; i < N; i++)
        cout << "x[" << i << "] = " << x[i] << "\n";
    cout << endl << endl;

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

void generateInput(double**& matrix, double*& answer) {
    init(matrix);        
    srand(time(0));
    //int c = 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 50;
              cout << matrix[i][j] << " ";
        }
        answer[i] = rand() % 50;
        cout << answer[i] << endl;
    }
    cout << "***\n";
    for (int i = 0; i < N; ++i) {
        matrix[i][N] = 0;
        for (int j = 0; j < N; ++j) {
            matrix[i][N] += matrix[i][j] * answer[j];
        }
        cout << (int)matrix[i][N] << endl;
    }
}

void init(double**& matrix) {
    matrix = new double*[N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new double[N + 1];
    }
}

void clear(double**& matrix) {
    for (int i = 0; i < N; ++i) {
        delete [] matrix[i];
    }
    delete [] matrix;
}

void copyMatrix(double** mat1, double** mat2) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N+1; ++j) {
            mat2[i][j] = mat1[i][j];
        }
    }
}
