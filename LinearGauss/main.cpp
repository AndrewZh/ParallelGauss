#include "common.h"

int main() {    
    double** working; //[N][N+1];
    double** original;
    
    cout << setprecision(2);

    ofstream report("results.csv", ios::trunc);
    report << "Size,Linear Gauss,Tiled Single,OpenMP(outer),OpenMP(inner),OpenMP(collapsed),OpenMP(single loop)" << endl;
        
    for (int N = 100; N < 3000; N += 100) {
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
            report << innerTime << endl;
        }
        {
            copyMatrix(original, working, N);
            double collapseTime = collapseParallelGauss(working, answer, N);
            report << collapseTime << endl;
        }
        {
            copyMatrix(original, working, N);
            double oneLoopTime = oneLoopParallelGauss(working, answer, N);
            report << oneLoopTime << endl;
        }
        
        delete [] answer;
        clear(original, N);
        clear(working, N);
    }
    report.close();   
    cin.ignore();
}
