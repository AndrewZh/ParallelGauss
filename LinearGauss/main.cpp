#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

using namespace std;
#define N 3

void generateInput(double**& matrix, double*& answer);
void init(double**& matrix);
void clear(double**& matrix);

int main()
{
	double** a;//[N][N+1];
        double* answer = new double[N];
	double* x = new double[N];
        
        generateInput(a, answer);
	
        cout << setprecision(2);
	for (int i=0; i<N; i++)
	{
		if (a[i][i] == 0)
		{
			for (int j=i+1; j<N; j++)
				if (a[j][i] !=0)
				{
					for (int k=0; k<N; k++)
					{
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
	for (int k = 0; k<N-1; k++)
	{
		for (int i=k+1; i<N; i++)
		{
			for (int j = k+1; j<N+1; j++)
			{
				a[i][j] = a[i][j] - a[i][k]*a[k][j] / a[k][k];
			}
		}
	}
	
        x[N-1] = a[N-1][N]/a[N-1][N-1];
        a[N-1][N-1] = 1;
	for (int i = N-2; i>=0; i--)
	{
		x[i] = a[i][N];
		for (int j=i+1; j<N; j++)
			x[i]-=x[j] * a[i][j]/a[j][j];
                x[i] /= a[i][i];
                a[i][i] = 1;
	}	
	
	cout << endl;
	for (int i=0; i<N; i++)
		cout << "x[" << i << "] = " << x[i] << "\n";
	cout << endl << endl;
        
        bool flag = true;
        for (int i = 0; i < N; ++i) {
            if (x[i] != answer[i]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            cout << "ERROR\n"; 
        } else {
            cout << "OK\n";
        }
        cin.ignore().get();
}

void generateInput(double**& matrix, double*& answer) 
{
    init(matrix);
    srand(time(0));    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 100;
            cout << matrix[i][j] << " ";
        }        
        answer[i] = rand()%100;        
        cout << endl;
    }
    for (int i = 0; i < N; ++i) {
        matrix[i][N] = 0;
        for (int j = 0; j < N; ++j) {
            matrix[i][N] += matrix[i][j] * answer[j];
        }
    }
}
void init(double**& matrix)
{
    matrix = new double*[N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new double[N+1];
    }
}
void clear(double**& matrix)
{
    for (int i = 0; i < N; ++i) {
        delete [] matrix[i];
    }
    delete [] matrix;
}