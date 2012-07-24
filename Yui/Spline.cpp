//
//  Spline.cpp
//  Azuka
//
//  Created by Diego Andrade on 5/14/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>

#include "Spline.h"
#include "BubbleGeometry.h"

#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

using namespace std;

#define NUM_POINTS 5
#define BZ_NUM_POINTS 4

float Points[NUM_POINTS][3] = {
    { 0,-1,0 },
    { 1,1.5,0 },
    { 2.5,2.5,0 },
    {5,1.5,0},
    {6,-1,0}
};

float BPoints[4][2] = {
    { 0,-2,},
    { 2,2.5},
    { 4,2.5},
    {6,3}
};


float	Yellow4[3]	=	{0.545098, 0.545098, 0};
float	SeaGreen1[3]	=	{0.329412, 1, 0.623529};
float	Thistle4[3]	=	{0.545098, 0.482353, 0.545098};
float	LightGoldenrod1[3]=	{1, 0.92549, 0.545098};



/// the number of curve segments required to make the clamped b-spline
/// curve is defined by NUM_POINTS + 1
///
#define NUM_SEGMENTS (NUM_POINTS+1)

#pragma mark ---- User's Objects ----

BubbleGeometry objBBS;

#pragma mark ---- Constructor ----


Spline::Spline()
{
    sPrint = false;
    
  
    
    //Number of bubbles in the curve
    NOB = 10;
    
    // the level of detail for the curve
    LOD= 50;
    
    spline_location_2d = CreateBubbleLocationSpline();
    
    bezier_location_2d = BezierCurveLocation(LOD);
    
    bezier_points_location_2d = BezierInitialPointsLocation(NOB);
    
    _bubble_size = 0.5001;
}

Spline::~Spline()
{
    
}

float* Spline::GetPoint(int i) {
    // return 1st point
    if (i<0) {
        return	Points[0];
    }
    
    if (i<NUM_POINTS)
        return Points[i];
    
    // return last point
    return Points[NUM_POINTS-1];
}

void Spline::draw_spline()
{
    
    
    //ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/BSpline.txt"); //Check is there is a file functionlaity does not exist

    int k = 0;

    //Color Used


  
	// draw curve convex-hull
	glColor3fv(Thistle4);
    glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	for(int i=0;i!=NUM_POINTS;++i) {
		glVertex3fv( Points[i] );
	}
	glEnd();
    

	// begin drawing our curve
    glLineWidth(2);
	glColor3fv(SeaGreen1);    
	glBegin(GL_LINE_STRIP);
    
	// in total i am going to draw (NUM_POINTS+1) curves. I will start
	// the curves at the imaginary index -3. Each section of the curve
	// will start on the next vertex index.
	// 
	for(int start_cv=-3,j=0;j!=NUM_SEGMENTS;++j,++start_cv)
	{
        
               
		// for each section of curve, draw LOD number of divisions
		for(int i=0;i!=LOD;++i) {
            
			// use the parametric time value 0 to 1 for this curve
			// segment.
			float t = (float)i/LOD;
            
			// the t value inverted
			float it = 1.0f-t;
            
			// calculate blending functions for cubic bspline
			float b0 = it*it*it/6.0f;
			float b1 = (3*t*t*t - 6*t*t +4)/6.0f;
			float b2 = (-3*t*t*t +3*t*t + 3*t + 1)/6.0f;
			float b3 =  t*t*t/6.0f;
            
			// calculate the x,y and z of the curve point
			float x = b0 * GetPoint( start_cv + 0 )[0] +
            b1 * GetPoint( start_cv + 1 )[0] +
            b2 * GetPoint( start_cv + 2 )[0] +
            b3 * GetPoint( start_cv + 3 )[0] ;
            
			float y = b0 * GetPoint( start_cv + 0 )[1] +
            b1 * GetPoint( start_cv + 1 )[1] +
            b2 * GetPoint( start_cv + 2 )[1] +
            b3 * GetPoint( start_cv + 3 )[1] ;
            
			float z = b0 * GetPoint( start_cv + 0 )[2] +
            b1 * GetPoint( start_cv + 1 )[2] +
            b2 * GetPoint( start_cv + 2 )[2] +
            b3 * GetPoint( start_cv + 3 )[2] ;
            
			// specify the point
			glVertex3f( x,y,z );
            
            spline_points.push_back(Point2D(x,y)); //Saves all the points of the spline to spline_points used later to calculate curve length
            
		}
        k++;
	}
    
    
    sPrint=false;   
    
	// we need to specify the last point on the curve
	glVertex3fv( Points[NUM_POINTS-1] );
    
    //outfile << "Segment [5]:"<< "POINT (\tX:\t" <<Points[4][0]<< "\tY:\t" <<Points[4][1]<< "\tZ:\t0"<<")"<<endl;  
	glEnd();
    
    
	// draw CV's
    glPointSize(3);
    glColor3fv(Yellow4);
	glBegin(GL_POINTS);
	for(int i=0;i!=NUM_POINTS;++i) {
		glVertex3fv( Points[i] );
	}
	glEnd();
    
   // outfile.close();

    
}

