//
//  BubbleGeometry.h
//  bubble
//
//  Created by diegoandrade on 4/11/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#ifndef bubble_BubbleGeometry_h
#define bubble_BubbleGeometry_h

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

class BubbleGeometry
{

public:
    vector<Point2D> _working_vector2d;
    //vector<Point3D> _working_vector3d;
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
     
    
    vector<float> _Time_solution;  //Time Solution
    
    vector<float>_Integration_Solution_f1_X;
    vector<float>_Integration_Solution_f1_Y;
    vector<float>_Integration_Solution_f2_X;
    vector<float>_Integration_Solution_f2_Y;
    
    vector<float> dp1;
    vector<float> dp2;
    
    float function (float x, float y);
    float function2(float t, float x,float fw);
    
    float** locations;
       
    
public:
    
    // Constructor 
    BubbleGeometry();
   
    // Destructor 
    ~BubbleGeometry();
    
    // Constructor    
    BubbleGeometry(ifstream& inp);
    
    //Creates a bubble with constant geometry
    void createGeometry();
    
    // This function creates the points
    void createPoints();
    
    // This functions creates the bubbles with a constant diameter
    void createBubble(Point2D ptn,float radius);
    
    void createBubble(float x_location, float y_location, float radius, float colorID);
    
    // This functions creates a bubbles in 1D with a constant diameter
    void createBubble(float x_location,float radius);
    
    // This functions creates a bubbles in 1D with a constant diameter
    void createBubble(float x_location,float radius, float colorID);
    
    // This function creates the spacing between bubbles in this case it is based upon locactin parameter
    // 1.0 gives an even dsitribution a higher number gives a number close to the margins 
    void createInterpolation(Point2D ptn1, Point2D ptn2,float location_parameter,int number_of_bubbles);
    
    // This functions creates subdivition of the geometry 
    void createSubdivision();
        
    //Use this function to create the boundary points in a 1D mesh
    void setBoundary (Point2D ptn1, Point2D ptn2);
    
    // Use the logic of  van der Waals
    void MoveBubble ();
    
    // This function finds the distance between two points
    float r_distance (Point2D ptn1,Point2D ptn2);
    
    // This function creates bubbles where the size is
    void bubble_size (float r); 
    
    // This function creates bubbles where the size is a function of the location
    void bubble_size_f (float xi);     
    
    // This function creates bubbles where the size is a function of the location and curvature
    void bubble_size_c (float location, float curvature); 
    
    // This function finds the distance between fixed bubbles and free bubbles
    float findDistanceBetweenBubbles (Point2D ptn1, Point2D ptn2);
    float findDistanceBetweenBubbles (float x1, float x2);
    
    // This function creates a bubble with an ID so it can be tracked
    void bubble_create_2d_id (BubbleDSt obj);
    
    //Initialize Point Location parameter can only be center, random, left, right (1,2,3,4)
    void bubble_location (int parameter);
    
    //This function finds the summation of two diameters
    float diameter_sum (float dia1, float dia2);
    
    //Calculating w parameter for force function 
    float w_parameter (float distance, float stable_distance);
    
    //Interbubble Force
    float interbubble_force (float spring_rate, float stable_distance, float w_parameter);
    
    //Function tries to solve runge Kutta for a system of equation
    //RuggeKutta Solution for a set of equations
    float RungeKuttaSolution(float _p1, float _p2i,float time_step, float fw);
    
    float RungeKuttaSolution2(float _p1, float _p2i,float time_step, float fw);
    
    float rk4 ( float x, float v, float dt);
    
    
    void rk4_sol(); //Working test function
    
    float rk4_sol(float initial_point_1D, float time_step, float interbubble_forces); // RungeKutta working function

 
    void onebubble (); //Creates the bubbles simulation (IMPORTANT)
    
    void twobubble (); //Creates the bubbles simulation (IMPORTANT)

    void threebubble(int k); //Creates the bubbles simulation (IMPORTANT)
    
    void fourbubble(int k); //Creates the bubbles simulation (IMPORTANT)
    
    void fivebubble(vector<Point2D> location_points); //Creates the bubbles simulation (IMPORTANT)

    vector<Point2D>  sixbubble(int state, vector<Point2D> & location_points); //Creates the bubbles simulation (IMPORTANT)
    


    
    void create_line(); //Creates the line that joins the bubbles
    
    void time_step(float** M); //This functions shows the solution one time step at the time
    
public: 
    
    float function_spacing(float _lacation); // Gives the bubbles a size depending the location
    
    void createSplineInterpolation(Point2D ptn1, Point2D ptn2, float location_parameter, int number_of_bubbles);
    
    float LocationCalc ( float _location_point, float _spring_rate, float _h, float _distance_, float _stable_distance_, int state);
    
    
};  // class matrix




#endif
