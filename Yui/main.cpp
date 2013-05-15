// ----------------------------------------------------------------------------
/**
 File: main.cpp
 
 System:         YUI
 Component Name: Carnegie Mellon University
 Status:         Version 1.0 Release 1
 Language: C++
 
 License: GNU Public License
 Licensed Material - Property of CERLAB (Carnegie Mellon Univerisity)
 
 (c) Copyright Carnegie Mellon Univerisity 2012
 
 Address:
 Carnegie Mellon University
 5000 Forbes Avenue Pittsburgh, PA 15213
 
 Author: Diego F Andrade    
 E-Mail: diegoandrade@gmail.com
 
 Description: Header file for Project X
 This file contains the defined types for Project X
 This is sometimes called the "Abstract" and may be
 followed by a section called "Notes".
 
 Limitations: bla bla bla
 
 Function: 1) bla bla bla
 2) bla bla bla
 3) bla bla bla
 
 Thread Safe: No
 
 Extendable: No
 
 Platform Dependencies: OSX
 
 Compiler Options: No

 */
// ----------------------------------------------------------------------------




//
//  main.cpp
//  Yui
//
//  Created by Diego Andrade on 6/13/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//



//Includes for system classes
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Includes for costume classes
#include "Common.h"
#include "trackball.h"
#include "SurfaceGeometry.h"
#include "BubbleGeometry.h"
#include "RungeKutta.h"
#include "Euler.h"
#include "Spline.h"
#include "BubblePacking.h"
#include "BSpline.h"
#include "Subdivision.h"
#include "BubblePacking2D.h"
#include "Util.h"

//#include "AllColor.h"


/*
 Costume #define pre-processor directives
 */

#define DTOR 0.017453925
#define CROSSPROD(p1,p2,p3) \
p3.x = p1.y*p2.z - p1.z*p2.y; \
p3.y = p1.z*p2.x - p1.x*p2.z; \
p3.z = p1.x*p2.y - p1.y*p2.x


#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#define HEIGHT 600
#define WIDTH 800

/*
 Open Gl Variables
 */
GLint gDollyPanStartPoint[2] = {0, 0};
//static GLint snowman_display_list;

GLuint gPointList = NULL;
GLuint gWireList = NULL;
GLuint gSolidList = NULL;

GLfloat gfDeltaX = .01;
GLfloat gfPosX = 0.0;
GLfloat gShapeSize = 11.0f;
GLfloat gTrackBallRotation [4] = {0.0, 0.0, 0.0, 0.0};
GLfloat gWorldRotation [4] = {180, 0.0, 1.0, 0.0}; //{155.0, 0.0, -1.0, 0.0};

GLboolean gDolly = GL_FALSE;
GLboolean gPan = GL_FALSE;


GLboolean gShowHelp = GL_TRUE;
GLboolean gShowInfo = GL_TRUE;
GLboolean gShowSplineControlPoints = GL_TRUE;
GLboolean gTrackBall = GL_FALSE;
GLboolean gVectorSimulation = GL_FALSE; //shows the vector simulation
GLboolean GgShowBoundariers = GL_FALSE; //shows the vector simulation

GLboolean sSimulationInBSplinePatch= GL_FALSE;
GLboolean sSimulationInternalBSplinePatch= GL_FALSE;
GLboolean sFlag=GL_TRUE;

static GLboolean WIRE=0;		// draw mesh in wireframe?

int gLastKey = ' ';
int gMainWindow = 0;
int k_loop=0;
int kinternal_loop=0;
int IMAX = 6;
int JMAX = 6;
int number_of_bubbles = IMAX; //(int) (distance_geometry)/(int) IMAX *2;

int numberOfBubblesl0 = NUMBER_OF_BUBBLES_L0; //bottom boundary
int numberOfBubblesl1 = NUMBER_OF_BUBBLES_L1; //bottom boundary
int numberOfBubblesl2 = NUMBER_OF_BUBBLES_L2; //bottom boundary
int numberOfBubblesl3 = NUMBER_OF_BUBBLES_L3; //bottom boundary



float a=HEIGHT;
float b=WIDTH;

float distance_geometry =4.48386; //here measure the correct circumference / lenght
float nodeformationRadius = distance_geometry/(float)number_of_bubbles*0.5; //here change
float initialBubbleRadius = nodeformationRadius;//10-0.0523;//7-0.083;//1/(float)7/(float)2;

float l0_bd, l1_bd,l2_bd ,l3_bd; // lenghts for each boundary

float * w; //weights

point_t * l0_curve_definition; //saves all points for curve l0 in boundary
point_t * l1_curve_definition;
point_t * l2_curve_definition;
point_t * l3_curve_definition;

point_t * DeltaVector;

Spoint1D * l0_uv_curve_definition; //saves teh values for the l0 in parametric space
Spoint1D * l1_uv_curve_definition; //saves teh values for the l0 in parametric space
Spoint1D * l2_uv_curve_definition; //saves teh values for the l0 in parametric space
Spoint1D * l3_uv_curve_definition; //saves teh values for the l0 in parametric space



/*
 Costume Structures
 */
typedef struct {
    GLdouble x,y,z;
} recVec;

typedef struct {
	recVec viewPos; // View position
	recVec viewDir; // View direction vector
	recVec viewUp; // View up direction
	recVec rotPoint; // Point to rotate about
	GLdouble focalLength; // Focal Length along view direction
	GLdouble aperture; // gCamera aperture
	GLdouble eyeSep; // Eye separation
	GLint screenWidth,screenHeight; // current window/screen height and width
} recCamera;


recCamera gCamera;
recVec gOrigin = {0.0, 0.0, 0.0};



#pragma mark ---- User's Objects ----

BubbleGeometry objBB;
BubblePacking objBP;
BSPline objMainBSPline;
BubblePacking2D objBP2D;
Euler objEuler;
RungeKutta objRK;
Spline objSpline;
Subdivision objMainSubdivision;

PointUVp currentPoint;
point_t currentPointXYZ;

Util objUtil;


//myPoint3D S;
myPoint3D** sMAT;

//bubble B1,B2,B3;
bubble ** PointMat; //matrix saves all the data for all the points in the surface
bubble ** PointMat2; //matrix saves all the data for all the points in the surface

bubble * l0c; //
bubble * l1c;
bubble * l2c;
bubble * l3c;

bubble * vectorSimulationAllPoints = new bubble [1000]; //it has a maximum number of 1000 bubbles CHANGE

point_t * d0 ;
point_t * d1 ;
point_t * d2 ;
point_t * d3 ;

vector<myPoint3D> pointsBSpline;


#pragma mark ---- gCamera control ----


// ----------------------------------------------------------------------------
/**
 Routine: gCameraReset()
 Inputs: none
 Arguments: void
 Externals: gCamera struct
 Others: none
 
 Outputs: gCamera struct
 Arguments: 
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 */
// ----------------------------------------------------------------------------
void gCameraReset(void)
{
    gCamera.aperture = 25;
    gCamera.focalLength = 30; //THIS IS THE DEFAULT ZOOM
    gCamera.rotPoint = gOrigin;
    
    gCamera.viewPos.x = 0.0;
    gCamera.viewPos.y = 0.0;
    gCamera.viewPos.z = -gCamera.focalLength;
    
    gCamera.viewDir.x = -gCamera.viewPos.x;
    gCamera.viewDir.y = -gCamera.viewPos.y;
    gCamera.viewDir.z = -gCamera.viewPos.z;
    
    gCamera.viewUp.x = 0;
    gCamera.viewUp.y = 1;
    gCamera.viewUp.z = 0;
}



#pragma mark ---- Geometries  ----

// ----------------------------------------------------------------------------
/**
 Routine: drawBubble()
 Inputs: none
 Arguments: none
 Externals:none
 Others: none
 
 Outputs: gCamera struct
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 */
// ----------------------------------------------------------------------------
void drawBubble ()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(1.0f, 1.0f, 1.0f);
    
	glBegin(GL_POLYGON);
	glColor3f(   0.2,  0.39812096,  .0918263 );
	glVertex3f(  0.5,  0.5,  0.5 );
	glVertex3f(  0.5,  0.5, -0.5 );
	glVertex3f( -0.5,  0.5, -0.5 );
	glVertex3f( -0.5,  0.5,  0.5 );
	glEnd();
    
    
	glBegin(GL_LINES);
	glColor3f(   0.23,  1.0,  0.23 );
	glVertex3f(  0.5,  0.5,  0.5 );
	glVertex3f(  0.5,  0.5, -0.5 );
	glEnd();
    
	glBegin(GL_LINES);
	glColor3f(   0.23,  1.0,  0.23 );
	glVertex3f(  0.5,  0.5, -0.5 );
	glVertex3f( -0.5,  0.5, -0.5 );
	glEnd();
    glBegin(GL_LINES);
	glColor3f(   0.23,  1.0,  0.23 );
    glVertex3f( -0.5,  0.5, -0.5 );
	glVertex3f( -0.5,  0.5,  0.5 );
	glEnd();
    glBegin(GL_LINES);
	glColor3f(   0.23,  1.0,  0.23 );
	glVertex3f( -0.5,  0.5,  0.5 );
	glVertex3f(  0.5,  0.5,  0.5 );
	glEnd();
    
    
}


GLuint createDL() {
	GLuint snowManDL;
    
	// Create the id for the list
	snowManDL = glGenLists(1);
    
	glNewList(snowManDL,GL_COMPILE);
    drawBubble();
	glEndList();
    
	return(snowManDL);
}

#pragma mark ---- Utilities ----

// ----------------------------------------------------------------------------
/**
 Routine: drawGLString()
 Inputs: GLfloat x, GLfloat y, char* string
 Arguments: none
 Externals: glRasterPos2f(x, y), glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, string[i])
 Others: strlen(len)
 
 Outputs: 
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 */
// ----------------------------------------------------------------------------
void
drawGLString(GLfloat x, GLfloat y, char *string)
{
    int len, i;
    
    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, string[i]);
    }
}


#pragma mark ---- Drawing ----


void SetLighting(unsigned int mode)
{
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {90.0};
    
	GLfloat position[4] = {7.0,-7.0,12.0,0.0};
	GLfloat ambient[4]  = {0.2,0.2,0.2,1.0};
	GLfloat diffuse[4]  = {1.0,1.0,1.0,1.0};
	GLfloat specular[4] = {1.0,1.0,1.0,1.0};
	
	glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv (GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    
	switch (mode) {
		case 0:
			break;
		case 1:
			glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
			glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_FALSE);
			break;
		case 2:
			glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
			glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
			break;
		case 3:
			glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
			glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_FALSE);
			break;
		case 4:
			glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
			glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
			break;
	}
    
	glLightfv(GL_LIGHT0,GL_POSITION,position);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	glEnable(GL_LIGHT0);
}

