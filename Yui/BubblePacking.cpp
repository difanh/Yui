//
//  BubblePacking.cpp
//  Keel
//
//  Created by Diego Andrade on 6/24/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>

#include "BubblePacking.h"
#include "BubbleGeometry.h"
#include "Spline.h"



Spline objSplineBP;




BubblePacking::BubblePacking()
{
    _number_of_bubbles_v = 10; //7
    _max_iter_outter = 150;
    _number_k = 150;
    
    _sphereX=0.0f;
    _sphereY=0.0f;
    
    _r_bubble_distance = 0.0;
    _ro_stable_bubble_distance = 0.0; 
    
    _parameter_location = 4.0; //4
    
    _bubble_size = 0.5001; //0.5 // 0.35 //radius
    
    _w = 1.0;
    
    _max_iteration = 33;//30 //42
    
    
    
    //Use the following relationship to find c = 0.7 * 2 * sqrt(m*ko)
    
    _spring_rate = 0.1*0.001;// ko 0.1 0.001*0.0001
    
    
    _mass =1.0; //m
    
    _time_step = 0.1; // t 0.01
    
    
    _damping_force = 0.7*sqrt(_spring_rate*_mass); // c
    
    p1 = 0.0;
    p2 = 0.0;
    
    dp2.push_back(0.0);  ///CHANGE THIS VALUE
    
    _set_presition =10;
    
    ptn_ini = 0;
    ptn_last = 6;
    
    counter =0;
    
    //   glutSwapBuffers();
    
    
    
}


BubblePacking::~BubblePacking()
{
    cout << "BubblePacking::~BubblePacking() \n"; 
    
    //Line using berzier ideas
    
    
    /*delete spline_;
     
     //circles_.clear();
     for(int i = 0; i < circles_.size(); i++)
     delete circles_[i];
     
     circles_.clear();
     
     delete [] dataPts_;*/
}

