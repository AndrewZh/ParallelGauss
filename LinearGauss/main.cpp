#include "common.h"

#include <sstream>

int main() {
    double** working; //[N][N+1];
    double** original;
    
    cout << setprecision(4);    

    omp_set_num_threads(NUMBER_OF_THREADS);

	int R1[] = {1};//{1,10, 50, 100};//{1, MAX_N, 1, 2};
	int R2[] = {1};//{1,10, 50, 100};//{MAX_N, 1, 1, 2};

	char* filenames[] = {
		//"reports/2015-05-06/100x100_4_nodes.csv",
		//"reports/2015-05-06/50x50_4_nodes.csv",
		//"reports/2015-05-07/Nx1_4_nodes.csv",
		"reports/2015-05-07/1xN_4_nodes.csv"};
    
    double linearTime;
    int numberOfExperiments = sizeof(R1) / sizeof(*R1);
    for (int experimentNumber = 0; experimentNumber < numberOfExperiments; ++experimentNumber) {
        int r1 = R1[experimentNumber];
        int r2 = R2[experimentNumber];
		
		ofstream report(filenames[experimentNumber], ios::app);
        report << setprecision(4);
        report << "Size,Linear Gauss,Tiled Single,OpenMP(outer),OpenMP(inner),OpenMP(single loop)" << endl;

        for (int N = MIN_N; N <= MAX_N; N += DIFF_N) {
			r2 = N;
			cout << "****\nSize\t" << N << endl;
			cout << "Tile\t" << r1 << "x" << r2 << endl;
			double* answer = new double[N];
			generateInput(original, answer, N);
			init(working, N);
			copyMatrix(original, working, N);

			// don't do it again! linar time depends on N!!!
			//if (experimentNumber == 0) {
			linearTime = linearGauss(working, answer, N);
			//}
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