void Spline::draw_bezier()
{
    
    
    //ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/BSpline.txt"); //Check is there is a file functionlaity does not exist
    
    int k = 0;
    
    float x =0.0;
    float y =0.0;
    
    //Color Used
    
    
    
	// draw curve convex-hull
    	glColor3fv(Thistle4);
        glLineWidth(3);
    	glBegin(GL_LINE_STRIP);
    	for(int i=0;i!=BZ_NUM_POINTS;++i) {
    		glVertex2fv( BPoints[i] );
	}
    	glEnd();
        
    
	// begin drawing our curve
    glLineWidth(2);
	glColor3fv(SeaGreen1);    
	glBegin(GL_LINE_STRIP);
    
	// in total i am going to draw (NUM_POINTS+1) curves. I will start
	// the curves at the imaginary index -3. Each section of the curve
	// will start on the next vertex index.
	// 
	       
		// for each section of curve, draw LOD number of divisions
		for(int i=0;i!=LOD;++i) {
            
			x = bezier_location_2d[i].x;
            y = bezier_location_2d[i].y;
            
			// specify the point
			glVertex2f( x,y );
           
            
		}
  
    
    

	//glVertex3fv( Points[NUM_POINTS-1] );
    
    //outfile << "Segment [5]:"<< "POINT (\tX:\t" <<Points[4][0]<< "\tY:\t" <<Points[4][1]<< "\tZ:\t0"<<")"<<endl;  
	glEnd();
    
    
	// draw CV's
    glPointSize(5);
    glColor3fv(Yellow4);
	glBegin(GL_POINTS);
	for(int i=0;i!=BZ_NUM_POINTS;++i) {
		glVertex2fv( BPoints[i] );
	}
	glEnd();
    
    // outfile.close();
    
    
}

float Spline::Displacement(float ptn1, float ptn2)
{
    float tmp = 0.0;
    
    tmp = ptn2 - ptn1;
    
    return tmp;
    
}
 