vector<Point2D> BubblePacking::sixbubble(int state, vector<Point2D> & location_points)
{
    
    ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/SixBubble.txt"); //Check is there is a file functionlaity does not exist
    // glClear(GL_COLOR_BUFFER_BIT);
    
    float _distance_left =0.0;
    float _distance_right =0.0;
    
    float _distance_bubbles =0.0;
    
    float _bubble_size_left = 0.0;
    float _bubble_size_right= 0.0;
    float _bubble_size_current= 0.0;
    
    float _stable_distance =0.0;
    float _interbubble_force = 0.0;
    
    float _diameter_bubble = _bubble_size;
    
    float h=0.01;
    
    float tempX = 0.0;
    float tempY =0.0;
    
    
    float kcolor=0.0;
    
    float spring_var = _spring_rate;
    
    vector<Point2D> Vnext; //next vector
    vector<Point2D> Vcurr; //current vector
    
    int _id = 0;
    
    float xt =0.0;
    float yt =0.0;
    
    float tempS =0.0;
    
    float tpar =0.0;
    
    const int TIMERMSECS = 20;
    float animation_time = 0;
    const float  animation_step = .5;
    
    Point2D _Tpoint(0,0); //tangent a that point in the bezier curve
    Point2D _Delta(xt,yt); //delta X point
    Point2D _BL(xt,yt); //bubble location after finding parameter t using bezier curve information
    
    
    // _location_spline = objSplineBB.CreateBubbleLocationSpline(); //crea otro vector por eso no son iguales
    //_location_spline = objSplineBB.spline_location_2d;
    
    //glClear(GL_COLOR_BUFFER_BIT);
    // glColor3f(0.0, 0.0, 0.0);
    // glLoadIdentity(); 
    
    if (state < 1)
    {
        
        float *locationX = new float [location_points.size()];
        float *locationY = new float [location_points.size()];
        
        float *locationXn = new float [location_points.size()];
        float *locationYn = new float [location_points.size()];
        
        for (int i=0;i<location_points.size()+1;i++) 
        {
            locationX[i] = location_points[i].x;
            locationY[i] = location_points[i].y;
            
            locationXn[i] = location_points[i].x;
            locationYn[i] = location_points[i].y;
            
        }
        
        for(int k=0; k<100 ; k++){
            
            
            tempX = 0.0;
            tempY =0.0;
            
            for(int j=1;j<location_points.size()-1;j++)
            {
                
                _distance_bubbles = findDistanceBetweenBubbles(location_points[j+1].x, location_points[j].x)  ; 
                _stable_distance = diameter_sum(_diameter_bubble,_diameter_bubble);
                
                if(_stable_distance > _distance_bubbles)
                {
                    
                    tempX = LocationCalc(locationX[j],spring_var, h, _distance_bubbles, _stable_distance, 1);
                    
                    
                }
                else if (_stable_distance <= _distance_bubbles) {
                    
                    tempX = LocationCalc(locationX[j], spring_var, h, _distance_bubbles, _stable_distance, 1);
                }
                
                
                // glutSwapBuffers();
                // objSplineBP.createBubble(tempX, locationY[j], _diameter_bubble, 0.05*j);
                
                
                _distance_bubbles = findDistanceBetweenBubbles(location_points[j+1].y, location_points[j].y)  ; 
                _stable_distance = diameter_sum(_diameter_bubble,_diameter_bubble);
                
                
                if(_stable_distance > _distance_bubbles)
                {
                    
                    tempY = LocationCalc(locationY[j], spring_var, h, _distance_bubbles, _stable_distance, 1);
                    
                    
                }
                else if (_stable_distance <= _distance_bubbles) {
                    
                    tempY = LocationCalc(locationY[j], spring_var, h, _distance_bubbles, _stable_distance, 1);
                }
                
                ////glutSwapBuffers();
                // objSplineBP.createBubble(tempX, tempY, _diameter_bubble, 0.05*j);
                
                
                // locationX[j] = tempX;
                // locationY[j] = tempY;
                
                
                _distance_bubbles = findDistanceBetweenBubbles(location_points[j-1].x, location_points[j].x)  ; 
                _stable_distance = diameter_sum(_diameter_bubble,_diameter_bubble);
                
                
                if(_stable_distance > _distance_bubbles)
                {
                    
                    tempX = LocationCalc(tempX,spring_var, h, _distance_bubbles, _stable_distance, 0);
                    
                    
                }
                else if (_stable_distance <= _distance_bubbles) {
                    
                    tempX = LocationCalc(tempX,spring_var, h, _distance_bubbles, _stable_distance, 0);
                }
                
                // glutSwapBuffers();
                // objSplineBP.createBubble(tempX, tempY, _diameter_bubble, 0.05*j);
                
                
                _distance_bubbles = findDistanceBetweenBubbles(location_points[j-1].y, location_points[j].y)  ; 
                _stable_distance = diameter_sum(_diameter_bubble,_diameter_bubble);
                
                
                if(_stable_distance > _distance_bubbles)
                {
                    
                    tempY = LocationCalc(tempY, spring_var, h, _distance_bubbles, _stable_distance, 1);
                    
                    
                }
                else if (_stable_distance <= _distance_bubbles) {
                    
                    tempY = LocationCalc(tempY, spring_var, h, _distance_bubbles, _stable_distance, 1);
                    
                }
                
                //glutSwapBuffers();
                // objSplineBP.createBubble(tempX, tempY, _bubble_size, 0.05*j);
                
                
                
                
                locationXn[j] = tempX;
                locationYn[j] = tempY;
                
                locationX[0] = 0;
                locationX[location_points.size()] = 6;
                
                locationY[0] = -1;
                locationY[location_points.size()] = -1;
                
                locationXn[0] = 0;
                locationXn[location_points.size()] = 6;
                
                locationYn[0] = -1;
                locationYn[location_points.size()] = -1;
                
                
                //finds the index of the value closest to the value tempX in X
                //  _id = AproxSearch(tempX,objSplineBP.bezier_location_2d, 0);  
                //  xt = objSplineBP.bezier_location_2d[_id+1].x-objSplineBP.bezier_location_2d[_id].x;
                //  yt = objSplineBP.bezier_location_2d[_id+1].y-objSplineBP.bezier_location_2d[_id].y;
                
                
                
                xt = locationXn[j]-locationX[j];
                yt = locationYn[j]-locationY[j];
                
                cout << "locationXn[j]: " << locationXn[j]   << "\t locationYn[j]: " << locationYn[j] ;
                cout << "\nlocationX[j]: " << locationX[j]   << "\t locationY[j]: " << locationY[j] ;
                
                _Delta.x =xt;
                _Delta.y =yt;
                _Tpoint = Tangent(objSplineBP.bezier_location_2d, tempX);
                
                tempS = deltaS(_Delta, _Tpoint);
                cout << "\t Delta S : " << tempS << endl; //dot product of the same vector is zero
                
                
                
                tpar = objSplineBP.parameter_for_each_bubble_location[j]+tempS;
                
                _BL = objSplineBP.XYParametric(tpar);
                
                locationX[j] = _BL.x;
                locationY[j] = _BL.y;
                
                
                if(k%5==0)
                {
                    //cout <<"hoy" <<endl<<endl;
                    glutSwapBuffers();
                    objSplineBP.createBubble(tempX, tempY, _bubble_size, 0.05*j);
                    
                    // glFlush();
                    //glutPostRedisplay();
                }
                
                
                
                
            }
            
            
            
            outfile << k << "  : --------------------------------------------" << endl;
            
            for (int i=0;i<location_points.size();i++) 
            {
                location_points[i].x = locationX[i]; 
                location_points[i].y = locationY[i]; 
                
                outfile << "Location X : " << locationX[i] << "\t";
                outfile << "Location Y : " << locationY[i] << endl;
            }
            
            // _distance_bubbles = r_distance(location_points[0],location_points[1]);
            
            
            // cout << "distance : " << _distance_bubbles << endl;
        }
        
        
    }
    
    for(int i=0;i<location_points.size();i++)
    {
        glutSwapBuffers();
        objSplineBP.createBubble(location_points[i] ,0.1,0);
        //  outfile << "Location X : " << _location_spline[i].x << "\t"; 
        //  outfile << "Location Y : " << _location_spline[i].y << endl;
        // locationX[i] = 0.0;
        
    }
    
   // int num_bubbles = (int) NumberBubbles(_bubble_size,_bubble_size);
    
    
    
    outfile.close();
    
    return location_points;
    
    
}


