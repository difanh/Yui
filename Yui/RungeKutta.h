//
//  RungeKutta.h
//  bubble
//
//  Created by diegoandrade on 4/12/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#ifndef bubble_RungeKutta_h
#define bubble_RungeKutta_h

#include <vector>
#include <cmath>

class RungeKutta{
    
public:
       float time_step;
    float X0; //Initial contidion at t=0
    float _k1,_k2,_k3,_k4;
    float F2_k1,F2_k2,F2_k3,F2_k4;
    
    
    float c,m,ko; 
  
     
    
public:
    RungeKutta();
    ~RungeKutta();
    float function ( float x);
    
    
    float function_p1 ( float p1);    
    float function_p2 ( float p2, float p2i, float fw);
    
    float K1 (float p1);
    float K2 (float p1,float time_step);
    float K3 (float p1,float time_step);
    float K4 (float p1,float time_step);
    
    float F2_K1 (float p2, float p2i, float fw);
    float F2_K2 (float p2, float time_step, float fw);
    float F2_K3 (float p2, float time_step, float fw);
    float F2_K4 (float p2, float time_step, float fw);
    void operation_test (); // this functions just test 4th degree RK works
    
    float function2 (float x, float y);
       
    
    
};


#endif
