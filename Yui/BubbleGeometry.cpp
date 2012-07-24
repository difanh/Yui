//
//  BubbleGeometry.cpp
//  bubble
//
//  Created by diegoandrade on 4/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>

#include "BubbleGeometry.h"
#include "Spline.h"

RungeKutta RK_obj;
Spline objSplineBB;


BubbleGeometry::BubbleGeometry(ifstream& inp)
{
    if(!inp.is_open())
    {
        cout << "ERROR: cannot open the input file \n";
        exit(0);
    }
    
   /* inp >> nDataPts_ >> curveDensity_ ;
    dataPts_ = new Point3d[nDataPts_];
    
    cout << "nDataPts =" << nDataPts_  << endl;
    
    for(int i = 0; i < nDataPts_; i++)
        inp >> dataPts_[i].x >> dataPts_[i].y >> dataPts_[i].z; 
    
    //read the circle info
    inp >> radius_  >> circleDensity_;
    inp >> center_.x >> center_.y >> center_.z;*/
    
    //this->createGeometry();  
}


BubbleGeometry::BubbleGeometry()
{
    _number_of_bubbles_v = 8; //7
    _max_iter_outter = 180;
    _number_k = 150;
    
    _sphereX=0.0f;
    _sphereY=0.0f;
    
    _r_bubble_distance = 0.0;
    _ro_stable_bubble_distance = 0.0; 
    
    _parameter_location = 4.0; //4
    
    _bubble_size = 0.2; //0.5 // 0.35
    
    _w = 1.0;
        
    _max_iteration = 30;//30 //42
    
    
    
    //Use the following relationship to find c = 0.7 * 2 * sqrt(m*ko)
    
    _spring_rate = 0.001;// ko 0.1
   
    
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


   
}

BubbleGeometry::~BubbleGeometry()
{
    cout << "BubbleGeometry::~BubbleGeometry() \n"; 
    
    //Line using berzier ideas
    
    
    /*delete spline_;
    
    //circles_.clear();
    for(int i = 0; i < circles_.size(); i++)
        delete circles_[i];
	
    circles_.clear();
    
    delete [] dataPts_;*/
}

void BubbleGeometry::createGeometry()
{  

    //_location_vector2d[_number_of_bubbles_v-1].x=3; //CHANGE THIS
    
    for (int i=0;i<_number_of_bubbles_v;i++)
    {
       // glColor3f(0.2f, 0.8f, 0.0f);
        
        _bubble_size = function_spacing(_location_vector2d[i].x);
        
        //cout << "_bubble_size : " << _bubble_size << endl;
        
        createBubble(_location_vector2d[i], _bubble_size );  //0.2 represents the size of the bubble
        
    }   
    
    create_line();
    
    //cout << "Subdivision was created succesfully... \n" << endl;      
    
    //cout << "Geometry was created succesfully... \n";    
}


void BubbleGeometry::createPoints()
{
   

    //_parameter_location = 1.0;
    
    createInterpolation(Point2D(ptn_ini,0), Point2D(ptn_last,0), _parameter_location,_number_of_bubbles_v); //Creates locations for the Bubbles
    
    
}

void BubbleGeometry::createBubble(Point2D ptn, float radius)
{
    glPushMatrix(); //Copies the matrix on the top of the stack, this would be like save the funcion
    glColor3f(1,0,1);  //set colour ball
    glTranslatef(0.0, 0.0 , 0.0); // back to origin
    glTranslatef(ptn.x, ptn.y, 0.0);
    
    
    float	LightYellow2[3]	=	{0.933333, 0.933333, 0.4};

   
    float x,y;
    
    glLineWidth(1);

    glBegin(GL_LINES); 
    glColor3fv(LightYellow2);
        
    x = (float)radius * cos(359*PI/180.0f);
    y = (float)radius * sin(359*PI/180.0f); 
    
    for (int j=0; j<360; j++)
    {
        glVertex2f(x, y);
        
        x = (float)radius * cos(j*PI/180.0f);
    
        y = (float)radius * sin(j*PI/180.0f); 
    
        glVertex2f(x, y);
    }
    
    
    //cout << "PI Value = " << PI << endl;
    
    glEnd();
    glPopMatrix(); // Would be equivalent like load the function 
    
}

void BubbleGeometry::createBubble(float x_location, float radius)
{
    glPushMatrix(); //Copies the matrix on the top of the stack, this would be like save the funcion
    glColor3f(1,0,1);  //set colour ball
    glTranslatef(0.0, 0.0 , 0.0); // back to origin
    glTranslatef(x_location, 0.0, 0.0);
    
    float x,y;
    
    float	LightYellow2[3]	=	{0.933333, 0.933333, 0.4};

    
    glBegin(GL_LINES);
    glColor3fv(LightYellow2);
    
    x = (float)radius * cos(359*PI/180.0f);
    y = (float)radius * sin(359*PI/180.0f); 
    
    for (int j=0; j<360; j++)
    {
        glVertex2f(x, y);
        
        x = (float)radius * cos(j*PI/180.0f);
        
        y = (float)radius * sin(j*PI/180.0f); 
        
        glVertex2f(x, y);
    }
    
    //cout << "PI Value = " << PI << endl;
    
    glEnd();
    glPopMatrix(); // Would be equivalent like load the function 
    
}

void BubbleGeometry::createBubble(float x_location, float radius, float colorID)
{
    glPushMatrix(); //Copies the matrix on the top of the stack, this would be like save the funcion
    glColor3f(1,0,1);  //set colour ball
    glTranslatef(0.0, 0.0 , 0.0); // back to origin
    glTranslatef(x_location, 0.0, 0.0);
    
    float x,y;
    
    float	colorUSER[3]	=	{1-colorID, 0.45-colorID, colorID};
        
    glBegin(GL_LINES);
    glColor3fv(colorUSER);
    
    x = (float)radius * cos(359*PI/180.0f);
    y = (float)radius * sin(359*PI/180.0f); 
    
    for (int j=0; j<360; j++)
    {
        glVertex2f(x, y);
        
        x = (float)radius * cos(j*PI/180.0f);
        
        y = (float)radius * sin(j*PI/180.0f); 
        
        glVertex2f(x, y);
    }
    
        
    //cout << "PI Value = " << PI << endl;
    
    glEnd();
    
 
    glPopMatrix(); // Would be equivalent like load the function 
    
}


void BubbleGeometry::createBubble(float x_location, float y_location, float radius, float colorID)
{
    glPushMatrix(); //Copies the matrix on the top of the stack, this would be like save the funcion
    glColor3f(1,0,1);  //set colour ball
    glTranslatef(0.0, 0.0 , 0.0); // back to origin
    glTranslatef(x_location, y_location, 0.0);
    
    float x,y;
    
    float	colorUSER[3]	=	{1-colorID, 0.45-colorID, colorID};
    
    glBegin(GL_LINES);
    glColor3fv(colorUSER);
    
    x = (float)radius * cos(359*PI/180.0f);
    y = (float)radius * sin(359*PI/180.0f); 
    
    for (int j=0; j<360; j++)
    {
        glVertex2f(x, y);
        
        x = (float)radius * cos(j*PI/180.0f);
        
        y = (float)radius * sin(j*PI/180.0f); 
        
        glVertex2f(x, y);
    }
    
    //cout << "PI Value = " << PI << endl;
    
    glEnd();
    
   
    glPopMatrix(); // Would be equivalent like load the function 
    
}