vector<Point2D> BubblePacking::sevenbubble(int state, vector<Point2D> & location_points, int k, float _bubble_size_owner)
{
    
    // ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/SevenBubble.txt"); //Check is there is a file functionlaity does not exist
    
    //float _distance_bubbles =0.0;
    
    
    float _stable_distance =0.0;
    
    float _diameter_bubble = 2*_bubble_size_owner;
    
    float _distance_left =0.0;
  //  float _distance_right =0.0;
    
    float h=0.01;
    
    float tempX = 0.0;
    float tempY =0.0;
    
    float _interbubble_force = 0.0;
    
    
    
    float spring_var = _spring_rate;
    
    vector<Point2D> Vnext; //next vector
    vector<Point2D> Vcurr; //current vector
    
    
    float xt =0.0;
    float yt =0.0;
    
    float tempS =0.0;
    
    
    Point2D _Tpoint(0,0); //tangent a that point in the bezier curve
    Point2D _Delta(xt,yt); //delta X point
    Point2D _BL(xt,yt); //bubble location after finding parameter t using bezier curve information
    
    float *locationX = new float [location_points.size()];
    float *locationY = new float [location_points.size()];
    
    float *locationXn = new float [location_points.size()];
    float *locationYn = new float [location_points.size()];
    
   
    
    if (state < 1)
    {
        
        
        for (int i=0;i<location_points.size();i++) 
        {
            locationX[i] = location_points[i].x;
            locationY[i] = location_points[i].y;
            
            locationXn[i] = location_points[i].x;
            locationYn[i] = location_points[i].y;
            
        }
        
        
       
        
        
      
        
        
        
        
        for(int j=1;j<location_points.size()-1;j++)
        {
            
            ///J+1
            
            _distance_left = findDistanceBetweenBubbles(location_points[j].x, location_points[j-1].x)  ; 
            _stable_distance = diameter_sum(_diameter_bubble,_diameter_bubble);
            
        
        cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout <<  "_distance_left:  " << _distance_left <<endl;           
        cout <<  "_stable_distance:  " << _stable_distance <<endl;
            
            if(_stable_distance > _distance_left)
            {
                
                _w = w_parameter(_distance_left, _stable_distance);
                _interbubble_force =  interbubble_force(spring_var, _stable_distance, _w);
                tempX=rk4_sol(locationX[j], h, _interbubble_force);
                
                //cout <<  "w : " << _w <<endl;
                //cout <<  "interbubble_force : " << _interbubble_force <<endl;
               // cout <<  "tempx : " << tempX <<endl;
                
                
                
            }
            else if (_stable_distance <= _distance_left) {
                
                _w = w_parameter(_distance_left, _stable_distance);
                _interbubble_force =  interbubble_force(spring_var, _stable_distance, _w);
                tempX=rk4_sol(locationX[j], h, _interbubble_force);
            }
            
        
            
            locationXn[j] = tempX;
             cout <<  "X[j+1]l : " << tempX <<endl;
            
            _distance_left = findDistanceBetweenBubbles(location_points[j].x, location_points[j+1].x)  ; 
            _stable_distance = diameter_sum(_diameter_bubble,_diameter_bubble);
            
            cout << "\n-----------------------------------------------------" << endl;
            cout <<  "_distance_left:  " << _distance_left <<endl;           
            cout <<  "_stable_distance:  " << _stable_distance <<endl;


            
            if(_stable_distance > _distance_left)
            {
                
                _w = w_parameter(_distance_left, _stable_distance);
                _interbubble_force =  interbubble_force(spring_var, _stable_distance, _w);
                tempX=rk4_sol(locationXn[j], h, -_interbubble_force);
                
               // cout <<  "w : " << _w <<endl;
               // cout <<  "interbubble_force : " << _interbubble_force <<endl;
               // cout <<  "tempx : " << tempX <<endl;
                
                
                
            }
            else if (_stable_distance <= _distance_left) {
                
                _w = w_parameter(_distance_left, _stable_distance);
                _interbubble_force =  interbubble_force(spring_var, _stable_distance, _w);
                tempX=rk4_sol(locationXn[j], h, -_interbubble_force);
            }
            
            locationXn[j] = tempX;
            
            cout <<  "X[j+1]r : " << tempX <<endl;


                       
            ////J-1
            
            _distance_left = findDistanceBetweenBubbles(location_points[j].y, location_points[j-1].y)  ; 
            _stable_distance = diameter_sum(_diameter_bubble,_diameter_bubble);
            
            cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
            cout <<  "_distance_left:  " << _distance_left <<endl;           
            cout <<  "_stable_distance:  " << _stable_distance <<endl;

            
            if(_stable_distance > _distance_left)
            {
                
                _w = w_parameter(_distance_left, _stable_distance);
                _interbubble_force =  interbubble_force(spring_var, _stable_distance, _w);
                tempY=rk4_sol(locationY[j], h, _interbubble_force);
                
                 cout <<  "w : " << _w <<endl;
                 cout <<  "interbubble_force : " << _interbubble_force <<endl;
              
                
                
                
            }
            else if (_stable_distance <= _distance_left) {
                
                _w = w_parameter(_distance_left, _stable_distance);
                _interbubble_force =  interbubble_force(spring_var, _stable_distance, _w);
                 tempY=rk4_sol(locationY[j], h, _interbubble_force);
                
                cout <<  "w : " << _w <<endl;
                cout <<  "interbubble_force : " << _interbubble_force <<endl;
               
                

            }
            
            
             locationYn[j] = tempY;
            
            cout <<  "Y[j+1]l : " << tempY <<endl;
            
            _distance_left = findDistanceBetweenBubbles(location_points[j].y, location_points[j+1].y)  ; 
            _stable_distance = diameter_sum(_diameter_bubble,_diameter_bubble);
            
            cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
            cout <<  "_distance_left:  " << _distance_left <<endl;           
            cout <<  "_stable_distance:  " << _stable_distance <<endl;
            
            if(_stable_distance > _distance_left)
            {
                
                _w = w_parameter(_distance_left, _stable_distance);
                _interbubble_force =  interbubble_force(spring_var, _stable_distance, _w);
                tempY=rk4_sol( locationYn[j], h, -_interbubble_force); 
                
                cout <<  "w : " << _w <<endl;
                cout <<  "interbubble_force : " << _interbubble_force <<endl;

                
                
            }
            else if (_stable_distance <= _distance_left) {
                
                _w = w_parameter(_distance_left, _stable_distance);
                _interbubble_force =  interbubble_force(spring_var, _stable_distance, _w);
                 tempY=rk4_sol(locationYn[j], h, -_interbubble_force);   
                
                cout <<  "w : " << _w <<endl;
                cout <<  "interbubble_force : " << _interbubble_force <<endl;

            }
            
            
            
           locationYn[j] = tempY;
            
            
            cout <<  "Y[j+1]l : " << tempY <<endl;
            
            xt = locationXn[j]-locationX[j];
            yt = locationYn[j]-locationY[j];
            
            cout << "..................................." << endl;
            cout << "xt:  " <<xt <<endl;
            cout << "yt:  " <<yt <<endl;
            
         //   cout << "locationXn[j]: " << locationXn[j]   << "\t locationYn[j]: " << locationYn[j] ;
          //  cout << "\nlocationX[j]: " << locationX[j]   << "\t locationY[j]: " << locationY[j] ;
            
            _Delta.x =xt;
            _Delta.y =yt;
            _Tpoint = Tangent(objSplineBP.bezier_location_2d, tempX);
            
            cout << "tangentPoint.x : " << _Tpoint.x <<endl;
            cout << "tangentPoint.y :  " <<_Tpoint.y <<endl;


            
            tempS = deltaS(_Delta, _Tpoint);
            
            cout << "tempS :  " << tempS <<endl;
          //  cout << "\t Delta S : " << tempS << endl; //dot product of the same vector is zero
            
            float temppS2 = objSplineBP.parameter_for_each_bubble_location[j];
            
          //  cout << "tempS2 :  " << temppS2 <<endl;

            
            objSplineBP.parameter_for_each_bubble_location[j] = objSplineBP.parameter_for_each_bubble_location[j]+tempS;
            
            cout << "tempS2 :  " << objSplineBP.parameter_for_each_bubble_location[j] <<endl;
          
            
            
            _BL = objSplineBP.XYParametric(objSplineBP.parameter_for_each_bubble_location[j]);
            
            locationX[j] = _BL.x;
            locationY[j] = _BL.y;
            
            
        }
        
        
        
        locationX[0] = 0;
        locationX[location_points.size()-1] = 6;
        
        locationY[0] = -2;
        locationY[location_points.size()-1] = 3;
        
        locationXn[0] = 0;
        locationXn[location_points.size()-1] = 6;
        
        locationYn[0] = -2;
        locationYn[location_points.size()-1] = 3;
        
        
        
        
        
        //  outfile << k << "  : --------------------------------------------" << endl;
        
        for (int i=0;i<location_points.size();i++) 
        {
            location_points[i].x = locationX[i]; 
            location_points[i].y = locationY[i]; 
            
            // outfile << "Location X : " << locationX[i] << "\t";
            // outfile << "Location Y : " << locationY[i] << endl;
        }
        
        tempX = 0.0;
        tempY =0.0;
        
        
        
    }
    
    /* for(int i=0;i<location_points.size();i++)
     {
     glutSwapBuffers();
     objSplineBP.createBubble(location_points[i] ,0.1);
     
     }*/
    
    // int num_bubbles = (int) NumberBubbles(_bubble_size,_bubble_size);
    
    
    //  outfile.close();
    
    delete [] locationX;
    delete [] locationY;
    delete [] locationXn;
    delete [] locationYn;
    
    return location_points;
    
    
}


