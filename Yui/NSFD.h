//
//  NSFD.h
//  Yui
//
//  Created by Diego Andrade on 4/4/13.
//  Copyright (c) 2013 Carnegie Mellon University. All rights reserved.
//

#ifndef Yui_NSFD_h
#define Yui_NSFD_h

#include <iostream>
#include "matrix.h"

#define REAL double

using namespace std;



class ChorinProjection{
    
public:
    
    ChorinProjection();
    ~ChorinProjection();
    
    void INIT_UVP(char *problem,
                  REAL **U,REAL **V,REAL **P,REAL **TEMP,REAL **KA,
                  REAL **EP,int imax,int jmax,REAL delx,REAL dely,
                  REAL delxw,REAL delyw,REAL UI,REAL VI,REAL TI,
                  REAL KAI,REAL EPI);
    
};

#endif