// ----------------------------------------------------------------------------
/**
 Routine: drawGLText ()
 Inputs: GLint window_width, GLint window_height
 Arguments: none
 Externals: drawGLString()
 Others:
 
 Outputs:
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 */
// ----------------------------------------------------------------------------
void drawGLText (GLint window_width, GLint window_height)
{
	char outString [256] = "";
	GLint matrixMode;
	GLint vp[4];
	GLint lineSpacing = 13;
	GLint line = 0;
	GLint startOffest = 7;
	
	glGetIntegerv(GL_VIEWPORT, vp);
	glViewport(0, 0, window_width, window_height);
	
	glGetIntegerv(GL_MATRIX_MODE, &matrixMode);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glScalef(2.0f / window_width, -2.0f / window_height, 1.0f);
	glTranslatef(-window_width / 2.0f, -window_height / 2.0f, 0.0f);
    
    int temp3 = NUMBER_OF_BUBBLES_IN_SIMULATION - NUMBER_OF_BUBBLES_L0 - NUMBER_OF_BUBBLES_L1 - NUMBER_OF_BUBBLES_L2 - NUMBER_OF_BUBBLES_L3 -3; //MAL
	
	// draw
	glDisable(GL_LIGHTING);
	glColor3f (1.0, 1.0, 1.0);
	if (gShowInfo) {
        
		sprintf (outString, "Camera Position: (%0.1f, %0.1f, %0.1f)", gCamera.viewPos.x, gCamera.viewPos.y, gCamera.viewPos.z);
		drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
		sprintf (outString, "Trackball Rotation: (%0.1f, %0.2f, %0.2f, %0.2f)", gTrackBallRotation[0], gTrackBallRotation[1], gTrackBallRotation[2], gTrackBallRotation[3]);
		drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
		sprintf (outString, "World Rotation: (%0.1f, %0.2f, %0.2f, %0.2f)", gWorldRotation[0], gWorldRotation[1], gWorldRotation[2], gWorldRotation[3]);
		drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
		sprintf (outString, "Aperture: %0.1f", gCamera.aperture);
		drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
		sprintf (outString, "Focus Distance: %0.1f", gCamera.focalLength);
		drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
        
        sprintf (outString, "Number in the surface: %0.1d",temp3);
		drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
        
        sprintf (outString, "Animation Current Iteration Boundary: %0.1d",k_loop);
		drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
        
        sprintf (outString, "Animation Current Iteration Surface: %0.1d",kinternal_loop);
		drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
        
        sprintf (outString, "Max Number of Iterations for Runge Kutta: %0.1d", NUM_ITERATIONS);
		drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
        
        sprintf (outString, "Number of Bubbles in the Simulation: %0.1d", IMAX*IMAX);
		drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
        
        sprintf (outString, "Carnegie Mellon University 2012 : Diego Andrade");
		drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
        
        
        
	}
	
	if (gShowHelp) {
		line = 1;
		sprintf (outString, "Controls:\n");
		drawGLString (10, (lineSpacing * line++) + startOffest, outString);
		sprintf (outString, "left button drag: rotate camera\n");
		drawGLString (10, (lineSpacing * line++) + startOffest, outString);
		sprintf (outString, "right (or crtl-left) button drag: dolly (zoom) camera\n");
		drawGLString (10, (lineSpacing * line++) + startOffest, outString);
		sprintf (outString, "arrows: aperture & focal length\n");
		drawGLString (10, (lineSpacing * line++) + startOffest, outString);
		sprintf (outString, "H: toggle help\n");
		drawGLString (10, (lineSpacing * line++) + startOffest, outString);
		sprintf (outString, "I: toggle info\n");
		drawGLString (10, (lineSpacing * line++) + startOffest, outString);
		sprintf (outString, "W: toggle wire frame\n");
		drawGLString (10, (lineSpacing * line++) + startOffest, outString);
        sprintf (outString, "R: rungge krutta simulation\n");
		drawGLString (10, (lineSpacing * line++) + startOffest, outString);
        
	}
	
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(matrixMode);
	
	glViewport(vp[0], vp[1], vp[2], vp[3]);
}

#pragma mark ---- GLUT callbacks ----

// ----------------------------------------------------------------------------
/**
 Routine: MatPointInitial()
 Inputs: bubble** PMat
 Arguments: none
 Externals: objMainBSPline.ptsNURBS()
 Others:
 
 Outputs:  PMat (x,y,z)
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 */
// ----------------------------------------------------------------------------
void MatPointInitial (bubble** PMat)
{
    
    float* Uknot = new float [9];
    float* Vknot = new float [9];
    
    Uknot[0]= Uknot[1] = Uknot[2]= Uknot[3]= Uknot[4] =  0.0;
    Uknot[5]= Uknot[6] = Uknot[7]= Uknot[8]= Uknot[9] =  1.0; //here how to strech space
    
    
    Vknot[0]= Vknot[1] = Vknot[2]= Vknot[3]= Vknot[4] =  0.0;
    Vknot[5]= Vknot[6] = Vknot[7]= Vknot[8]= Vknot[9] =  1.0;
    
    
    
    //float prevu, prevv;
    float lastu, lastv;
    //float lastx, lasty, lastz;
    // bool mtrue = false;
    
    
    for(int i=0;i<IMAX;i++){
        for(int j=0;j<IMAX;j++){
            
            
            lastu = 1/(float)(IMAX-1)*i; //using IMAX because is square same number of rows and columns
            lastv = 1/(float)(JMAX-1)*j;
            
            //cout << "\nU:" << lastu << endl;
            // cout << "V:" << lastv << endl;
            
            
            objMainBSPline.ptsNURBS(objMainBSPline.controlPointsArray, objMainBSPline.controlPointsWeightsArray, Uknot, Vknot, 5, 5, 5, 5, lastu,lastv, objMainBSPline.pts);
            
            PMat[i][j].x = objMainBSPline.pts[0];
            PMat[i][j].y = objMainBSPline.pts[1];
            PMat[i][j].z = objMainBSPline.pts[2];
        }
    }
    
    
    
}

// ----------------------------------------------------------------------------
/**
 Routine: VectPointInitial()
 Inputs: bubble* lcb, int numBubles, int iniBubble, int lastBubble
 Arguments: none
 Externals: objMainBSPline.ptsNURBS()
 Others:
 
 Outputs:  bubble* lcb
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 */
// ----------------------------------------------------------------------------
void VectPointInitial (bubble* lcb, int numBubles, int iniBubble, int lastBubble)
{
    
    float* Uknot = new float [10];
    float* Vknot = new float [10];
    
    Uknot[0]= Uknot[1] = Uknot[2]= Uknot[3]= Uknot[4] =  0.0;
    Uknot[5]= Uknot[6] = Uknot[7]= Uknot[8]= Uknot[9] =  1.0; //here how to strech space
    
    
    Vknot[0]= Vknot[1] = Vknot[2]= Vknot[3]= Vknot[4] =  0.0;
    Vknot[5]= Vknot[6] = Vknot[7]= Vknot[8]= Vknot[9] =  1.0;
    
    
    float lastu, lastv;
    
    
    
    for(int i=0;i<numBubles;i++){
        
        lastu = lcb[i].u;
        lastv = lcb[i].v;
        
        
        objMainBSPline.ptsNURBS(objMainBSPline.controlPointsArray, objMainBSPline.controlPointsWeightsArray, Uknot, Vknot, 5, 5, 5, 5, lastu,lastv, objMainBSPline.pts);
        
        lcb[i].x = objMainBSPline.pts[0];
        lcb[i].y = objMainBSPline.pts[1];
        lcb[i].z = objMainBSPline.pts[2];
        
       
        
        
    }
    
    for(int j=0;j<numBubles;j++)
    {
        lcb[iniBubble+j].idx = iniBubble+j;
        //cout << "index: " << lcb[iniBubble+j].idx << endl;
        
    }
    
    
    
}

// ----------------------------------------------------------------------------
/**
 Routine: radiusFind()
 Inputs: int nOfBubbles, float len
 Arguments: none
 Externals: none
 Others:
 
 Outputs:  radius
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 */
// ----------------------------------------------------------------------------
float radiusFind(int nOfBubbles, float len)
{
    float radius = len/(float)(nOfBubbles-2)*0.5;
    
    return radius;
    
}

// ----------------------------------------------------------------------------
/**
 Routine: findBoundariesLengths()
 Inputs: myPoint3D **controlPoints, int numberOfControlPoints
 Arguments: none
 Externals: none
 Others:
 
 Outputs:  lxx_bd, lxx_curve_definition,  lxx_uv_curve_definition
 Arguments:
 Externals: objMainBSPline.findLengthCurve()
 Returns: 
 Errors:
 
 Routines Called:
 */
// ----------------------------------------------------------------------------
void findBoundariesLengths ( myPoint3D **controlPoints, int numberOfControlPoints)
{
    
    float* Uknot = new float [9];
    float* Vknot = new float [9];
    
    Uknot[0]= Uknot[1] = Uknot[2]= Uknot[3]= Uknot[4] =  0.0;
    Uknot[5]= Uknot[6] = Uknot[7]= Uknot[8]= Uknot[9] =  1.0; //here how to strech space
    
    
    Vknot[0]= Vknot[1] = Vknot[2]= Vknot[3]= Vknot[4] =  0.0;
    Vknot[5]= Vknot[6] = Vknot[7]= Vknot[8]= Vknot[9] =  1.0;
    
    
    d0 = new point_t[5];
    d1 = new point_t[5];
    d2 = new point_t[5];
    d3 = new point_t[5];
    
    w = new float[5]; //weights
    
    for(int i =0;i<5;i++)
    {
        w[i] = 1.0;
    }
    
    for(int i =0;i<numberOfControlPoints;i++) //actual points in different loops because the number of bubbles can change in each boundary
    {
        //boundary l0
        d0[i].x = controlPoints[0][i].x;
        d0[i].y = controlPoints[0][i].y;
        d0[i].z = controlPoints[0][i].z;
        
    }
    
    //objUtil.printVectPoints(d0, numberOfControlPoints, "/Users/Serenity/Dropbox/CMU 2012/d0.txt");
    
    for(int i =0;i<numberOfControlPoints;i++) //actual points
    {
        //boundary l1
        
        d1[i].x = controlPoints[i][0].x;
        d1[i].y = controlPoints[i][0].y;
        d1[i].z = controlPoints[i][0].z;
    }
    
    for(int i =0;i<numberOfControlPoints;i++) //actual points
    {
        //boundary l2
        d2[i].x = controlPoints[numberOfControlPoints-1][i].x;
        d2[i].y = controlPoints[numberOfControlPoints-1][i].y;
        d2[i].z = controlPoints[numberOfControlPoints-1][i].z;
        
    }
    
    for(int i =0;i<numberOfControlPoints;i++) //actual points
    {
        //boundary l3
        d3[i].x = controlPoints[i][numberOfControlPoints-1].x;
        d3[i].y = controlPoints[i][numberOfControlPoints-1].y;
        d3[i].z = controlPoints[i][numberOfControlPoints-1].z;
        
    }
    
    
    float* wpts = new float [3];
    wpts[0]=0.0;
    wpts[1]=0.0;
    wpts[2]=0.0;
    
    l0_bd = objMainBSPline.findLengthCurve(d0, w, Uknot, numberOfControlPoints, 5, wpts, 50); //5 i sthe degree of the curve
    l0_curve_definition = objMainBSPline.l_c; //saves the XYZ coordinates of hte boundary points
    l0_uv_curve_definition = objMainBSPline.l_uv_curve_definition; //saves the UV locations of the boundary points
    
    // objUtil.printVectPoints(l0_curve_definition, 50);
    
    //    wpts[0]= 3.0; //make sure this is the correct point
    //   wpts[1]= 0.0;
    //   wpts[2]= 0.0;
    l1_bd = objMainBSPline.findLengthCurve(d1, w, Uknot, numberOfControlPoints, 5, wpts, 50);
    l1_curve_definition = objMainBSPline.l_c;
    l1_uv_curve_definition = objMainBSPline.l_uv_curve_definition;
    
    //    wpts[0]=3.0;
    //   wpts[1]=0.0;
    //    wpts[2]=4.0;
    l2_bd = objMainBSPline.findLengthCurve(d2, w, Uknot, numberOfControlPoints, 5, wpts, 50);
    l2_curve_definition = objMainBSPline.l_c;
    l2_uv_curve_definition = objMainBSPline.l_uv_curve_definition;
    
    
       // wpts[0]=-3.0;
     //  wpts[1]=0.0;
     //  wpts[2]=0.0;
    l3_bd = objMainBSPline.findLengthCurve(d3, w, Uknot, numberOfControlPoints, 5, wpts, 50);
    l3_curve_definition = objMainBSPline.l_c;
    l3_uv_curve_definition = objMainBSPline.l_uv_curve_definition;
    
    
    cout << l0_bd <<endl;
    cout << l1_bd <<endl;
    cout << l2_bd <<endl;
    cout << l3_bd <<endl;
    
}


// ----------------------------------------------------------------------------
/**
 Routine: functionRadius()
 Inputs: bubble * l0, bubble * l1, bubble* l2, bubble* l3
 Arguments: none
 Externals: none
 Others:
 
 Outputs:  rad_new
 Arguments:
 Externals: 
 Returns:
 Errors:
 
 Routines Called:
 
 Summary:
 This function is used to calculate the average of the bubbles in the extremes of 
 the geometry  maybe there is a better way of doing this, aslo HOW put same number 
 of bubbles requested and making smooth transistions
 */
// ----------------------------------------------------------------------------
float functionRadius ( bubble * l0, bubble * l1, bubble* l2, bubble* l3)
{
    
    //  float rm2 = 0.0;
    //  float len_new = 0.0;
    float rad_new = 0.0;
    
    //rm1 = (l0[0].radius+l1[0].radius)/(float)2;
    //rm2 = (l0[0].radius+l3[0].radius)/(float)2;
    
    rad_new = ( l0[0].radius + l1[0].radius +l2[0].radius +l3[0].radius ) / (float) 4;
    
    //len_new = len - (rm1+rm2);
    //rad_new = len_new/(float)(numBubbles-2)*0.5;
    
    
    return rad_new;
    
}


// ----------------------------------------------------------------------------
/**
 Routine: changeRadius()
 Inputs: bubble * l0, float newradius, int numBubbles
 Arguments: none
 Externals: none
 Others:
 
 Outputs:  rad_new
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 
 Summary:
 This function changes the radius in all the bubbles in a vector definition 
 */