vector<Point2D> BubblePacking::eightbubble(int state, vector<Point2D> & location_points, int k, float _bubble_size_owner)
{
    
    // ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/SevenBubble.txt"); //Check is there is a file functionlaity does not exist
    
 //   float _distance_bubbles =0.0;
    float _bubble_size_left =0.0;
    float _bubble_size_current =0.0;
    
    
    float _stable_distance =0.0;
    
    //float _diameter_bubble = 2*_bubble_size_owner;
    
    float _distance_left =0.0;
  //  float _distance_right =0.0;
    
    float h=0.01;
    
    float tempX = 0.0;
    float tempY =0.0;
    
    float _interbubble_force = 0.0;
    
    
    
    float spring_var = _spring_rate;
    
    ////vector<Point2D> Vnext; //next vector
   // vector<Point2D> Vcurr; //current vector
    
    
    float xt =0.0;
    float yt =0.0;
    
    float tempS =0.0;
    
    
    Point2D _Tpoint(0,0); //tangent a that point in the bezier curve
    Point2D _Delta(xt,yt); //delta X point
    Point2D _BL(xt,yt); //bubble location after finding parameter t using bezier curve information
    
    float *locationX = new float [location_points.size()];
    float *locationY = new float [location_points.size()];
    
    float *locationXn = new float [location_points.size()];
    float *locationYn = new float [location_points.size()];
    
    
    
    if (state < 1)
    {
        
        
        for (int i=0;i<location_points.size();i++) 
        {
            locationX[i] = location_points[i].x;
            locationY[i] = location_points[i].y;
            
            locationXn[i] = location_points[i].x;
            locationYn[i] = location_points[i].y;
            
        }
        
        
        
        
        
        
        
        
        
        
        for(int j=1;j<location_points.size()-1;j++)
        {
            
            ///J+1
            
            _distance_left = findDistanceBetweenBubbles(location_points[j].x, location_points[j-1].x)  ; 
            
         
            
            _bubble_size_left = 2*function_spacing(location_points[j-1].x);
            _bubble_size_current = 2*function_spacing(location_points[j].x);
            

            _stable_distance = diameter_sum(_bubble_size_left,_bubble_size_current);
            

            
            if(_stable_distance > _distance_left)
            {
                
                _w = w_parameter(_distance_left, _stable_distance);
                _interbubble_force =  interbubble_force(spring_var, _stable_distance, _w);
                tempX=rk4_sol(locationX[j], h, _interbubble_force);
                
                cout <<  "w : " << _w <<endl;
                cout <<  "interbubble_force : " << _interbubble_force <<endl;
                cout <<  "tempx : " << tempX <<endl;
                
                
                
            }
            else if (_stable_distance <= _distance_left) {
                
                _w = w_parameter(_distance_left, _stable_distance);
                _interbubble_force =  interbubble_force(spring_var, _stable_distance, _w);
                tempX=rk4_sol(locationX[j], h, _interbubble_force);
            }
            
            
            locationXn[j] = tempX;
            
            cout <<  "X [j+1] : " << tempX <<endl;
            
            _distance_left = findDistanceBetweenBubbles(location_points[j].x, location_points[j+1].x)  ; 
            
            _bubble_size_left = 2*function_spacing(location_points[j+1].x);
            _bubble_size_current = 2*function_spacing(location_points[j].x);
            
            
            _stable_distance = diameter_sum(_bubble_size_left,_bubble_size_current);

                    
            if(_stable_distance > _distance_left)
            {
                
                _w = w_parameter(_distance_left, _stable_distance);
                _interbubble_force =  interbubble_force(spring_var, _stable_distance, _w);
                tempX=rk4_sol(locationXn[j], h, -_interbubble_force);
                
               
                
                
            }
            else if (_stable_distance <= _distance_left) {
                
                _w = w_parameter(_distance_left, _stable_distance);
                _interbubble_force =  interbubble_force(spring_var, _stable_distance, _w);
                tempX=rk4_sol(locationXn[j], h, -_interbubble_force);
            }
            
            locationXn[j] = tempX;
            
            
             cout <<  "X [j-1] : " << tempX <<endl;
            
            ////J-1
            
            _distance_left = findDistanceBetweenBubbles(location_points[j].y, location_points[j-1].y)  ; 
            
            
            _bubble_size_left = 2*function_spacing(location_points[j-1].x);
            _bubble_size_current = 2*function_spacing(location_points[j].x);
            
            
            _stable_distance = diameter_sum(_bubble_size_left,_bubble_size_current);

            
            if(_stable_distance > _distance_left)
            {
                
                _w = w_parameter(_distance_left, _stable_distance);
                _interbubble_force =  interbubble_force(spring_var, _stable_distance, _w);
                tempY=rk4_sol(locationY[j], h, _interbubble_force);
                
                
                
            }
            else if (_stable_distance <= _distance_left) {
                
                _w = w_parameter(_distance_left, _stable_distance);
                _interbubble_force =  interbubble_force(spring_var, _stable_distance, _w);
                tempY=rk4_sol(locationY[j], h, _interbubble_force);
            }
            
            
            locationYn[j] = tempY;
            
            _distance_left = findDistanceBetweenBubbles(location_points[j].y, location_points[j+1].y)  ; 
         
            
            _bubble_size_left = 2*function_spacing(location_points[j+1].x);
            _bubble_size_current = 2*function_spacing(location_points[j].x);
            
            
            _stable_distance = diameter_sum(_bubble_size_left,_bubble_size_current);

            
            if(_stable_distance > _distance_left)
            {
                
                _w = w_parameter(_distance_left, _stable_distance);
                _interbubble_force =  interbubble_force(spring_var, _stable_distance, _w);
                tempY=rk4_sol( locationYn[j], h, -_interbubble_force);                
                
                
            }
            else if (_stable_distance <= _distance_left) {
                
                _w = w_parameter(_distance_left, _stable_distance);
                _interbubble_force =  interbubble_force(spring_var, _stable_distance, _w);
                tempY=rk4_sol(locationYn[j], h, -_interbubble_force);   
            }
            
            
            
            locationYn[j] = tempY;
            
            
            
            
            xt = locationXn[j]-locationX[j];
            yt = locationYn[j]-locationY[j];
            
            cout << "xt[j]: " << xt   << endl ;
            
            
            
            
          //  cout << "locationXn[j]: " << locationXn[j]   << "\t locationYn[j]: " << locationYn[j] ;
          //  cout << "\nlocationX[j]: " << locationX[j]   << "\t locationY[j]: " << locationY[j] ;
            
            _Delta.x =xt;
            _Delta.y =yt;
            _Tpoint = Tangent(objSplineBP.bezier_location_2d, tempX);
            
            tempS = deltaS(_Delta, _Tpoint);
            cout << "\t Delta S : " << tempS << endl; //dot product of the same vector is zero
            
            
            
            objSplineBP.parameter_for_each_bubble_location[j] = objSplineBP.parameter_for_each_bubble_location[j]+tempS;
            
            _BL = objSplineBP.XYParametric(objSplineBP.parameter_for_each_bubble_location[j]);
            
            locationX[j] = _BL.x;
            locationY[j] = _BL.y;
            
            
            //creates bubble
           // objSplineBP.createBubble(_BL ,_bubble_size_current,0);
            
            

            
            
        }
        
        
        
        locationX[0] = 0;
        locationX[location_points.size()-1] = 6;
        
        locationY[0] = -2;
        locationY[location_points.size()-1] = 3;
        
        locationXn[0] = 0;
        locationXn[location_points.size()-1] = 6;
        
        locationYn[0] = -2;
        locationYn[location_points.size()-1] = 3;
        
        
        
        
        
        //  outfile << k << "  : --------------------------------------------" << endl;
        
        for (int i=0;i<location_points.size();i++) 
        {
            location_points[i].x = locationX[i]; 
            location_points[i].y = locationY[i]; 
            
            // outfile << "Location X : " << locationX[i] << "\t";
            // outfile << "Location Y : " << locationY[i] << endl;
        }
        
        tempX = 0.0;
        tempY =0.0;
        
        
        
    }
    
    // for(int i=0;i<location_points.size();i++)
    // {
    // glutSwapBuffers();
   //  objSplineBP.createBubble(location_points[i] ,0.1);
     
    // }
    
    // int num_bubbles = (int) NumberBubbles(_bubble_size,_bubble_size);
    
    
    //  outfile.close();
    
    delete [] locationX;
    delete [] locationY;
    delete [] locationXn;
    delete [] locationYn;
    
    return location_points;
    
    
}



