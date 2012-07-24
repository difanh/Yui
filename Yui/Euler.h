//
//  Euler.h
//  Azuka
//
//  Created by Diego Andrade on 5/7/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#ifndef Azuka_Euler_h
#define Azuka_Euler_h

#include <vector>
#include <cmath>

class Euler{
    
public:
    float _c,_m,_ko; 
    float _time_step;
    int _set_presition;   
    
    float *location_out;
    
    int _number_of_bubbles;
    
public:
    Euler();
    ~Euler();
    float function (float x);
    float function2 (float x, float _fw);
    
    float fw (float _w, float stable_distance);
    
     void operation_test (); // this functions just test 4th degree RK works
    
    
    float fuction_check(float x, float y);
    void operation_test2();
    
    
};



#endif
