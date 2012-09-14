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
#define SPRING_RATE 0.0001
#define DAMPING_FORCE 0.7*sqrt(SPRING_RATE*MASS)
#define NUM_ITERATIONS 50

typedef struct {
	float x, y, z;
} point_t; //, Point3d, Vector3d;

typedef struct {
	float u;
} Spoint1D; // this estructure represents the point in a parametrix space

//This is the bubble data structure
struct bubble {
    int idx; //unique id
    
    float u; //position in the parametric u space (0-1) dependes on the KnotVector
    float v; //position in the parametric v space (0-1)
    
    float x; //position in the real space
    float y; //position in the real space
    float z; //position in the real space
    
    float radius;
    
}; //use here number of bubbles inside the geometry


#endif