float BubblePacking::LocationCalc ( float _location_point,
                                   float _spring_rate,
                                   float _h, 
                                   float _distance_, 
                                   float _stable_distance_, 
                                   int state)
{
    
    float _w ;
    float _interbubble_force;
    
    if (state==0){ //LEFT
        
        _w = w_parameter(_distance_, _stable_distance_);
        _interbubble_force =  interbubble_force(_spring_rate, _stable_distance_, _w);
        _location_point = rk4_sol( _location_point, _h, _interbubble_force);
        
    }
    else if (state==1){ //RIGHT
        _w = w_parameter(_distance_, _stable_distance_);
        _interbubble_force =  interbubble_force(_spring_rate, _stable_distance_, _w);
        _location_point = rk4_sol( _location_point, _h, -_interbubble_force);
    }
    
    
    return _location_point;
}

float BubblePacking::w_parameter(float distance, float stable_distance)
{
    float _w_parameter = 1.5;
    
    _w_parameter = distance/(float)(stable_distance);
    
    //cout << ">> W parameter =  " << _w_parameter << endl << endl;
    
    
    return _w_parameter;
    
    
}


float BubblePacking::interbubble_force(float spring_rate, float stable_distance, float w_parameter)
{
    float _fw; //Temporal variable with the interbubble force at certain distance
    
    if( w_parameter >= 0 && w_parameter < 1.5)
    {
        _fw = 1.25 * (spring_rate/(float)(stable_distance)) * pow(w_parameter,3) - 
        2.375 * (spring_rate/(float)(stable_distance)) * pow(w_parameter,2) +
        1.125 * (spring_rate/(float)(stable_distance)) ;
    }
    else {
        _fw = 0.0;
    }
    
    //cout << "_fw : " << _fw << endl;
    
    return _fw;
    
}

