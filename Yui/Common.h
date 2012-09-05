//
//  Common.h
//  Yui
//
//  Created by Diego Andrade on 8/30/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#ifndef Yui_Common_h
#define Yui_Common_h


#define PI 4*atan(1)

#define MASS 1.0
#define SPRING_RATE 0.00001
#define DAMPING_FORCE 0.7*sqrt(SPRING_RATE*MASS)
#define NUM_ITERATIONS 35

typedef struct {
	float x, y, z;
} point_t; //, Point3d, Vector3d;



#endif
