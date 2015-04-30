#include "common.h"

int main() {    
    double** working; //[N][N+1];
    double** original;
    
	ofstream report("results.csv", ios::trunc);
    //report << "Size,Linear Gauss,Tiled Single,OpenMP(outer),OpenMP(inner),OpenMP(collapsed),OpenMP(single loop)" << endl;
	report << "Size,Linear Gauss,Tiled Single,OpenMP(outer),OpenMP(inner),OpenMP(single loop)" << endl;

	cout << setprecision(3);
	report << setprecision(4);

	omp_set_num_threads(NUMBER_OF_THREADS);
        
    for (int N = MIN_N; N < MAX_N; N += DIFF_N) {
        cout << "****\nSize\t" << N << endl; 
        double* answer = new double[N];
        generateInput(original, answer, N);
        init(working, N);
        copyMatrix(original, working, N);
        
        double linearTime = linearGauss(working, answer, N);
        report << N << "," << linearTime << ",";

        {
            copyMatrix(original, working, N);
            double tiledTime = tiledGauss(working, answer, N);
            report << tiledTime << ",";
        }
        {
            copyMatrix(original, working, N);
            double outerTime = tiledOuterParallelGauss(working, answer, N);
            report << outerTime << ",";
        }
        {
            copyMatrix(original, working, N);
            double innerTime = tiledInnerParallelGauss(working, answer, N);
            report << innerTime;
        }
        {
           /* copyMatrix(original, working, N);
            double collapseTime = collapseParallelGauss(working, answer, N);
            report << collapseTime;*/
        }
        {
            copyMatrix(original, working, N);
            double oneLoopTime = oneLoopParallelGauss(working, answer, N);
            report << oneLoopTime;
        }
        cout << endl;
        
        delete [] answer;
        clear(original, N);
        clear(working, N);
    }
    report.close();   
    cin.ignore();
}
