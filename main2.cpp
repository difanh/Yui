//
//  main2.cpp
//  Yui
//
//  Created by Diego Andrade on 8/30/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

//#include "main2.h"


//
//  main.cpp
//  Yui
//
//  Created by Diego Andrade on 6/13/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

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

//#include "AllColor.h"

#define DTOR 0.017453925
#define CROSSPROD(p1,p2,p3) \
p3.x = p1.y*p2.z - p1.z*p2.y; \
p3.y = p1.z*p2.x - p1.x*p2.z; \
p3.z = p1.x*p2.y - p1.y*p2.x

#define PI 4*atan(1)

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

enum {
	kTextureSize = 256
};

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



GLfloat gShapeSize = 11.0f;

GLint gDollyPanStartPoint[2] = {0, 0};
GLfloat gTrackBallRotation [4] = {0.0, 0.0, 0.0, 0.0};
GLboolean gDolly = GL_FALSE;
GLboolean gPan = GL_FALSE;
GLboolean gTrackBall = GL_FALSE;
GLfloat gWorldRotation [4] = {180, 0.0, 1.0, 0.0}; //{155.0, 0.0, -1.0, 0.0};

GLboolean gLines = GL_FALSE;
GLboolean gPolygons = GL_TRUE;
GLboolean gSplines = GL_FALSE;
GLboolean gPrint = GL_FALSE;
GLboolean gGeometrySpline = GL_FALSE;


GLboolean gShowHelp = GL_TRUE;
GLboolean gShowInfo = GL_TRUE;

GLboolean sLastIter = GL_TRUE;
GLboolean gKRestart = GL_FALSE;
GLboolean sWire = GL_TRUE;

GLboolean sFlag = GL_TRUE;
GLboolean sCreateBubbleBSpline = GL_FALSE;

GLboolean sSubdivision = GL_TRUE;

GLboolean sOneBubble = GL_TRUE;
GLboolean sResetSim = GL_TRUE;

myPoint3D S;

GLboolean gShowSplineControlPoints = GL_TRUE;

recCamera gCamera;
recVec gOrigin = {0.0, 0.0, 0.0};

int gLastKey = ' ';

int gMainWindow = 0;

int SixBubbleState = 0;

GLuint gPointList = NULL;
GLuint gWireList = NULL;
GLuint gSolidList = NULL;

static GLboolean WIRE=0;		// draw mesh in wireframe?
static GLboolean RUNGAKUTTA=0;		// starts simualtion Runge Kutta
static GLboolean EULERV=0;		// starts simualtion Runge Kutta

float* location_x =  new float [200]; // Vector with the x locations for the bubbles 1D
float* location_y =  new float [200]; // Vector with the y locations for the bubbles 1D  CHANGE THIS SO THE MEMORY IS DYNAMIC

GLfloat gfPosX = 0.0;
GLfloat gfDeltaX = .01;

int k=0;

#define HEIGHT 600
#define WIDTH 800

float a=HEIGHT;
float b=WIDTH;

myPoint3D** sMAT;

int IMAX = 12;
int JMAX = 12;

bubble ** PointMat; //matrix saves all the data for all the points in the surface

bubble ** PointMat2; //matrix saves all the data for all the points in the surface


static GLint snowman_display_list;

float distance_geometry =4.0;

int number_of_bubbles = IMAX; //(int) (distance_geometry)/(int) IMAX *2;

float nodeformationRadius = distance_geometry/(float)number_of_bubbles*0.5+0.015;


float initialBubbleRadius = nodeformationRadius/(float) distance_geometry;// 0.05;//10-0.0523;//7-0.083;//1/(float)7/(float)2;


#pragma mark ---- User's Objects ----

Spline objSpline;
BubbleGeometry objBB;
RungeKutta objRK;
Euler objEuler;

BubblePacking objBP;

BSPline objMainBSPline;

Subdivision objMainSubdivision;

BubblePacking2D objBP2D;

vector<Point2D> location_2d;
vector<Point2D> location_2d_tmp;

