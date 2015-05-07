#ifndef COMMON_H
#define COMMON_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <string>

#include <omp.h>

#define NUMBER_OF_THREADS 4
#define EPS 10e-4

#define MIN_N 100
#define MAX_N 3000
#define DIFF_N 100

#define RESULT_FILE "reports/2015-05-06/100x100_4_nodes.csv"

using namespace std;

void generateInput(double**& matrix, double*& answer, size_t N);
void init(double**& matrix, size_t N);
void clear(double**& matrix, size_t N);

double linearGauss(double** matrix, double* answer, size_t N);
double tiledGauss(double** a, double* answer, size_t N, int r1, int r2);
double tiledOuterParallelGauss(double** a, double* answer, size_t N, int r1, int r2);
double tiledInnerParallelGauss(double** a, double* answer, size_t N, int r1, int r2);
double oneLoopParallelGauss(double** a, double* answer, size_t N, int r1, int r2);
double collapseParallelGauss(double** a, double* answer, size_t N, int r1, int r2);

void tile(int k, int i_gl, int j_gl, int r1, int r2, double** matrix, size_t N);
void copyMatrix(double** mat1, double** mat2, size_t N);
void makeMainElementNotZero(double** matrix, size_t N);

void check(std::string title, double **a, double *answer, size_t N, double time);

#endif // COMMON_H
