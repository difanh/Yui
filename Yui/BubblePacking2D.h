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

#include "RungeKutta.h"

using namespace std;


#define PI 4*atan(1)

//Strores location in U and V
struct PointUVp {
    float u;
    float v;
};

//This is the bubble data structure
struct bubble {
    int idx; //unique id
    
    float u; //position in the parametric u space (0-1) dependes on the KnotVector  
    float v; //position in the parametric v space (0-1)
    
   // PointUVp location;
    
    //what level
   // int level;
    
    //radius
    float radius;
    
}; //use here number of bubbles inside the geometry




class BubblePacking2D
{
    
    public:
    
    float _mass; // Mass of a bubble for phisical simulation    
    float _damping_force; //Damping force for phisical simulation
    float _spring_rate;  // spring constant for physical simulation k0
    int MAXI;
        
    BubblePacking2D();
    ~BubblePacking2D();
    
    //This function finds the distance between bubbles in each direction
    float findDistanceXDirection(bubble B1, bubble B2, int state);
  
    //This function finds the distance between bubbles
    float findDistanceBetweenBubbles (bubble B1, bubble B2);
    
    //This function finds the summation of two radii
    float radiiSum (bubble B1, bubble B2);
    
    //Calculating w parameter for force function
    float wParameter(float distance, float stable_distance);
    
    //Interbubble Force
    float interBubbleForces (float spring_rate, float stable_distance, float w_parameter);
    
    float function2(float t, float v,float fw);
    
    PointUVp Simulation(bubble B1, bubble B2);
    
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

    

   
    
    
    
};  // class bubble packing simulation

#endif