vector<Point2D> location_bezier_2d; //For curve definition
vector<Point2D> location_bubbles_bezier_2d; //For bubble definition

vector<Point2D> location_2da;

vector<myPoint3D> pointsBSpline;

bubble B1,B2,B3;
PointUVp currentPoint;


#pragma mark ---- gCamera control ----

void gCameraReset(void)
{
    gCamera.aperture = 25;
    gCamera.focalLength = 25;
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

void drawSphere(double r, int lats, int longs)
{
    int i, j;
    for(i = 0; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);
        
        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);
        
        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++) {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);
            
            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0, y * zr0, z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1, y * zr1, z1);
        }
        glEnd();
    }
}

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
        
        sprintf (outString, "Animation Current Iteration: %0.1d",k);
		drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
        
        sprintf (outString, "Max Number of Iterations for Runge Kutta: %0.1d", objBB._max_iteration);
		drawGLString (10, window_height - (lineSpacing * line++) - startOffest, outString);
        
        sprintf (outString, "Number of Bubbles in the Simulation: %0.1d", objBB._number_of_bubbles_v);
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

void init12 (void)
{
	glEnable(GL_DEPTH_TEST);
    
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);
    
	glColor3f(1.0,1.0,1.0);
    
	//BuildGeometry (kTranguloidTrefoil, 4, 64, 3, &gSolidList, &gWireList, &gPointList);
    // dodecahedron();
	
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
    //objSpline.SplinePointsLocation();   //Create location on spline
    
    // objBB._location_vector_spline_2d = objSpline.spline_location_2d; //Estoy pasando la info al vector de //esta manera o que????s
    
    //objSpline.
    
    cout << "\n --------------- SPLINE CURVE POINTS DEFINITION : " << endl;
    
    for (int i=0; i<objSpline.spline_location_2d.size();i++)
    {
        //slocation_2d.push_back(Point2D(objSpline.spline_location_2d[i].x, objSpline.spline_location_2d[i].y));
        
        location_2d.push_back(objSpline.spline_location_2d[i]);
        cout << "x: " << location_2d[i].x << "\t y: " << location_2d[i].y <<endl;
    }
    
    
    cout << "\n --------------- BEZIER CURVE POINTS DEFINITION : " << endl;
    
    
    for (int i=0; i<objSpline.bezier_location_2d.size();i++)
    {
        //slocation_2d.push_back(Point2D(objSpline.spline_location_2d[i].x, objSpline.spline_location_2d[i].y));
        
        location_bezier_2d.push_back(objSpline.bezier_location_2d[i]);
        cout <<"Id["<<i<<"] " << "x: " << location_bezier_2d[i].x << "\t y: " << location_bezier_2d[i].y <<endl;
    }
    
    cout << "\n --------------- BEZIER BUBBLE DEFINITION: " << endl;
    
    
    for (int i=0; i<objSpline.bezier_points_location_2d.size();i++)
    {
        //slocation_2d.push_back(Point2D(objSpline.spline_location_2d[i].x, objSpline.spline_location_2d[i].y));
        
        location_bubbles_bezier_2d.push_back(objSpline.bezier_points_location_2d[i]);
        cout << "x: " << location_bubbles_bezier_2d[i].x << "\t y: " << location_bubbles_bezier_2d[i].y <<endl;
    }
    
    
    myPoint3D S(0,0,0);
    
    //  location_2da = location_bubbles_bezier_2d;
    
	glPolygonOffset (1.0, 1.0);
	
    SetLighting(1); //Lighting function
	
    glEnable(GL_LIGHTING);
    
    
    
    
    
    //----------------
    // bubble packing 2d
    //----------------
    
    objMainBSPline.InitializeControlPoints();
    
    B1.u = 0.3;
    B1.v = 0.5;
    B1.radius = 0.05;
    
    B2.u = 0.4;
    B2.v = 0.5;
    B2.radius = 0.05;
    
    B3.u = 0.4;
    B3.v = 0.5;
    B3.radius = 0.05;
    
    
    //Initializes U, V and P matrices
    
    
    
    PointMat = new bubble * [IMAX];
    for(int i=0;i<IMAX;i++){
        PointMat[i] = new bubble  [JMAX];
        for(int j=0;j<JMAX;j++){
            PointMat[i][j].radius = initialBubbleRadius; //change here if needed
            PointMat[i][j].u = 0.0;
            PointMat[i][j].v = 0.0;
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
            PointMat2[i][j].idx = 0.0;
        }
        
    }
    
