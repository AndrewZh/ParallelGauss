#include "common.h"

int main() {
    double** working; //[N][N+1];
    double** original;
    double* answer = new double[N];
    cout << setprecision(2);

    ofstream report("results.csv", ios::app);
    //report << "Size, Linear Gauss, Tiled Single Thred, OpenMP(outer), OpenMP(inner)" << endl;

    generateInput(original, answer);
    init(working);
    copyMatrix(original, working);
    
    double linearTime = linearGauss(working, answer);
    report << N << "," << linearTime << ",";

    {
        copyMatrix(original, working);
        double tiledTime = tiledGauss(working, answer);
        report << tiledTime << ",";
    }
    {
        copyMatrix(original, working);
        double outerTime = tiledOuterParallelGauss(working, answer);
        report << outerTime << ",";
    }
    {
        copyMatrix(original, working);
        double innerTime = tiledInnerParallelGauss(working, answer);
        report << innerTime << endl;
    }

    report.close();
    delete [] answer;
    cin.ignore();
}