// ----------------------------------------------------------------------------
void changeRadius(bubble * l0, float newradius, int numBubbles)
{
    
    for (int i=0; i< numBubbles;i++)
    {
        l0[i].radius  = newradius;
    }
    
}


// ----------------------------------------------------------------------------
/**
 Routine: init()
 Inputs: bubble * l0, float newradius, int numBubbles
 Arguments: none
 Externals: objBB.createPoints() , objMainBSPline.InitializeControlPoints() , 
            subdivisionHardCode() , findBoundariesLengths() , MatPointInitial(), 
            objBP2D.bubbleBoundaries() ,  VectPointInitial();
            
 Others:
 
 Outputs:  many
 Arguments:
 Externals: 
 Returns:
 Errors:
 
 Routines Called:
 
 Summary:
 This function initializes all the properties and the needed data for the YUI
 to work needs to be run before any other.
 */
// ----------------------------------------------------------------------------
void init (void)
{
	glEnable(GL_DEPTH_TEST);
    
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);
    
	glColor3f(1.0,1.0,1.0);
    
	
	glClearColor(0.0,0.0,0.0,0.0);         /* Background recColor */
    
	gCameraReset ();
    
    //Initialize matrix
    sMAT = new myPoint3D* [IMAX];
    for (int i=0;i<JMAX;i++){
        sMAT[i] = new myPoint3D [JMAX];
        for(int j=0;j<JMAX ;j++){
            sMAT[i][j].x = 0.0;
            sMAT[i][j].y = 0.0;
            sMAT[i][j].z = 0.0;
        }
    }
	
    
    objBB.createPoints(); //Creates location // IMPORTANT
    
    
    
    //----------------
    // bubble packing 2d
    //----------------
    
    
    
    
    objMainBSPline.InitializeControlPoints();
    
    
    
    
    
    //Initializes U, V and P matrices
    
    PointMat = new bubble * [IMAX];
    for(int i=0;i<IMAX;i++){
        PointMat[i] = new bubble  [JMAX];
        for(int j=0;j<JMAX;j++){
            PointMat[i][j].radius = initialBubbleRadius; //change here if needed
            PointMat[i][j].u = 0.0;
            PointMat[i][j].v = 0.0;
            
            PointMat[i][j].x = 0.0;
            PointMat[i][j].y = 0.0;
            PointMat[i][j].z = 0.0;
            
            PointMat[i][j].idx = 0.0;
            
            
        }
        
    }
    
    PointMat2 = new bubble * [IMAX];
    for(int i=0;i<IMAX;i++){
        PointMat2[i] = new bubble  [JMAX];
        for(int j=0;j<JMAX;j++){
            PointMat2[i][j].radius = initialBubbleRadius; //change here if needed
            PointMat2[i][j].u = 0.0;
            PointMat2[i][j].v = 0.0;
            
            PointMat2[i][j].x = 0.0;
            PointMat2[i][j].y = 0.0;
            PointMat2[i][j].z = 0.0;
            
            
            PointMat2[i][j].idx = 0.0;
        }
        
    }
    
    
    objBP2D.subdivisionHardCode( PointMat, IMAX, JMAX);
    
    objBP2D.subdivisionHardCode2( PointMat2 , IMAX, JMAX, distance_geometry);
    
    
    //----------------
    // Vector defined simulation
    //----------------
    
    //lengths in the boundaries
    findBoundariesLengths(objMainBSPline.controlPointsArray, 5);
    //Creates the initial position of the points and finds lenght of boundaries
    MatPointInitial(PointMat2);
    
    
    
    l0c = objBP2D.bubbleBoundaries(numberOfBubblesl0, l0_bd, 0); //l0 curve getting the values of the boundary
    l1c = objBP2D.bubbleBoundaries(numberOfBubblesl1, l1_bd, 1); //l1 curve getting the values of the boundary
    l2c = objBP2D.bubbleBoundaries(numberOfBubblesl2, l2_bd, 2); //l1 curve getting the values of the boundary
    l3c = objBP2D.bubbleBoundaries(numberOfBubblesl3, l3_bd, 3); //l1 curve getting the values of the boundary
    
    
    
    /* USE THIS FUNCTION FOR A WELL DISTRIBUTED BOUNDARY, BASED ON NUMBER OF BUBBLES PER SIDE */
    
    float rad = functionRadius(l0c,l1c,l2c,l3c);
    
    float new_len = l0_bd - 2*rad;
    float rad0 = radiusFind(numberOfBubblesl0, new_len);
    l0c = objBP2D.bubbleBoundaries(numberOfBubblesl0, new_len, 0); //l0 curve getting the values of the boundary
    changeRadius(l0c, rad0, numberOfBubblesl0);
    l0c[0].radius = rad; l0c[numberOfBubblesl0-1].radius = rad;
    
    new_len = l1_bd - 2*rad;
    float rad1 = radiusFind(numberOfBubblesl1, new_len);
    l1c = objBP2D.bubbleBoundaries(numberOfBubblesl1, new_len, 1); //l0 curve getting the values of the boundary
    changeRadius(l1c, rad1, numberOfBubblesl1);
    l1c[0].radius = rad; l1c[numberOfBubblesl1-1].radius = rad;
    
    new_len = l2_bd - 2*rad;
    float rad2 = radiusFind(numberOfBubblesl2, new_len);
    l2c = objBP2D.bubbleBoundaries(numberOfBubblesl2, new_len, 2); //l0 curve getting the values of the boundary
    changeRadius(l2c, rad2, numberOfBubblesl2);
    l2c[0].radius = rad; l2c[numberOfBubblesl2-1].radius = rad;
    
    new_len = l3_bd - 2*rad;
    float rad3 = radiusFind(numberOfBubblesl3, new_len);
    l3c = objBP2D.bubbleBoundaries(numberOfBubblesl3, new_len, 3); //l0 curve getting the values of the boundary
    changeRadius(l3c, rad3, numberOfBubblesl3);
    l3c[0].radius = rad; l3c[numberOfBubblesl3-1].radius = rad;
    
    
    /* USE THIS FOR EQUAL DISTRIBUTION OF BALL OF THE SAME SIZE
      INDEPENDENT OF THE NUMBER OF BUBBLES
     
     float rad0 = functionRadius(l0c,l1c,l3c,l0_bd,numberOfBubblesl0);
     
     changeRadius(l0c, rad0, numberOfBubblesl0);
     changeRadius(l1c, rad0, numberOfBubblesl1);
     changeRadius(l3c, rad0, numberOfBubblesl3);
     
     float rad1 = functionRadius(l0c,l1c,l2c,l1_bd,numberOfBubblesl1);
     
     changeRadius(l0c, rad1, numberOfBubblesl0);
     changeRadius(l1c, rad1, numberOfBubblesl1);
     changeRadius(l2c, rad1, numberOfBubblesl2);
     
     
     float rad2 = functionRadius(l1c,l2c,l3c,l2_bd,numberOfBubblesl2);
     
     changeRadius(l1c, rad2, numberOfBubblesl1);
     changeRadius(l2c, rad2, numberOfBubblesl2);
     changeRadius(l3c, rad2, numberOfBubblesl3);
     
     float rad3 = functionRadius(l2c,l3c,l0c,l3_bd,numberOfBubblesl3);
     
     changeRadius(l2c, rad3, numberOfBubblesl2);
     changeRadius(l3c, rad3, numberOfBubblesl3);
     changeRadius(l0c, rad3, numberOfBubblesl0);
     
     float radm = (rad1+rad2+rad3+rad0)/4;
     
     cout << "radm: " << radm << endl;
     
     */
    
    
    VectPointInitial(l0c, numberOfBubblesl0, 0, 7);
    VectPointInitial(l1c, numberOfBubblesl1, 7, 14);
    VectPointInitial(l2c, numberOfBubblesl2, 14, 21);
    VectPointInitial(l3c, numberOfBubblesl3, 21,28);
    
    
    /* INITIALIZES THE VECTOR AND ALL THE POINTS
      */
    for (int i=0; i<1000; i++)
    {
        vectorSimulationAllPoints[i].radius = 0;
        vectorSimulationAllPoints[i].x = 0;
        vectorSimulationAllPoints[i].y = 0;
        vectorSimulationAllPoints[i].z = 0;
        vectorSimulationAllPoints[i].u = 0;
        vectorSimulationAllPoints[i].v = 0;
        vectorSimulationAllPoints[i].idx = i;
    }
    
}

void reshape (int w, int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	gCamera.screenWidth = w;
	gCamera.screenHeight = h;
	glutPostRedisplay();
}


// ----------------------------------------------------------------------------
/**
 Routine: functionRadius()
 Inputs: bubble * l0, bubble * l1, bubble* l2, bubble* l3
 Arguments: none
 Externals: none
 Others:
 
 Outputs:  rad_new
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 
 Summary:
 Finds the span of the geometry 
**/
// ----------------------------------------------------------------------------
float findspan(float v1, float v2, float v3, float v4, int state)
{
        
    float * vect = new float [4];
    
    vect[0] = abs(v3-v1);
    vect[1] = abs(v3-v2);
    vect[2] = abs(v4-v1);
    vect[3] = abs(v4-v2);
    
    float val = 0.0;
    
    if (state==0) //find the smallest in the vector 
    {
        float small = vect[0];
        for (int i=1 ; i<4 ; i++)
        {
            if(vect[i]<small)
                small = vect[i];
        }
        val=small;
    }
    
    if (state==1) // find the largest in the vector
    {
        float big = vect[0];
        for (int i=1 ; i<4 ; i++)
        {
            if(vect[i]>big)
                big = vect[i];
        }
        val = big;
    }

    return val;
    
}

// ----------------------------------------------------------------------------
/**
 Routine: createBubbleSplineT()
 Inputs: float dx, float dy, float radius
 Arguments: none
 Externals: none
 Others:
 
 Outputs:  objMainBSPline.ptsNURBS()
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 
 Summary:
 This function creates bubbles in a BSPline surface
 **/
// ----------------------------------------------------------------------------
void createBubbleSplineT(float dx, float dy, float radius)
{
    float* Uknot = new float [9];
    float* Vknot = new float [9];
    
    Uknot[0]= Uknot[1] = Uknot[2]= Uknot[3]= Uknot[4] =  0.0;
    Uknot[5]= Uknot[6] = Uknot[7]= Uknot[8]= Uknot[9] =  1.1; //By changing the knot value the extends
    
    
    Vknot[0]= Vknot[1] = Vknot[2]= Vknot[3]= Vknot[4] =  0.0;
    Vknot[5]= Vknot[6] = Vknot[7]= Vknot[8]= Vknot[9] =  1.1;
    
    
    // glPushMatrix(); //Copies the matrix on the top of the stack, this would be like save the funcion
    glColor3f(1,0,1);  //set colour ball
    glTranslatef(0.0, 0.0 , 0.0); // back to origin
    
    float	colorUSER[3]	=	{255, 245, 195}; //{0.99609375, 0.3984375, 0};
    
    glBegin(GL_LINES);
    glColor3fv(colorUSER);
    
    float x = (float)radius * cos(359*PI/180.0f)+dx;
    float z = (float)radius * sin(359*PI/180.0f)+dy;
    
    objMainBSPline.ptsNURBS(objMainBSPline.controlPointsArray, objMainBSPline.controlPointsWeightsArray,
                            Uknot, Vknot, 5, 5, 5, 5, x, z, objMainBSPline.pts);
    
    for (int j=0; j<360; j++)
    {
        glVertex3f(objMainBSPline.pts[0], objMainBSPline.pts[1] , objMainBSPline.pts[2]);
        
        x = (float)radius * cos(j*PI/180.0f)+dx;
        
        z = (float)radius * sin(j*PI/180.0f)+dy;
        
        objMainBSPline.ptsNURBS(objMainBSPline.controlPointsArray, objMainBSPline.controlPointsWeightsArray,
                                Uknot, Vknot, 5, 5, 5, 5, x, z, objMainBSPline.pts);
        
        
        glVertex3f(objMainBSPline.pts[0], objMainBSPline.pts[1] , objMainBSPline.pts[2]);
        
    }
    
    glEnd();
    
    delete [] Uknot;
    delete [] Vknot;
    
}

#pragma mark <F> creates the vector for simulation

// ----------------------------------------------------------------------------
/**
 Routine: vectorForSimulation()
 Inputs: bubble* l0, int numl0,
         bubble* l1, int numl1,
         bubble* l2, int numl2,
         bubble* l3, int numl3,
         int numBX, int numBY, float spanX, int spanY
 Arguments: none
 Externals: none
 Others:
 
 Outputs:  objMainBSPline.ptsNURBS()
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 
 Summary:
 Initializes the data in the simulation
 **/