void Spline::SplinePointsLocation()
{
  
 
  //  vector<Point2D> location;
 
    
    // begin drawing our curve
    //glLineWidth(2);
	//glColor3fv(SeaGreen1);    
	//glBegin(GL_LINE_STRIP);
    //int k=0;
    // in total i am going to draw (NUM_POINTS+1) curves. I will start
	// the curves at the imaginary index -3. Each section of the curve
	// will start on the next vertex index.
	// 
	for(int start_cv=-3,j=0;j!=NUM_SEGMENTS;++j,++start_cv)
	{
       // cout << "hola" << endl;
        
        if (j==3) sPrint=true;
        if (j>4) sPrint=false;

		// for each section of curve, draw LOD number of divisions
		for(int i=0;i!=LOD;++i) {
            
			// use the parametric time value 0 to 1 for this curve
			// segment.
			float t = (float)i/LOD;
            
			// the t value inverted
			float it = 1.0f-t;
            
			// calculate blending functions for cubic bspline
			float b0 = it*it*it/6.0f;
			float b1 = (3*t*t*t - 6*t*t +4)/6.0f;
			float b2 = (-3*t*t*t +3*t*t + 3*t + 1)/6.0f;
			float b3 =  t*t*t/6.0f;
            
			// calculate the x,y and z of the curve point
			float x = b0 * GetPoint( start_cv + 0 )[0] +
            b1 * GetPoint( start_cv + 1 )[0] +
            b2 * GetPoint( start_cv + 2 )[0] +
            b3 * GetPoint( start_cv + 3 )[0] ;
            
			float y = b0 * GetPoint( start_cv + 0 )[1] +
            b1 * GetPoint( start_cv + 1 )[1] +
            b2 * GetPoint( start_cv + 2 )[1] +
            b3 * GetPoint( start_cv + 3 )[1] ;
            
			float z = b0 * GetPoint( start_cv + 0 )[2] +
            b1 * GetPoint( start_cv + 1 )[2] +
            b2 * GetPoint( start_cv + 2 )[2] +
            b3 * GetPoint( start_cv + 3 )[2] ;
            
			// specify the point
			////glVertex3f( x,y,z );
            
            if (sPrint)
            {
               // outfile << "Segment ["<<k<<"]:"<< "POINT (\tX:\t" << x << "\tY:\t" << y << "\tZ:\t"<< z <<")"<<endl;  
               //cout << "Segment ["<<j<<"]:"<< "POINT (\tX:\t" << x << "\tY:\t" << y << "\tZ:\t"<< z <<")"<<endl; 
                
                spline_location_2d.push_back(Point2D(x,y));
                
                //sPrint=false;
            }
            
            
		}
       // k++;
        
         
	}
    
     
    
	// we need to specify the last point on the curve
	//glVertex3fv( Points[NUM_POINTS-1] );
    
  //  cout << "Segment []:"<< "POINT (\tX:\t" <<Points[4][0]<< "\tY:\t" <<Points[4][1]<< "\tZ:\t0"<<")"<<endl;  
	//glEnd();
    
    

    
	// draw CV's
    //glPointSize(5);
    //glColor3fv(LightGoldenrod1);
	//glBegin(GL_POINTS);
	//for(int i=0;i!=NUM_POINTS;++i) {
	//	glVertex3fv( Points[i] );
	//}
	//glEnd();
    
    //return location;
    
  /*  for( int k=0; k<location.size();k++)
    {
        cout << "X["<< k << "]: " << location[k].x << endl;
        
    }
    */
    
    //return (spline_location_2d );
}


vector<Point2D> Spline::CreateBubbleLocationSpline()
{
    vector<Point2D> location;
    
    location.push_back(Point2D(0,-2));

    
    // in total i am going to draw (NUM_POINTS+1) curves. I will start
	// the curves at the imaginary index -3. Each section of the curve
	// will start on the next vertex index.
	// 
	for(int start_cv=-3,j=0;j!=NUM_SEGMENTS;++j,++start_cv)
	{
        if (j==3) sPrint=true;
        if (j>4) sPrint=false;
        
		// for each section of curve, draw LOD number of divisions
		for(int i=0;i!=LOD;++i) {
            
			// use the parametric time value 0 to 1 for this curve
			// segment.
			float t = (float)i/LOD;
            
			// the t value inverted
			float it = 1.0f-t;
            
			// calculate blending functions for cubic bspline
			float b0 = it*it*it/6.0f;
			float b1 = (3*t*t*t - 6*t*t +4)/6.0f;
			float b2 = (-3*t*t*t +3*t*t + 3*t + 1)/6.0f;
			float b3 =  t*t*t/6.0f;
            
			// calculate the x,y and z of the curve point
			float x = b0 * GetPoint( start_cv + 0 )[0] +
            b1 * GetPoint( start_cv + 1 )[0] +
            b2 * GetPoint( start_cv + 2 )[0] +
            b3 * GetPoint( start_cv + 3 )[0] ;
            
			float y = b0 * GetPoint( start_cv + 0 )[1] +
            b1 * GetPoint( start_cv + 1 )[1] +
            b2 * GetPoint( start_cv + 2 )[1] +
            b3 * GetPoint( start_cv + 3 )[1] ;
            
			float z = b0 * GetPoint( start_cv + 0 )[2] +
            b1 * GetPoint( start_cv + 1 )[2] +
            b2 * GetPoint( start_cv + 2 )[2] +
            b3 * GetPoint( start_cv + 3 )[2] ;
            
		
            
            if (sPrint)
            {
               
                
                location.push_back(Point2D(x,y));
                
                
            }
            
            
		}
        
        
        
	}
    
    location.push_back(Point2D(6,-1));

       
    return (location );
    
    
}

