//
//  Spline.h
//  Azuka
//
//  Created by Diego Andrade on 5/14/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#ifndef Azuka_Spline_h
#define Azuka_Spline_h

#include "Point2d.h"
#include <vector>


using namespace std;

class Spline{
    
public:
    
    Spline();
    ~Spline();
    
    unsigned int LOD; // level of detail of the curve
    unsigned int NOB; //number of bubbles in the bezier curve
    
    //bubble size
    float _bubble_size;
    
    void draw_spline();
    
    void draw_bezier();
    
    //------------------------------------------------------------	GetPoint()
    // To handle the clamped curves i imagine the curve to have 3 
    // extra control points at the beginning of the curve, and 3 extra
    // at the end. To simply the iteration of the points, i start
    // the indices at -3. Obviously if i use that value as an array
    // index it will crash horribly. Instead i use a function that
    // returns either the first, or last point if the index requested
    // is out of range. This basically simplifies our curve calculation
    // greatly!!
    //
    float* GetPoint(int i) ;
    
    bool sPrint; // Controls when to print Bspline values to txt archive
    
    float* displacement; // holds the information for the bubble displacement at each time step
    
    float Displacement(float ptn1, float ptn2);
    
    void SplinePointsLocation (); //Creates the points in the spline between 2 points 
    
    vector<Point2D> spline_location_2d;
    
    vector<Point2D> bezier_location_2d;
    
    vector<Point2D> bezier_points_location_2d;
    
    vector<Point2D> spline_points;
    
    vector<float> parameter_for_each_bubble_location;
    
    //This functions creates an even distribution for the bubbles between two segments
    vector<Point2D> CreateBubbleLocationSpline();     

    void SplinePrintLocation ();

    //This funtion receives an object to print the bubbles
    void SplinePrintLocation (const vector<Point2D> & location_2d);

    
    // This functions creates the bubbles with a constant diameter
    void createBubble(Point2D ptn,float radius, int state);
    
    // This functions creates the bubbles with a constant diameter and changing color
    void createBubble(float locationx,float locationy, float radius, float color);
    
    // Calculates the lenght of the curve adding the segments on the spline
    float curve_length (vector<Point2D> & spline_location);
    
    //Creates a bezier curve for a set of 4 points based on a LOD of definition
    vector<Point2D> BezierCurveLocation (int LOD);
    
    
    //Creates a bezier curve for a set of 4 points based on a NOP : number of points
    vector<Point2D> BezierInitialPointsLocation (int NOP);

    //Parametric calcualtion of X and Y giveng a value of t
    Point2D XYParametric( float t);

   
};


#endif