// ----------------------------------------------------------------------------
void vectorForSimulation (bubble* l0, int numl0,
                             bubble* l1, int numl1,
                             bubble* l2, int numl2,
                             bubble* l3, int numl3,
                           int numBX, int numBY, float spanX, int spanY)
{
   
    int temp = 0;
    
    float s1,s2,s3,s4;
    s1=s2=s3=s4=0.0;
    
    float t1,t2,t3,t4;
    t1=t2=t3=t4=0.0;
    
    for(int i=0; i<numl0 ; i++)
    {
        vectorSimulationAllPoints[i].radius = l0[i].radius;
        vectorSimulationAllPoints[i].x = l0[i].x;
        vectorSimulationAllPoints[i].y = l0[i].y;
        vectorSimulationAllPoints[i].z = l0[i].z;
        vectorSimulationAllPoints[i].u = l0[i].u;
        vectorSimulationAllPoints[i].v = l0[i].v;
       // vectorSimulationAllPoints[i].idx = l0[i].idx;
        if (l0[i].x < s1) s1 = l0[i].x;
        else s1=s1;
    
        if (l0[i].x > s2) s2 = l0[i].x;
        else s2=s2;
        
                
        
    }

    
    for(int i=0; i<numl1 ; i++)
    {
        vectorSimulationAllPoints[numl0-1+i].radius = l1[i].radius;
        vectorSimulationAllPoints[numl0-1+i].x = l1[i].x;
        vectorSimulationAllPoints[numl0-1+i].y = l1[i].y;
        vectorSimulationAllPoints[numl0-1+i].z = l1[i].z;
        vectorSimulationAllPoints[numl0-1+i].u = l1[i].u;
        vectorSimulationAllPoints[numl0-1+i].v = l1[i].v;
      //  vectorSimulationAllPoints[numl0-1+i].idx = l1[i].idx;
        
        
        if (l1[i].z < t1) t1 = l1[i].z;
        else t1=t1;
        
        if (l1[i].z > t2) t2 = l1[i].z;
        else t2=t2;
        
    }
    
    
    for(int i=0; i<numl2 ; i++)
    {
        vectorSimulationAllPoints[numl0+numl1-2+i].radius = l2[i].radius;
        vectorSimulationAllPoints[numl0+numl1-2+i].x = l2[i].x;
        vectorSimulationAllPoints[numl0+numl1-2+i].y = l2[i].y;
        vectorSimulationAllPoints[numl0+numl1-2+i].z = l2[i].z;
        vectorSimulationAllPoints[numl0+numl1-2+i].u = l2[i].u;
        vectorSimulationAllPoints[numl0+numl1-2+i].v = l2[i].v;
       // vectorSimulationAllPoints[numl0+numl1-2+i].idx = l2[i].idx;
        
        if (l2[i].x < s3) s3 = l2[i].x;
        else s3=s3;
        
        if (l2[i].x > s4) s4 = l2[i].x;
        else s4=s4;
        
    }
    
    
    for(int i=0; i<numl3 ; i++)
    {
        vectorSimulationAllPoints[numl0+numl1+numl2-3+i].radius = l3[i].radius;
        vectorSimulationAllPoints[numl0+numl1+numl2-3+i].x = l3[i].x;
        vectorSimulationAllPoints[numl0+numl1+numl2-3+i].y = l3[i].y;
        vectorSimulationAllPoints[numl0+numl1+numl2-3+i].z = l3[i].z;
        vectorSimulationAllPoints[numl0+numl1+numl2-3+i].u = l3[i].u;
        vectorSimulationAllPoints[numl0+numl1+numl2-3+i].v = l3[i].v;
        //vectorSimulationAllPoints[numl0+numl1+numl2-3+i].idx = l3[i].idx;
        
        if (l3[i].z < t3) t3 = l3[i].z;
        else t2=t2;
        
        if (l3[i].z> t4) t4 = l3[i].z;
        else t3=t3;

        
    }
    
    /*float minvalX = findspan(s1,s2,s3,s4, 0);
    float maxvalX = findspan(s1,s2,s3,s4, 1);
    
    float minvalY = findspan(t1,t2,t3,t4, 0);
    float maxvalY = findspan(t1,t2,t3,t4, 1);*/
    
    
    
    temp = numl0+numl1+numl2-3+numl3;
    
    float rad = (l0c[1].radius + l1c[1].radius + l2c[1].radius + l3c[1].radius)/(float)4.0; //average size for internal bubbles change 4 fro average
    
    
    for(int i=numl0+numl1+numl2+numl3-3; i<300 ; i++) //100 maximum number of bubbles
    {
        vectorSimulationAllPoints[i].radius = rad;
        vectorSimulationAllPoints[i].x = 0.0;
        vectorSimulationAllPoints[i].y = 0.0;
        vectorSimulationAllPoints[i].z = 0.0;
        vectorSimulationAllPoints[i].u = 0.0;
        vectorSimulationAllPoints[i].v = 0.0;
        vectorSimulationAllPoints[i].idx = i;
        
        
        
    }
    
    
    
    
    spanX = 2;//abs(maxvalX-minvalX); //change here
    spanY = 2;//abs(maxvalY-minvalY);
    
    int m=0;
    int n=0;
    
    float* Uknot = new float [9];
    float* Vknot = new float [9];
    
    Uknot[0]= Uknot[1] = Uknot[2]= Uknot[3]= Uknot[4] =  0.0;
    Uknot[5]= Uknot[6] = Uknot[7]= Uknot[8]= Uknot[9] =  1.0; //here how to strech space
    
    
    Vknot[0]= Vknot[1] = Vknot[2]= Vknot[3]= Vknot[4] =  0.0;
    Vknot[5]= Vknot[6] = Vknot[7]= Vknot[8]= Vknot[9] =  1.0;
    
    float lastv, lastu;
    
    lastu = lastv=0.1;
    
    cout << "startcount:" << numl0+numl1+numl2+numl3-3<< endl;
    
    int temp1 = NUMBER_OF_BUBBLES_IN_SIMULATION+(numl0+numl1+numl2+numl3-3);
    
    if (MAX_NUMBER_OF_BUBBLES_INITILIAZED<NUMBER_OF_BUBBLES_IN_SIMULATION) cout << \
        "ERROR: MAX_NUMBER_OF_BUBBLES_INITILIAZED (" <<MAX_NUMBER_OF_BUBBLES_INITILIAZED <<" ) < NUMBER_OF_BUBBLES_IN_SIMULATION (" \
        <<NUMBER_OF_BUBBLES_IN_SIMULATION <<" ) " << endl;
    
    cout << "endcount:" << temp1 << endl;
    
    for(int k =0 ; k<temp1; k++)
    {
        
        
        //vectorSimulationAllPoints[k].x = spanX/(150-1)*m + 1.0;
        //vectorSimulationAllPoints[k].z = 0.3*n+0.5;
        
        m++;
        if(k%10 == 0)
        {
            n++; m=0;
            
            if(n%10==0) n=0;
        }

        
        lastu =  0.1+m/(float)(temp1-1)*15; //17
        lastv =  0.1+n/(float)(temp1-1)*15; //19

      
        
        objMainBSPline.ptsNURBS(objMainBSPline.controlPointsArray, objMainBSPline.controlPointsWeightsArray, Uknot, Vknot, 5, 5, 5, 5, lastu,lastv, objMainBSPline.pts);
        
               
        
        vectorSimulationAllPoints[k+(numl0+numl1+numl2+numl3-3)].x = objMainBSPline.pts[0];
        vectorSimulationAllPoints[k+(numl0+numl1+numl2+numl3-3)].y = objMainBSPline.pts[1];
        vectorSimulationAllPoints[k+(numl0+numl1+numl2+numl3-3)].z = objMainBSPline.pts[2];
            
        //spanX/(float)(numBX-1)*i+(-0.0); //AQUI ESTA MAL i*numBX+j
        //        vectorSimulationAllPoints[k].z = spanY/(float)(numBY-1)*i+(-0.0);
        
    }
    
   // objUtil.printVect(vectorSimulationAllPoints, 100, "/Users/Serenity/Dropbox/CMU 2012/bubbleVectAllPoints.txt");
    
    // cout << vectorSimulationAllPoints[temp].idx ;
    
}


#pragma mark <F> create bubbles no deformation

// ----------------------------------------------------------------------------
/**
 Routine: createBubbleSplineNoDeformation()
 Inputs: float dx, float dy, float radius
 Arguments: none
 Externals: none
 Others:
 
 Outputs:  objMainBSPline.ptsNURBS()
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 
 Summary:
 This function creates bubbles in a BSPline surface
 **/
// ----------------------------------------------------------------------------
void createBubbleSplineNoDeformation(float dx, float dy, float radius)
{
    glPushMatrix(); //Copies the matrix on the top of the stack, this would be like save the funcion
    glColor3f(1,0,1);  //set colour ball
    ////glTranslatef(0.0, 0.0 , 0.0); // back to origin
    //glTranslatef(dx, 0.0, dy);
    
    float* Uknot = new float [9];
    float* Vknot = new float [9];
    
    Uknot[0]= Uknot[1] = Uknot[2]= Uknot[3]= Uknot[4] =  0.0;
    Uknot[5]= Uknot[6] = Uknot[7]= Uknot[8]= Uknot[9] =  1.0; //By changing the knot value the extends
    
    
    Vknot[0]= Vknot[1] = Vknot[2]= Vknot[3]= Vknot[4] =  0.0;
    Vknot[5]= Vknot[6] = Vknot[7]= Vknot[8]= Vknot[9] =  1.0;
    
    
    float x ,y,z;
    
    y=0;
    
    float	colorUSER[3]	=	{255, 245, 190};
    
    
    objMainBSPline.ptsNURBS(objMainBSPline.controlPointsArray, objMainBSPline.controlPointsWeightsArray,
                            Uknot, Vknot, 5, 5, 4, 4, dx, dy, objMainBSPline.pts); //gives the location of a point in the NURB patch
    
    //glVertex3f(objMainBSPline.pts[0], objMainBSPline.pts[1] , objMainBSPline.pts[2]); //location of the point in a NURB patch
    
    //glPushMatrix(); //Copies the matrix on the top of the stack, this would be like save the funcion
    glColor3f(1,0,1);  //set colour ball
    glTranslatef(0.0, 0.0 , 0.0); // back to origin
    glTranslatef(objMainBSPline.pts[0], objMainBSPline.pts[1] , objMainBSPline.pts[2]);
    
    glBegin(GL_LINES);
    glColor3fv(colorUSER);
    
    x = (float)radius * cos(359*PI/180.0f);
    y= objMainBSPline.pts[1];
    z = (float)radius * sin(359*PI/180.0f);
    
    for (int j=0; j<360; j++)
    {
        glVertex3f(x, y, z);
        
        x = (float)radius * cos(j*PI/180.0f);
        y = objMainBSPline.pts[1];
        z = (float)radius * sin(j*PI/180.0f);
        
        glVertex3f(x, y, z);
    }
    
    //cout << "PI Value = " << PI << endl;
    
    glEnd();
    
    
    //glPopMatrix(); // Would be equivalent like load the function
    
    
    
    // glutSolidSphere(radius, 5, 5);
    
    delete [] Uknot;
    delete [] Vknot;
    
    
    
    
    glPopMatrix(); // Would be equivalent like load the function
    
    
    
}


// ----------------------------------------------------------------------------
/**
 Routine: createBubbleXYZNoDeformation()
 Inputs: float dx, float dy, float dz, float radius
 Arguments: none
 Externals: none
 Others:
 
 Outputs:  
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 
 Summary:
 This function draws the bubbles on the screen
 **/