void Spline::SplinePrintLocation()
{
    Point2D ptn1(0,0);
    Point2D ptn2(0,1);
    
    //SplinePointsLocation();
    
    for(int i=0;i<spline_location_2d.size();i++)
    {
    
       // cout << "sX : " << _location_vector_spline_2d[i].x << endl;
       // cout << "sY : " << _location_vector_spline_2d[i].y << endl;
       // glutSwapBuffers();
        createBubble(spline_location_2d[i], _bubble_size,0);
        
        
    }
    
    
    
}


void Spline::SplinePrintLocation(const vector<Point2D> & location_2d)
{
    Point2D ptn1(0,0);
    Point2D ptn2(0,1);
    
      
    for(int i=0;i<location_2d.size();i++)
    {
        
        // cout << "sX : " << _location_vector_spline_2d[i].x << endl;
        // cout << "sY : " << _location_vector_spline_2d[i].y << endl;
        // glutSwapBuffers();
        
       // _bubble_size = objBBS.function_spacing(location_2d[i].x);
        
        createBubble(location_2d[i],_bubble_size, 2*0.5001);
        
        
    }
    
    
    
}

void Spline::createBubble(Point2D ptn, float radius, int state)
{
    glPushMatrix(); //Copies the matrix on the top of the stack, this would be like save the funcion
    glColor3f(1,0,1);  //set colour ball
    glTranslatef(0.0, 0.0 , 0.0); // back to origin
    glTranslatef(ptn.x, ptn.y, 0.0);
    
    float   HotPink1[3]	=	{1, 0.431373, 0.705882};

    float	HotPink2[3]	=	{1, 0.2, 0.0012341};
    
    
    float x,y;
    
    glLineWidth(1);
    
    glBegin(GL_LINES); 
    if (state==0) glColor3fv(HotPink1);
    if (state==1) glColor3fv(HotPink2);

    
    x = (float)radius * cos(359*PI/180.0f);
    y = (float)radius * sin(359*PI/180.0f); 
    
    for (int j=0; j<360; j++)
    {
        glVertex2f(x, y);
        
        x = (float)radius * cos(j*PI/180.0f);
        
        y = (float)radius * sin(j*PI/180.0f); 
        
        glVertex2f(x, y);
    }
    
    
    //cout << "PI Value = " << PI << endl;
    
    glEnd();
    glPopMatrix(); // Would be equivalent like load the function 
}


void Spline::createBubble(float locationx, float locationy, float radius, float colorID)
{
    
    glPushMatrix(); //Copies the matrix on the top of the stack, this would be like save the funcion
    glColor3f(1,0,1);  //set colour ball
    glTranslatef(0.0, 0.0 , 0.0); // back to origin
    glTranslatef(locationx, locationy, 0.0);
    
    
   float	colorUSER[3]	=	{1-colorID, 0.45-colorID, colorID};
    
    
    float x,y;
    
    glLineWidth(1);
    
    glBegin(GL_LINES); 
    glColor3fv(colorUSER);
    
    x = (float)radius * cos(359*PI/180.0f);
    y = (float)radius * sin(359*PI/180.0f); 
    
    for (int j=0; j<360; j++)
    {
        glVertex2f(x, y);
        
        x = (float)radius * cos(j*PI/180.0f);
        
        y = (float)radius * sin(j*PI/180.0f); 
        
        glVertex2f(x, y);
    }
    
     
    glEnd();
    glPopMatrix(); // Would be equivalent like load the function
    
}


float Spline::curve_length( vector<Point2D> & spline_)
{
    
    float length;
    
    for (int i=1;i<spline_.size();i++)
    {
        length += sqrt(pow((spline_[i].x-spline_[i+1].x),2)+pow((spline_[i].y-spline_[i+1].y),2));
    }
    
    return length;
    
    
}

