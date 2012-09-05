//
//  BubblePacking2D.cpp
//  Yui
//
//  Created by Diego Andrade on 7/26/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "BubblePacking2D.h"


BubblePacking2D::BubblePacking2D()
{
    _mass = MASS;
    _damping_force = DAMPING_FORCE;
    _spring_rate = SPRING_RATE;
    MAXI = NUM_ITERATIONS;
   // _mass = 1.0; // Mass of a bubble for phisical simulation
   // _damping_force = 0.7*sqrt( _spring_rate*_mass); //Damping force for phisical simulation
   // _spring_rate = 0.1*0.001;// ko 0.1 0.001*0.0001 faster
   // MAXI = 40; //max number of iterations
}

BubblePacking2D::~BubblePacking2D()
{
    
}

float BubblePacking2D::findDistanceXDirection(bubble B1, bubble B2, int state)
{
    float result =0.0;
    
    if (state == 0) // X direction
    {
        result = fabs(B1.u-B2.u);
    }
    if (state == 1) // Y direction
    {
        result = fabs(B1.v-B2.v);
    }
    return (result);
    
}

float BubblePacking2D::findDistanceBetweenBubbles(bubble B1, bubble B2)
{
    float distance = 0.0;
    
    distance = sqrt(pow((B1.u-B2.u),2)+pow((B1.v-B2.v),2));    
    
    return(distance);
}

