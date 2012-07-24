//
//  Vector2D.cpp
//  bubble
//
//  Created by diegoandrade on 4/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "Vector2D.h"


Origin2D_ Origin2D;


Vector2D& Vector2D::Rotate(float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);
    
    float nx = c * x - s * y;
    float ny = s * x + c * y;
    
    x = nx;
    y = ny;
    
    return (*this);
}