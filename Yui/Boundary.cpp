//
//  Boundary.cpp
//  Yui
//
//  Created by Diego Andrade on 9/4/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#include "Boundary.h"
#include <assert.h>


Boundary::Boundary()
{
    
    numberOfBubbles = 5;
    numberOfControlPoints = 5;
    numberOfPointsInCurveRepresentation = 50;
    
    
    //intialization for point variable used in the nurb curve stores locally the data of a point 
    pts = new float [3];
    pts[0]=pts[1]=pts[2]=0.0;
 
    
}


Boundary::~Boundary()
{
    cout << "Boundary::~Boundary() \n";
    
}

/**
 * \verbatim
 *     ****** Function/NURBS_form_uniform_knots
 * SYNOPSIS
 *  void NURBS_form_uniform_knots(int nctlpts, int order,
 *				              int* nknots, double** knots)
 * PURPOSE
 *  This routine computes a default uniform knot vector for given
 *  number of controlpoints and order. The knot vector will have
 *  order times repeated knots at the ends. Start and end knot
 *  values are 0 and 1.
 * INPUTS
 *  nctlpts  : Number of control points
 *  order    : Order (degree + 1)
 * OUTPUT
 *  nknots   : Number of knots = nctlpts + order
 *  knots    : Uniform knot vector
 * \endverbatim
 */
void Boundary::NURBS_form_uniform_knots(int nctlpts, int order, int* nknots, float** knots)
{
	int		i;
    
	if ((order < 2) || (nctlpts < order)) { *nknots = 0; return; }
	
	*nknots = nctlpts + order;
	*knots = (float*) malloc(sizeof(float)* (*nknots));
	for (i = 0; i < order; i++) (*knots)[i] = 0.0;
	for (i = order; i < nctlpts; i++)
        (*knots)[i] = (float)(i+1-order) / (float)(nctlpts+1-order);
	for (i = nctlpts; i < *nknots; i++) (*knots)[i] = 1.0;
}



/**
 * \verbatim
 *     ****** Function/NURBS_Curve
 * SYNOPSIS
 *     NURBS_curve_t* NURBS_Curve(int npts, int order, double* knots,
 *                                point_t* pts, double* weights)
 * PURPOSE
 *  This routine creates a NURBS curve for given control points, order
 *  and knot vector.
 * INPUTS
 *   npts    : Number of points
 *   order   : order ( = degree + 1) of the curve
 *   pts     : Array of control points
 *   knots   : Knot vector
 *   weights : Weights of control points
 * RETURN VALUE
 *   NURBS curve
 * \endverbatim
 */

 NURBS_curve_t* Boundary::NURBS_Curve(int npts, int order, float *knots, point_t *pts, float *weights)
{
    NURBS_curve_t   *curve;
	int				i, nknots;
    
	curve = (NURBS_curve_t*) malloc(sizeof(NURBS_curve_t));
	
	curve->numControlPoints = npts;
	curve->order = order;
    
	// Knot vector
  	nknots = npts + order;
	curve->knot_vec = (float*) malloc(sizeof(float)*nknots);
	assert(curve->knot_vec != NULL);
	for (i = 0; i < nknots; i++) curve->knot_vec[i] = knots[i];
    
	/* Control points and weights */
  	curve->controlPoints =
    (point_t*) malloc(curve->numControlPoints*sizeof(point_t));
  	assert(curve->controlPoints != NULL);
    
  	curve->weights = (float*) malloc(curve->numControlPoints*sizeof(float));
  	assert(curve->weights != NULL);
    
	for (i = 0; i < npts; i++) {
		curve->controlPoints[i] = pts[i];
  		curve->weights[i] = weights[i];
	}
    
  	return (curve);
    
}


/**
 * \verbatim
 *     ****** Function/NURBS_CurveByControlPoints
 * SYNOPSIS
 *  NURBS_curve_t* NURBS_CurveByControlPoints(int npts, point_t* pts,
 *                                            int order)
 * PURPOSE
 *  This routine creates a NURBS curve of given control points and order.
 * INPUTS
 *   npts : Number of points
 *   pts  : Array of points
 *   order: order ( = degree + 1) of the curve
 * RETURN VALUE
 *   NURBS curve
 * \endverbatim
 */

NURBS_curve_t* Boundary::NURBS_CurveByControlPoints(int npts, point_t* pts, int order)
{
    NURBS_curve_t   *curve;
	float	*knots;
	int		i, nknots;
	
	curve = (NURBS_curve_t*) malloc(sizeof(NURBS_curve_t));
	
	curve->numControlPoints = npts;
	curve->order = order;
    
	// Knot vector
	NURBS_form_uniform_knots(npts, order, &nknots, &knots);
  	curve->knot_vec = knots;
    
	/* allocate storage dynamically for control points and weights*/
  	curve->controlPoints =
    (point_t*) malloc(curve->numControlPoints*sizeof(point_t));
  	assert(curve->controlPoints != NULL);
    
  	curve->weights = (float*) malloc(curve->numControlPoints*sizeof(float));
  	assert(curve->weights != NULL);
    
	for (i = 0; i < npts; i++) {
		curve->controlPoints[i] = pts[i];
  		curve->weights[i] = 1.0;
	}
    
  	return (curve);
    
}



/* ---------------------------------------------- */
/* ---- ptsNURBC: calculate the point on the ---- */
/* ----           NURBS curve                ---- */
/* ---- Coded   : March 13, 1994             ---- */
/* ---- Updated : March 13, 1994             ---- */
/* ---- Author  : YU,TZU-YI  NSF/ERC         ---- */
/* ---------------------------------------------- */
void  Boundary::ptsNURBC(point_t *d, float *weight, float *knot_i, int orderi, int m, float s, float *fp)
{
    
    int lowi, highi;
    int I;
    int which_i, ii;
    float   basis_i[50];
    float   tempx,tempy,tempz,denominator;
    BSPline objBS;
    
    /* ----------- End of Decleration -------------- */
    lowi = orderi - 1 ; highi = m + 1;
    /*
     
     multi = 0 ;  i = m ;
     while ((knot_i[m+1] == knot_i[i]) && (i > (orderi - 1)))
     {
     multi ++ ; i-- ;
     }
     
     I = orderi  - 1 ;
     while ((!((knot_i[I] <= s) && (knot_i[I+1] > s))) && (I < (m+1)))
     I ++  ;
     if (I >= (m+1)) I = (m+1) -  multi - 1 ;
     basis_value(I,s,orderi,knot_i,basis_i) ;
     */
    I = objBS.knotSearch(knot_i,s,lowi,highi);
    objBS.basis_value(I,s,orderi,knot_i,basis_i);
    
    tempx=0.0;tempy=0.0;tempz=0.0;denominator=0.0;
    
    which_i = I - orderi + 1 ;
    
    for (ii=0;ii<orderi;ii++)
    {
        denominator += weight[ii+which_i]* basis_i[ii] ;
        tempx       += weight[ii+which_i]* d[ii+which_i].x * basis_i[ii] ;
        tempy       += weight[ii+which_i]* d[ii+which_i].y * basis_i[ii] ;
        tempz       += weight[ii+which_i]* d[ii+which_i].z * basis_i[ii] ;
    }
    
    fp[0] = tempx/denominator ;
    fp[1] = tempy/denominator ;
    fp[2] = tempz/denominator ;
    
    
}