float BubblePacking::rk4_sol(float xi, float time_step, float fw)
{
    // ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/PointsRK4.txt"); //Check is there is a file functionlaity does not exist
    
    
    
    //int _number_of_iter = _number_of_iter;
    
    float *x= new float [_max_iteration+1];
    float *v = new float [_max_iteration+1];
    float *a = new float [_max_iteration+1];
    
    // cout << ">> Runge Kutta Solution Points Test<< " << endl << endl;
    
    x[0]=xi;
    v[0]=0.0;
    a[0]=0.0;
    
    float x1,x2,x3,x4;
    float v1,v2,v3,v4;
    float a1,a2,a3,a4;
    
    float h = time_step;
    float dt;
    
    if(_max_iteration>180) _max_iteration=180; //CHANGE HERE
    
    for (int i =0 ; i<_max_iteration ; i++)
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
    
    return (x[_max_iteration]);
    
}

float BubblePacking::findDistanceBetweenBubbles(Point2D ptn1, Point2D ptn2)
{
    
    float _distance_temp = sqrt(pow((ptn2.x-ptn1.x),2)+pow((ptn2.y-ptn1.y),2));
    
    cout << "distance bubbles: " << _distance_temp << endl;
    
    return _distance_temp;
    
}

float BubblePacking::findDistanceBetweenBubbles(float x1, float x2)
{
    
    float _distance_temp = abs(x1-x2);
    
    return _distance_temp;
    
}