void BubbleGeometry::create_line()
{
    
    glPushMatrix(); //Copies the matrix on the top of the stack, this would be like save the funcion
    glColor3f(1,0,1);  //set colour ball
    glTranslatef(0.0, 0.0 , 0.0); // back to origin
    
    
    float	Beige[3]	=	{0.960784, 0.960784, 0.862745};
    
    glLineWidth(1);
    glBegin(GL_LINES);
        glColor3fv(Beige);
      
        glVertex2f(0, 0);  
        glVertex2f(6, 0);  
   
    glEnd();
    
    glPopMatrix(); // Would be equivalent like load the function 
    
}

void BubbleGeometry::createInterpolation(Point2D ptn1, Point2D ptn2, float location_parameter, int number_of_bubbles)
{
    
    float t=0.0; //parameter
    float lx=0.0,ly=0.0; //location 
    
    for (int i=0;i<number_of_bubbles;i++) //by using 1 to n-1 fixes the fisrt and last bubble ????
    {
        t=(float)i/((number_of_bubbles-1)); //location_parameter allows the bubbles to be in the center 
        //lx =(1-t)*ptn1.x+ t*ptn2.x;
       // ly =(1-t)*ptn1.y+ t*ptn2.y;
        
        lx =(1-t)*2.8+ t*3.2; //change this centers the postions towrds the center
        ly =(1-t)*ptn1.y+ t*ptn2.y;
        
       // cout << "Parameter t = " << setprecision(_set_presition)<< t << endl;
       // cout << "Location X = " << lx << endl;
       // cout << "Location Y = " << ly << endl;
        
        _location_vector2d.push_back(Point2D(lx,ly)); // here is where the location are stored for the bubbles in 2D
    }
    
    _location_vector2d[0].x=ptn_ini;
    
    _location_vector2d[number_of_bubbles-1].x=ptn_last;
}


void BubbleGeometry::createSplineInterpolation(Point2D ptn1, Point2D ptn2, float location_parameter, int number_of_bubbles)
{

    
}


void BubbleGeometry::createSubdivision()
{
    for (int i=0;i<_number_of_bubbles_v;i++)
    {
        //glColor3f(1.0f, 0.8f, 0.75f);

        createBubble(_location_vector2d[i], _bubble_size );  //0.2 represents the size of the bubble
        
    }   
    
    cout << "Subdivision was created succesfully... \n" << endl;        
    
}

float BubbleGeometry::findDistanceBetweenBubbles(Point2D ptn1, Point2D ptn2)
{
    
    float _distance_temp = sqrt(pow((ptn2.x-ptn1.x),2)+pow((ptn2.y-ptn1.y),2));
    
    cout << "distance bubbles: " << _distance_temp << endl;
    
    return _distance_temp;
    
}

float BubbleGeometry::findDistanceBetweenBubbles(float x1, float x2)
{
    
    float _distance_temp = abs(x1-x2);
    
    return _distance_temp;
    
}


float BubbleGeometry::r_distance( Point2D ptn1,  Point2D ptn2)
{
    float tmp =0.0;
    
    tmp = sqrt(pow((ptn2.x-ptn1.x),2)+pow((ptn2.y-ptn1.y),2)); //     
    
    return (tmp);
}

float BubbleGeometry::diameter_sum(float dia1, float dia2)
{
    float _diameter_sum = 0.0;
    
    _diameter_sum = (dia1/(float)(2))+(dia2/(float)(2));
    
    return _diameter_sum;
    
    
}


void BubbleGeometry::onebubble()
{
    
   // float ptn1,ptn2;
    float h;
   // float fw;
   // float location_x;
   // float time;
    
   // ptn1 = 0;
    //ptn2 = 1;
   // location_x = 1;
   // fw=1.2;
    h=0.01;
   // time = 0.0;
    
    float _diameter_bubble = 2*_bubble_size;
    float _stable_distance =0.0;
    float _bubbles_distance = 0.0;
    float _interbubble_force = 0.0;
   
    float kcolor=0.0;
    
  //  float tmp_time = _time_step;
    
  //  float point_x = 0.0;
    
    float *location = new float [_number_of_bubbles_v];
   // float *locationtmp = new float [_number_of_bubbles_v];


    

  //  createGeometry(); // Creates Visualization Initial
    
    ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/WorkingPoints.txt"); //Check is there is a file functionlaity does not exist

    
//    //Passing temprarrly info to a vector location
   for (int i=0;i<_number_of_bubbles_v;i++) {
//        
       location[i] = _location_vector2d[i].x;
//  
//        createBubble(location[i], 0.5);
//        
        outfile  <<"Location in X[ "<<i<<"]"<<location[i]<< "\n"; 
//        
    }
//    
  
    
    location[0]=ptn_ini;
    location[_number_of_bubbles_v-1]=ptn_last;
    
    
    //Matrix initialization to stared all the points in the animation for each time step for all bubbles
    float **M = new float * [_max_iter_outter];
    for(int i=0;i<_max_iter_outter;i++){
        M[i] = new float  [_number_of_bubbles_v];
        for(int j=0;j<_number_of_bubbles_v;j++){
            M[i][j] = 0.0;
            //M[i][j] = M[i][j];
        }
        
    }

    
    for(int t=0;t<_max_iter_outter;t++)
    {
        
    for (int i=1;i<_number_of_bubbles_v; i++)
    {
        //LEFT BUBBLE SIDE
         outfile  << "LEFT BUBBLE SIDE" << endl;
        
        
        _bubbles_distance = findDistanceBetweenBubbles(location[i], location[i-1]);
        cout << "_bubbles_distance = " << _bubbles_distance << endl;
        outfile  << "_bubbles_distance = " << _bubbles_distance << endl;
        
        _stable_distance = diameter_sum(_diameter_bubble,_diameter_bubble);
        cout << "_diameter_sum = " << _stable_distance << endl;
        outfile  << "_diameter_sum = " << _stable_distance << endl;
        
        if(_stable_distance > _bubbles_distance)
        {
            cout << "\n\nDIAMETERS ARE BIGGER THAN DISTANCE BETWEEN BUBBLES " << endl;
            outfile << "\nDIAMETERS ARE BIGGER THAN DISTANCE BETWEEN BUBBLES " << endl << endl;
            cout << "-------------------------------------------------------- " << endl << endl;
            outfile << "-------------------------------------------------------- " << endl << endl;

           
            _w = w_parameter(_bubbles_distance, _stable_distance);
            
            outfile  <<"W"<<i<<": " << _w << "\n"; 
            
            _interbubble_force =  interbubble_force(_spring_rate, _stable_distance, _w);
            
            outfile  <<"fw"<<i<<": " << _interbubble_force << "\n";
            cout << "fw"<<i<<": " << _interbubble_force << "\n"; 

            
            location[i]=rk4_sol(location[i], h, _interbubble_force);
            
            cout << "location["<<i<<"]: " << location[i] << "\n"; 
            outfile  << "location["<<i<<"]: " << location[i] << "\n";
            
                       
            M[t][i] = location[i];
            
            //cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
            

            
            
        }
        else if (_stable_distance <= _bubbles_distance) {
           // cout << "\n\nDIAMETERS ARE SMALLER THAN DISTANCE BETWEEN BUBBLES " << endl;
            outfile << "\nDIAMETERS ARE SMALLER THAN DISTANCE BETWEEN BUBBLES " << endl << endl;
           // cout << "-------------------------------------------------------- " << endl << endl;
            outfile << "-------------------------------------------------------- " << endl << endl;
            
            
            _w = w_parameter(_bubbles_distance, _stable_distance);
            
            outfile  <<"W"<<i<<": " << _w << "\n"; 
            
            _interbubble_force =  interbubble_force(_spring_rate, _stable_distance, _w);
            
            outfile  <<"fw"<<i<<": " << _interbubble_force << "\n"; 
           // cout << "fw"<<i<<": " << _interbubble_force << "\n";
            
            location[i]=rk4_sol(location[i], h, _interbubble_force);
           // cout << "location["<<i<<"]: " << location[i] << "\n";   
            outfile  << "location["<<i<<"]: " << location[i] << "\n"; 
            

            M[t][i] = location[i];
            
            //cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
            



        }
        
        
 
        
              
        
        // RIGHT BUBBLE SIDE
       /* outfile  << "RIGHT BUBBLE SIDE" << endl;

        _bubbles_distance = findDistanceBetweenBubbles(location[i+1], location[i]);
      //  cout << "_bubbles_distance = " << _bubbles_distance << endl;
        outfile  << "_bubbles_distance = " << _bubbles_distance << endl;
        
        _stable_distance = diameter_sum(_diameter_bubble,_diameter_bubble);
      //  cout << "_diameter_sum = " << _stable_distance << endl;
        outfile  << "_diameter_sum = " << _stable_distance << endl;
        
             
        
        
        
        if(_stable_distance > _bubbles_distance)
        {
            cout << "\n\nDIAMETERS ARE BIGGER THAN DISTANCE BETWEEN BUBBLES " << endl;
            outfile << "\nDIAMETERS ARE BIGGER THAN DISTANCE BETWEEN BUBBLES " << endl << endl;
            cout << "-------------------------------------------------------- " << endl << endl;
            outfile << "-------------------------------------------------------- " << endl << endl;
            
            
            _w = w_parameter(_bubbles_distance, _stable_distance);
            
            outfile  <<"W"<<i<<": " << _w << "\n"; 
            
            _interbubble_force =  interbubble_force(_spring_rate, _stable_distance, _w);
            
            outfile  <<"fw"<<i<<": " << _interbubble_force << "\n";
            cout << "fw"<<i<<": " << _interbubble_force << "\n"; 
            
            
            location[i]=rk4_sol(location[i], h, _interbubble_force);
            
            cout << "location["<<i<<"]: " << location[i] << "\n"; 
            outfile  << "location["<<i<<"]: " << location[i] << "\n"; 
            
            
            
            
            
            
            
            
        }
        else if (_stable_distance <= _bubbles_distance) {
            cout << "\n\nDIAMETERS ARE SMALLER THAN DISTANCE BETWEEN BUBBLES " << endl;
            outfile << "\nDIAMETERS ARE SMALLER THAN DISTANCE BETWEEN BUBBLES " << endl << endl;
            cout << "-------------------------------------------------------- " << endl << endl;
            outfile << "-------------------------------------------------------- " << endl << endl;
            
            
            _w = w_parameter(_bubbles_distance, _stable_distance);
            
            outfile  <<"W"<<i<<": " << _w << "\n"; 
            
            _interbubble_force =  interbubble_force(_spring_rate, _stable_distance, _w);
            
            outfile  <<"fw"<<i<<": " << _interbubble_force << "\n"; 
            cout << "fw"<<i<<": " << _interbubble_force << "\n";
            
            location[i]=rk4_sol(location[i], h, _interbubble_force);
            cout << "location["<<i<<"]: " << location[i] << "\n";   
            outfile  << "location["<<i<<"]: " << location[i] << "\n"; 
            
            
            
            
            
        }
*/
        
 
        
    }
        
    
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
   // glutPostRedisplay();
    
    glutSwapBuffers();
        
    kcolor = (t/(float)(_max_iter_outter-1));
        
        cout << "kcolor: "<< setprecision(7)<<setw(7)<< kcolor << "\t\n";

              
    for (int i=0;i<_number_of_bubbles_v;i++) {
        
        //sleep(5);
        createBubble(location[i], _bubble_size,kcolor);
        outfile << "----------------------------------------- " << endl << endl;
        outfile  <<"\n\nLocation in X[ "<<i<<"]"<<location[i]<< "\n"; 
        _location_vector2d[i].x = location[i];
        _location_vector2d[i].y = 0.0;
       
    
          } 
    }
    
    
    
    for(int i=0;i<20;i++){

            M[i][0] = 0;
            M[i][_number_of_bubbles_v-1] = 6.0;
   
        
    }
    
    
       
    
    create_line();
    
    outfile.close();
    
    
   // time_step(M); // sends the matreix to time_step to be render
    

    
    
}

