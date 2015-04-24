#ifndef COMMON_H
#define COMMON_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

#include <omp.h>

#define N 10
#define NUMBER_OF_THREADS 4

using namespace std;

void generateInput(double**& matrix, double*& answer);
void init(double**& matrix);
void clear(double**& matrix);
double linearGauss(double** matrix, double* answer);
double tiledGauss(double** a, double* answer);
double tiledOuterParallelGauss(double** a, double* answer);
double tiledInnerParallelGauss(double** a, double* answer);
void tile(int k, int i_gl, int j_gl, int r1, int r2, double** matrix);
void copyMatrix(double** mat1, double** mat2);
void makeMainElementNotZero(double** matrix);

#endif // COMMON_H