float BubblePacking::function2(float t, float v,float fw)
{
    
    float f = (1/(float)(_mass))*(fw-_damping_force*v);
    
    return (f);
}

float BubblePacking::diameter_sum(float dia1, float dia2)
{
    float _diameter_sum = 0.0;
    
    _diameter_sum = (dia1/(float)(2))+(dia2/(float)(2));
    
    return _diameter_sum;
    
    
}

float BubblePacking::NumberBubbles(float diameter_Xend1, float diameter_Xend2)
{
    
    float length = objSplineBP.curve_length(objSplineBP.spline_location_2d);
    float number_of_bubbles = 0.0;
    float Lo = 1; //Unit edge bubble diameter
    
    // number_of_bubbles = (1/(float)Lo)*(length-(Lo/(float)2)*(1/(float)diameter_Xend1+1/(float)diameter_Xend2));
    
    //  int approx_search = AproxSearch(1.2, objSplineBP.bezier_location_2d,1);
    
    Point2D CPOINT(0,0);
    
    
    CPOINT = Tangent(objSplineBP.bezier_location_2d, 1.4);
    
    float xt, yt;
    int _id = AproxSearch(1.4, objSplineBP.bezier_location_2d, 0);
    
    
    xt = objSplineBP.bezier_location_2d[_id+1].x-objSplineBP.bezier_location_2d[_id].x;
    yt = objSplineBP.bezier_location_2d[_id+1].y-objSplineBP.bezier_location_2d[_id].y;
    
    Point2D DeltaX (xt,yt);
    
    float tempS = deltaS(DeltaX, CPOINT);
    
    return number_of_bubbles;
}