// ----------------------------------------------------------------------------
void createBubbleXYZNoDeformation(float dx, float dy, float dz, float radius)
{
    
    glPushMatrix(); //Copies the matrix on the top of the stack, this would be like save the funcion basically does not move
    
    float x ,y,z;
    
    y=0;
    
    float	colorUSER[3]	=	{255, 245, 190};
    
    
    //  objMainBSPline.ptsNURBS(objMainBSPline.controlPointsArray, objMainBSPline.controlPointsWeightsArray,
    //                        Uknot, Vknot, 5, 5, 4, 4, dx, dy, objMainBSPline.pts); //gives the location of a point in the NURB patch
    
    //glVertex3f(objMainBSPline.pts[0], objMainBSPline.pts[1] , objMainBSPline.pts[2]); //location of the point in a NURB patch
    
    //glPushMatrix(); //Copies the matrix on the top of the stack, this would be like save the funcion
    glColor3f(1,0,1);  //set colour ball
    glTranslatef(0.0, 0.0 , 0.0); // back to origin
    glTranslatef(dx, dy , dz);
    
    glBegin(GL_LINES);
    glColor3fv(colorUSER);
    
    x = (float)radius * cos(359*PI/180.0f);
    y= 0;
    z = (float)radius * sin(359*PI/180.0f);
    
    for (int j=0; j<360; j++)
    {
        glVertex3f(x, y, z);
        
        x = (float)radius * cos(j*PI/180.0f);
        y = 0;
        z = (float)radius * sin(j*PI/180.0f);
        
        glVertex3f(x, y, z);
    }
    
    //cout << "PI Value = " << PI << endl;
    
    glEnd();
    
    
    //glPopMatrix(); // Would be equivalent like load the function
    
    
    
    // glutSolidSphere(radius, 5, 5);
    
    //  delete [] Uknot;
    //  delete [] Vknot;
    
    
    
    
    glPopMatrix(); // Would be equivalent like load the function
    
    
    
}

// ----------------------------------------------------------------------------
/**
 Routine: createBubbleXYZNoDeformationBoundary()
 Inputs: float dx, float dy, float dz, float radius
 Arguments: none
 Externals: none
 Others:
 
 Outputs:
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 
 Summary:
 This function draws the bubbles on the screen
 **/
// ----------------------------------------------------------------------------
void createBubbleXYZNoDeformationBoundary(float dx, float dy, float dz, float radius)
{
    
    glPushMatrix(); //Copies the matrix on the top of the stack, this would be like save the funcion basically does not move
    
    float x ,y,z;
    
    y=0;
    
    float	colorUSER[3]	=	{0.933333, 0.866667, 0.509804};
    
    
    //  objMainBSPline.ptsNURBS(objMainBSPline.controlPointsArray, objMainBSPline.controlPointsWeightsArray,
    //                        Uknot, Vknot, 5, 5, 4, 4, dx, dy, objMainBSPline.pts); //gives the location of a point in the NURB patch
    
    //glVertex3f(objMainBSPline.pts[0], objMainBSPline.pts[1] , objMainBSPline.pts[2]); //location of the point in a NURB patch
    
    //glPushMatrix(); //Copies the matrix on the top of the stack, this would be like save the funcion
    //glColor3f(1,0,1);  //set colour ball
    glTranslatef(0.0, 0.0 , 0.0); // back to origin
    glTranslatef(dx, dy , dz);
    
    glBegin(GL_LINES);
    glColor3fv(colorUSER);
    
    x = (float)radius * cos(359*PI/180.0f);
    y= 0;
    z = (float)radius * sin(359*PI/180.0f);
    
    for (int j=0; j<360; j++)
    {
        glVertex3f(x, y, z);
        
        x = (float)radius * cos(j*PI/180.0f);
        y = 0;
        z = (float)radius * sin(j*PI/180.0f);
        
        glVertex3f(x, y, z);
    }
    
    //cout << "PI Value = " << PI << endl;
    
    glEnd();
    
    
    //glPopMatrix(); // Would be equivalent like load the function
    
    
    
    // glutSolidSphere(radius, 5, 5);
    
    //  delete [] Uknot;
    //  delete [] Vknot;
    
    
    
    
    glPopMatrix(); // Would be equivalent like load the function
    
    
    
}


// ----------------------------------------------------------------------------
/**
 Routine: createBubbleXYZVector()
 Inputs: float dx, float dy, float dz, float radius, float* color
 Arguments: none
 Externals: none
 Others:
 
 Outputs:
 Arguments:
 Externals:
 Returns:
 Errors:
 
 Routines Called:
 
 Summary:
 This function draws the bubbles on the screen
 **/
// ----------------------------------------------------------------------------
void createBubbleXYZVector(float dx, float dy, float dz, float radius, float* color)
{
    glPushMatrix(); //Copies the matrix on the top of the stack, this would be like save the funcion basically does not move
    
    float x ,y,z;
    
    y=0;
    
    
    //  objMainBSPline.ptsNURBS(objMainBSPline.controlPointsArray, objMainBSPline.controlPointsWeightsArray,
    //                        Uknot, Vknot, 5, 5, 4, 4, dx, dy, objMainBSPline.pts); //gives the location of a point in the NURB patch
    
    //glVertex3f(objMainBSPline.pts[0], objMainBSPline.pts[1] , objMainBSPline.pts[2]); //location of the point in a NURB patch
    
    //glPushMatrix(); //Copies the matrix on the top of the stack, this would be like save the funcion
    //glColor3f(1,0,1);  //set colour ball
    glTranslatef(0.0, 0.0 , 0.0); // back to origin
    glTranslatef(dx, dy , dz);
    
    glBegin(GL_LINES);
    glColor3fv(color);
    
    x = (float)radius * cos(359*PI/180.0f);
    y= 0;
    z = (float)radius * sin(359*PI/180.0f);
    
    for (int j=0; j<360; j++)
    {
        glVertex3f(x, y, z);
        
        x = (float)radius * cos(j*PI/180.0f);
        y = 0;
        z = (float)radius * sin(j*PI/180.0f);
        
        glVertex3f(x, y, z);
    }
    
    //cout << "PI Value = " << PI << endl;
    
    glEnd();
    
    
    //glPopMatrix(); // Would be equivalent like load the function
    
    
    
    // glutSolidSphere(radius, 5, 5);
    
    //  delete [] Uknot;
    //  delete [] Vknot;
    
    
    
    
    glPopMatrix(); // Would be equivalent like load the function
    
    
    
}




#pragma mark ---- Boundaries Display----
void boundariesDisplay()
{
    //Draw boundaries
    //TOP AND BOTTOM
    for (int i=0;i<IMAX;i++)
    {
        createBubbleXYZNoDeformation(PointMat2[0][i].x, PointMat2[0][i].y, PointMat2[0][i].z, PointMat2[0][i].radius);
        createBubbleXYZNoDeformation(PointMat2[IMAX-1][i].x, PointMat2[IMAX-1][i].y, PointMat2[IMAX-1][i].z, PointMat2[IMAX-1][i].radius);
        
        // just now
        // createBubbleSplineNoDeformation(PointMat2[0][i].u, PointMat2[0][i].v, nodeformationRadius);
        // createBubbleSplineNoDeformation(PointMat2[IMAX-1][i].u,PointMat2[IMAX-1][i].v, nodeformationRadius);
        
        
        // createBubbleSplineT(PointMat[0][i].u,PointMat[0][i].v, initialBubbleRadius);
        // createBubbleSplineT(PointMat[IMAX-1][i].u,PointMat[IMAX-1][i].v, initialBubbleRadius);
        
        
    }
    
    //SIDES
    for (int i=0;i<IMAX;i++)
    {
        
        createBubbleXYZNoDeformation(PointMat2[i][0].x, PointMat2[i][0].y, PointMat2[i][0].z, PointMat2[i][0].radius);
        createBubbleXYZNoDeformation(PointMat2[i][IMAX-1].x, PointMat2[i][IMAX-1].y, PointMat2[i][IMAX-1].z, PointMat2[i][IMAX-1].radius);
        
        //just now
        // createBubbleSplineNoDeformation(PointMat2[i][0].u,PointMat2[i][0].v, nodeformationRadius);
        // createBubbleSplineNoDeformation(PointMat2[i][IMAX-1].u,PointMat2[i][IMAX-1].v, nodeformationRadius);
        
        
        // createBubbleSplineT(PointMat[i][0].u,PointMat[i][0].v, initialBubbleRadius);
        // createBubbleSplineT(PointMat[i][IMAX-1].u,PointMat[i][IMAX-1].v, initialBubbleRadius);
        
        
        
    }
    
    //INTERNAL POINTS
    for(int m=1;m<IMAX-1;m++){
        for(int n=1;n<IMAX-1;n++){
            
            
            createBubbleXYZNoDeformation(PointMat2[m][n].x, PointMat2[m][n].y, PointMat2[m][n].z, PointMat2[m][n].radius);
            
            //just now
            //createBubbleSplineNoDeformation(PointMat2[m][n].u, PointMat2[m][n].v, nodeformationRadius);
            
            
            //createBubbleSplineT(PointMat[m][n].u,PointMat[m][n].v, initialBubbleRadius);
            
        }
    }
    
    //  if (k==250) printMatrix(PointMat2);
    
}

