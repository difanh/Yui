//
//  grid.h
//  NSChorinProjection
//
//  Created by Diego Andrade on 5/12/13.
//  Copyright (c) 2013 Diego Andrade. All rights reserved.
//

#ifndef NSChorinProjection_grid_h
#define NSChorinProjection_grid_h


#include <iostream>	// Directiva de preprocesamiento para entraaada y salida de datos //Pre-proccessor directive for input - output
#include <iomanip>
#include <cmath>	// Libreria matematica		//Math library
#include <cstdio>
#include <fstream>

//Strores location in U and V
struct PointXY {
    float x;
    float y;
};

using namespace std;

class Grid
{
public:
	Grid();		//Constructor
	virtual ~Grid();	//Destructor
	
    //Boundaries in Physical Space
    PointXY Xb(double s);   //Bottom
    PointXY Xt(double s);   //Top
    PointXY Xl(double s);   //Left
    PointXY Xr(double s);   //Right
    
    int SIZE;
    
    double** equal_spacing(double a, double b,double* xi, int SIZE); //works for any direction x or y
    
   void TFI(double* xi, double* eta, int SIZE);
    
    double** X;
    double** Y;

};


#endif