void BubbleGeometry::twobubble()
{
   

    float h;
    //float fw;
   
   // float time;
    
 
    //fw=1.2;
    h=0.01;
    //time = 0.0;
    
  //  int m=0;
    
    float _diameter_bubble = 2*_bubble_size;
    float _stable_distance =0.0;
    float _bubbles_distance = 0.0;
    float _interbubble_force = 0.0;
    
    float kcolor=0.0;
    
     
    cout <<"FINAL in X[ "<< endl; 
    
    
    float *location = new float [_number_of_bubbles_v];
 
    
    ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/Working2Points.txt"); //Check is there is a file functionlaity does not exist
    
    for (int i=0;i<_number_of_bubbles_v;i++) {
             
        location[i] = _location_vector2d[i].x;
        
        outfile  <<"Location in XXX[ "<<i<<"]"<<location[i]<< "\n"; 
           
    }
   
    
    
    location[0]=ptn_ini;
    location[_number_of_bubbles_v-1]=ptn_last;
    
    
    //Matrix initialization to stared all the points in the animation for each time step for all bubbles
    float **M = new float * [_max_iter_outter];
    for(int i=0;i<_max_iter_outter;i++){
        M[i] = new float  [_number_of_bubbles_v];
        for(int j=0;j<_number_of_bubbles_v;j++){
            M[i][j] = 0.0;
                    }
        
    }
    
    
    for(int t=0;t<_max_iter_outter;t++)
    {
        
        for (int i=1;i<_number_of_bubbles_v-1; i++)
        {
                      
            _bubbles_distance = findDistanceBetweenBubbles(location[i], location[i-1]);
            cout << "_bubbles_distance = " << _bubbles_distance << endl;
            outfile  << "_bubbles_distance = " << _bubbles_distance << endl;
            
            _stable_distance = diameter_sum(_diameter_bubble,_diameter_bubble);
            //cout << "_diameter_sum = " << _stable_distance << endl;
            //outfile  << "_diameter_sum = " << _stable_distance << endl;
            
            if(_stable_distance > _bubbles_distance)
            {
                cout << "Bubble Diamter Bigger than distance"<< endl;
                
                _w = w_parameter(_bubbles_distance, _stable_distance);
                _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance, _w);
                location[i]=rk4_sol(location[i], h, _interbubble_force);
                
                
                M[t][i] = location[i];
                
                cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                outfile << "M-["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                
            }
            else if (_stable_distance <= _bubbles_distance) {
                cout << "Distance Bigger than diameter of bubbles"<< endl;
                
                 _w = w_parameter(_bubbles_distance, _stable_distance);
                _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance, _w);
                location[i]=rk4_sol(location[i], h, _interbubble_force);
                
                M[t][i] = location[i];
                
                cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n";
                 outfile << "-M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                
            }
            
            location[_number_of_bubbles_v] = ptn_last;
            
          
            
            
            
            
           
            
            
        }
        
        
        /*m=0;
        
        while (m<5){
              location[1] = location[1]-0.001;
            m++;
        }
         */
      
        
        glutSwapBuffers();
        
        kcolor = (t/(float)(_max_iter_outter-1));
        
        cout << "kcolor: "<< setprecision(7)<<setw(7)<< kcolor << "\t\n";
        
        
        for (int i=0;i<_number_of_bubbles_v;i++) {
            
            createBubble(location[i], _bubble_size,kcolor);
            //outfile << "----------------------------------------- " << endl << endl;
            outfile  <<"Location in Xf[ "<<i<<"]:\t"<<location[i]<< "\n"; 
            _location_vector2d[i].x = location[i];
            _location_vector2d[i].y = 0.0;
            
            
        } 
        
        outfile << "----------------------------------------- " << endl << endl;
    }
    
    
    
    for(int i=0;i<_max_iter_outter;i++){
        
        M[i][0] = ptn_ini;
        M[i][_number_of_bubbles_v-1] = ptn_last;
        
        
    }
    
    
    
    
    create_line();
    
    outfile.close();
    
    
    // time_step(M); // sends the matreix to time_step to be render
    
    
    
    
}