void simulationVector( bubble* vectorLo, int numBubbles, int iter, point_t * l_curve_definition, int numberOfPoints_curve_definition, point_t * convex_hull, int state)
{
    
    point_t currentPointXYZ;
    bubble start = vectorLo[0];
    bubble end = vectorLo[numBubbles-1];
    
    DeltaVector = new point_t [numBubbles]; //initializes delta vector to numBubbles;
    point_t* V1 = new point_t [numBubbles]; //initializes delta vector to numBubbles;
    point_t* V2 = new point_t [numBubbles]; //initializes delta vector to numBubbles;
    
    point_t tangent;
    
    float delta_s = 0.0;
    float _u = 0.0;
   // point_t delta_point;
    float* pts = new float [3];
    
    float* Uknot = new float [9];
    float* Vknot = new float [9];
    
    Uknot[0]= Uknot[1] = Uknot[2]= Uknot[3]= Uknot[4] =  0.0;
    Uknot[5]= Uknot[6] = Uknot[7]= Uknot[8]= Uknot[9] =  1.0; //here how to strech space
    
    
    Vknot[0]= Vknot[1] = Vknot[2]= Vknot[3]= Vknot[4] =  0.0;
    Vknot[5]= Vknot[6] = Vknot[7]= Vknot[8]= Vknot[9] =  1.0;
    
    
    //initial value of xi
    for(int k=0; k<numBubbles; k++)
    {
        DeltaVector[k].x = vectorLo[k].x; //vectorLo no cambia toma lo tienes que ser dinamico
        DeltaVector[k].y = vectorLo[k].y;
        DeltaVector[k].z = vectorLo[k].z;
        
        V1[k].x = vectorLo[k].x; //vectorLo no cambia toma lo tienes que ser dinamico
        V1[k].y = vectorLo[k].y;
        V1[k].z = vectorLo[k].z;
        
        V2[k].x = vectorLo[k].x;
        V2[k].y = vectorLo[k].y;
        V2[k].z = vectorLo[k].z;
        
        
    }
    
    //first loop for the iteration
    for( int ii=0;ii<iter;ii++)
    {
        //printVect(vectorLo, numBubbles);
        
        int m = 0;
        
        for(int i=0;i<numBubbles;i++)
        {
            if(i==0 || i==numBubbles-1)
            {
                // cout << "----: " << ii<< endl;
                // cout << "you enter the loop: " << i << endl ;
                
                // So the borders do not interact
            }
            
            else
            {
                for(int j=0;j<numBubbles;j++)
                {
                    if(i==j)
                    {
                        // So the bubbles do not repeat themselves
                    }
                    
                    else{
                        
                        currentPointXYZ = objBP2D.SimulationXYZ_Vector(vectorLo[j], vectorLo[i]);
                        
                        vectorLo[i].x = currentPointXYZ.x;
                        vectorLo[i].y = currentPointXYZ.y;
                        vectorLo[i].z = currentPointXYZ.z;
                        
                        V2[i].x = currentPointXYZ.x;
                        V2[i].y = currentPointXYZ.y;
                        V2[i].z = currentPointXYZ.z;
                        
                        
                    }
                    
                    
                    
                }
                
                
                
                
                
            }
            
            vectorLo[0] = start;
            vectorLo[numBubbles-1]= end;
            
        }
        
        //    objUtil.printVectPoints(V2, numBubbles, "/Users/Serenity/Dropbox/CMU 2012/V2.txt");
        //    objUtil.printVectPoints(V1, numBubbles, "/Users/Serenity/Dropbox/CMU 2012/V1.txt");
        
        for (int i=0 ;i<numBubbles;i++)
        {
            DeltaVector[i].x = V2[i].x - V1[i].x;
            DeltaVector[i].y = V2[i].y - V1[i].y;
            DeltaVector[i].z = V2[i].z - V1[i].z;
            
        }
        
        //     objUtil.printVectPoints(DeltaVector, numBubbles, "/Users/Serenity/Dropbox/CMU 2012/DeltaVector.txt");
        
        //    objUtil.printVectPoints(l0_curve_definition, 15, "/Users/Serenity/Dropbox/CMU 2012/lo_curve_def.txt");
        
        
        for(int i=0;i<numBubbles;i++)
        {
            if (state==0)
            {
                tangent = objBP2D.Tangent(l_curve_definition, numberOfPoints_curve_definition, V1[i].z,1);
                
                //  cout << "\ntanX: " << tangent.x << endl;
                //  cout << "tanY: " << tangent.y << endl;
                // cout << "tanZ: " << tangent.z << endl;
                
                delta_s = objBP2D.DotProduct( DeltaVector[i], tangent);
                
                delta_s = delta_s/(float)(pow(tangent.x,2)+pow(tangent.y,2)+pow(tangent.z,2));
                
                //  cout <<" vectorLo[i].v: " <<  vectorLo[i].v << endl;
                _u =  vectorLo[i].v + delta_s; //importante to chance u and v
                vectorLo[i].v = _u;
                
                //  cout <<"_u: " << _u << endl;
                //  cout <<" vectorLo[i].v: " <<  vectorLo[i].v << endl;
                
                objMainBSPline.ptsNURBS(convex_hull, w, Uknot, 5, 5, vectorLo[i].v, pts);
                
                vectorLo[i].x = pts[0];
                vectorLo[i].y = pts[1];
                vectorLo[i].z = pts[2];
                
                m++;
            }
            
            if (state==1)
            {
                tangent = objBP2D.Tangent(l_curve_definition, numberOfPoints_curve_definition, V1[i].x,0);
                
                //  cout << "\ntanX: " << tangent.x << endl;
                //  cout << "tanY: " << tangent.y << endl;
                // cout << "tanZ: " << tangent.z << endl;
                
                delta_s = objBP2D.DotProduct( DeltaVector[i], tangent);
                
                delta_s = delta_s/(float)(pow(tangent.x,2)+pow(tangent.y,2)+pow(tangent.z,2));
                
                //  cout <<" vectorLo[i].v: " <<  vectorLo[i].v << endl;
                _u =  vectorLo[i].u + delta_s; //importante to chance u and v
                vectorLo[i].u = _u;
                
                //  cout <<"_u: " << _u << endl;
                //  cout <<" vectorLo[i].v: " <<  vectorLo[i].v << endl;
                
                objMainBSPline.ptsNURBS(convex_hull, w, Uknot, 5, 5, vectorLo[i].u, pts);
                
                vectorLo[i].x = pts[0];
                vectorLo[i].y = pts[1];
                vectorLo[i].z = pts[2];
                
                m++;
            }
            
            //  cout << "V1.x: " << V1[i].x << endl;
            //  cout << "V1.y: " << V1[i].y << endl;
            // cout << "V1.z: " << V1[i].z << endl<< endl;
            
            //   cout << "vectorLo.x: " << vectorLo[i].x << endl;
            //   cout << "vectorLo.y: " << vectorLo[i].y << endl;
            //   cout << "vectorLo.z: " << vectorLo[i].z << endl;
            //   cout<< "--------------"<< endl<<endl;
            
            
            
            
        }
        
        /*
         for (int i=0;i<numBubbles;i++)
         {
         cout << "vectorLo.x: " << vectorLo[i].x << endl;
         cout << "vectorLo.y: " << vectorLo[i].y << endl;
         cout << "vectorLo.z: " << vectorLo[i].z << endl;
         
         tangent = objBP2D.Tangent(l0_curve_definition, 15, V1[i].x,0);
         
         delta_point.x = V2[i].x-V1[i].x;
         delta_point.y = V2[i].y-V1[i].y;
         delta_point.z = V2[i].z-V1[i].z;
         
         delta_s = objBP2D.DotProduct(delta_point, tangent);
         
         delta_s = delta_s/(float)(pow(tangent.x,2)+pow(tangent.y,2)+pow(tangent.z,2));
         _u =  vectorLo[i].v + delta_s; //importante to chance u and v
         
         objMainBSPline.ptsNURBS(d0, w, Uknot, 5, 5, _u, pts);
         
         vectorLo[i].x = pts[0];
         vectorLo[i].y = pts[1];
         vectorLo[i].z = pts[2];
         
         m++;
         
         cout << "\ni:" <<i<< ": "<< l0c[i].v << endl;
         cout << "delta_s: " << delta_s << endl;
         cout << "tangent: " << tangent.x << endl;
         cout <<"_u: " << _u << endl;
         
         cout << "V1.x: " << V1[i].x << endl;
         cout << "V1.y: " << V1[i].y << endl;
         cout << "V1.z: " << V1[i].z << endl<< endl;
         
         cout << "vectorLo.x: " << vectorLo[i].x << endl;
         cout << "vectorLo.y: " << vectorLo[i].y << endl;
         cout << "vectorLo.z: " << vectorLo[i].z << endl;
         cout<< "--------------"<< endl<<endl;
         
         
         
         
         }
         */
        
        /*/
         tangent = objBP2D.Tangent(l0_curve_definition, 15, V1[i].x,0);
         delta_point.x = vectorLo[i].x-V1[i].x;
         delta_point.y = vectorLo[i].y-V1[i].y;
         delta_point.z = vectorLo[i].z-V1[i].z;
         
         delta_s = objBP2D.DotProduct(delta_point, tangent);
         
         delta_s = delta_s/(float)(pow(tangent.x,2)+pow(tangent.y,2)+pow(tangent.z,2));
         _u =  vectorLo[i].u + delta_s; //importante to chance u and v
         
         objMainBSPline.ptsNURBS(d0, w, Uknot, 5, 5, _u, pts);
         
         vectorLo[i].x = pts[0];
         vectorLo[i].y = pts[1];
         vectorLo[i].z = pts[2];
         
         m++;
         
         
         cout << "\ni:" <<i<< ": "<< l0c[i].v << endl;
         cout << "delta_s: " << delta_s << endl;
         cout << "tangent: " << tangent.x << endl;
         cout <<"_u: " << _u << endl;
         
         cout << "V1.x: " << V1[i].x << endl;
         cout << "V1.y: " << V1[i].y << endl;
         cout << "V1.z: " << V1[i].z << endl<< endl;
         
         cout << "vectorLo.x: " << vectorLo[i].x << endl;
         cout << "vectorLo.y: " << vectorLo[i].y << endl;
         cout << "vectorLo.z: l0cu" << vectorLo[i].z << endl;
         cout<< "--------------"<< endl<<endl;
         
         
         */
        
        
    }
    
    
    //if(k%50==250)  objUtil.printMatrix(PointMat2,  k); //prints the matrix to a txt file
    
    // delete [] DeltaVector;
    
    //k_loop++;
    
    
}

void simulation()
{
    
    
    
    float lastu, lastv;
    // int deti = 5;
    // int detj = 1;
    
    /*currentPoint = objBP2D.Simulation(PointMat[6][0], PointMat[deti][detj]);
     
     PointMat[deti][detj].u = currentPoint.u;
     PointMat[deti][detj].v = currentPoint.v;
     
     lastu= currentPoint.u;
     lastv= currentPoint.v;
     
     
     createBubbleSplineT(PointMat[deti][detj].u,PointMat[deti][detj].v, initialBubbleRadius);
     
     
     
     float	Diegol[3]=	{255, 245, 195};
     
     
     glColor3fv(Diegol);
     glPointSize(2);
     //  glBegin(GL_POINTS);
     
     
     
     createBubbleSplineT(PointMat[deti][detj].u,PointMat[deti][detj].v, initialBubbleRadius);
     */
    
    
    
    for(int m=1;m<IMAX-1;m++){
        for(int n=1;n<IMAX-1;n++){
            
            for(int i=0;i<IMAX;i++){
                for(int j=0;j<IMAX;j++){
                    
                    if(i==m && j==n)
                    {
                        //P[m][n].u =  P[m][n].u;
                        // P[m][n].v =  P[m][n].v;
                    }
                    /* if(i==0 && j==0)
                     {
                     
                     
                     }*/
                    
                    else{
                        lastu = PointMat[m][n].u;
                        lastv = PointMat[m][n].v;
                        
                        currentPoint = objBP2D.Simulation(PointMat[i][j], PointMat[m][n]);
                        
                        PointMat[m][n].u = currentPoint.u;
                        PointMat[m][n].v = currentPoint.v;
                        
                        if(PointMat[m][n].u>=0.99) PointMat[m][n].u = lastu; ////IMPORTANT TO CHANGE
                        if(PointMat[m][n].v>=0.99) PointMat[m][n].v = lastv;
                        
                        if(PointMat[m][n].u<=0.01) PointMat[m][n].u = lastu; ////IMPORTANT TO CHANGE
                        if(PointMat[m][n].v<=0.01) PointMat[m][n].v = lastv;
                        
                        
                        
                        
                    }
                    
                    
                    
                }
                
            }
            
            // createBubbleSplineT(PointMat[m][n].u,PointMat[m][n].v, initialBubbleRadius);
            
           
            
            
            
        }
    }
    
    
    k_loop++;
    
    
}

//simulation2 makes the sim in the 2d real not the nurb surface in other words no deformation
void simulation2()
{
    
    
    //  float* Uknot = new float [9];
    //  float* Vknot = new float [9];
    
    //  Uknot[0]= Uknot[1] = Uknot[2]= Uknot[3]= Uknot[4] =  0.0;
    //  Uknot[5]= Uknot[6] = Uknot[7]= Uknot[8]= Uknot[9] =  1.0; //here how to strech space
    
    
    ///  Vknot[0]= Vknot[1] = Vknot[2]= Vknot[3]= Vknot[4] =  0.0;
    //  Vknot[5]= Vknot[6] = Vknot[7]= Vknot[8]= Vknot[9] =  1.0;
    
    
    
    //float prevx, prevy, prevz;
   // float lastx, lasty, lastz;
    //float lastx, lasty, lastz;
    bool mtrue = false;
    
    for(int m=1;m<IMAX-1;m++){
        for(int n=1;n<IMAX-1;n++){
            
            // prevx = PointMat2[m][n].x; //
            //  prevy = PointMat2[m][n].y;
            //  prevz = PointMat2[m][n].z;
            
            
            //  objMainBSPline.ptsNURBS(objMainBSPline.controlPointsArray, objMainBSPline.controlPointsWeightsArray, Uknot, Vknot, 5, 5, 5, 5, prevu,prevv, objMainBSPline.pts);
            
            //  PointMat2[m][n].x = objMainBSPline.pts[0];
            //  PointMat2[m][n].y = objMainBSPline.pts[1];
            //  PointMat2[m][n].z = objMainBSPline.pts[2];
            
            mtrue = true;
            
            for(int i=0;i<IMAX;i++){
                for(int j=0;j<IMAX;j++){
                    
                    if(i==m && j==n)
                    {
                        
                        
                    }
                    /* if(i==0 && j==0)
                     {
                     
                     
                     }*/
                    
                    else{
                        
                        
                        // lastx = PointMat2[i][j].x;
                        // lasty = PointMat2[i][j].y;
                        // lastz = PointMat2[i][j].z;
                        
                        //cout << "\nU:" << lastu << endl;
                        // cout << "V:" << lastv << endl;
                        
                        
                        // objMainBSPline.ptsNURBS(objMainBSPline.controlPointsArray, objMainBSPline.controlPointsWeightsArray, Uknot, Vknot, 5, 5, 5, 5, lastu,lastv, objMainBSPline.pts);
                        
                        //PointMat2[i][j].x = objMainBSPline.pts[0];
                        //PointMat2[i][j].y = objMainBSPline.pts[1];
                        //PointMat2[i][j].z = objMainBSPline.pts[2];
                        
                        
                        // lastx = PointMat2[i][j].x;
                        //  lasty = PointMat2[i][j].y;
                        //  lastz = PointMat2[i][j].z;
                        
                        //currentPoint = objBP2D.Simulation(PointMat2[i][j], PointMat2[m][n]);
                        
                        currentPointXYZ = objBP2D.SimulationXYZ(PointMat2[i][j], PointMat2[m][n]);
                        
                        PointMat2[m][n].x = currentPointXYZ.x;
                        PointMat2[m][n].y = currentPointXYZ.y;
                        PointMat2[m][n].z = currentPointXYZ.z;
                        
                        
                        if(mtrue == true)
                        {
                            
                            //   cout <<"i:" << i <<"\t j: " << j << endl;
                            //  cout << "\nX:" << PointMat2[m][n].x  << endl;
                            //  cout << "Y:" << PointMat2[m][n].y  << endl;
                            //   cout << "Z:" << PointMat2[m][n].z  << endl;
                            
                            //  mtrue = false;
                        }
                        
                        
                        
                        // if(PointMat2[m][n].x>=5.0) PointMat2[m][n].x = lastx; ////IMPORTANT TO CHANGE
                        // if(PointMat2[m][n].z>=5.0) PointMat2[m][n].z = lastz;
                        
                        /// if(PointMat2[m][n].x<=-1.0) PointMat2[m][n].x = lastx; ////IMPORTANT TO CHANGE
                        //if(PointMat2[m][n].z<=-1.0) PointMat2[m][n].z = lastz;
                        
                        
                        
                    }
                    
                    
                    
                }
                
            }
            
            
            
            // createBubbleSplineT(PointMat[m][n].u,PointMat[m][n].v, initialBubbleRadius);
            
          
            
            
            
        }
    }
    
    
    //if(k%50==250)  printMatrix(PointMat2,  k); //prints the matrix to a txt file
    
    k_loop++;
    
    
}

