#ifndef COMMON_H
#define COMMON_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

#include <omp.h>

#define NUMBER_OF_THREADS 4

using namespace std;

void generateInput(double**& matrix, double*& answer, size_t N);
void init(double**& matrix, size_t N);
void clear(double**& matrix, size_t N);
double linearGauss(double** matrix, double* answer, size_t N);
double tiledGauss(double** a, double* answer, size_t N);
double tiledOuterParallelGauss(double** a, double* answer, size_t N);
double tiledInnerParallelGauss(double** a, double* answer, size_t N);
double oneLoopParallelGauss(double** a, double* answer, size_t N);
double collapseParallelGauss(double** a, double* answer, size_t N);
void tile(int i_gl, int j_gl, int r1, int r2, double** matrix, size_t N);
void copyMatrix(double** mat1, double** mat2, size_t N);
void makeMainElementNotZero(double** matrix, size_t N);

#endif // COMMON_H