#pragma mark >  INIT().subdivisionHardCode
    
    
    objBP2D.subdivisionHardCode( PointMat, IMAX, JMAX);
    
    objBP2D.subdivisionHardCode2( PointMat2 , IMAX, JMAX, distance_geometry);
    
    
    snowman_display_list = createDL();
    
    
    //number_of_bubbles = (int)(4/10)*2;
    
    // nodeformationRadius = 2/(float)(number_of_bubbles);
    
    
    
    
    //-----------------
    
}

void reshape (int w, int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	gCamera.screenWidth = w;
	gCamera.screenHeight = h;
	glutPostRedisplay();
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(gfPosX, 0.25, 0.0);
    glVertex3f(1.0 - gfPosX, 0.75,0.0);
    glEnd();
    //glutSwapBuffers();
    gfPosX += gfDeltaX;
    if (gfPosX >= 1.0 || gfPosX <= 0.0) {
        gfDeltaX = -gfDeltaX;
    }
}


//This function creates bubbles in a BSPline surface
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
    //   glTranslatef(1.0, 0.0, -2.0);
    
    
    // float radius = 0.1;
    
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
    
    //cout << "PI Value = " << PI << endl;
    
    glEnd();
    
    delete [] Uknot;
    delete [] Vknot;
    
    
    
}


#pragma mark > create Bubble NO deformation



//This function creates bubbles in a BSPline surface
void createBubbleSplineNoDeformation(float dx, float dy, float radius)
{
    glPushMatrix(); //Copies the matrix on the top of the stack, this would be like save the funcion
    glColor3f(1,0,1);  //set colour ball
    ////glTranslatef(0.0, 0.0 , 0.0); // back to origin
    //glTranslatef(dx, 0.0, dy);
    
    float* Uknot = new float [9];
    float* Vknot = new float [9];
    
    Uknot[0]= Uknot[1] = Uknot[2]= Uknot[3]= Uknot[4] =  0.0;
    Uknot[5]= Uknot[6] = Uknot[7]= Uknot[8]= Uknot[9] =  1.1; //By changing the knot value the extends
    
    
    Vknot[0]= Vknot[1] = Vknot[2]= Vknot[3]= Vknot[4] =  0.0;
    Vknot[5]= Vknot[6] = Vknot[7]= Vknot[8]= Vknot[9] =  1.1;
    
    
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

void simulation()
{
    
    
    
    
    
    
    float lastu, lastv;
    int deti = 5;
    int detj = 1;
    
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
            
            if(k%5==0)
            {
                
            }
            
            
            
        }
    }
    
    
    
    
    
    
    
    
    k++;
    
    
    
    
    
    
}

//simulation2 makes the sim in the 2d real not the nurb surface in other words no deformation
void simulation2()
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
            
            if(k%5==0)
            {
                
            }
            
            
            
        }
    }
    
    
    
    
    
    
    
    
    k++;
    
    
    
    
    
    
}

#pragma mark > Main Display