//simulation3 makes the sim in the 2d real not the nurb surface in other words no deformation
void simulation3()
{
    
    
    float lastu, lastv;
    
    for(int m=1;m<IMAX-1;m++){
        for(int n=1;n<IMAX-1;n++){
            
            for(int i=0;i<IMAX;i++){
                for(int j=0;j<IMAX;j++){
                    
                    if(i==m && j==n)
                    {
                        
                        
                    }
                    /* if(i==0 && j==0)
                     {
                     
                     
                     }*/
                    
                    else{
                        lastu = PointMat2[m][n].u;
                        lastv = PointMat2[m][n].v;
                        
                        currentPoint = objBP2D.Simulation(PointMat2[i][j], PointMat2[m][n]);
                        
                        PointMat2[m][n].u = currentPoint.u;
                        PointMat2[m][n].v = currentPoint.v;
                        
                        if(PointMat2[m][n].u>=0.99) PointMat2[m][n].u = lastu; ////IMPORTANT TO CHANGE
                        if(PointMat2[m][n].v>=0.99) PointMat2[m][n].v = lastv;
                        
                        if(PointMat2[m][n].u<=0.01) PointMat2[m][n].u = lastu; ////IMPORTANT TO CHANGE
                        if(PointMat2[m][n].v<=0.01) PointMat2[m][n].v = lastv;
                        
                        
                        
                        
                    }
                    
                    
                    
                }
                
            }
            
            // createBubbleSplineT(PointMat[m][n].u,PointMat[m][n].v, initialBubbleRadius);
         
            
            
        }
    }
    
    
    
    k_loop++;
    
    
}

//simulation vector makes the sim in the 2d real not the nurb surface in other words no deformation
void simulationVector2( bubble* vectorLo, int numBubblesBoundary, int numBubblesTotal)
{
    for(int i=numBubblesBoundary ;i<numBubblesTotal;i++){
        for(int j=0;j<numBubblesTotal;j++){
            if(i==j)
            {
                
            }
            
            else
            {
                
                currentPointXYZ = objBP2D.SimulationXYZ(vectorLo[j], vectorLo[i]); //j changes faster always second position
                
                vectorLo[i].x = currentPointXYZ.x;
                vectorLo[i].y = currentPointXYZ.y;
                vectorLo[i].z = currentPointXYZ.z;
                
               // cout << currentPointXYZ.x << endl;
                
                
            }
            
            
            
        }
        
    }
    
    
    kinternal_loop++;
    
}


#pragma mark <F> main display function

void maindisplay(void)
{
	GLdouble xmin, xmax, ymin, ymax;
	// far frustum plane
	GLdouble zFar = -gCamera.viewPos.z + gShapeSize * 0.5;
	// near frustum plane clamped at 1.0
	GLdouble zNear = MIN (-gCamera.viewPos.z - gShapeSize * 0.5, 1.0);
	// window aspect ratio
	GLdouble aspect = gCamera.screenWidth / (GLdouble)gCamera.screenHeight;
    
    glEnable(GL_LIGHTING); //not really used just put here to remind me to use it... CHANGE
    
    glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
    
	if (aspect > 1.0) {
		ymax = zNear * tan (gCamera.aperture * 0.5 * DTOR);
		ymin = -ymax;
		xmin = ymin * aspect;
		xmax = ymax * aspect;
	} else {
		xmax = zNear * tan (gCamera.aperture * 0.5 * DTOR);
		xmin = -xmax;
		ymin = xmin / aspect;
		ymax = xmax / aspect;
	}
	glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
	
	
	gluLookAt (gCamera.viewPos.x, gCamera.viewPos.y, gCamera.viewPos.z,
               gCamera.viewPos.x + gCamera.viewDir.x,
               gCamera.viewPos.y + gCamera.viewDir.y,
               gCamera.viewPos.z + gCamera.viewDir.z,
               gCamera.viewUp.x, gCamera.viewUp.y ,gCamera.viewUp.z);
    
	// track ball rotation
	glRotatef (gTrackBallRotation[0], gTrackBallRotation[1], gTrackBallRotation[2], gTrackBallRotation[3]);
	glRotatef (gWorldRotation[0], gWorldRotation[1], gWorldRotation[2], gWorldRotation[3]);
    
    glTranslatef(-1.0, 0.0, -2); // this translations is done after a world rotation so we are looking at x-z and then translation
	
	glClearColor (0.2f, 0.2f, 0.4f, 1.0f);	// clear the surface
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    drawGLText (gCamera.screenWidth, gCamera.screenHeight);
    
    
    //Erases the control points and the convex hull from the screen
    if(gShowSplineControlPoints)
    {
        objMainBSPline.InitializeControlPoints();
        
        
        float* Uknot = new float [9];
        float* Vknot = new float [9];
        
        Uknot[0]= Uknot[1] = Uknot[2]= Uknot[3]= Uknot[4] =  0.0;
        Uknot[5]= Uknot[6] = Uknot[7]= Uknot[8]= Uknot[9] =  1.0; //here how to strech space
        
        
        Vknot[0]= Vknot[1] = Vknot[2]= Vknot[3]= Vknot[4] =  0.0;
        Vknot[5]= Vknot[6] = Vknot[7]= Vknot[8]= Vknot[9] =  1.0;
        
        
        
        float	LightGoldenrod1[3]=	{0.5, 0.92549, 0.545098/5};
        
        
        glColor3fv(LightGoldenrod1);
        
        glBegin(GL_POINTS);
        for(int i=0;i<5;i++) {
            for(int j=0;j<5;j++) {
                
                float Points[3] = {objMainBSPline.controlPointsArray[i][j].x,
                    objMainBSPline.controlPointsArray[i][j].y,
                    objMainBSPline.controlPointsArray[i][j].z };
                
                glVertex3fv(Points);
                
            }
        }
        
        glEnd();
        
        
        glBegin(GL_LINES);
        
        for(int i=0;i<5-1;i++) {
            for(int j=0;j<5;j++) {
                float Point1[3] = {objMainBSPline.controlPointsArray[i][j].x,
                    objMainBSPline.controlPointsArray[i][j].y,
                    objMainBSPline.controlPointsArray[i][j].z };
                
                float Point2[3] = {objMainBSPline.controlPointsArray[i+1][j].x,
                    objMainBSPline.controlPointsArray[i+1][j].y,
                    objMainBSPline.controlPointsArray[i+1][j].z };
                
                
                glVertex3fv(Point1);
                glVertex3fv(Point2);
                
            }
        }
        
        glEnd();
        
        
        glBegin(GL_LINES);
        
        
        for(int j=0;j<5-1;j++) {
            for(int i=0;i<5;i++) {
                
                float Point1[3] = {objMainBSPline.controlPointsArray[i][j].x,
                    objMainBSPline.controlPointsArray[i][j].y,
                    objMainBSPline.controlPointsArray[i][j].z };
                
                float Point2[3] = {objMainBSPline.controlPointsArray[i][j+1].x,
                    objMainBSPline.controlPointsArray[i][j+1].y,
                    objMainBSPline.controlPointsArray[i][j+1].z };
                
                
                glVertex3fv(Point1);
                glVertex3fv(Point2);
                
            }
        }
        
        glEnd();
        
        
        glPointSize(1);
        float	LightGoldenrod13[3]=	{1.0, 1-0.92549, 0.545098/5};
        glColor3fv(LightGoldenrod13);
        
        
        float u,v;
        
        if(sFlag == GL_TRUE )
        {
            for (int i=0;i<IMAX;i++){
                
                u=i/(float)(IMAX-1)*1; //change to 2 to strech space
                
                
                for(int j=0;j<JMAX ;j++){
                    
                    
                    v=j/(float)(JMAX-1)*1;
                    
                    
                    objMainBSPline.ptsNURBS(objMainBSPline.controlPointsArray, objMainBSPline.controlPointsWeightsArray, Uknot, Vknot, 5, 5, 5, 5, u,v, objMainBSPline.pts);
                    
                    sMAT[i][j].x = objMainBSPline.pts[0];
                    sMAT[i][j].y = objMainBSPline.pts[1];
                    sMAT[i][j].z = objMainBSPline.pts[2];
                    
                    pointsBSpline.push_back(sMAT[i][j]);
                    
                    
                }
                
            }
            
        }
        
        sFlag =GL_FALSE;
        
        
        
        glEnd();
        
        glBegin(GL_LINES);
        
        for(int i=0;i<IMAX-1;i++) {
            for(int j=0;j<JMAX;j++) {
                
                
                float Point1[3] = { sMAT[i][j].x,sMAT[i][j].y ,sMAT[i][j].z  };
                float Point2[3] = { sMAT[i+1][j].x,sMAT[i+1][j].y ,sMAT[i+1][j].z  };
                
                glVertex3fv(Point1);
                glVertex3fv(Point2);
                
            }
        }
        
        glEnd();
        
        
        glBegin(GL_LINES);
        
        
        for(int j=0;j<JMAX-1;j++) {
            for(int i=0;i<IMAX;i++) {
                
                float Point1[3] = { sMAT[i][j].x,sMAT[i][j].y ,sMAT[i][j].z  };
                float Point2[3] = { sMAT[i][j+1].x,sMAT[i][j+1].y ,sMAT[i][j+1].z  };
                
                glVertex3fv(Point1);
                glVertex3fv(Point2);
                
                
            }
        }
        
        glEnd();
        
        
        delete [] Uknot;
        delete [] Vknot;
        
        
    }
    
    //Starts the simulation for the given geometry and stops after 250 iterations
    if(sSimulationInBSplinePatch)
    {
        //simulation();
        //simulation2(); //working
        //simulation3();
        if(k_loop<1000)
        {
            //simulationVector( l0c, numberOfBubblesl0, 5, l0_curve_definition, 15, l0c, d0, 0);//
            
            simulationVector(l0c, numberOfBubblesl0, 1, l0_curve_definition, 50, d0, 0);
           //
            simulationVector(l1c, numberOfBubblesl1, 1, l1_curve_definition, 50, d1, 1);
            
            simulationVector(l2c, numberOfBubblesl2, 1, l2_curve_definition, 50, d2, 0);
            
            simulationVector(l3c, numberOfBubblesl3, 1, l3_curve_definition, 50, d3, 1);
            
            
            //  simulationVector(l1c, numberOfBubblesl1, );
            //simulationVector( l1c, numberOfBubblesl1, 5, l1_curve_definition, 50, l1c, d0, 0);// (l0c, numberOfBubblesl0, 5,);
            
            ////simulationVector(l1c, numberOfBubblesl1, 5);
            //simulationVector(l2c, numberOfBubblesl2, 5);
            //simulationVector(l3c, numberOfBubblesl3, 5);
        }
        
        
        if (k_loop% MAX_NUMBER_OF_ITERATIONS_K_BOUND-1 == 0)
        {
            sSimulationInBSplinePatch = false;
            
            vectorForSimulation(l0c, numberOfBubblesl0,
                                l1c, numberOfBubblesl1,
                                l2c, numberOfBubblesl2,
                                l3c, numberOfBubblesl3,
                                7,5,6,6);
            
        }
        

            
        
        k_loop++;
        
    }
    
    
    ////////---------------------- VECTOR SIM START

    
    int totalNum = numberOfBubblesl0 + numberOfBubblesl1 + numberOfBubblesl2 +numberOfBubblesl3 -3;
    
    if (sSimulationInternalBSplinePatch == true && k_loop > 300)
    {
       // if (k_loop < 700)
     //   {
      //      cout<< "\n Boundaries need more iterations" << endl;
            //sSimulationInBSplinePatch = true;

       // }
     
        simulationVector2(vectorSimulationAllPoints, totalNum, NUMBER_OF_BUBBLES_IN_SIMULATION);
        
        if (kinternal_loop==MAX_NUMBER_OF_ITERATIONS_K_SURF) sSimulationInternalBSplinePatch = sSimulationInternalBSplinePatch-1;
        
        
    }
    
    
    
    //shows the boundaris in the vector
    if(gVectorSimulation)
    {
        
        float	colorUSER[3]	=	{0.23, 0.866667, 0.5898654654};
        
        
              
        for(int i=0;i<NUMBER_OF_BUBBLES_IN_SIMULATION;i++) //34
        {
            
            colorUSER[0]	=	i/(float)NUMBER_OF_BUBBLES_IN_SIMULATION;
            colorUSER[1]	=	1-i/(float)NUMBER_OF_BUBBLES_IN_SIMULATION;
            colorUSER[2]	=	i/(float)NUMBER_OF_BUBBLES_IN_SIMULATION;


            
            createBubbleXYZVector(vectorSimulationAllPoints[i].x, vectorSimulationAllPoints[i].y, vectorSimulationAllPoints[i].z, vectorSimulationAllPoints[i].radius, colorUSER);
            
        }
        
        if(kinternal_loop==600) objUtil.printVect(vectorSimulationAllPoints, NUMBER_OF_BUBBLES_IN_SIMULATION, "/Users/Serenity/Dropbox/CMU 2012/export_coor.txt");
      
        
    }
    
    ////////---------------------- VECTOR SIM END

    
    
    
#pragma mark <F> Boundaries
    //boundariesDisplay();
    
    if(GgShowBoundariers)
    {
        //----------------
        // Vector defined simulation
        //----------------
        //TOP AND BOTTOM
        for (int i=0;i<numberOfBubblesl0;i++)
        {
            createBubbleXYZNoDeformationBoundary(l0c[i].x, l0c[i].y, l0c[i].z, l0c[i].radius);
            
            
        }
        
        for (int i=0;i<numberOfBubblesl1;i++)
        {
            
            createBubbleXYZNoDeformationBoundary(l1c[i].x, l1c[i].y, l1c[i].z, l1c[i].radius);
            
            
        }
        
        for (int i=0;i<numberOfBubblesl2;i++)
        {
            
            createBubbleXYZNoDeformationBoundary(l2c[i].x, l2c[i].y, l2c[i].z, l2c[i].radius);
            
            
        }
        
        for (int i=0;i<numberOfBubblesl3;i++)
        {
            
            createBubbleXYZNoDeformationBoundary(l3c[i].x, l3c[i].y, l3c[i].z, l3c[i].radius);
            
        }
        
        
    }
    
    glutSwapBuffers();
    
    
	
	
}



