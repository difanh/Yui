//
//  BubblePacking.h
//  Keel
//
//  Created by Diego Andrade on 6/24/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#ifndef Keel_BubblePacking_h
#define Keel_BubblePacking_h


#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>

#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <vector>

//#include "Vector2D.h"
#include "Point2d.h"
//#include "Point3d.h"

#include "BubbleDSt.h"
#include "RungeKutta.h"
//#include "AllColor.h"

using namespace std;

//==============================================================================
// macro calls location () with arguments __FILE__ and __LINE__

//#define mLocation Log::location( __FILE__ , __LINE__)
//#define mTimenow Log::timenow()

//==============================================================================

#define PI 4*atan(1)

class BubblePacking
{
    
public:
    vector<Point2D> _working_vector2d;
    // vector<Point3D> _working_vector3d;
    vector<BubbleDSt> _working_BDST_;
    
public:
    vector<Point2D> _location_vector2d;
    
    vector<Point2D> _location_spline;
    
    int counter;
    
    int _number_of_bubbles_v;
    int _number_k;
    float _size_of_bubble;
    float _sphereX;
    float _sphereY;
    
    int _parameter_location;
    float _bubble_size;
    
    float p2 ; // dx/dt = p2
    float p1 ; // p1 = x
    
    float ptn_ini;
    float ptn_last;
    
    int _set_presition; 
    
    vector<float> dp1;
    vector<float> dp2;
    
public:
    float _r_bubble_distance;
    float _ro_stable_bubble_distance;
    
    float _w; // parameter for force function
    
    float _spring_rate;  // spring constant for physical simulation k0
    
    int _max_iteration; // Maximum number of iterations 
    
    float _mass; // Mass of a bubble for phisical simulation    
    float _damping_force; //Damping force for phisical simulation
    float _time_step; //Time needed for the relaxation to work 
    
    int _max_iter_outter; // Maximum number of iteatrion in the outter loop for the bubble smoothing
    
    
    float function2(float t, float x,float fw);
    

    
    
public:
    
    // Constructor 
    BubblePacking();
    
    // Destructor 
    ~BubblePacking();
    
    
     // This function finds the distance between fixed bubbles and free bubbles
    float findDistanceBetweenBubbles (Point2D ptn1, Point2D ptn2);
    float findDistanceBetweenBubbles(float x1, float x2);
   
     //This function finds the summation of two diameters
    float diameter_sum (float dia1, float dia2);
    
    //Calculating w parameter for force function 
    float w_parameter (float distance, float stable_distance);
    
    //Interbubble Force
    float interbubble_force (float spring_rate, float stable_distance, float w_parameter);
    
    //Function tries to solve runge Kutta for a system of equation
    //RuggeKutta Solution for a set of equations
    float rk4_sol(float initial_point_1D, float time_step, float interbubble_forces); // RungeKutta working function
        
    //Calculates the next position for a bubble based upon interbubble forces and current location point
    float LocationCalc ( float _location_point, float _spring_rate, float _h, float _distance_, float _stable_distance_, int state);
    
     //Creates the bubbles simulation (IMPORTANT)
    vector<Point2D>  sixbubble(int state, vector<Point2D> & location_points);
    
    vector<Point2D>  sevenbubble(int state, vector<Point2D> & location_points, int k, float _bubble_size_owner);
    
    vector<Point2D>  eightbubble(int state, vector<Point2D> & location_points, int k, float _bubble_size_owner);
    
    //This funciton calculates the number of bubbles per edge
    float NumberBubbles (float diameter_Xend1, float diameter_Xend2);
    
    //Calculatesthe delta between two vectors express as xi = v1-v2
    vector<Point2D> DeltaXi ( vector<Point2D> & V1, vector<Point2D> & V2);
    
    //Given a vecor and location finds the closest value to calculate the tangent at that location
    Point2D Tangent (vector<Point2D> & V, float x);
    
    //Search the closest index to an entered value mode signals if works for X or Y values
    int AproxSearch (const double val, vector<Point2D> & V, int mode );
    
    //Dot Product for unit vector 2D
    float DotProduct (Point2D & P1, Point2D & P2);
    
    //Delta S in the parametrix space is the amount that s moves 
    float deltaS (Point2D &P1, Point2D &P2);
    
    //Draw lines
    void drawlines(int k);
    
    float function_spacing(float _location);

    
};  // class matrix




#endif
