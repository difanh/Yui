/*!
    \file       matrix.cpp
    \modified	02/15/06
    \copyright  (c) Diego F Andrade (diegoandrade@gmail.com)
    \licence    GPL
    \brief      matrix class implementation
    \author     Diego F Andrade
    \date	02/13/06
 */

#include "matrix.h"

//const double pi = 4*atan(1); // Constant value for PI
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Matrix::Matrix()
{
	
}

Matrix::~Matrix() 
{
	
}

//Inizialize a square matrix of SIZE
double** Matrix::crearM(int SIZE)
{
	double **M = new double * [SIZE];
	for(i=0;i<SIZE;i++){
		M[i] = new double  [SIZE];
		for(j=0;j<SIZE;j++){
			M[i][j] = 0.0;
			//M[i][j] = M[i][j];
		}
		
	}

	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			M[i][j] = M[j][i];
		}
		
	}
	return M;
}

double** Matrix::crearM(int IMAX, int JMAX)
{
    double **M = new double * [IMAX];
	for(i=0;i<IMAX;i++){
		M[i] = new double  [JMAX];
		for(j=0;j<JMAX;j++){
			M[i][j] = 0.0;
		}
		
	}
    
    return M;
    
}


//Inizialize a vector de tamano SIZE
double* Matrix::crearV(int SIZE)
{
	double * V = new double [SIZE];
	for(j=0;j<SIZE;j++){
			V[j] = 0.0;
		}
	return V;
}

//Imprime los valores de la matriz A y el vector b en un archivo file
void Matrix::print (double** A, double* b, double* temp, int imax, char* file)
{
	ofstream sol_01 (file);
	
	sol_01 << "\n Matrix A";
	sol_01 << "\n -------------------------" << endl << endl;
	for(int i=0;i<imax;i++){
		for(int j=0;j<imax;j++){
		sol_01 << A[i][j] << "\t";
		}
	sol_01 <<"\n";
	}
			
	sol_01 << "\n Vector b";
	sol_01 << "\n -------------------------" << endl << endl;
	for(int i=0;i<imax;i++){
		sol_01 << b[i]<<endl;
	}

	sol_01 << "\n Vector x";
	sol_01 << "\n -------------------------" << endl << endl;
	for(int i=0;i<imax;i++){
		sol_01 << temp[i]<<endl;
	}

	sol_01.close();
}

//Imprime los valores de la matriz A y el vector b en pantalla
void Matrix::print (double** A, double* b, int imax)
{
	cout << "\n Matrix A" << endl << endl;
	for(int i=0;i<imax;i++){
		for(int j=0;j<imax;j++){;
		cout << A[i][j] << "\t";
		}
	cout<<"\n";
	}
			
	cout << "\n Vector b" << endl << endl;
	for(int i=0;i<imax;i++){
		cout << b[i]<<endl;
	}
}

//Imprime los valores de la matriz A  en pantalla
void Matrix::print (double** A, int imax)
{
	cout << "\n Matrix A" << endl << endl;
	for(int i=0;i<imax;i++){
		for(int j=0;j<imax;j++){;
		cout << A[i][j] << "\t";
		}
	cout<<"\n";
	}
}



/*** Compute Ap ***/
double* Matrix::mult (double** A, double* p, int imax)
{
	double * result = new double [imax];
	for(int i=0; i<imax; i++)
	{
		result[i] = 0.0;
		for(int j=0; j<imax; j++)
			result[i] += A[i][j] * p[j];
	}

	return result;	
}

/*** Product of two vectors ***/
double Matrix::vectorProduct (double *x, double* y, int imax)
{
	double product = 0.0;
	for(int i=0; i<imax; i++)
		product += x[i]*y[i];
	return product;
}

/*** Is CG done ? ***/
bool Matrix::cgDone (double*r, double e, int imax)
{
	for(int i=0; i<imax; i++)
		if(fabs(r[i]) > e)  
			return false;
	return true;
}

/*** Is the Matrix Positive Definite ***/
bool Matrix::isPositiveDefinite (double** A, int imax)
{
	double** mat;
	double temp = 0.0;
	for(int i=1; i<=imax; i++)
	{
		mat = new double*[i];
		for(int j=0; j<i; j++)
		{
			mat[j] = new double[i];
			for(int k=0; k<i; k++)
				mat[j][k] = A[j][k];
		}

		if(getDet(mat, i) < 0)
			return false;
	}
	
	return true;
}

