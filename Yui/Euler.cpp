//
//  Euler.cpp
//  Azuka
//
//  Created by Diego Andrade on 5/7/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Euler.h"


using namespace std;


Euler::Euler()
{
    
     
    _ko= 1.0;  //CHANGE THIS VARIABLES 
    _m = 1.0;
    _c = 0.7*sqrt(_ko*_m);
    
    _set_presition = 5;  //MAKE GLOABL PARAMETERS
    
    _number_of_bubbles = 7;
    
}

Euler::~Euler()
{
    
    
    
}


float Euler::function(float x)
{
    float dy = x;
    return dy;
    
}

float Euler::function2(float p1, float _fw)
{
    float dp1 = (float)(1/_m)*(_fw-_c*(p1));
    
    cout << "dp1 : " << dp1 << endl;  
    return dp1;
    
    
}

float Euler::fw(float _w, float stable_distance)
{
    float _w_tmp=0.0; //temporal value
    
    if(_w>=0 && _w<=1.5)
    {
       cout << "Within the range 0<= w <=1.5 : " << _w << endl;  
        
        _w_tmp = 1.25 * (_ko/stable_distance) * pow(_w,3) - 
        2.375 * (_ko/stable_distance) * pow(_w,2) +
        1.125 * (_ko/stable_distance) ;
         
    } 
    else if(_w>1.5)
    {
       cout << "Beyond the range w>1.5 : " << _w << endl;
        
        _w_tmp = 0.0;
    }
    
    
    return _w_tmp;
    
}

float Euler::fuction_check(float x, float y)
{
    
    float yn = 2*x*y;
    
    return (yn);
    
    
    
}

void Euler::operation_test2()
{
    ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/PointsEuler2.txt"); //Check is there is a file functionlaity does not exist
    
    
    
  //  int _number_of_iter = 20;
    int _number_of_points = 10;
    
    
    float* X = new float[_number_of_points];
    
    float* Y = new float[_number_of_points];
    
    float _time_step_ = 0.1;
    
    //float* fsol = new float[_number_of_points];
    float temp=0.0;
    
    
    X[0] = 1;
    Y[0] = 1;
    
    
    for (int i =1 ; i<_number_of_points; i++)
    {
        X[i] = X[0]+i*_time_step_;
        temp =fuction_check(X[i-1], Y[i-1]);
        
        cout << "temp" << i << ": "<< temp <<"\t";
        
        Y[i] = Y[i-1]+_time_step_*temp;
        
        cout << "X[" << i << "]= "<< X[i] <<"\t";
        
        cout << "Y[" << i << "]= "<< Y[i] <<"\n";
       

        
        outfile  << "X[" << i << "]= "<< X[i] <<"\t";
        outfile  << "Y[" << i << "]= "<< Y[i] << endl;
        
    }

    outfile.close();
    
}

void Euler::operation_test()
{
    
    int _number_of_bubbles=7; //number of bubbles
    
    float a = -3; //range
    float b = 3;
    float t = 0.0; // parameter
    
    float ro = 0.5; //diameter of the bubble
    float w; // w parameter
    
    float *distance = new float [_number_of_bubbles];
    float *location = new float [_number_of_bubbles];
    
    float _inter_bubble_force = 0.0;
    
    float _time_step = 0.05;
    
    float p1 = 0.0;
    float p2 = 0.0;
    
    float _max_iter = 2;
    
    location_out = new float[_number_of_bubbles];
    float * dist = new float[_number_of_bubbles];
    
    
    ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/PointsEuler.txt"); //Check is there is a file functionlaity does not exist
    
    
    //Location for the bubbles
    
    location[0] = a;
    
    for (int i=1;i<_number_of_bubbles-1;i++){
        
        t=(float)i/((_number_of_bubbles-1));         
        cout << "Parameter t = " << setprecision(_set_presition)<< t << endl;

        location[i] = (1-t)*a+t*b; 
           }
    
    location[_number_of_bubbles-1] = b;
    
    
    
    for (int i=0;i<_number_of_bubbles;i++){
       
        dist[i] = location[i];
    }
   
    
    //Simulation starts
    
    float p1i =0.0;
    
    for (int j=0;j<_max_iter;j++){
    
    for (int i=1;i<_number_of_bubbles-1;i++){
        
        cout << j << "  ....................................... " <<endl;

           
        distance[i]= abs(dist[i]-dist[i-1]);
        cout << "distance["<<i<<"] = " << distance[i] << endl;
        
        w = distance[i]/ro; // distance between bubbles / stable distance
        
        cout << "location["<<i<<"] = " << location[i] << endl;

        _inter_bubble_force = fw(w,ro);     
        cout << "_inter_bubble_force["<<i<<"] = " << _inter_bubble_force << endl;
        
        p1 = function(dist[i]+0.5*_time_step*function(dist[i]));
        cout << "p1["<<i<<"] = " << p1 << endl;
        
        p2 = function2(p1i+0.5*_time_step*function2(p1i, _inter_bubble_force),_inter_bubble_force);
        cout << "p2["<<i<<"] = " << p2 << endl;    
        
        p1i = p2;
        
        dist[i]=dist[i]-p1i;
        
        cout << "dist["<<i<<"] = " <<  dist[i] << endl;   
        
        location_out[i] = dist[i];
        
        cout << "location_out["<<i<<"] = " <<  location_out[i] << endl;   
        
       // outfile  << "location[" << i << "]= "<< location_out[i] << endl; 
        
    }
    }
    
    
    //Pinting the values for the location in a file
    location_out = location;
    
    for (int i=0;i<_number_of_bubbles;i++){
        
       outfile  << "---- >>> location[" << i << "]= "<< location_out[i] << endl;    
    
    }
    
    
    outfile.close();
       

    
    
}