void BubbleGeometry::threebubble(int k)
{
     cout << "sin(tx): " << endl;
    
    float h;
   // float fw;
    
   // float time;
    
    
    //fw=1.2;
    h=0.01;
    //time = 0.0;
    
    //  int m=0;
    
    float _diameter_bubble = 2*_bubble_size;
    float _stable_distance =0.0;
   // float _bubbles_distance = 0.0;
    float _interbubble_force = 0.0;
    
    float kcolor=0.0;
    
    float _distance_left =0.0;
    float _distance_right =0.0;
    
    
   float *location = new float [_number_of_bubbles_v];
    
    
  //  ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/Working2Points.txt"); //Check is there is a file functionlaity does not exist
    
    for (int i=0;i<_number_of_bubbles_v;i++) {
        
        location[i] = _location_vector2d[i].x;
        
     //   outfile  <<"Location in Xi[ "<<i<<"]: "<<location[i]<< "\n"; 
        
    }
    
    
    
   
    //Matrix initialization to stared all the points in the animation for each time step for all bubbles
    float **M = new float * [_max_iter_outter];
    for(int i=0;i<_max_iter_outter;i++){
        M[i] = new float  [_number_of_bubbles_v];
        for(int j=0;j<_number_of_bubbles_v;j++){
            M[i][j] = 0.0;
        }
        
    } //CHANGE make sure to erase float**
    
 
    
   
    
    for(int t=0;t<_max_iter_outter;t++)
    {
        
        for (int i=1;i<_number_of_bubbles_v-1; i++)
        {
            _distance_left = findDistanceBetweenBubbles(location[i], location[i-1]);
            _stable_distance = diameter_sum(_diameter_bubble,_diameter_bubble);
                      
            if(_stable_distance > _distance_left)
            {
             //   cout << "Bubble Diamter Bigger than distance"<< endl;
                
                _w = w_parameter(_distance_left, _stable_distance);
                _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance, _w);
                location[i]=rk4_sol(location[i], h, _interbubble_force);
                
                
                M[t][i] = location[i];
                
               // cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
               // outfile << "M-["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                
            }
            else if (_stable_distance <= _distance_left) {
                //cout << "Distance Bigger than diameter of bubbles"<< endl;
                
                _w = w_parameter(_distance_left, _stable_distance);
                _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance, _w);
                location[i]=rk4_sol(location[i], h, _interbubble_force);
                
                M[t][i] = location[i];
                
               // cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n";
               // outfile << "-M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                
            }
            
            location[_number_of_bubbles_v] = ptn_last;
            location[0]=ptn_ini;
            
            _distance_right = findDistanceBetweenBubbles(location[i], location[i+1]);
            _stable_distance = diameter_sum(_diameter_bubble,_diameter_bubble);
            
            if(_stable_distance > _distance_right)
            {
                //cout << "Bubble Diamter Bigger than distance"<< endl;
                
                _w = w_parameter(_distance_right, _stable_distance);
                _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance, _w);
                location[i]=rk4_sol(location[i], h, -_interbubble_force);
                
                
                M[t][i] = location[i];
                
              //  cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
              //  outfile << "M-["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                
            }
            else if (_stable_distance <= _distance_right) {
                //cout << "Distance Bigger than diameter of bubbles"<< endl;
                
                _w = w_parameter(_distance_right, _stable_distance);
                _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance, _w);
                location[i]=rk4_sol(location[i], h, -_interbubble_force);
                
                M[t][i] = location[i];
                
               // cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n";
               // outfile << "-M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                
            }

            location[_number_of_bubbles_v] = ptn_last;
            location[0]=ptn_ini;

            
            
            
            
            
            
            
        }
        
        
        /*m=0;
         
         while (m<5){
         location[1] = location[1]-0.001;
         m++;
         }
         */
        
        
       
        
       // cout << "kcolor: "<< setprecision(7)<<setw(7)<< kcolor << "\t\n";
        
                
       // outfile << "----------------------------------------- " << endl << endl;
    }
       // glutSwapBuffers();
        
        kcolor = (k/(float)(_max_iter_outter-1));
        
        if(k%5==0)
        {
        for (int i=0;i<_number_of_bubbles_v;i++) {
            
            createBubble(location[i], _bubble_size,kcolor);
            //outfile << "----------------------------------------- " << endl << endl;
            // outfile  <<"Location in Xf[ "<<i<<"]:\t"<<location[i]<< "\n"; 
            _location_vector2d[i].x = location[i];
            _location_vector2d[i].y = 0.0;
            
            
        } 
        }

    
    
    
   // for(int i=0;i<_max_iter_outter;i++){
    //    
    //    M[i][0] = ptn_ini;
     //   M[i][_number_of_bubbles_v-1] = ptn_last;
        
        
  //  }
    
   
    
    create_line();
    
    for(int j=0;j<_number_of_bubbles_v;j++){
            delete [] M[j];
        }
    
    delete [] M;
    
    delete [] location;
    
  //  outfile.close();
    
    
    // time_step(M); // sends the matreix to time_step to be render
    
    
    
    
}


