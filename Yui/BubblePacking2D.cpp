//
//  BubblePacking2D.cpp
//  Yui
//
//  Created by Diego Andrade on 7/26/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#include <iostream>
#include "BubblePacking2D.h"


BubblePacking2D::BubblePacking2D()
{
    
    _mass = 1.0; // Mass of a bubble for phisical simulation    
    _damping_force = 0.7*sqrt( _spring_rate*_mass); //Damping force for phisical simulation
    _spring_rate = 0.1*0.001;// ko 0.1 0.001*0.0001
    
     
    
}

BubblePacking2D::~BubblePacking2D()
{
    
}

float BubblePacking2D::findDistanceBetweenBubbles(bubble B1, bubble B2)
{
    float distance = 0.0;
    
    distance = sqrt(pow((B1.u-B2.u),2)+pow((B1.v-B2.v),2));    
    
    return(distance);
}

float BubblePacking2D::diameterAverage(bubble B1, bubble B2)
{
    float diameter = 0.0;
    
    diameter = (B1.radius + B2.radius)/(float)2;    
    
    return(diameter);
}

float BubblePacking2D::wParameter(float distance, float stableDistance)
{
    float w = 0.0;
    
    w = distance/(float)(stableDistance);
    
    return(w);
}

float BubblePacking2D::interBubbleForces (float spring_rate, float stable_distance, float w_parameter)
{
    float _fw; //Temporal variable with the interbubble force at certain distance
    
    if( w_parameter >= 0 && w_parameter < 1.5)
    {
        _fw = 5/(float)4 * (spring_rate/(float)(stable_distance)) * pow(w_parameter,3) - 
        19/(float)8 * (spring_rate/(float)(stable_distance)) * pow(w_parameter,2) +
        9/(float)8 * (spring_rate/(float)(stable_distance)) ;
    }
    else {
        _fw = 0.0;
    }
    
    //cout << "_fw : " << _fw << endl;
    
    return _fw;
    
}

float BubblePacking2D::function2(float t, float v,float fw)
{
    
    float f = (1/(float)(_mass))*(fw-_damping_force*v);
    
    return (f);
}


