//
//  BubblePacking2D.h
//  Yui
//
//  Created by Diego Andrade on 7/26/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#ifndef Yui_BubblePacking2D_h
#define Yui_BubblePacking2D_h

#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>


#include "Common.h"
#include "RungeKutta.h"
#include "BSpline.h"

using namespace std;

//Strores location in U and V
struct PointUVp {
    float u;
    float v;
};


class BubblePacking2D
{
    
    public:
    
    float _mass; // Mass of a bubble for phisical simulation    
    float _damping_force; //Damping force for phisical simulation
    float _spring_rate;  // spring constant for physical simulation k0
    int MAXI;
        
    BubblePacking2D();
    ~BubblePacking2D();
    
    bubble * lo; //boundary
    bubble * l1; //boundary
    bubble * l2; //boundary
    bubble * l3; //boundary
    
  
    
    int Nlo,Nl1, Nl2, Nl3; // number of bubbles per baoundary;
    
    //This function finds the distance between bubbles in each direction
    float findDistanceXDirection(bubble B1, bubble B2, int state);
  
    //This function finds the distance between bubbles
    float findDistanceBetweenBubbles (bubble B1, bubble B2);
    
    float findDistanceBetweenBubblesXYZ(bubble B1, bubble B2);

    
    //This function finds the summation of two radii
    float radiiSum (bubble B1, bubble B2);
    
    //Calculating w parameter for force function
    float wParameter(float distance, float stable_distance);
    
    //Interbubble Force
    float interBubbleForces (float spring_rate, float stable_distance, float w_parameter);
    
    float function2(float t, float v,float fw);
    
    PointUVp Simulation(bubble B1, bubble B2);  
    
    point_t SimulationXYZ(bubble B1, bubble B2);
    
    point_t SimulationXYZ_Vector(bubble B1, bubble B2);
    
    //point_t SimulationXYZVector(bubble B1, bubble B2);
    
    //Function tries to solve runge Kutta for a system of equation
    //RuggeKutta Solution for a set of equations
    float rk4_sol(float initial_point_1D, float time_step, float interbubble_forces); // RungeKutta working function
    
    //This function creates check if a bubble interact with another within a region
    // defined as 1.5 times the radius of the bubble looked upon
    // input: matrix with all the bubbles definitions
    // output: matrix with all the bubbles definitions after interaction 1 step
    void surfaceSimulation (bubble **mBubbles, int IMAX, int JMAX);
    
    //This function checks for the distance between bubbles and the region interest
    // in this case 1.5 times the radius of the bubble looked upon
    // input: the current bubble and all the matrix with all bubble locations
    // output: bubble current location changes
    void  bubbleInteraction (bubble current, bubble** bubbleAll , int IMAX, int JMAX) ;
    
    //Domain subdivision
    void subdivisionHardCode (bubble** P, int IMAX, int JMAX);
    
    //Domain subdivision in real space
    void subdivisionHardCode2 (bubble** P, int IMAX, int JMAX, float distance);


    //Boundaries stae show when a boundary is top, left , bottom, right or  (0-3)
    bubble* bubbleBoundaries (int nOfBubbles, float len, int state);
    
    int AproxSearch(float val, point_t *curve,int numberOfPointsInCurve, int mode);

    point_t * DeltaVector (point_t *V1, point_t *V2, int numberOfPoints);
    
    //Given a vecor and location finds the closest value to calculate the tangent at that location
    point_t Tangent (point_t *V, int numberOfPoints, float x, int state);
    
    //Dot Product for unit vector 3D
    float DotProduct (point_t P1, point_t P2);
    
    //Unit vector
    //float UnitVector (val t);
    

        
    
    
};  // class bubble packing simulation

#endif