void BubbleGeometry::fourbubble(int k)
{
    //cout << "sin(tx): " << endl;
    
    float h;
  //  float fw;
    
   // float time;
    
    
    //fw=1.2;
    h=0.01;
    //time = 0.0;
    
    //  int m=0;
    
   // float _diameter_bubble = 2*_bubble_size;
    float _stable_distance =0.0;
   // float _bubbles_distance = 0.0;
    float _interbubble_force = 0.0;
    
    float kcolor=0.0;
    
    float _distance_left =0.0;
    float _distance_right =0.0;
    
    float _bubble_size_left = 0.0;
    float _bubble_size_right= 0.0;
     float _bubble_size_current= 0.0;
    
    
    
    float *location = new float [_number_of_bubbles_v+1];
    
    
    //  ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/Working2Points.txt"); //Check is there is a file functionlaity does not exist
    
    for (int i=0;i<_number_of_bubbles_v;i++) {
        
        location[i] = _location_vector2d[i].x;
        
        //   outfile  <<"Location in Xi[ "<<i<<"]: "<<location[i]<< "\n"; 
        
    }
    
    
    
    
    //Matrix initialization to stared all the points in the animation for each time step for all bubbles
    float **M = new float * [_max_iter_outter];
    for(int i=0;i<_max_iter_outter;i++){
        M[i] = new float  [_number_of_bubbles_v];
        for(int j=0;j<_number_of_bubbles_v;j++){
            M[i][j] = 0.0;
        }
        
    } //CHANGE make sure to erase float**
    
    
    
 
        
        for(int t=0;t<_max_iter_outter;t++)
        {
            
            for (int i=1;i<_number_of_bubbles_v-1; i++)
            {
                _distance_left = findDistanceBetweenBubbles(location[i], location[i-1]);
                
                _bubble_size_left = 2*function_spacing(location[i-1]);
                _bubble_size_current = 2*function_spacing(location[i]);
                
                _stable_distance = diameter_sum(_bubble_size_left,_bubble_size_current);
                
                if(_stable_distance > _distance_left)
                {
                     //  cout << "Bubble Diamter Bigger than distance"<< endl;
                    
                    _w = w_parameter(_distance_left, _stable_distance);
                    _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance, _w);
                    location[i]=rk4_sol(location[i], h, _interbubble_force);
                    
                    
                    M[t][i] = location[i];
                    
                    // cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                    // outfile << "M-["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                    
                }
                else if (_stable_distance <= _distance_left) {
                   // cout << "Distance Bigger than diameter of bubbles"<< endl;
                    
                    _w = w_parameter(_distance_left, _stable_distance);
                    _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance, _w);
                    location[i]=rk4_sol(location[i], h, _interbubble_force);
                    
                    M[t][i] = location[i];
                    
                   //  cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n";
                    // outfile << "-M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                    
                }
                
                location[_number_of_bubbles_v] = ptn_last;
                location[0]=ptn_ini;
                
                _distance_right = findDistanceBetweenBubbles(location[i], location[i+1]);
                
                _bubble_size_right = 2*function_spacing(location[i+1]);
                _bubble_size_current = 2*function_spacing(location[i]);
                
                _stable_distance = diameter_sum(_bubble_size_right,_bubble_size_current);

                
                if(_stable_distance > _distance_right)
                {
                   // cout << "Bubble Diamter Bigger than distance"<< endl;
                    
                    _w = w_parameter(_distance_right, _stable_distance);
                    _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance, _w);
                    location[i]=rk4_sol(location[i], h, -_interbubble_force);
                    
                    
                    M[t][i] = location[i];
                    
                    //  cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                    //  outfile << "M-["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                    
                }
                else if (_stable_distance <= _distance_right) {
                   // cout << "Distance Bigger than diameter of bubbles"<< endl;
                    
                    _w = w_parameter(_distance_right, _stable_distance);
                    _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance, _w);
                    location[i]=rk4_sol(location[i], h, -_interbubble_force);
                    
                    M[t][i] = location[i];
                    
                    // cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n";
                    // outfile << "-M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                    
                }
                
                location[_number_of_bubbles_v] = ptn_last;
                location[0]=ptn_ini;
                
                
                
                
                
                
                
                
            }
            
            
            /*m=0;
             
             while (m<5){
             location[1] = location[1]-0.001;
             m++;
             }
             */
            
            
            
            
            // cout << "kcolor: "<< setprecision(7)<<setw(7)<< kcolor << "\t\n";
            
            
            // outfile << "----------------------------------------- " << endl << endl;
        }
       // glutSwapBuffers();
        
       // kcolor = (k/(float)(_max_iter_outter-1));
        
        
            for (int i=0;i<_number_of_bubbles_v;i++) {
                
                
                _bubble_size_current = function_spacing(location[i]);
                createBubble(location[i], _bubble_size_current,0.6);
                //outfile << "----------------------------------------- " << endl << endl;
                // outfile  <<"Location in Xf[ "<<i<<"]:\t"<<location[i]<< "\n"; 
                _location_vector2d[i].x = location[i];
                //_location_vector2d[i].y = 0.0;
                
                
            } 
        
        
        
    
    
    // for(int i=0;i<_max_iter_outter;i++){
    //    
    //    M[i][0] = ptn_ini;
    //   M[i][_number_of_bubbles_v-1] = ptn_last;
    
    
    //  }
    
    
    
    create_line();
    
    for(int j=0;j<_number_of_bubbles_v;j++){
        delete [] M[j];
    }
    
    delete [] M;
    
    //  outfile.close();
    
    
    // time_step(M); // sends the matreix to time_step to be render
    
    
    
    
}

void BubbleGeometry::fivebubble(vector<Point2D> location_points)
{
    float h;
    h=0.01;
    
    // _number_of_bubbles_v =10;
      
    //float *location = new float [_number_of_bubbles_v];
    
    bool stop_sim = true;
    
    float *locationX = new float [location_points.size()];
    float *locationY = new float [location_points.size()];
    
      
    float _stable_distance =0.0;
       float _interbubble_force = 0.0;
    
    float kcolor=0.0;
    
    float _distance_left =0.0;
    float _distance_right =0.0;
    
    float _bubble_size_left = 0.0;
    float _bubble_size_right= 0.0;
    float _bubble_size_current= 0.0;
     
    cout << "SOLVER XXX: "<< location_points[0].x <<endl;
   
     
    for (int i=0;i<10;i++) {
                    
        locationX[i] = location_points[i].x;
        locationY[i] = location_points[i].y;
                
    }
    
    
    
   while(stop_sim)
   {
        
    for( int k=0;k<_number_k;k++)
    {
        
        for(int t=0;t<_max_iter_outter;t++)
        {
            
            for (int i=1;i<location_points.size()-1; i++)
            {
                _distance_left = findDistanceBetweenBubbles(locationX[i], locationX[i-1]);
                
                _bubble_size_left = function_spacing(locationX[i-1]);
                _bubble_size_current = function_spacing(locationX[i]);
                
                _stable_distance = diameter_sum(_bubble_size_left,_bubble_size_current);
                
                if(_stable_distance > _distance_left)
                {
                    //  cout << "Bubble Diamter Bigger than distance"<< endl;
                    
                    _w = w_parameter(_distance_left, _stable_distance);
                    _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance, _w);
                    locationX[i]=rk4_sol(locationX[i], h, _interbubble_force);
                    
                    
                                      
                    // cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                    // outfile << "M-["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                    
                }
                else if (_stable_distance <= _distance_left) {
                    // cout << "Distance Bigger than diameter of bubbles"<< endl;
                    
                    _w = w_parameter(_distance_left, _stable_distance);
                    _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance, _w);
                    locationX[i]=rk4_sol(locationX[i], h, _interbubble_force);
                    
                 
                    
                    //  cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n";
                    // outfile << "-M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                    
                }
                
                locationX[location_points.size()] = 6;
                locationX[0]=0;
                
                _distance_right = findDistanceBetweenBubbles(locationX[i], locationX[i+1]);
                
                _bubble_size_right = function_spacing(locationX[i+1]);
                _bubble_size_current = function_spacing(locationX[i]);
                
                _stable_distance = diameter_sum(_bubble_size_right,_bubble_size_current);
                
                
                if(_stable_distance > _distance_right)
                {
                    // cout << "Bubble Diamter Bigger than distance"<< endl;
                    
                    _w = w_parameter(_distance_right, _stable_distance);
                    _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance, _w);
                    locationX[i]=rk4_sol(locationX[i], h, -_interbubble_force);
                    
                   
                    
                    //  cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                    //  outfile << "M-["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                    
                }
                else if (_stable_distance <= _distance_right) {
                    // cout << "Distance Bigger than diameter of bubbles"<< endl;
                    
                    _w = w_parameter(_distance_right, _stable_distance);
                    _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance, _w);
                    locationX[i]=rk4_sol(locationX[i], h, -_interbubble_force);
                    
                                      
                    // cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n";
                    // outfile << "-M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                    
                }
                
                locationX[location_points.size()] = 6;
                locationX[0]=0;
                
                
                
                
                
                
                
                
            }
            
            for (int i=1;i<location_points.size()-1; i++)
            {
                _distance_left = findDistanceBetweenBubbles(locationY[i], locationY[i-1]);
                
                _bubble_size_left = function_spacing(locationY[i-1]);
                _bubble_size_current = function_spacing(locationY[i]);
                
                _stable_distance = diameter_sum(_bubble_size_left,_bubble_size_current);
                
                if(_stable_distance > _distance_left)
                {
                    //  cout << "Bubble Diamter Bigger than distance"<< endl;
                    
                    _w = w_parameter(_distance_left, _stable_distance);
                    _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance, _w);
                    locationY[i]=rk4_sol(locationY[i], h, _interbubble_force);
                    
                    
                    
                    // cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                    // outfile << "M-["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                    
                }
                else if (_stable_distance <= _distance_left) {
                    // cout << "Distance Bigger than diameter of bubbles"<< endl;
                    
                    _w = w_parameter(_distance_left, _stable_distance);
                    _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance, _w);
                    locationY[i]=rk4_sol(locationY[i], h, _interbubble_force);
                    
                    
                    
                    //  cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n";
                    // outfile << "-M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                    
                }
                
                locationY[location_points.size()] = -1;
                locationY[0]=-1;
                
                _distance_right = findDistanceBetweenBubbles(locationY[i], locationY[i+1]);
                
                _bubble_size_right = function_spacing(locationY[i+1]);
                _bubble_size_current = function_spacing(locationY[i]);
                
                _stable_distance = diameter_sum(_bubble_size_right,_bubble_size_current);
                
                
                if(_stable_distance > _distance_right)
                {
                    // cout << "Bubble Diamter Bigger than distance"<< endl;
                    
                    _w = w_parameter(_distance_right, _stable_distance);
                    _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance, _w);
                    locationY[i]=rk4_sol(locationY[i], h, -_interbubble_force);
                    
                    
                    
                    //  cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                    //  outfile << "M-["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                    
                }
                else if (_stable_distance <= _distance_right) {
                    // cout << "Distance Bigger than diameter of bubbles"<< endl;
                    
                    _w = w_parameter(_distance_right, _stable_distance);
                    _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance, _w);
                    locationY[i]=rk4_sol(locationY[i], h, -_interbubble_force);
                    
                    
                    // cout << "M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n";
                    // outfile << "-M["<<t<<"]"<<"["<<i<<"]: "<< M[t][i] << "\n"; 
                    
                }
                
                locationY[location_points.size()] = -1;
                locationY[0]=-1;
                
                
                
                
                
                
                
                
            }
            
            
        }
        
        glutSwapBuffers();
        
        kcolor = (1/(float)(_max_iter_outter-1));
        
       
            for (int i=0;i<location_points.size();i++) {
                
                
                _bubble_size = 0.2;//function_spacing(_location_vector_spline_2d[i]);
                createBubble(location_points[i].x,location_points[i].y,_bubble_size,kcolor);
               
                location_points[i].x = locationX[i];
                location_points[i].y = locationY[i];
                               
            } 
        
                
    }
       
       counter++;

       if (counter>0) stop_sim =false;

    
   }
    
    
          
    create_line();
    
      
   
    location_points = _location_spline;
    
    
}

