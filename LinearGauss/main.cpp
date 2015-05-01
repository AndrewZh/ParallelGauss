#include "common.h"

#include <sstream>

int main() {
    double** working; //[N][N+1];
    double** original;
    
    cout << setprecision(3);    

    omp_set_num_threads(NUMBER_OF_THREADS);

    int R1[] = {1, MAX_N, 1, 2};
    int R2[] = {MAX_N, 1, 1, 2};
    
    double linearTime;
    int numberOfExperiments = sizeof(R1) / sizeof(*R1);
    for (int experimentNumber = 0; experimentNumber < numberOfExperiments; ++experimentNumber) {
        int r1 = R1[experimentNumber];
        int r2 = R2[experimentNumber];
        std::stringstream report_name("report_");
        report_name << r1 << "x" << r2 << ".csv";
        ofstream report(report_name.str().c_str(), ios::trunc);        
        report << setprecision(4);
        report << "Size,Linear Gauss,Tiled Single,OpenMP(outer),OpenMP(inner),OpenMP(single loop)" << endl;

        for (int N = MIN_N; N <= MAX_N; N += DIFF_N) {
            cout << "****\nSize\t" << N << endl;
            double* answer = new double[N];
            generateInput(original, answer, N);
            init(working, N);
            copyMatrix(original, working, N);

            if (experimentNumber == 0) {
                linearTime = linearGauss(working, answer, N);
            }
            report << N << "," << linearTime << ",";

            {
                copyMatrix(original, working, N);
                double tiledTime = tiledGauss(working, answer, N, r1, r2);
                report << tiledTime << ",";
            }
            {
                copyMatrix(original, working, N);
                double outerTime = tiledOuterParallelGauss(working, answer, N, r1, r2);
                report << outerTime << ",";
            }
            {
                copyMatrix(original, working, N);
                double innerTime = tiledInnerParallelGauss(working, answer, N, r1, r2);
                report << innerTime << ",";
            }
            {
                /* copyMatrix(original, working, N);
                 double collapseTime = collapseParallelGauss(working, answer, N, r1, r2);
                 report << collapseTime << ",";*/
            }
            {
                copyMatrix(original, working, N);
                double oneLoopTime = oneLoopParallelGauss(working, answer, N, r1, r2);
                report << oneLoopTime;
            }
            cout << endl;
            report << endl;

            delete [] answer;
            clear(original, N);
            clear(working, N);
        }
        report.close();
    }    
    cin.ignore();
}
