#include <fstream>
#include <iostream>
#include <iomanip>


using namespace std;
#define N 4

void main()
{
	double a[N][N][N] = {0}, b[N][N] = {0}; // основна€ матрица и столбец свободных членов со всеми модификаци€ми
	double c[N][N] = {0}, q[N] = {0}; // матрица, получена€ после пр€мого хода метода √аусса
	double x[N] = {0}; // столбец решени€
	double detA = 1; // определитель основной матрицы
	double r[N] = {0}; // вектор нев€зки
	double a1[N][N] = {0}; // обратна€ матрица к основной

	cout << setprecision(2);
	ifstream in;
	in.open("input.txt");

	for (int i=1; i<N; i++) // считывание матрицы
	{
		for (int j=1; j<N; j++) 
		{
			in >> a[i][j][0];
			cout << a[i][j][0] << " ";
		}
		in >> b[i][0];
		cout << b[i][0] << endl;
	}

	for (int i=0; i<N; i++) // начальные значени€ вспомогательных элементов
		c[i][i] = 1;
	for (int i=1; i<N; i++)
		for (int j=0; j<N; j++)
			a[j][j][i] = 1;

	for (int i=1; i<N; i++) // переставл€ем строки, чтобы ведущий элемент не был нулевым
	{
		if (a[i][i][0] == 0)
		{
			detA*=-1;
			for (int j=i+1; j<N; j++)
				if (a[j][i][0] !=0)
				{
					for (int k=0; k<N; k++)
					{
						double p = a[i][k][0];
						a[i][k][0] = a[j][k][0];
						a[j][k][0] = p;
						
					}
					double p = b[i][0];
					b[i][0] = b[j][0];
					b[j][0] = p;
					break;
				}
		}
	}
	for (int k = 1; k<N-1; k++) // вычисление коэффициентов
	{
		for (int i=k+1; i<N; i++)
		{
			for (int j = k+1; j<N; j++)
			{
				c[k][j] = a[k][j][k-1] / a[k][k][k-1];
				a[i][j][k] = a[i][j][k-1] - a[i][k][k-1]*c[k][j];
			}
		}
		q[k] = b[k][k-1]/a[k][k][k-1];
		for (int i=k+1; i<N; i++)
			b[i][k] = b[i][k-1] - a[i][k][k-1]*q[k];
	}
	q[N-1] = b[N-1][N-2] / a[N-1][N-1][N-2];

	x[N-1] = q[N-1];	
	for (int i = N-2; i>0; i--) // нахождение решени€ системы линейных уравнений
	{
		x[i] = q[i];
		for (int j=i+1; j<N; j++)
			x[i]-=c[i][j]*x[j];
	}	
	
	cout << endl;
	for (int i=1; i<N; i++)
		cout << "x[" << i << "] = " << x[i] << "\n";
	cout << endl << endl;
	
	bool flag = true;
	for (int i=1; i<N; i++) // проверка решени€ системы
	{
		double p = 0;
		for (int j=1; j<N; j++)
			p+=a[i][j][0]*x[j];
		if (p - b[i][0] > 10e-4) {
			flag = false;
		}
	}
	if (flag)
		cout << "OK" << endl;
	else 
		cout << "ERROR" << endl;
	system("pause");

}