void special(int key, int px, int py)
{
    gLastKey = key;
    switch (key) {
        case GLUT_KEY_UP: // arrow forward, close in on world
            gCamera.focalLength -= 1.5f;
            if (gCamera.focalLength < 0.0f)
                gCamera.focalLength = 0.0f;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN: // arrow back, back away from world
            gCamera.focalLength += 1.5f;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT: // arrow left, smaller aperture
            gCamera.aperture -= 1.5f;
            if (gCamera.aperture < 0.0f)
                gCamera.aperture = 0.0f;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT: // arrow right, larger aperture
            gCamera.aperture += 1.5f;
            glutPostRedisplay();
            break;
    }
}

void mouseDolly (int x, int y)
{
	if (gDolly) {
		GLfloat dolly = (gDollyPanStartPoint[1] - y) * -gCamera.viewPos.z / 200.0f;
		GLfloat eyeRelative = gCamera.eyeSep / gCamera.focalLength;
		gCamera.focalLength += gCamera.focalLength / gCamera.viewPos.z * dolly;
		if (gCamera.focalLength < 1.0)
			gCamera.focalLength = 1.0;
		gCamera.eyeSep = gCamera.focalLength * eyeRelative;
		gCamera.viewPos.z += dolly;
		if (gCamera.viewPos.z == 0.0) // do not let z = 0.0
			gCamera.viewPos.z = 0.0001;
		gDollyPanStartPoint[0] = x;
		gDollyPanStartPoint[1] = y;
		glutPostRedisplay();
	}
}

void mousePan (int x, int y)
{
	if (gPan) {
		GLfloat panX = (gDollyPanStartPoint[0] - x) / (900.0f / -gCamera.viewPos.z);
		GLfloat panY = (gDollyPanStartPoint[1] - y) / (900.0f / -gCamera.viewPos.z);
		gCamera.viewPos.x -= panX;
		gCamera.viewPos.y -= panY;
		gDollyPanStartPoint[0] = x;
		gDollyPanStartPoint[1] = y;
		glutPostRedisplay();
	}
}

void drag(int x, int y)
{
    a = x/1.0;
    b = 300.0 - (y/1.0);
    glutPostRedisplay();}

void mouseTrackball (int x, int y)
{
	if (gTrackBall) {
		rollToTrackball (x, y, gTrackBallRotation);
		glutPostRedisplay();
	}
}


void mouse (int button, int state, int x, int y)
{
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		if (gDolly) { // if we are currently dollying, end dolly
			mouseDolly (x, y);
			gDolly = GL_FALSE;
			glutMotionFunc (NULL);
			gTrackBallRotation [0] = gTrackBallRotation [1] = gTrackBallRotation [2] = gTrackBallRotation [3] = 0.0f;
			glutMotionFunc (NULL);
		} else if (gPan) {
			mousePan (x, y);
			gPan = GL_FALSE;
			glutMotionFunc (NULL);
			gTrackBallRotation [0] = gTrackBallRotation [1] = gTrackBallRotation [2] = gTrackBallRotation [3] = 0.0f;
			glutMotionFunc (NULL);
		}
		startTrackball (x, y, 0, 0, gCamera.screenWidth, gCamera.screenHeight);
		glutMotionFunc (mouseTrackball);
		gTrackBall = GL_TRUE;
	} else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) {
		gTrackBall = GL_FALSE;
		glutMotionFunc (NULL);
		rollToTrackball (x, y, gTrackBallRotation);
		if (gTrackBallRotation[0] != 0.0)
			addToRotationTrackball (gTrackBallRotation, gWorldRotation);
		gTrackBallRotation [0] = gTrackBallRotation [1] = gTrackBallRotation [2] = gTrackBallRotation [3] = 0.0f;
	}
	/*else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) { //GLUT_MIDDLE_BUTTON
     if (gTrackBall) {// if we are currently trackballing, end trackball
     gTrackBall = GL_FALSE;
     glutMotionFunc (NULL);
     rollToTrackball (x, y, gTrackBallRotation);
     if (gTrackBallRotation[0] != 0.0)
     addToRotationTrackball (gTrackBallRotation, gWorldRotation);
     gTrackBallRotation [0] = gTrackBallRotation [1] = gTrackBallRotation [2] = gTrackBallRotation [3] = 0.0f;
     } else if (gPan) {
     mousePan (x, y);
     gPan = GL_FALSE;
     glutMotionFunc (NULL);
     gTrackBallRotation [0] = gTrackBallRotation [1] = gTrackBallRotation [2] = gTrackBallRotation [3] = 0.0f;
     glutMotionFunc (NULL);
     }
     gDollyPanStartPoint[0] = x;
     gDollyPanStartPoint[1] = y;
     glutMotionFunc (mouseDolly);
     gDolly = GL_TRUE;
     } else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_UP)) { //GLUT_MIDDLE_BUTTON
     mouseDolly (x, y);
     gDolly = GL_FALSE;
     glutMotionFunc (NULL);
     gTrackBallRotation [0] = gTrackBallRotation [1] = gTrackBallRotation [2] = gTrackBallRotation [3] = 0.0f;
     glutMotionFunc (NULL);
     }*/
    
	else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
		if (gTrackBall) {// if we are currently trackballing, end trackball
			gTrackBall = GL_FALSE;
			glutMotionFunc (NULL);
			rollToTrackball (x, y, gTrackBallRotation);
			if (gTrackBallRotation[0] != 0.0)
				addToRotationTrackball (gTrackBallRotation, gWorldRotation);
			gTrackBallRotation [0] = gTrackBallRotation [1] = gTrackBallRotation [2] = gTrackBallRotation [3] = 0.0f;
		} else if (gDolly) {
			mouseDolly (x, y);
			gDolly = GL_FALSE;
			glutMotionFunc (NULL);
			gTrackBallRotation [0] = gTrackBallRotation [1] = gTrackBallRotation [2] = gTrackBallRotation [3] = 0.0f;
			glutMotionFunc (NULL);
		}
		gDollyPanStartPoint[0] = x;
		gDollyPanStartPoint[1] = y;
		glutMotionFunc (mousePan);
		gPan = GL_TRUE;
	} else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_UP)) {
		mousePan (x, y);
		gPan = GL_FALSE;
		glutMotionFunc (NULL);
		gTrackBallRotation [0] = gTrackBallRotation [1] = gTrackBallRotation [2] = gTrackBallRotation [3] = 0.0f;
		glutMotionFunc (NULL);
	}
}

void key(unsigned char inkey, int px, int py)
{
    gLastKey = inkey;
    switch (inkey) {
        case 27:
            exit(0);
            break;
        case 'h': // help
        case 'H':
            gShowHelp =  1 - gShowHelp;
            glutPostRedisplay();
            break;
        case 'i': // info
        case 'I':
            gShowInfo =  1 - gShowInfo;
            glutPostRedisplay();
            break;
        case 'c':
        case 'C':
            gShowSplineControlPoints =  1 - gShowSplineControlPoints;
            glutPostRedisplay();
            break; // print point spline
        case 'y':
        case 'Y':
            sSimulationInBSplinePatch =  1 - sSimulationInBSplinePatch;
            glutPostRedisplay();
            break; // print point spline
        case 's':
        case 'S':
            gVectorSimulation =  1 - gVectorSimulation;
            glutPostRedisplay();
            break; // print point spline
        case 'm':
        case 'M':
            sSimulationInternalBSplinePatch =  1 - sSimulationInternalBSplinePatch;
            glutPostRedisplay();
            break; // print point spline
        case 'b':
        case 'B':
            GgShowBoundariers =  1 - GgShowBoundariers;
            glutPostRedisplay();
            break; // print point spline

            
            
            
        default:   break;
            
    }
}

void spaceballmotion (int x, int y, int z)
{
	long deadZone = 105;
	float scale = -gCamera.viewPos.z * 0.00000001f;
	if (abs (x) > deadZone) {
		GLfloat panX = abs (x) * x * scale;
		gCamera.viewPos.x += panX;
	}
	if (abs (y) > deadZone) {
		GLfloat panY = abs (y) * y * scale;
		gCamera.viewPos.y -= panY;
	}
	if (abs (z) > deadZone) {
		GLfloat dolly = abs (z) * z * scale;
		gCamera.viewPos.z += dolly;
		if (gCamera.viewPos.z == 0.0) // do not let z = 0.0
			gCamera.viewPos.z = 0.0001;
	}
	glutPostRedisplay();
}

void spaceballrotate (int rx, int ry, int rz)
{
	long deadZone = 60;
	float rotation[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	// handle rotations about each respective axis
	if (abs (rx) > deadZone) {
		rotation[0] = abs (rx) * -rx * 0.0000008f;
		rotation[1] = 1.0f;
		rotation[2] = 0.0f;
		rotation[3] = 0.0f;
		addToRotationTrackball (rotation, gWorldRotation);
	}
	if (abs (ry) > deadZone) {
		rotation[0] = abs (ry) * ry * 0.0000008f;
		rotation[1] = 0.0f;
		rotation[2] = 1.0f;
		rotation[3] = 0.0f;
		addToRotationTrackball (rotation, gWorldRotation);
	}
	if (abs(rz) > deadZone) {
		rotation[0] = abs (rz) * -rz * 0.0000008f;
		rotation[1] = 0.0f;
		rotation[2] = 0.0f;
		rotation[3] = 1.0f;
		addToRotationTrackball (rotation, gWorldRotation);
	}
	glutPostRedisplay();
}

#pragma mark ---- menu ----

void menuOb (int value)
{
    switch (value) {
        case 0:  WIRE = !WIRE;		break;
        default:   				break;
    }
    glutPostRedisplay();
}

#pragma mark ---- timer for animation ----

void Timer(int iUnused)
{
    glutPostRedisplay();
    glutTimerFunc(30, Timer, 0);
}

#pragma mark ---- main ----

int main (int argc, const char * argv[])
{
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // non-stereo for main window
	glutInitWindowPosition (300, 50);
	glutInitWindowSize (WIDTH, HEIGHT);
	gMainWindow = glutCreateWindow("BUBBLE PACKING IMPLEMENTATION CMU");
    
    init(); // standard GL init
    
    glutReshapeFunc (reshape);
    glutDisplayFunc (maindisplay);
    Timer(0);
	glutKeyboardFunc (key);
	glutSpecialFunc (special);
    
	glutMouseFunc (mouse);
    glutMotionFunc(drag);
	glutSpaceballMotionFunc(spaceballmotion);
	glutSpaceballRotateFunc(spaceballrotate);
    
    glutMainLoop();
    return 0;
}





