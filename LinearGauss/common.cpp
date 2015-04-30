#include "common.h"

void generateInput(double**& matrix, double*& answer, size_t N) {
    init(matrix, N);        
    srand(time(0));
    //int c = 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 50;
//              cout << matrix[i][j] << " ";
        }
        answer[i] = rand() % 50;
//        cout << answer[i] << endl;
    }
//    cout << "***\n";
    for (int i = 0; i < N; ++i) {
        matrix[i][N] = 0;
        for (int j = 0; j < N; ++j) {
            matrix[i][N] += matrix[i][j] * answer[j];
        }
//        cout << (int)matrix[i][N] << endl;
    }
}

void init(double**& matrix, size_t N) {
    matrix = new double*[N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new double[N + 1];
    }
}

void clear(double**& matrix, size_t N) {
    for (int i = 0; i < N; ++i) {
        delete [] matrix[i];
    }
    delete [] matrix;
}

void copyMatrix(double** mat1, double** mat2, size_t N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N+1; ++j) {
            mat2[i][j] = mat1[i][j];
        }
    }
}

void makeMainElementNotZero(double **a, size_t N) {
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

}

void tile(int k, int i_gl, int j_gl, int r1, int r2, double** matrix, size_t N) {
	int start_i = max(k+1, 1+i_gl * r1);
	int finish_i = min(1+r1*(1 + i_gl), (int)N);
	int start_j = max(k+1, 1 + j_gl * r2);
	int finish_j = min(1+r2 * (1 + j_gl), (int)N+1);
	/*
	cout << "k = " << k << endl
	<< "i = [" << start_i << ", " << finish_i << "]" << endl
	<< "j = [" << start_j << ", " << finish_j << "]" << endl;
	*/   
	for (int i = start_i; i < finish_i; ++i) {               
		double coef = matrix[i][k] / matrix[k][k];
		for (int j = start_j; j < finish_j; ++j) {
			matrix[i][j] = matrix[i][j] - matrix[k][j] * coef;
			//            cout << matrix[i][j] << " ";
		}
		//        cout << endl;
	}
	//    cout << "*******\n\n";

}

void check(char *title, double **a, double *answer, size_t N, double time) {
	double* x = new double[N];

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
        if (abs(x[i] - answer[i]) > EPS) {
            flag = false;
            break;
        }
    }
	cout << title << ":\n";
    if (flag) {
        cout << "\tOK\n";
    } else {
        cout << "\tERROR\n";
		for (int i = 0; i < N; ++i) {
			if (abs(x[i] - answer[i]) > EPS) {
				cout << "\t\t" << i << ": expected " << answer[i] << " got " << x[i] << " - difference = " << abs(x[i] - answer[i]) << endl;
        }
    }
    }
	cout << "\tTime spent " << time << " seconds\n";

	delete [] x;
}
