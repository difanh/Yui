//
//  Util.h
//  Yui
//
//  Created by Diego Andrade on 9/10/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#ifndef __Yui__Util__
#define __Yui__Util__

#include <iostream>
#include <fstream>
#include "Common.h"

using namespace std;

class Util
{
    
public:
    
    Util();
    ~Util();
    
    void printMatrix (bubble** Mat, int IMAX);
    
    void printVect (bubble* Vect, int numberOfBubbles);
    
    void printVectPoints (point_t* Vect, int numberOfPoints, char* file);
    
};  // class creates the boundaries for the given geometry




#endif /* defined(__Yui__Util__) */