vector<Point2D> BubbleGeometry::sixbubble(int state, vector<Point2D> & location_points)
{
    
    //ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/SixBubble.txt"); //Check is there is a file functionlaity does not exist
    
    float _distance_left =0.0;
    float _distance_right =0.0;
    
    float _distance_bubbles =0.0;
    
    float _bubble_size_left = 0.0;
    float _bubble_size_right= 0.0;
    float _bubble_size_current= 0.0;
    
     float _stable_distance =0.0;
    float _interbubble_force = 0.0;
    
    float _diameter_bubble =0.2;
    
    float h=0.01;
    
    
    float kcolor=0.0;

    
   // _location_spline = objSplineBB.CreateBubbleLocationSpline(); //crea otro vector por eso no son iguales
    //_location_spline = objSplineBB.spline_location_2d;
    
    if (state < 1)
    {
    
        float *locationX = new float [location_points.size()];
        float *locationY = new float [location_points.size()];
        
        for (int i=0;i<location_points.size()+1;i++) 
        {
            locationX[i] = location_points[i].x;
            locationY[i] = location_points[i].y;
            
        }
        
        for(int k=0; k<60 ; k++){
        for(int j=1;j<location_points.size()-1;j++)
        {
        
            _bubble_size_left = findDistanceBetweenBubbles(location_points[j-1], location_points[j])  ; 
            _stable_distance = diameter_sum(_diameter_bubble,_diameter_bubble);

                if(_stable_distance > _distance_left)
                {
                    
                    locationX[j] = LocationCalc(locationX[j], 0.25*_spring_rate, h, _distance_bubbles, _stable_distance, 0);
                    
                    
                }
                else if (_stable_distance <= _distance_left) {
                    
                    locationX[j] = LocationCalc(locationX[j], 0.25*_spring_rate, h, _distance_bubbles, _stable_distance, 0);
                }
            
            
            glutSwapBuffers();
            objSplineBB.createBubble(locationX[j], locationY[j], _diameter_bubble, 0.05*j);
            
            
            _bubble_size_left = findDistanceBetweenBubbles(location_points[j+1], location_points[j])  ; 
            _stable_distance = diameter_sum(_diameter_bubble,_diameter_bubble);

            
                if(_stable_distance > _distance_left)
                {
                    
                    locationY[j] = LocationCalc(locationY[j], 0.25*_spring_rate, h, _distance_bubbles, _stable_distance, 0);
                    
                    
                }
                else if (_stable_distance <= _distance_left) {
                    
                    locationY[j] = LocationCalc(locationY[j], 0.25*_spring_rate, h, _distance_bubbles, _stable_distance, 0);
                }
            
            glutSwapBuffers();
            objSplineBB.createBubble(locationX[j], locationY[j], _diameter_bubble, 0.05*j);
            
            _bubble_size_left = findDistanceBetweenBubbles(location_points[j-1], location_points[j])  ; 
            _stable_distance = diameter_sum(_diameter_bubble,_diameter_bubble);
            
            
            if(_stable_distance > _distance_left)
            {
                
                locationX[j] = LocationCalc(locationX[j], 0.25*_spring_rate, h, _distance_bubbles, _stable_distance, 1);
                
                
            }
            else if (_stable_distance <= _distance_left) {
                
                locationX[j] = LocationCalc(locationX[j], 0.25*_spring_rate, h, _distance_bubbles, _stable_distance, 1);
            }
            
            glutSwapBuffers();
            objSplineBB.createBubble(locationX[j], locationY[j], _diameter_bubble, 0.05*j);
            
            
            _bubble_size_left = findDistanceBetweenBubbles(location_points[j+1], location_points[j])  ; 
            _stable_distance = diameter_sum(_diameter_bubble,_diameter_bubble);
            
            
            if(_stable_distance > _distance_left)
            {
                
                locationY[j] = LocationCalc(locationY[j], 0.25*_spring_rate, h, _distance_bubbles, _stable_distance, 1);
                
                
            }
            else if (_stable_distance <= _distance_left) {
                
                locationY[j] = LocationCalc(locationY[j], 0.25*_spring_rate, h, _distance_bubbles, _stable_distance, 1);
            }
            
            glutSwapBuffers();
            objSplineBB.createBubble(locationX[j], locationY[j], _diameter_bubble, 0.05*j);


            
            for(int i=0;i<location_points.size();i++)
            {
                
                //  outfile << "Location X : " << _location_spline[i].x << "\t";
                //  outfile << "Location Y : " << _location_spline[i].y << endl;
                // locationX[i] = 0.0;
                
            }
            
            
            
            
        }
            
            
        
        for (int i=0;i<location_points.size();i++) 
        {
            location_points[i].x = locationX[i]; 
            location_points[i].y = locationY[i];        
        }
        
       // _distance_bubbles = r_distance(location_points[0],location_points[1]);
        
        
        // cout << "distance : " << _distance_bubbles << endl;
        }
        
       
    }
    
    for(int i=0;i<location_points.size();i++)
    {
        glutSwapBuffers();
        objSplineBB.createBubble(location_points[i] ,0.1,0);
        //  outfile << "Location X : " << _location_spline[i].x << "\t";
        //  outfile << "Location Y : " << _location_spline[i].y << endl;
        // locationX[i] = 0.0;
        
    }
    
   
    
    return location_points;
    
    //outfile.close();
  
    
}


