#include <fstream>
#include <iostream>
#include <iomanip>


using namespace std;
#define N 4

int main()
{
	double a[N][N+1] = {0};
	double x[N] = {0};

	cout << setprecision(2);
	ifstream in;
	in.open("input.txt");

	for (int i=1; i<N; i++) 
	{
		for (int j=1; j<N+1; j++) 
		{
			in >> a[i][j];
			cout << a[i][j] << " ";
		}
	}

	for (int i=1; i<N; i++)
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
	for (int k = 1; k<N-1; k++)
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
	for (int i = N-2; i>0; i--)
	{
		x[i] = a[i][N];
		for (int j=i+1; j<N; j++)
			x[i]-=x[j] * a[i][j]/a[j][j];
                x[i] /= a[i][i];
                a[i][i] = 1;
	}	
	
	cout << endl;
	for (int i=1; i<N; i++)
		cout << "x[" << i << "] = " << x[i] << "\n";
	cout << endl << endl;
        cin.ignore().get();
}