vector<Point2D> Spline::BezierCurveLocation(int LOD)
{
    vector<Point2D> BezierCurvePoints;
    
    ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/BezierCurve.txt"); //Check is there is a file functionlaity does not exist

    
    //Temporal values for x and y
    float x = 0.0;
    float y = 0.0;
    
    float t;
    
    //Parametric curve 
    for(int i=0;i<LOD;i++)
    {
        t = i/(float)(LOD-1);
        
        x =  BPoints[0][0]+3*t*(BPoints[1][0]-BPoints[0][0])+3*t*t*(BPoints[0][0]+BPoints[2][0]-2*BPoints[1][0])+t*t*t*
        (BPoints[3][0]-BPoints[0][0]+3*BPoints[1][0]-3*BPoints[2][0]);
        
        y =  BPoints[0][1]+3*t*(BPoints[1][1]-BPoints[0][1])+3*t*t*(BPoints[0][1]+BPoints[2][1]-2*BPoints[1][1])+t*t*t*
        (BPoints[3][1]-BPoints[0][1]+3*BPoints[1][1]-3*BPoints[2][1]);
        
        BezierCurvePoints.push_back(Point2D(x,y));
        
        outfile << "X: " << BezierCurvePoints[i].x << "\t" << "Y: " << BezierCurvePoints[i].y << endl;
        
        
    }
    outfile.close();
    
    
    return BezierCurvePoints;
}



vector<Point2D> Spline::BezierInitialPointsLocation(int NOB)
{
    vector<Point2D> BezierBubblePoints;
    
    
    ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/BezierCurveNOP.txt"); //Check is there is a file functionlaity does not exist
    
    
    //Temporal values for x and y
    float x = 0.0;
    float y = 0.0;
    
    float t;
    
    BezierBubblePoints.push_back(Point2D(0,-2));
    parameter_for_each_bubble_location.push_back(0);
    
    //Parametric curve 
    for(int i=1;i<NOB-1;i++)
    {
        t =  i/(float)(NOB-1); //0.5
        
        x =  BPoints[0][0]+3*t*(BPoints[1][0]-BPoints[0][0])+3*t*t*(BPoints[0][0]+BPoints[2][0]-2*BPoints[1][0])+t*t*t*
        (BPoints[3][0]-BPoints[0][0]+3*BPoints[1][0]-3*BPoints[2][0]);
        
        y =  BPoints[0][1]+3*t*(BPoints[1][1]-BPoints[0][1])+3*t*t*(BPoints[0][1]+BPoints[2][1]-2*BPoints[1][1])+t*t*t*
        (BPoints[3][1]-BPoints[0][1]+3*BPoints[1][1]-3*BPoints[2][1]);
        
        BezierBubblePoints.push_back(Point2D(x,y));
        
        outfile << "X: " << BezierBubblePoints[i].x << "\t" << "Y: " << BezierBubblePoints[i].y ;
        
        parameter_for_each_bubble_location.push_back(t);
        
        outfile << "\t: " << parameter_for_each_bubble_location[i] <<endl;
        
    }
    
   
    BezierBubblePoints.push_back(Point2D(6,3));
    parameter_for_each_bubble_location.push_back(1);
    
    
    outfile.close();
    
    
    return BezierBubblePoints;
}


Point2D Spline::XYParametric(float t)
{
    Point2D temp(0.0,0.0);
    
    temp.x =  BPoints[0][0]+3*t*(BPoints[1][0]-BPoints[0][0])+3*t*t*(BPoints[0][0]+BPoints[2][0]-2*BPoints[1][0])+t*t*t*
    (BPoints[3][0]-BPoints[0][0]+3*BPoints[1][0]-3*BPoints[2][0]);
    
    temp.y =  BPoints[0][1]+3*t*(BPoints[1][1]-BPoints[0][1])+3*t*t*(BPoints[0][1]+BPoints[2][1]-2*BPoints[1][1])+t*t*t*
    (BPoints[3][1]-BPoints[0][1]+3*BPoints[1][1]-3*BPoints[2][1]);
    
    return(temp);
}