float BubbleGeometry::LocationCalc ( float _location_point,
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
        _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance_, _w);
        _location_point = rk4_sol( _location_point, _h, _interbubble_force);

    }
    else if (state==1){ //RIGHT
        _w = w_parameter(_distance_, _stable_distance_);
        _interbubble_force =  interbubble_force(0.25*_spring_rate, _stable_distance_, _w);
        _location_point = rk4_sol( _location_point, _h, -_interbubble_force);
    }
    
    
    return _location_point;
}

void BubbleGeometry::time_step(float** M)
{
    
    for(int t=0;t<20;t++){
        //glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(int i=0;i<_number_of_bubbles_v;i++){
            
            createBubble(M[t][i], _bubble_size);
        }
    }
    
    
    
}


void BubbleGeometry::bubble_location(int parameter) //physical simulaiton implementation
{
  //  float _diameter_bubble = _bubble_size;
    float _stable_distance =0.0;
    float _bubbles_distance = 0.0;
    float _interbubble_force = 0.0;
    
   // int k =0;
    

    
    createGeometry(); // Creates Visualization Initial
    
    vector <Point2D> _LOCATION;
    vector <Point2D> _LOCATION2;
    
    _LOCATION = _location_vector2d;
    
     ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/PointsRGK.txt"); //Check is there is a file functionlaity does not exist
    
    _Integration_Solution_f1_X.push_back(0);
    _Integration_Solution_f1_Y.push_back(0);
    _Integration_Solution_f2_X.push_back(0);
    _Integration_Solution_f2_Y.push_back(0);
    
    float tmp_time = _time_step;
    
    float point_x = 0.0;
    
    float *location = new float [_number_of_bubbles_v];

      
   
    if (parameter==1) 
    {
        cout << "You have entered the FIRST choice bubbles will be packed towards the Center. " << endl <<endl;
        for (int t=0; t<_max_iteration ; t++) // number of itraeations 
        {
             outfile  << ">---" << t << "---<" <<endl <<endl;    
            
            for (int i=0;i<_number_of_bubbles_v-1; i++)
            {
                
                                
                _bubbles_distance = findDistanceBetweenBubbles(_LOCATION[i], _LOCATION[i+1]);
                 cout << "_bubbles_distance = " << _bubbles_distance << endl;
                 outfile  << "_bubbles_distance = " << _bubbles_distance << endl;
                
                _stable_distance = diameter_sum(_bubble_size,_bubble_size);
                cout << "_diameter_sum = " << _stable_distance << endl;
                outfile  << "_diameter_sum = " << _stable_distance << endl;
               
                if (_stable_distance > _bubbles_distance)
                {
                    cout << "\n\nDIAMETERS ARE BIGGER THAN DISTANCE BETWEEN BUBBLES " << endl << endl;
                    
                    outfile << "\nDIAMETERS ARE BIGGER THAN DISTANCE BETWEEN BUBBLES " << endl << endl;
                    
                    _w = w_parameter(_bubbles_distance, _stable_distance);
                    
                    outfile  <<"W"<<t<<": " << _w << "\n"; 
                    
                    _interbubble_force =  interbubble_force(_spring_rate, _stable_distance, _w);
                    
                    outfile  <<"fw"<<t<<": " << _interbubble_force << "\n"; 
                    
                    p1 = _LOCATION[i].x;
                    p2 = dp2[i-1];
                    
                    point_x = RungeKuttaSolution2(p1, p2, _time_step, _interbubble_force);
                    
                    cout << "> point_x = "<<  _LOCATION[i].x << endl;
                    
                    cout << "> Location X["<<i << "] = "<<  _LOCATION[i].x << endl;
                    
                    _LOCATION[i].x =  _LOCATION[i].x + point_x;
                    
                    cout << "> Location X["<<i << "] + point_x = "<<  _LOCATION[i].x << endl;
                    
                    outfile  <<"L"<<t<<": " << tmp_time<< "\t "<<_LOCATION[i].x<< "\t "<<_LOCATION[i].y<< "\n\n\n"; 
                    
                   // location[i] = _LOCATION[i].x;
                    
                    //(_LOCATION[i], _bubble_size);
                    
                }
                
               
                
                else {
                    
                    cout << "\nDIAMETERS ARE SMALLER THAN DISTANCE BETWEEN BUBBLES " << endl << endl;
                    
                    outfile << "\n\nDIAMETERS ARE SMALLER THAN DISTANCE BETWEEN BUBBLES " << endl << endl;
                    
                    _w = w_parameter(_bubbles_distance, _stable_distance);
                    
                    outfile  <<"W"<<t<<": " << _w << "\n"; 
                    
                    _interbubble_force =  interbubble_force(_spring_rate, _stable_distance, _w);
                    
                      outfile  <<"fw"<<t<<": " << _interbubble_force << "\n"; 

                    p1 = _LOCATION[i].x;
                    p2 = dp2[i-1];
                    
                    point_x = RungeKuttaSolution2(p1, p2, _time_step, _interbubble_force);
                    
                    cout << "> point_x = "<<  _LOCATION[i].x << endl;
                    
                    cout << "> Location X["<<i << "] = "<<  _LOCATION[1].x << endl;
                    
                    _LOCATION[i].x =  _LOCATION[i].x + point_x;
                    
                    cout << "> Location X["<<i << "] + point_x = "<<  _LOCATION[i].x << endl;
                                       
                    outfile  <<"L"<<t<<": " << tmp_time<< "\t "<<_LOCATION[i].x<< "\t "<<_LOCATION[i].y<< "\n";  

                   // createBubble(_LOCATION[i], _bubble_size);
                    
                     location[i] = _LOCATION[i].x;

                                      
                }
           
          
            }
        
        }
    }
        
       

        else if (parameter== 2) {
            cout << "You have entered the SECOND choice bubbles will be packed towards the Left. " << endl;
            
        } 
        else if (parameter== 3) {
            cout << "You have entered the THIRD choice bubbles will be packed towards the Right. " << endl;
            
        } 
        else if (parameter== 4) {
            cout << "You have entered the FOURTH choice bubbles will be packed towards the center. " << endl;
            
        } 
    
    
    for(int _i=0 ; _i<_number_of_bubbles_v-1 ; _i++)
    {
        outfile  << "X[" << _i << "]= "<< location[_i] << endl;
        
        createBubble(location[_i], _bubble_size);

        
    }
    
   
    outfile.close();
    
    
}

float BubbleGeometry::w_parameter(float distance, float stable_distance)
{
    float _w_parameter = 1.0;
    
    _w_parameter = distance/(float)(stable_distance);
    
    //cout << ">> W parameter =  " << _w_parameter << endl << endl;

    
    return _w_parameter;
    
    
}


float BubbleGeometry::interbubble_force(float spring_rate, float stable_distance, float w_parameter)
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

float BubbleGeometry::function(float t, float dx)
{
    
    float f = dx; // not the point but dx/dt
    
    return (f);
}

float BubbleGeometry::function2(float t, float v,float fw)
{
    
    float f = (1/(float)(_mass))*(fw-_damping_force*v);
    
    return (f);
}