void maindisplay(void)
{
	GLdouble xmin, xmax, ymin, ymax;
	// far frustum plane
	GLdouble zFar = -gCamera.viewPos.z + gShapeSize * 0.5;
	// near frustum plane clamped at 1.0
	GLdouble zNear = MIN (-gCamera.viewPos.z - gShapeSize * 0.5, 1.0);
	// window aspect ratio
	GLdouble aspect = gCamera.screenWidth / (GLdouble)gCamera.screenHeight;
    
	glMatrixMode (GL_PROJECTION);
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
	
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	gluLookAt (gCamera.viewPos.x, gCamera.viewPos.y, gCamera.viewPos.z,
               gCamera.viewPos.x + gCamera.viewDir.x,
               gCamera.viewPos.y + gCamera.viewDir.y,
               gCamera.viewPos.z + gCamera.viewDir.z,
               gCamera.viewUp.x, gCamera.viewUp.y ,gCamera.viewUp.z);
    
	// track ball rotation
	glRotatef (gTrackBallRotation[0], gTrackBallRotation[1], gTrackBallRotation[2], gTrackBallRotation[3]);
	glRotatef (gWorldRotation[0], gWorldRotation[1], gWorldRotation[2], gWorldRotation[3]);
    
    glTranslatef(-3, 0.0, 0.0);
	
	glClearColor (0.2f, 0.2f, 0.4f, 1.0f);	// clear the surface
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    
    
    //objBP.drawlines(k);
    
    
    if (WIRE)
    {
        glDisable(GL_LIGHTING);
        //glColor3f (1.0, 1.0, 1.0); // no coloring
        
        
        objBB.createGeometry(); //Creates visalization of _location_vector_2d
        
        
    }
    
    
    drawGLText (gCamera.screenWidth, gCamera.screenHeight);
    
    
    
    
    if (gLines) {
		glColor3f (1.0, 1.0, 1.0); // no coloring
		glDisable(GL_LIGHTING);
		glCallList (gWireList);
        
        
        
	}
	if (gPolygons) {
		glEnable(GL_LIGHTING);
		glCallList (gSolidList);
        
        
    }
    
    if (gGeometrySpline)
    {
        glDisable(GL_LIGHTING);
        //glColor3f (1.0, 1.0, 1.0); // no coloring
        
        
        
        // objSpline.SplinePrintLocation(location_2d);
        
        objSpline.SplinePrintLocation(location_bubbles_bezier_2d);
        
        
        
    }
    if (RUNGAKUTTA)
    {
        glEnable(GL_LIGHT_MODEL_TWO_SIDE);
        
        if (sLastIter) {
            // objBB.onebubble();
            
            // objBB.twobubble();
            
            // objBB.threebubble(k);
            
            //  objBB.fourbubble(k);
            
            //objBB.fivebubble(objSpline.spline_location_2d);
            
            //objSpline.SplinePrintLocation();
            
            //   location_2d = objBB.sixbubble(SixBubbleState,location_2d);
            
            // location_2da = objBP.sixbubble(SixBubbleState,location_2da);// ---> working
            
            
            // cout << location_bubbles_bezier_2d.size() <<endl;
            location_bubbles_bezier_2d = objBP.sevenbubble(SixBubbleState,location_bubbles_bezier_2d,k, 0.5001);
            
            //location_bubbles_bezier_2d = objBP.eightbubble(SixBubbleState,location_bubbles_bezier_2d,k, 0.5001);
            
            
            //ksgr gGeometrySpline = gGeometrySpline-1;
            
            //SixBubbleState++;
            
            
            k++;
            
            //objSpline.SplinePrintLocation();
            
            
            //gKRestart=!gKRestart;// .....srstarst
            
        }
        
        if (k==5000) sLastIter = false;
        
        
    }
    
    if (gSplines)
    {
        glEnable(GL_LIGHT_MODEL_TWO_SIDE);
        
        //cout << "Spline 1D demo";
        
        // objSpline.draw_spline();
        objSpline.draw_bezier();
        
        
        // objSpline.SplinePointsLocation();
        
        //objSpline.SplinePrintLocation();
        //Draw();
        
    }
    
    if (gKRestart)
    {
        RUNGAKUTTA =true;
        sLastIter=true;
        SixBubbleState=0;
    }
    
    if (gPrint)
    {
        //objSpline.SplinePrintLocation();
        //gPrint= !gPrint;
        
    }
    
    
    if(gShowSplineControlPoints)
    {
        objMainBSPline.InitializeControlPoints();
        
        
        float* Uknot = new float [9];
        float* Vknot = new float [9];
        
        Uknot[0]= Uknot[1] = Uknot[2]= Uknot[3]= Uknot[4] =  0.0;
        Uknot[5]= Uknot[6] = Uknot[7]= Uknot[8]= Uknot[9] =  2.0;
        
        
        Vknot[0]= Vknot[1] = Vknot[2]= Vknot[3]= Vknot[4] =  0.0;
        Vknot[5]= Vknot[6] = Vknot[7]= Vknot[8]= Vknot[9] =  1.0;
        
        
        //Point2D alfaPoint(0,0,0);
        
        //objBSPline.controlPoints[0].push_back(alfaPoint);
        
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
        
        // S = objMainBSPline.surfacePoint(5, 2, Uknot, 4, 2, Vknot, objMainBSPline.controlPointsArray , 0.00001, 0.00001);//
        
        if(sFlag == GL_TRUE )
        {
            for (int i=0;i<IMAX;i++){
                //sMAT[i] = new myPoint3D [10];
                u=i/(float)(IMAX-1)*2;
                //  cout << "\n u : " << u << endl;
                
                for(int j=0;j<JMAX ;j++){
                    
                    
                    v=j/(float)(JMAX-1)*1;
                    //   cout << "\n v : " << v << endl;
                    
                    
                    /////////cout << "["<<i<<"]"<<"["<<j<<"]-----------------------------------------" << endl ;
                    //cout << "\nu: " << u << "v : " << v ;
                    // cout << "\t\t[ " << i <<"]"<< "[ " << j <<"]"<< endl;
                    // objMainBSPline.basisFuns(2, u, 2, Uknot);
                    
                    //    S = objMainBSPline.surfacePoint(5, 2, Uknot, 4, 2, Vknot, objMainBSPline.controlPointsArray , u, v);//
                    //   S = objMainBSPline.surfacePoint(5, 2, Uknot, 4, 2, Vknot, objMainBSPline.controlPointsArray , u, v);//
                    
                    objMainBSPline.ptsNURBS(objMainBSPline.controlPointsArray, objMainBSPline.controlPointsWeightsArray, Uknot, Vknot, 5, 5, 5, 5, u,v, objMainBSPline.pts);
                    
                    sMAT[i][j].x = objMainBSPline.pts[0];
                    sMAT[i][j].y = objMainBSPline.pts[1];
                    sMAT[i][j].z = objMainBSPline.pts[2];
                    
                    pointsBSpline.push_back(sMAT[i][j]);
                    
                    ///////cout << "\n\nSx: " << objMainBSPline.pts[0]  <<
                    ///////"\tSy: " <<objMainBSPline.pts[1] <<
                    ///////"\tSz: " <<objMainBSPline.pts[2] << endl<<endl ;
                    
                    
                }
                
                //S.x = 0.0;
            }
            
        }
        
        sFlag =GL_FALSE;
        
        
        glBegin(GL_POINTS);
        for(int i=0;i<IMAX;i++) {
            for(int j=0;j<JMAX;j++) {
                
                
                //  cout <<  sMAT[i][j].x<< endl;
                //   cout <<  sMAT[i][j].y<< endl;
                //   cout <<  sMAT[i][j].z<< endl;
                
                
            }
        }
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
        
        
        
        
        // QUADS
        
        /*
         
         glBegin(GL_QUADS);
         
         for(int j=0;j<JMAX-1;j++) {
         for(int i=0;i<IMAX-1;i++) {
         
         
         float Point1[3] = { sMAT[i][j].x,sMAT[i][j].y ,sMAT[i][j].z  };
         float Point2[3] = { sMAT[i][j+1].x,sMAT[i][j+1].y ,sMAT[i][j+1].z  };
         float Point3[3] = { sMAT[i+1][j+1].x,sMAT[i+1][j+1].y ,sMAT[i+1][j+1].z  };
         float Point4[3] = { sMAT[i+1][0].x,sMAT[i+1][0].y ,sMAT[i+1][0].z  };
         
         glVertex3fv(Point1);
         glVertex3fv(Point2);
         glVertex3fv(Point3);
         glVertex3fv(Point4);
         
         }
         }
         
         glEnd();
         
         */
        
        delete [] Uknot;
        delete [] Vknot;
        
        
        /*
         // sFlag= GL_FALSE;
         
         float	Diegol[3]=	{0.68549846516849846514, 0.849849149874651, 0.545098/5};
         
         
         glColor3fv(Diegol);
         glPointSize(5);
         glBegin(GL_POINTS);
         
         
         float Points[3] = {S.x, S.y,S.z};
         
         glVertex3fv(Points);
         */
        
        
    }
    
    if(sCreateBubbleBSpline)
    {
        //simulation();
        simulation2();
        
        if (k==250) sCreateBubbleBSpline = false;
        
        
        
        
        
    }
    
    //----->
    
    //BOUNDARIES
    
    for (int i=0;i<IMAX;i++)
    {
        
        // objBB.createBubble(PointMat[0][i].u, PointMat[0][i].v, initialBubbleRadius, 0.05);
        
        //createBubbleSplineNoDeformation(PointMat[0][i].u, PointMat[0][i].v, nodeformationRadius);
        //createBubbleSplineNoDeformation(PointMat[IMAX-1][i].u,PointMat[IMAX-1][i].v, nodeformationRadius);
        
        createBubbleSplineNoDeformation(PointMat2[0][i].u, PointMat2[0][i].v, nodeformationRadius);
        createBubbleSplineNoDeformation(PointMat2[IMAX-1][i].u,PointMat2[IMAX-1][i].v, nodeformationRadius);
        
        
        // createBubbleSplineT(PointMat[0][i].u,PointMat[0][i].v, initialBubbleRadius);
        
        // createBubbleSplineT(PointMat[IMAX-1][i].u,PointMat[IMAX-1][i].v, initialBubbleRadius);
        
        
    }
    
    for (int i=0;i<IMAX;i++)
    {
        
        //  createBubbleSplineNoDeformation(PointMat[i][0].u,PointMat[i][0].v, nodeformationRadius);
        //  createBubbleSplineNoDeformation(PointMat[i][IMAX-1].u,PointMat[i][IMAX-1].v, nodeformationRadius);
        
        createBubbleSplineNoDeformation(PointMat2[i][0].u,PointMat2[i][0].v, nodeformationRadius);
        createBubbleSplineNoDeformation(PointMat2[i][IMAX-1].u,PointMat2[i][IMAX-1].v, nodeformationRadius);
        
        /*
         createBubbleSplineT(PointMat[i][0].u,PointMat[i][0].v, initialBubbleRadius);
         
         createBubbleSplineT(PointMat[i][IMAX-1].u,PointMat[i][IMAX-1].v, initialBubbleRadius);
         */
        
        
    }
    
    
    for(int m=1;m<IMAX-1;m++){
        for(int n=1;n<IMAX-1;n++){
            
            // createBubbleSplineNoDeformation(PointMat[m][n].u, PointMat[m][n].v, nodeformationRadius);
            
            createBubbleSplineNoDeformation(PointMat2[m][n].u, PointMat2[m][n].v, nodeformationRadius);
            //createBubbleSplineT(PointMat[m][n].u,PointMat[m][n].v, initialBubbleRadius);
            
        }
    }
    
    /*
     
     int nPoints = 10; //numebr of points in the subdivision
     BubbleDSalfa QoP[nPoints*nPoints*nPoints];
     
     
     if(sSubdivision)
     {
     // objMainSubdivision.bubbleCreateInitialLocation(10);
     
     // objMainSubdivision.bubbleSubdivisionDomain();
     
     
     //Matrix initialization to stared all the points in the animation for each time step for all bubbles
     
     float **U = new float * [nPoints];
     for(int i=0;i<nPoints;i++){
     U[i] = new float  [nPoints];
     for(int j=0;j<nPoints;j++){
     U[i][j] = 0.0;
     }
     
     }
     
     float **V = new float * [nPoints];
     for(int i=0;i<nPoints;i++){
     V[i] = new float  [nPoints];
     for(int j=0;j<nPoints;j++){
     V[i][j] = 0.0;
     }
     
     }
     
     
     
     //  BubbleDSalfa QoP[nPoints*nPoints];
     
     objMainSubdivision.subdivisionHardCode(nPoints, U, V,QoP);
     
     
     float radius = 0.2/4;
     
     for(int i =0; i<(nPoints*nPoints)-nPoints;i++)
     {
     
     //  cout << "U:" << QoP[i].u << endl;
     //  cout << "V:" << QoP[i].v << endl;
     createBubbleSplineT(QoP[i].u,QoP[i].v, 0.053);
     }
     
     
     
     
     // sFlag=true;
     
     
     
     }
     */
    glutSwapBuffers();
    
    
    //if(k>20) k=0;
    
	
	
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
        case 'w': // toggle wire
        case 'W':
            gLines = 1 - gLines;
            gPolygons = 1 - gPolygons;
            WIRE = !WIRE;
            glutPostRedisplay();
            break;
        case 'r':
        case 'R':
            RUNGAKUTTA = !RUNGAKUTTA;
            break;	// starts Runge Kutta simualtion
        case 'e':
        case 'E':
            EULERV = !EULERV;
            break;	// starts Euler simualtion
        case 's':
        case 'S':
            gSplines =  1 - gSplines;
            glutPostRedisplay();
            break; // spline
        case 'k':
        case 'K':
            gKRestart =  1 - gKRestart;
            glutPostRedisplay();
            break; // spline
        case 'p':
        case 'P':
            gPrint =  1 - gPrint;
            glutPostRedisplay();
            break; // print point spline
        case 'c':
        case 'C':
            gShowSplineControlPoints =  1 - gShowSplineControlPoints;
            glutPostRedisplay();
            break; // print point spline
            
        case 'g':
        case 'G':
            gGeometrySpline =  1 - gGeometrySpline;
            glutPostRedisplay();
            break; // print point spline
            
        case 'm':
        case 'M':
            sResetSim =  1 - sResetSim;
            glutPostRedisplay();
            break; // print point spline
            
        case 'y':
        case 'Y':
            sCreateBubbleBSpline =  1 - sCreateBubbleBSpline;
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
        case 1:  RUNGAKUTTA = !RUNGAKUTTA;		break;	// starts simualtion
        case 2:  EULERV = !EULERV;		break;	// starts simualtion
        case 3:  gSplines = !gSplines;		break;	// starts simualtion
        case 4:  gKRestart = !gKRestart;		break;	// re-starts using current location vector
            
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
	gMainWindow = glutCreateWindow("GLUT Demo : BUBBLE PACKING IMPLEMENTATION CMU");
    
    init12(); // standard GL init
    
    glutReshapeFunc (reshape);
    glutDisplayFunc (maindisplay);
    Timer(0);
	glutKeyboardFunc (key);
	glutSpecialFunc (special);
    
	glutMouseFunc (mouse);
    glutMotionFunc(drag);
	glutSpaceballMotionFunc(spaceballmotion);
	glutSpaceballRotateFunc(spaceballrotate);
    
    glutCreateMenu (menuOb);
    glutAddMenuEntry ("> Geometry [w]", 0);
    glutAddMenuEntry ("> Runge Kutta [r]", 1);
    glutAddMenuEntry ("> Euler [e]", 2);
    glutAddMenuEntry ("> Spline [s]", 3);
    glutAddMenuEntry ("> Restart (uses current location) [k]", 4);
    glutAttachMenu (GLUT_KEY_HOME);
    
    
    
    glutMainLoop();
    return 0;
}