vector<Point2D> BubblePacking::DeltaXi(vector<Point2D> &V1, vector<Point2D> &V2)
{
    vector<Point2D> dX;
    float _tx,_ty; //temporal variable
    
    _tx = _ty =0.0; //initializing temporal variable
    
    //ADD A WAY OF CHECKING THAT THE VECTORS HAVE THE SAME LENGHT
    
    for(int i=0; i<V1.size(); i++){
        _tx = V2[i].x-V1[i].x;
        _ty = V2[i].y-V1[i].y;
        
        
        dX.push_back(Point2D(_tx,_ty));
        
    }
    
    return (dX);
}

Point2D BubblePacking::Tangent(vector<Point2D> &V, float x)
{
    int _id = 0;
    
    _id = AproxSearch((double)x, V, 0);
    
    Point2D uvC(0,0);
    
    //unit vector 
    uvC.x = (V[_id+1].x-V[_id].x);
    uvC.y = (V[_id+1].y-V[_id].y);
    
    
    return (uvC);
    
}

//Index of Vector Location For Tangent
int BubblePacking::AproxSearch(const double val, vector<Point2D> & V, int mode )
{
    
    //This will not work if entangle or descenging CHECK later!!!!
    double min_val = numeric_limits<double>::max();
    int index = 0;
    
    for(int i=0;i<V.size();++i)
    {
        
        if(mode==0) //X values
        {
            double diff = abs(V[i].x - val);
            if(diff<min_val)
            {
                min_val = diff;
                index = i;
            }
        }
        if(mode==1) //Y values
        {
            double diff = abs(V[i].y - val);
            if(diff<min_val)
            {
                min_val = diff;
                index = i;
            }
            
        }
        
    }
    return index;
    
}

//Finds the dot product of two unit vectors

float BubblePacking::DotProduct(Point2D &P1, Point2D &P2)
{
    float _tempC;
    
    _tempC = P1.x*P2.x+P1.y*P2.y;
    
    return (_tempC);
    
    
}

//Calculates delta s in the parametric space
float BubblePacking::deltaS(Point2D &X, Point2D &CS)
{
    float _delta_s = 0.0;
    float _dotproduct =0.0;
    float _temp_l =0.0;
    
    _dotproduct = DotProduct(X, CS);
    _temp_l = sqrt(pow(CS.x,2)+pow(CS.y,2));
    
    _delta_s = _dotproduct/pow((float)_temp_l,2);
    
    return _delta_s;
    
}

//draw test lines
void BubblePacking::drawlines(int k)
{
    float gfPosX = (float)k/(float)20;
    
    glBegin(GL_LINES);
    glVertex3f(gfPosX, 0.25, 0.0);
    glVertex3f(1.0 - gfPosX, 0.75,0.0);
    glEnd();    
    
    objSplineBP.createBubble(gfPosX, 0.2, _bubble_size, 0.2*k);
    
    
}

//Function spacing
float BubblePacking::function_spacing(float _location)
{
    float tmp = 0.0;
    tmp = PI*(_location/(float)(6));
    
    //cout << "tx : " << tx <<endl;
    //ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/functionSpacing.txt"); //Check is there is a 
    
    // cout << "tx: " << tx << endl;
    
    tmp = 0.4*sin(tmp)+0.1; //SIN FUNCTION
    
    //tmp =0.25; //constant
    
    /*if(_location<2)
     {
     tmp = sin(tx)*0.2+0.1;
     }else if (_location>=2 && _location<3) {
     tmp =0.8;
     }
     
     else {
     tmp= 0.5*sin(tx)+0.1;
     }*/
    
    
    //tmp = 0.5*(2*sin(tx)*cos(tx)+0.2*0.5*pow(tx,2))-0.025*exp(tx)+0.2;
    
    //tmp = -2*pow(tx,3)+3*pow(tx,2)+0.1+sin(tx)-tan(2*tx);
    
    //outfile << "sin(tx): " << tmp << endl;
    
    //outfile.close();
    
    return tmp;
    
    
}



