//
//  BubbleDSt.h
//  bubble
//
//  Created by diegoandrade on 4/27/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#ifndef bubble_BubbleDSt_h
#define bubble_BubbleDSt_h

class BubbleDSt{
    
public:
    float x; // object position x   
    float y; // object position y
    float z; // object position z
    float r; // radius
    

    
    int bubble_id_i; // bubble id x direction
    
    
public:
        
    BubbleDSt (float a, float b, float d, int i) { x =a; y=b; r=d; bubble_id_i=i;}
    
    BubbleDSt (float a, float b, float c, float d, int i ) { x =a; y=b; z=c; r=d; bubble_id_i=i; }
    

  

};



#endif