/*** Is this matrix Symmetric ***/
bool Matrix::isSymmetric (double** A, int imax)
{
	for(int i=0; i<imax; i++)
	{
		for(int j=0; j<i; j++)
			if(A[i][j] != A[j][i])
				return false;
	}
	return true;
}

/*** Compute the Determinant of a given array ***/
double Matrix::getDet (double** mat, int imax)
{
	if(imax == 1)
		return mat[0][0];

	if(imax == 2)
		return (mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0]);

	double** temp;
	double tempDet = 0.0;
	double det = 0.0;

	for(int i=0; i<imax; i++)
	{
		temp = getArray(mat, imax, i);
		tempDet = mat[0][i]*getDet(temp, imax-1);
		if(i%2 == 0)
			det += tempDet;
		else
			det -= tempDet;
			
	}
	
	return det;
}

/*** Gauss Elimination forward-row***/
double* Matrix::GaussElimin (double** A, double* b, int imax)
{
	double* x = crearV(imax);	
	x[0] = b[0]/A[0][0];
	
	for(i=0;i<imax;i++){
		for(j=i+1;j<imax;j++){
			x[i] = (double)(b[i]-A[i][j]*x[j])/(double)(A[i][i]);
		}
	}	

	

	return x;
}

/*** LU Factorization***/
double** Matrix::LUFactorization (double** A, int imax)
{
	double** S = crearM(imax);
	
	for (i=0;i<imax;i++){
		for(j=0;j<imax;j++){
		S[i][j] = A[i][j];
		}
	}

	for (k=0;k<imax;k++){
		for(j=k;j<imax;j++){
		S[k][j]=S[k][j]/S[k][k];
			for(i=k+1;i<imax;i++){
				S[i][j]=S[i][j]-S[i][k]*S[k][j];
			}
		}
	}
	
	/*for (j=0;j<imax;j++){
		for(k=0;k<j-1;k++){
			for(i=k+1;i<imax;i++){
				M[i][j]=A[i][j]-A[i][k]*A[k][j];
			}
		}
		for(i=j+1;i<imax;i++){
		A[i][j]=A[i][j]/A[j][j];
		}
	}*/
	
	return S;		
}


/*** Get a Minor Array for a given array ***/

double** Matrix::getArray(double** mat, int imax, int col)
{
	double** temp = new double*[imax-1];
	int k;
	for(int i=1; i<imax; i++)
	{
		temp[i-1] = new double[imax-1];
		k = 0;
		for(int j=0; j<imax; j++)
		{
			if(j == col)
				continue;
		
			temp[i-1][k++] = mat[i][j];
		}
	}
	
	return temp;
}

double Matrix::norm(double* vec, double* vec1, int imax)
{
	double norm = 0.0;
	for(int i=0; i<imax; i++)
		norm += vec[i]*vec1[i];
	return (double) sqrt (norm);
}

/*** Solve CG ***/
double*  Matrix::cg (double** A, double* b, double* x, int imax, double eps, int niter)
{
	double * temp = new double [imax];

	double* diPrev = new double[imax];
	double* diNext = new double[imax];
	double* riPrev = new double[imax];	
	double* riNext = new double[imax];
	double* xiPrev = new double[imax];
	double* xiNext = new double[imax];

	double* piPrev = new double[imax];
	double* piNext = new double[imax];

	

	if(!isSymmetric (A,imax))
	{
		cout << "This matrix is not Symmetric !" << endl;
		cout << "Returning .." << endl;
		//return ;
	}
	
	temp = mult(A,x,imax);

	for(i=0;i<imax;i++){
	riPrev[i] = b[i]-temp[i];
	piPrev[i] = riPrev[i];	
	}

	double alfa =0.0;
	double beta =0.0;

	int k=0;
	while (k<niter)
	{
	temp = mult(A,riPrev,imax);

	alfa = vectorProduct (piPrev,riPrev,imax)/ vectorProduct (piPrev,temp,imax);
	
	for(i=0;i<imax;i++){
	xiNext[i] = xiPrev[i]+alfa*piPrev[i];
	riNext[i] = riPrev[i]-alfa*temp[i];
	}
	
	beta = vectorProduct(temp,riNext,imax)/vectorProduct(temp,riPrev,imax);

	for(i=0;i<imax;i++){
	piNext[i] = riNext[i] - beta*piPrev[i];
	piPrev[i] = piNext[i];
	riPrev[i] = riNext[i];
	}
	cout<< "\n" << k  ;
	k++;
	}

	cout<< "alfa:"<<alfa;
	cout<< "beta:"<<beta;

	return piNext;
	

}





