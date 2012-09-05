//
//  Boundary.h
//  Yui
//
//  Created by Diego Andrade on 9/4/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#ifndef __Yui__Boundary__
#define __Yui__Boundary__

#include <iostream>
#include "Point3D.h"
#include "Common.h"
#include "BSpline.h"


typedef struct {
    int numControlPoints;
    int order;
    float *knot_vec;         /* knot vector, size: numControlPoints+order */
    point_t *controlPoints;   /* controlPoints, size: numControlPoints */
    float *weights;          /* weight vector, size: numControlPoints */
} NURBS_curve_t;
/* NOTE: When using this data structure, the library is supposed to
 * dynamically allocate the necessary storage for 'knot_vec', 'controlPoints'
 * and 'weights' since their sizes can not be determined in advance.
 * However, deallocating those dynamically allocated memory is outside of
 * the library routines, up to the interface routines or users.
 * This kind of non-symmetry is inevitable here.
 */


class Boundary
{
    
public:
    
    int numberOfControlPoints;
    int numberOfBubbles;
    
    int numberOfPointsInCurveRepresentation;
    
    float* pts;
    
    Boundary();
    ~Boundary();
    
    //For now the curves are prescribed as NURB curves
    myPoint3D * controlPointsVector [100];
    
    NURBS_curve_t* NURBS_Curve(int npts, int order, float* knots, point_t* pts, float* weights);
    
    NURBS_curve_t* NURBS_CurveByControlPoints(int npts, point_t* pts, int order);
    
    void NURBS_form_uniform_knots(int nctlpts, int order, int* nknots, float** knots);
    
    static void ptsNURBC(point_t *d,float *weight,float *knot_i,int orderi,int m,float s,float *fp);
    
     
    
};  // class creates the boundaries for the given geometry


#endif /* defined(__Yui__Boundary__) */
