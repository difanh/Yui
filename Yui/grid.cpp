//
//  grid.cpp
//  NSChorinProjection
//
//  Created by Diego Andrade on 5/13/13.
//  Copyright (c) 2013 Diego Andrade. All rights reserved.
//

#include "grid.h"
#include "matrix.h"
#include <cmath>

Matrix OBJMatGrid;


Grid::Grid()
{
    //Initializing the matrices for values for X and Y coordinates
          
    SIZE = 10;
    
}

Grid::~Grid()
{
    
    
}

double** Grid::equal_spacing(double a, double b, double* xi, int SIZE)
{

    double** A = OBJMatGrid.crearM(SIZE);
    
    double dm = (double)(b-a)/(SIZE-1);
    
    for(int i=0;i<SIZE;i++)
    {
        xi[i]=dm*i;
       // std::cout << "xi[" <<i <<"]:" << xi[i] << endl;
        
    }
    
    char* file = "/Users/Serenity/Dropbox/0CMU 2012/Programming Mac/NSChorinProjection/GRIDHW7.txt";
    
    OBJMatGrid.printVector(xi,SIZE,file);
    
    return A;
    
}

PointXY Grid::Xb(double s)
{
    PointXY xyb;
    
    double x=0.0;
    double y=0.0;
    
    x = s;
    y = 1+0.3*pow(s,2)*sin(s*3.1415);
    
    xyb.x = x;
    xyb.y = y;
    
    return(xyb); //Here there is a problem because i create this points but nor destroy them
    
}

PointXY Grid::Xt(double s)
{
    PointXY xyb;
    
    double x=0.0;
    double y=0.0;
    
    x = s;
    y = 1;
    
    xyb.x = x;
    xyb.y = y;
    
    return(xyb);
    
}

PointXY Grid::Xr(double s)
{
    PointXY xyb;
    
    double x=0.0;
    double y=0.0;
    
    x = 1;
    y = s;
    
    xyb.x = x;
    xyb.y = y;
    
    return(xyb);
    
}

PointXY Grid::Xl(double s)
{
    PointXY xyb;
    
    double x=0.0;
    double y=0.0;
    
    x = 0;
    y = s;
    
    xyb.x = x;
    xyb.y = y;
    
    return(xyb);
    
}

void Grid::TFI(double* xi, double* eta,int SIZE)
{
    PointXY XYgrid;
    double XI,ETA;
    XI=ETA=0.0;
    
    X = OBJMatGrid.crearM(SIZE);
    Y = OBJMatGrid.crearM(SIZE);
    
    for( int i=0; i<SIZE; i++)
    {
        XI = xi[i];
        for( int j=0; j<SIZE; j++)
        {
            ETA=eta[j];
            XYgrid.x = (1 - ETA) * Xb(XI).x+ ETA *Xt(XI).x +(1 - XI)*Xl(ETA).x+XI*Xr(ETA).x
            -(XI*ETA*Xt(1).x + XI*(1 - ETA)*Xb(1).x + ETA*(1 - XI)*Xt(0).x+(1 - XI)*(1 - ETA)*Xb(0).x);
            
            XYgrid.y = (1 - ETA) * Xb(XI).y+ ETA *Xt(XI).y +(1 - XI)*Xl(ETA).y+XI*Xr(ETA).y
            -(XI*ETA*Xt(1).y + XI*(1 - ETA)*Xb(1).y + ETA*(1 - XI)*Xt(0).y+(1 - XI)*(1 - ETA)*Xb(0).y);

            
            std::cout << "XYgrid.x[" <<i <<"][" <<j <<"]:" << XYgrid.x << "\t";
            std::cout << "XYgrid.y[" <<i <<"][" <<j <<"]:" << XYgrid.y << endl;

            
            X[i][j] = XYgrid.x;
            Y[i][j] = XYgrid.y;
            
        }
        
        
    }

    
}