float BubbleGeometry::rk4(float x, float v, float dt)
{
    float xf,vf;
    float x1,x2,x3,x4;
    float v1,v2,v3,v4;
    float a1,a2,a3,a4;
    
    
    x1 = x;
    v1 = v;
    a1 = function2(0,v1,dt);
    
    x2 = x+0.5*v1*dt;
    v2 = v+0.5*a1*dt;
    a2 = function2(0,v2,dt*0.5);
    
    x3 = x+0.5*v2*dt;
    v3 = v+0.5*a2*dt;
    a3 = function2(0,v3,dt*0.5);
    
    x4 = x+v3*dt;
    v4 = v+v3*dt;
    a4 = function2(0,v4,dt);
    
    xf = x + (dt/(float)(6.0))*(v1+2*v2+2*v3+v4);
    vf = v + (dt/(float)(6.0))*(a1+2*a2+2*a3+a4);

    
    return (xf);

}

void BubbleGeometry::rk4_sol()
{
    ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/PointsRK4.txt"); //Check is there is a file functionlaity does not exist
    
    
    
    int _number_of_iter = 3;
    
    float *x= new float [200];
    float *v = new float [200];
    float *a = new float [200];

    cout << ">> Runge Kutta Solution Points Test<< " << endl << endl;
     
    x[0]=1.0;
    v[0]=0.0;
    a[0]=0.0;
    
    float x1,x2,x3,x4;
    float v1,v2,v3,v4;
    float a1,a2,a3,a4;
    
    float h = 0.1;
    float dt;
    
    float fw = 0;
    
    
    for (int i =0 ; i<_number_of_iter; i++)
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
        
        
        cout << "x[" << i+1 << "]= "<<setprecision(7)<<setw(7)<< x[i+1] <<"\t";
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
        cout  << "a4[" << i << "]= "<< a4 <<"\t\t\t"<<endl;
        
        outfile  << "x[" << i << "]= "<< x[i] <<"\t";
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
        outfile  << "a4[" << i << "]= "<< a4 <<"\t"<<endl<<endl;
        
    }
    
    outfile.close();
    
}


float BubbleGeometry::rk4_sol(float xi, float time_step, float fw)
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

float BubbleGeometry::RungeKuttaSolution2(float ti, float xi, float h, float fw)
{
    ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/PointsRK3.txt"); //Check is there is a file functionlaity does not exist
    
    
    
    int _number_of_iter = 100;
     
    float* T = new float[200];    
    float* X = new float[200];
    float* dX = new float[200];
    
    float k1_,k2_,k3_,k4_;
   // cout << ">> RungeKuttaSolutionPoints << " << endl << endl;
    
    float temp = 0.0;
    
    
    T[0] = ti;
    X[0] = xi;
    dX[0] = 0.0;
    
    
    for (int i =1 ; i<_number_of_iter; i++)
    {
        T[i] = ti+i*h;
        
       
        
        k1_ = h* function(T[i-1], dX[i-1]);
        
        
        k2_ = h*function(T[i-1]+0.5*h, dX[i-1]+k1_*0.5);
        
        
        k3_ = h* function(T[i-1]+0.5*h, dX[i-1]+k2_*0.5);
        
        
        k4_ = h* function(T[i-1]+h, dX[i-1]+k3_);
        
        dX[i] = dX[i-1]+1/(float)(6)*(k1_+2*k2_+2*k3_+k4_);
        
        outfile  << "k1[" << i << "]= "<< k1_ <<"\t";
        outfile  << "k2[" << i << "]= "<< k2_<<"\t";
        outfile  << "k3[" << i << "]= "<< k3_ <<"\t";
        outfile  << "k4[" << i << "]= "<< k4_ <<"\n\n";

        
        
        k1_ = h* function2(T[i-1], temp, fw);
        
        k2_ = h*function2(T[i-1]+0.5*h, temp +k1_*0.5,fw);
        
        k3_ = h* function2(T[i-1]+0.5*h, temp+k2_*0.5,fw);
        
        k4_ = h* function2(T[i-1]+h,temp+k3_,fw);
        
        X[i] = X[i-1] +1/((float)(6))*(k1_+2*k2_+2*k3_+k4_);

        
             
        
              
        
        
        
    }
    
    
    for (int i =0 ; i<_number_of_iter; i++)
    {
        outfile  << "T[" << i << "]= "<< T[i] <<"\t";
        
        outfile  << "dX[" << i << "]= "<< dX[i] <<"\t";
        

        
       
        
        outfile  << "X[" << i << "]= "<< X[i]  << endl;
        
    }
    
    return (X[_number_of_iter-1]);
    
    outfile.close();    
    
}

float BubbleGeometry::RungeKuttaSolution(float _p1, float _p2i,float time_step, float fw)
{
    
    //_p2i the initial value of the derivative at t =0
    //_p2 the value calcualted t=t+1
    //_p1 is the initial position of the bubble
    
   // cout << ">> RungeKuttaSolutionPoints << " << endl << endl; 
     
    //cout << ">> X : " << _p1 << endl;    
       
    float rk = 0;
    float k1 = 0;
    float k2 = 0;
    float k3 = 0;
    float k4 = 0;
    
    float f2k1 = 0;
    float f2k2 = 0;
    float f2k3 = 0;
    float f2k4 = 0;    
   
    rk = RK_obj.function_p1(_p1);
    k1 = RK_obj.K1(_p1);
    k2 = RK_obj.K2(_p1, time_step);
    k3 = RK_obj.K3(_p1, time_step);
    k4 = RK_obj.K4(_p1, time_step);
    
   // cout << ">> RK_obj.function_p1 : " << rk << endl<<endl;
   // cout << ">> k1 : " << k1 <<endl;
   // cout << ">> k2 : " << k2 <<endl;
   // cout << ">> k3 : " << k3 <<endl;
   // cout << ">> k4 : " << k4 <<endl;
   
    float _p2 = _p1+1/(float)(6)*((k1+2*k2+2*k3+k4)*time_step);
    
    //_Integration_Solution_f1_X.push_back(_p2);
    
   // cout << ">> p2 : " << _p2<<endl<<endl;
    
    f2k1 = RK_obj.F2_K1(_p2, _p2i, fw);
    f2k2 = RK_obj.F2_K2(_p2, time_step, fw);
    f2k3 = RK_obj.F2_K3(_p2, time_step, fw);
    f2k4 = RK_obj.F2_K4(_p2, time_step, fw);
    
    
  //  cout << ">> F2k1 : " << f2k1 <<endl;
   // cout << ">> F2k2 : " << f2k2 <<endl;
   // cout << ">> F2k3 : " << f2k3 <<endl;
   // cout << ">> F2k4 : " << f2k4 <<endl;
    
    float _dp2 = _p2i +1/((float)(6))*((f2k1+2*f2k2+2*f2k3+f2k4)*time_step);// CHNAGE THIS MAKE SURE THE VALUE OF 0.0 IS CORRECT
    
   // cout << ">> dp2/dt : " << dp2 <<endl<<endl;
    
       
    dp1.push_back(_p2);
    dp2.push_back(_dp2);

    
    //ADD FUNTIONALITY TO CREATE AN ITERATION EACH TIME A KEY IS STROKE
       
    return _dp2; 
    
    
    
    
    
}


float BubbleGeometry::function_spacing(float _location)
{
    float tmp = 0.0;
     tmp = PI*(_location/(float)(ptn_last));
    
    //cout << "tx : " << tx <<endl;
    //ofstream outfile ("/Users/diegoandrade/Dropbox/CMU 2012/functionSpacing.txt"); //Check is there is a 
    
   // cout << "tx: " << tx << endl;
    
    tmp = 0.49*sin(tmp)+0.1; //SIN FUNCTION
    
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