float BubblePacking2D::radiiSum(bubble B1, bubble B2)
{
    float radius = 0.0;
    
    radius = 1*(B1.radius + B2.radius);
    
    return(radius);
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

PointUVp BubblePacking2D::Simulation(bubble B1, bubble B2)
{
    PointUVp result;
   // float distance = findDistanceBetweenBubbles(B1, B2);
    float stableDistance = radiiSum(B1, B2);
    float w = 0.0;
    float interbubbleForces = 0.0;
   // float tempX;
    float h=0.01; //time step
        
    result.u = B2.u;
    result.v = B2.v;
    
    float distanceIDirection = findDistanceBetweenBubbles(B1, B2);
    w = wParameter(distanceIDirection, stableDistance);
    interbubbleForces =  interBubbleForces( _spring_rate, stableDistance, w);
    
    
    
    // ( 1 )
    if (B2.u > B1.u && B2.v > B1.v )
    {
     result.u =rk4_sol(B2.u, h, interbubbleForces);
     result.v =rk4_sol(B2.v, h, interbubbleForces);
    }
    
    // ( 2 )
    if (B2.u > B1.u && B2.v < B1.v )
    {
        result.u =rk4_sol(B2.u, h, interbubbleForces);
        result.v =rk4_sol(B2.v, h, -interbubbleForces);
    }
    
    //( 3 )
    if (B2.u < B1.u && B2.v < B1.v )
    {
        result.u =rk4_sol(B2.u, h, -interbubbleForces);
        result.v =rk4_sol(B2.v, h, -interbubbleForces);
    }
    
    //( 4 )
    if (B2.u < B1.u && B2.v > B1.v )
    {
        result.u =rk4_sol(B2.u, h, -interbubbleForces);
        result.v =rk4_sol(B2.v, h, +interbubbleForces);
    }
    
    else{
        interbubbleForces = interbubbleForces;
    }
        
    
     
    // x direction
    /*float distanceIDirection = findDistanceXDirection(B1, B2, 0);
    w = wParameter(distanceIDirection, stableDistance);
    interbubbleForces =  interBubbleForces( _spring_rate, stableDistance, w);
    result.u =rk4_sol(B2.u, h, interbubbleForces);
    
    // y direction
    float distanceJDirection = findDistanceXDirection(B1, B2, 1);
    w = wParameter(distanceJDirection, stableDistance);
    interbubbleForces =  interBubbleForces( _spring_rate, stableDistance, w);
    result.v =rk4_sol(B2.v, h, interbubbleForces);*/
        
  //  cout <<  "w : " << w <<endl;
  //  cout <<  "interbubble_force : " << interbubbleForces <<endl;
  //  cout <<  "tempx : " << tempX <<endl;
        
    return (result);
    
}


float BubblePacking2D::rk4_sol(float xi, float time_step, float fw)
{
    // ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/PointsRK4.txt"); //Check is there is a file functionlaity does not exist
    
    
    
    //int _number_of_iter = _number_of_iter;
    
    float *x= new float  [MAXI+1];
    float *v = new float [MAXI+1];
    float *a = new float [MAXI+1];
    
    // cout << ">> Runge Kutta Solution Points Test<< " << endl << endl;
    
    x[0]=xi;
    v[0]=0.0;
    a[0]=0.0;
    
    float x1,x2,x3,x4;
    float v1,v2,v3,v4;
    float a1,a2,a3,a4;
    
    float h = time_step;
    float dt;
    
    if(MAXI>60) MAXI=60; //CHANGE HERE
    
    for (int i =0 ; i<MAXI ; i++)
    {             
        dt = i*h;
        
        x1 = x[i];
        v1 = v[i];
        a1 = function2(dt, v1, fw);
        
        x2 = x[i] + 0.5*v1*dt;
        v2 = v[i] + 0.5*a1*dt;
        a2 = function2(dt, v2, fw);
        
        x3 = x[i] + 0.5*v2*dt;
        v3 = v[i] + 0.5*a2*dt;
        a3 = function2(dt, v3, fw);
        
        x4 = x[i] + v3*dt;
        v4 = v[i] + a3*dt;
        a4 = function2(dt, v4, fw);
        
        x[i+1] = x[i]+(dt/((float)(6.0)))*(v1+2*v2+2*v3+v4);
        v[i+1] = v[i]+(dt/((float)(6.0)))*(a1+2*a2+2*a3+a4);
        
        
        /*cout << "x[" << i+1 << "]= "<<setprecision(7)<<setw(7)<< x[i+1] <<"\t\n";
         cout << "v[" << i+1 << "]= "<< v[i+1] <<"\n";
         
         cout  << "x1[" << i << "]= "<< x1 <<"\t\t\t";
         cout  << "x2[" << i << "]= "<< x2 <<"\t\t\t";
         cout  << "x3[" << i << "]= "<< x3 <<"\t\t\t";
         cout  << "x4[" << i << "]= "<< x4 <<"\t\t\t"<<endl;
         
         cout  << "v1[" << i << "]= "<< v1 <<"\t\t\t";
         cout  << "v2[" << i << "]= "<< v2 <<"\t\t\t";
         cout  << "v3[" << i << "]= "<< v3 <<"\t\t\t";
         cout  << "v4[" << i << "]= "<< v4 <<"\t\t\t"<<endl;
         
         cout  << "a1[" << i << "]= "<< a1 <<"\t\t\t";
         cout  << "a2[" << i << "]= "<< a2 <<"\t\t\t";
         cout  << "a3[" << i << "]= "<< a3 <<"\t\t\t";
         cout  << "a4[" << i << "]= "<< a4 <<"\t\t\t"<<endl;*/
        
        /*outfile  << "x[" << i << "]= "<< x[i] <<"\t";
         outfile  << "v[" << i << "]= "<< v[i] <<"\t"<<endl;
         
         outfile  << "x1[" << i << "]= "<< x1 <<"\t";
         outfile  << "x2[" << i << "]= "<< x2 <<"\t";
         outfile  << "x3[" << i << "]= "<< x3 <<"\t";
         outfile  << "x4[" << i << "]= "<< x4 <<"\t"<<endl;
         
         outfile  << "v1[" << i << "]= "<< v1 <<"\t";
         outfile  << "v2[" << i << "]= "<< v2 <<"\t";
         outfile  << "v3[" << i << "]= "<< v3 <<"\t";
         outfile  << "v4[" << i << "]= "<< v4 <<"\t"<<endl;
         
         
         outfile  << "a1[" << i << "]= "<< a1 <<"\t";
         outfile  << "a2[" << i << "]= "<< a2 <<"\t";
         outfile  << "a3[" << i << "]= "<< a3 <<"\t";
         outfile  << "a4[" << i << "]= "<< a4 <<"\t"<<endl<<endl;*/
        
    }
    
    // outfile.close();
    
    //delete []x;
    delete []v;
    delete []a;
    
    return (x[MAXI]);
    
}

void BubblePacking2D::surfaceSimulation(bubble **mBubbles, int IMAX , int JMAX)
{
    //working only with the interior points in the parametric domain
    for (int i=1;i<IMAX-1;i++){
        for(int j=1;j<JMAX-1;j++){
            bubbleInteraction(mBubbles[i][j], mBubbles,  IMAX,  JMAX);
        }
    }
    
    
}

void BubblePacking2D::bubbleInteraction(bubble current, bubble **bubbleAll, int IMAX, int JMAX)
{
    
    PointUVp currentPoint;
    float temp;
    
    for (int i=0;i<IMAX;i++){
        for(int j=0;j<JMAX;j++){
            
            temp= findDistanceBetweenBubbles(bubbleAll[i][j], current);
            
            if(temp<=(1.5*current.radius))
            {
                currentPoint = Simulation(bubbleAll[i][j], current);
                current.u = currentPoint.u;
                current.v = currentPoint.v;
                cout << "u :" << current.u << "v:" << current.u << endl;
            }
            else {
                //Just making explicit that point location does not change
                current.u = current.u;
                current.v = current.v;
            }
        }
    }
    
    
    
}


void BubblePacking2D:: subdivisionHardCode( bubble** P, int IMAX, int JMAX)
{
    
    
    for(int i=0; i<IMAX; i++)
    {
        for(int j=0; j<JMAX; j++)
        {
            P[i][j].u = 1/(float)(IMAX-1)*i;
            P[i][j].v=  1/(float)(JMAX-1)*j;
            //cout <<"P["<<i<<"]["<<j<<"].u:"<< P[i][j].u << endl;
            //cout <<"P["<<i<<"]["<<j<<"].v:"<< P[i][j].v << endl;
            
           
            P[i][j].idx = i*IMAX+j;
            //P[i][j].radius = 0.02; //change here
            
            //  cout << i*nPoints+j << endl;
            
        }
    }
    
    
    for(int i=1; i<IMAX-1; i++)
    {
        for(int j=1; j<JMAX-1; j++)
        {
            P[i][j].u = 1/(float)(IMAX-1)*i;
            P[i][j].v=  1/(float)(JMAX-1)*j;
            //cout <<"P["<<i<<"]["<<j<<"].u:"<< P[i][j].u << endl;
            //cout <<"P["<<i<<"]["<<j<<"].v:"<< P[i][j].v << endl;
            
            
            P[i][j].idx = i*IMAX+j;
            //P[i][j].radius = 0.02; //change here
            
            //  cout << i*nPoints+j << endl;
            
        }
    }
    
    
    
    
    
    
    //return (U);
}

void BubblePacking2D:: subdivisionHardCode2( bubble** P, int IMAX, int JMAX, float distance)
{
    
    
    for(int i=0; i<IMAX; i++)
    {
        for(int j=0; j<JMAX; j++)
        {
            P[i][j].u = 1/(float)(IMAX-1)*i;
            P[i][j].v=  1/(float)(JMAX-1)*j;
            //cout <<"P["<<i<<"]["<<j<<"].u:"<< P[i][j].u << endl;
            //cout <<"P["<<i<<"]["<<j<<"].v:"<< P[i][j].v << endl;
            
            
            P[i][j].idx = i*IMAX+j;
            //P[i][j].radius = 0.02; //change here
            
            //  cout << i*nPoints+j << endl;
            
        }
    }
    
    
    for(int i=1; i<IMAX-1; i++)
    {
        for(int j=1; j<JMAX-1; j++)
        {
            P[i][j].u = 1/(float)(IMAX-1)*i;// 1/(float)(IMAX-1)*i;//1/(float)(IMAX-1)*i*0.5;
            P[i][j].v=  1/(float)(IMAX-1)*j; //1/(float)(JMAX-1)*j;
            //cout <<"P["<<i<<"]["<<j<<"].u:"<< P[i][j].u << endl;
            //cout <<"P["<<i<<"]["<<j<<"].v:"<< P[i][j].v << endl;
            
            
            //P[i][j].idx = i*IMAX+j;
            //P[i][j].radius = 0.02; //change here
            
            //  cout << i*nPoints+j << endl;
            
        }
    }
    
    
    
    
    
    
    //return (U);
}


