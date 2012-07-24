//
//  Subdivision.h
//  Nerv
//
//  Created by Diego Andrade on 7/23/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#ifndef Nerv_Subdivision_h
#define Nerv_Subdivision_h

//Strores location in U and V
struct PointUV {
    float u;
    float v;
};

//This is the bubble data structure
struct BubbleDSalfa {
    int idx; //unique id
    
    float u; //position in the parametric u space (0-1) dependes on the KnotVector  
    float v; //position in the parametric v space (0-1)
    
    PointUV location;
    
    bool wasUsedFlag;
    
    // gives the indeces of the bubbles that create this one if a node 4 if a corner one node dependoing
    // of the location in this vector one knows is notrh south east or west 
    // V [ north, south, west, east];
    int createdBy [4];
    
    //for center
    bool isN;
    bool isS;
    bool isW;
    bool isE;
    bool isC;
    
    //for corners
    bool isNW;
    bool isNE;
    bool isSW;
    bool isSE;
    
    //what level
    int level;
    
    //radius
    float radius;
    
}; //use here number of bubbles inside the geometry



class Subdivision{
    
public:
    
    // Constructor 
    Subdivision();
    
    // Destructor 
    ~Subdivision();
    
    int indexCounter; //keeps track of the indeces
    
    BubbleDSalfa cluster[9]; //Initial cluster
    BubbleDSalfa BubbleSD[15];
    
    
    void bubbleCreateInitialLocation (int numberOfBubbles);
    
    void bubbleSubdivisionDomain ();
    
    float distanceBetweenBubbles (PointUV P1, PointUV P2);
    
    void fillDataStructure(int i, int level, float u, float v);
    
       
};


#endif
