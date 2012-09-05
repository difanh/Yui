//
//  BSpline.h
//  Nerv
//
//  Created by Diego Andrade on 7/17/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//
// These procedures and functions were based on THE BURBS BOOK, Springer 1997


#ifndef Nerv_BSpline_h
#define Nerv_BSpline_h

#include <vector>
#include "Point2d.h"
#include "Point3d.h"
#include "Common.h"
using namespace std;



class BSPline{
    
public:
    
    // Constructor 
    BSPline();
    
    // Destructor 
    ~BSPline();
    
    vector< vector<myPoint3D> > controlPoints;
    float*  Nu ;
    float*  Nv;
    
   
    myPoint3D ** controlPointsArray;
    
     float ** controlPointsWeightsArray;
    
    float* pts;
    
    //myPoint3D ** controlPointsArray;

    //Determines the Knot span index
    int findSpan (int n, int p, float u, float* U);

    //Basis functions
    float*  basisFuns (int i, float u, int p, float* U);
    
    float*  basisFuns (int p,  int n, float u, float* U);
    
    //BSPLINE Surface Point
    myPoint3D surfacePoint (int n, int p, float* U,
                          int m, int q, float* V,
                          myPoint3D** P, float u, float v);
    
    //initialize control Point matrix
    void InitializeControlPoints();
    
    //Row Vector N(k,p) X Matrix P(k,l)
   // vector<Point2D>  matrixVectorMult (
    
    static int knotSearch (float *knot, float s, int low, int high);
    
    static void basis_value(int left,float u,int order,float *knot,float *basis);
    
    float* Uknot;
    
    float* Vknot;
    
    static void ptsNURBS(myPoint3D** P,float **weight,float *knot_i,
                         float *knot_j,int orderi,int orderj,
                         int m,int n,float s, float t,float* pts);
    
    static void ptsNURBS(point_t *d,float *weight,float *knot_i,
                         float *knot_j,int orderi,int orderj,
                         int m,int n,float s, float t,float *pts);
        
    
    
    
};





#endif
