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
struct PointUV {
    float u;
    float v;
};

//This is the bubble data structure
struct bubble {
    int idx; //unique id
    
    float u; //position in the parametric u space (0-1) dependes on the KnotVector  
    float v; //position in the parametric v space (0-1)
    
    PointUV location;
    
    //what level
    int level;
    
    //radius
    float radius;
    
}; //use here number of bubbles inside the geometry




class BubblePacking2D
{
    
    public:
    
    float _mass; // Mass of a bubble for phisical simulation    
    float _damping_force; //Damping force for phisical simulation
    float _spring_rate;  // spring constant for physical simulation k0
        
    BubblePacking2D();
    ~BubblePacking2D();
    
    //This function finds the distance between bubbles
    float findDistanceBetweenBubbles (bubble B1, bubble B2);
    
    //This function finds the summation of two diameters
    float diameterAverage (bubble B1, bubble B2);
    
    //Calculating w parameter for force function
    float wParameter(float distance, float stable_distance);
    
    //Interbubble Force
    float interBubbleForces (float spring_rate, float stable_distance, float w_parameter);
    
    float function2(float t, float v,float fw);
   
    
    
    
};  // class bubble packing simulation

#endif
