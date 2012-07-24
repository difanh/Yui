//
//  RungeKutta.cpp
//  bubble
//
//  Created by diegoandrade on 4/12/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "RungeKutta.h"


using namespace std;


RungeKutta::RungeKutta()
{
    
    _k1=_k2=_k3=_k4=0.0;
    F2_k1=F2_k2=F2_k3=F2_k4=0.0;
    
    ko= 0.5;  //CHANGE THIS VARIABLES 
    m = 0.5;
    c = 0.7*sqrt(ko*m);
 
}

RungeKutta::~RungeKutta()
{
    
    
    
}

//For the first equation we use the location of the bubble and try to integrate the movement over 
//the time steps and update new location every step
float RungeKutta::function_p1(float x)
{
    float dp1 = x;
    //cout << "> X value = " << x << endl;
    return dp1;
}


//float RungeKutta::function(float x, float y)
//{
//    float dy = -2.2067e-12*(pow(y,4)-81e8);
//    
//    return dy;
//    
//    
//}


float RungeKutta::K1( float x)
{
    
    _k1= function_p1(x);
    //cout << "> _k1 value = " << _k1 << endl;
    return _k1;
    
}

float RungeKutta::K2(float x, float time_step)
{
    _k2 = function_p1(x+0.5*_k1*time_step);
    return _k2;
    
    
}

float RungeKutta::K3(float x, float time_step)
{
    _k3 = function_p1(x+0.5*_k2*time_step);
    return _k3;

  
    
}

float RungeKutta::K4(float x, float time_step)
{
    
    _k4 = function_p1(x+_k3*time_step);
    return _k4;

    
}

//For the second equation we use the location, interbubble forces fw, damping forces c, and mass m
float RungeKutta::function_p2(float p2, float p2i, float fw)
{
    
    float dp2 = p2i + (1/m)*(fw-c*p2);
    

    
    return dp2;
    
    
}

float RungeKutta::F2_K1(float p2, float p2i, float fw)
{
    
    F2_k1= function_p2(p2,p2i,fw);
    return F2_k1;
    
}

float RungeKutta::F2_K2(float p2, float time_step, float fw)
{
    F2_k2 =function_p2( p2+0.5*F2_k1*time_step,0,fw);
    return F2_k2;

   
    
}

float RungeKutta::F2_K3(float p2, float time_step, float fw)
{
    F2_k3 = function_p2( p2+0.5*F2_k2*time_step,0,fw);
    return F2_k3;

    
    
}

float RungeKutta::F2_K4(float p2, float time_step, float fw)
{
    
    F2_k4 = function_p2( p2+F2_k3*time_step,0,fw);  
    return F2_k4;

 
    
}


float RungeKutta::function2(float x, float y)
{
    float f = 2*x*y;
    return (f);
    
}


void RungeKutta::operation_test()
{
    
    ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/PointsRK2.txt"); //Check is there is a file functionlaity does not exist
    
    
    
    //  int _number_of_iter = 20;
    int _number_of_points = 10;
    
    
    float* X = new float[_number_of_points];
    
    float* Y = new float[_number_of_points];
    
    float h = 0.1;
    
    //float* fsol = new float[_number_of_points];
   // float temp=0.0;
    
    float k1_,k2_,k3_,k4_;
    
    
    X[0] = 1;
    Y[0] = 1;
    
    for (int i =1 ; i<_number_of_points; i++)
    {
        X[i] = X[0]+i*h;
        outfile  << "X[" << i << "]= "<< X[i] <<"\t";
        
        
        k1_ = h* function2(X[i-1], Y[i-1]);
        
         
        k2_ = h*function2(X[i-1]+0.5*h, Y[i-1]+k1_*0.5);
        
       
        k3_ = h* function2(X[i-1]+0.5*h, Y[i-1]+k2_*0.5);
        
      
        k4_ = h* function2(X[i-1]+h, Y[i-1]+k3_);
        
        Y[i] = Y[i-1]+1/(float)(6)*(k1_+2*k2_+2*k3_+k4_);
                
        
        outfile  << "k1[" << i << "]= "<< k1_ <<"\t";
        outfile  << "k2[" << i << "]= "<< k2_<<"\t";
        outfile  << "k3[" << i << "]= "<< k3_ <<"\t";
        outfile  << "k4[" << i << "]= "<< k4_ <<"\t";
        
        outfile  << "Y[" << i << "]= "<< Y[i] << "\t" << endl;
        
        //cout << "temp" << i << ": "<< temp <<"\t";
        
        //Y[i] = Y[i-1]+h*temp;
        
        //cout << "X[" << i << "]= "<< X[i] <<"\t";
        
       // cout << "Y[" << i << "]= "<< Y[i] <<"\n";
        
        
        
      
       
        
    }
    
    outfile.close();

    

  /*  time_step = 240; 
    
    vector<float> _is_;  //Integration Solution 
    vector<float> _time_;  //time 
    
    dy = function_p1(0, 1200);
    // cout << "Funtion 0,0" << dy << endl;  
    
    _is_.push_back(1200);  
    _time_.push_back(0);
    
    // cout << "_integration_solution (0,1200)" << dy << endl; 
    
    
	string file_input;
    
    file_input = "RungeKuttaSolution.txt";
    
    ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/RungeKuttaSolution.txt");			//Checking if there is a file
	
    
    outfile  <<"T0\t "<<_is_[0]<< "\n";
    
    
    
    for (int i=1;i<100;i++)
    {
        
        
        //  cout << "Integration Solution" << _is_[i-1] << endl; 
        K1(_time_[i-1], _is_[i-1]);   
        // cout << "K1 = " << k1 << endl; 
        K2(_time_[i-1], _is_[i-1], time_step);
        //  cout << "K2 = " << k2 << endl;
        K3(_time_[i-1], _is_[i-1], time_step);
        //  cout << "K3 = " << k3 << endl;
        K4(_time_[i-1], _is_[i-1], time_step);
        // cout << "K4 = " << k4 << endl;
        
        dy = _is_[i-1]+1/(float)(6)*((_k1+2*_k2+2*_k3+_k4)*time_step);
        _is_.push_back(dy);
        
        
        outfile  <<"T"<<i<<"\t "<<_is_[i]<< "\n";
        
        //  cout << "dy = " << _is_[i] << endl;
        
        //  cout << "time_step" << time_step << endl;    
        
        
        
    }
    
    
	outfile.close();
    
  */  
    
}

