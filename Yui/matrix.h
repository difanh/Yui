/*!
    \file       matrix.h
    \modified	02/10/06
    \copyright  (c) Diego F Andrade (diegoandrade@gmail.com)
    \licence    GPL
    \brief      Describes matrix class
    \author     Diego F Andrade
    \date	02/10/06
 */

//This is the regular C/C++ define that ensures the compiler will include the stuff in this .h header file only once, over the course of the //compilation. It is of the format shown: this header file's filename in all capitals, with .h replaced as _H, with underscores at each end.

//----------------------------------------------------------------------------------------
// Inclusion simple del archivo .h
//----------------------------------------------------------------------------------------

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>	// Directiva de preprocesamiento para entraaada y salida de datos //Pre-proccessor directive for input - output
#include <iomanip>	
#include <cmath>	// Libreria matematica		//Math library
#include <cstdio>
#include <fstream>

using namespace std;

class Matrix
{
public:
	Matrix();		//Constructor
	virtual ~Matrix();	//Destructor
	double pi;

	int i,j,k;	//Contadores

	double** K (int col,int row);
	double* f (int row);
	double* d (int row);

	double* mult (double** A, double* p, int imax);
	double vectorProduct (double *x, double* y, int imax);
	bool cgDone (double*r, double e, int imax);
	bool isPositiveDefinite (double** A, int imax);
	bool isSymmetric (double** A, int imax);
	double getDet (double** mat, int imax);
	double* cg (double** A, double* b, double* x, int imax, double eps, int niter);
	double** getArray(double** mat, int n, int col);

	double** crearM(int SIZE);	//Crea una matriz cuadrada de tamano size
 	double* crearV(int SIZE);	//Crea un vector de tamano size
    
    double** crearM(int IMAX, int JMAX);	//Crea una matriz cuadrada de tamano size

	void print(double** A, double* b, int imax);
	void print(double** A, int imax);
	void print(double** A, double* b, double* temp, int imax, char* file);
    void printVector (double* b, int imax, char* file);

	double norm (double* V, double* V1, int imax);

	double* GaussElimin (double** A, double* b, int imax);
	double** LUFactorization (double** A, int imax);

	
};

#endif  //_MATRIX_H_
