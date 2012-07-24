//
//  Subdivision.cpp
//  Nerv
//
//  Created by Diego Andrade on 7/23/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#include <iostream>
#include "Subdivision.h"
#include <math.h>

using namespace std;


Subdivision::Subdivision()
{
    
}

Subdivision::~Subdivision()
{
    
}

void Subdivision::bubbleCreateInitialLocation(int numberOfBubbles)
{
    
    
    //BUBBLE CENTER
    BubbleSD[0].idx = 0;
    
    BubbleSD[0].u = 0.5;  BubbleSD[0].v = 0.5;
    
    BubbleSD[0].location.u = BubbleSD[0].u;
    BubbleSD[0].location.v = BubbleSD[0].v;

    
    BubbleSD[0].isC=true; //it is a node
    BubbleSD[0].isN=false;  BubbleSD[0].isS=false;  BubbleSD[0].isW=false;  BubbleSD[0].isE=false;
    BubbleSD[0].isNW=false; BubbleSD[0].isSW=false; BubbleSD[0].isSE=false; BubbleSD[0].isNE=false;
   
    BubbleSD[0].createdBy[0]=1;
    BubbleSD[0].createdBy[1]=2;
    BubbleSD[0].createdBy[2]=3;
    BubbleSD[0].createdBy[3]=4;
    
    BubbleSD[0].level= 0;
    
    BubbleSD[0].wasUsedFlag = false;
    
    BubbleSD[0].radius = 0.05;
    
    
    //BUBBLE CENTER NW
    BubbleSD[1].idx = 1;
    
    BubbleSD[1].u = 0;  BubbleSD[1].v = 0;
    
    BubbleSD[1].location.u = BubbleSD[1].u;
    BubbleSD[1].location.v = BubbleSD[1].v;
    
    BubbleSD[1].isC=false; //it is a node
    BubbleSD[1].isN=false;  BubbleSD[1].isS=false;  BubbleSD[1].isW=false;  BubbleSD[1].isE=false;
    BubbleSD[1].isNW=true; BubbleSD[1].isSW=false; BubbleSD[1].isSE=false; BubbleSD[1].isNE=false;
    
    BubbleSD[1].createdBy[0]=0;
    BubbleSD[1].createdBy[1]=0;
    BubbleSD[1].createdBy[2]=0;
    BubbleSD[1].createdBy[3]=0;
    
    BubbleSD[1].level= 0;
    
    BubbleSD[1].wasUsedFlag = false;
    
    BubbleSD[1].radius = 0.05;
    
    //BUBBLE CENTER SW
    BubbleSD[2].idx = 2;
    
    BubbleSD[2].u = 0;  BubbleSD[2].v = 1;
    
    BubbleSD[2].location.u = BubbleSD[2].u;
    BubbleSD[2].location.v = BubbleSD[2].v;
    
    BubbleSD[2].isC=false; //it is a node
    BubbleSD[2].isN=false; BubbleSD[2].isS=false;  BubbleSD[2].isW=false;  BubbleSD[2].isE=false;
    BubbleSD[2].isNW=false; BubbleSD[2].isSW=true; BubbleSD[2].isSE=false; BubbleSD[2].isNE=false;
    
    BubbleSD[2].createdBy[0]=0;
    BubbleSD[2].createdBy[1]=0;
    BubbleSD[2].createdBy[2]=0;
    BubbleSD[2].createdBy[3]=0;
    
    BubbleSD[2].level= 0;
    
    BubbleSD[2].wasUsedFlag = false;
    
    BubbleSD[2].radius = 0.05;
    
    //BUBBLE CENTER SW
    BubbleSD[3].idx = 3;
    
    BubbleSD[3].u = 1;  BubbleSD[3].v = 1;
    
    BubbleSD[3].location.u = BubbleSD[3].u;
    BubbleSD[3].location.v = BubbleSD[3].v;
    
    BubbleSD[3].isC=false; //it is a node
    BubbleSD[3].isN=false; BubbleSD[3].isS=false;  BubbleSD[3].isW=false;  BubbleSD[3].isE=false;
    BubbleSD[3].isNW=false; BubbleSD[3].isSW=false; BubbleSD[3].isSE=true; BubbleSD[3].isNE=false;
    
    BubbleSD[3].createdBy[0]=0;
    BubbleSD[3].createdBy[1]=0;
    BubbleSD[3].createdBy[2]=0;
    BubbleSD[3].createdBy[3]=0;
    
    BubbleSD[3].level= 0;
    
    BubbleSD[3].wasUsedFlag = false;
    
    BubbleSD[3].radius = 0.05;
    
    //BUBBLE CENTER SW
    BubbleSD[4].idx = 4;
    
    BubbleSD[4].u = 1;  BubbleSD[4].v = 1;
    
    BubbleSD[4].location.u = BubbleSD[4].u;
    BubbleSD[4].location.v = BubbleSD[4].v;
    
    BubbleSD[4].isC=false; //it is a node
    BubbleSD[4].isN=false; BubbleSD[3].isS=false;  BubbleSD[3].isW=false;  BubbleSD[3].isE=false;
    BubbleSD[4].isNW=false; BubbleSD[3].isSW=false; BubbleSD[3].isSE=false; BubbleSD[3].isNE=true;
    
    BubbleSD[4].createdBy[0]=0;
    BubbleSD[4].createdBy[1]=0;
    BubbleSD[4].createdBy[2]=0;
    BubbleSD[4].createdBy[3]=0;
    
    BubbleSD[4].level= 0;
    
    BubbleSD[4].wasUsedFlag = false;
    
    BubbleSD[4].radius = 0.05;
    
    indexCounter = 4;

    
    
    //Transfering data to cluster
    cluster[0] = BubbleSD[0];
    cluster[1] = BubbleSD[1];
    cluster[2] = BubbleSD[2];
    cluster[3] = BubbleSD[3];
    cluster[4] = BubbleSD[4];
    
    
    
    
}

void Subdivision::bubbleSubdivisionDomain()
{
    
    int numberOfBubbles = 10;
    float distance = 0.0;
    float u=0.0;
    float v=0.0;
    
    for (int i=0; i<numberOfBubbles;i++)
    {
        if(BubbleSD[i].isC==true) 
        {
            cout << "BSda[" << i << "]:" << BubbleSD[i].isC<< endl;
            cout << "It is in the center : " << endl;

        }        
        else {
            cout << "BSda[" << i << "]:" << BubbleSD[i].isC<< endl;
            cout << "It is not in the center : " << endl;
            
            if(BubbleSD[i].isNW==true && BubbleSD[i].wasUsedFlag==false)
            {
                //NW and SW locations
                distance = distanceBetweenBubbles(BubbleSD[i].location, BubbleSD[i+1].location); 
                
                u = (BubbleSD[i+1].u-BubbleSD[i].u)/(float)2;
                v = (BubbleSD[i+1].v-BubbleSD[i].v)/(float)2;

                
                cout << "distance : " << distance << endl;
                cout << "u : " << u << endl;
                cout << "v : " << v << endl;
                
                BubbleSD[i].wasUsedFlag=true;
                
                fillDataStructure(indexCounter+1, 2, u, v);
                
                BubbleSD[indexCounter+1].createdBy[0]=i;
                BubbleSD[indexCounter+1].createdBy[1]=i+1;
                BubbleSD[indexCounter+1].createdBy[2]=0;
                BubbleSD[indexCounter+1].createdBy[3]=0;
                
                BubbleSD[indexCounter+1].isW = true;
                cluster[indexCounter+1] = BubbleSD[indexCounter+1];
            }
            
            if(BubbleSD[i].isSW==true && BubbleSD[i].wasUsedFlag==false)
            {
                //NW and SW locations
                distance = distanceBetweenBubbles(BubbleSD[i].location, BubbleSD[i+1].location); 
                
                u = (BubbleSD[i+1].u-BubbleSD[i].u)/(float)2;
                v = (BubbleSD[i+1].v-BubbleSD[i].v)/(float)2;
                
                
                cout << "distance : " << distance << endl;
                cout << "u : " << u << endl;
                cout << "v : " << v << endl;
                
                BubbleSD[i].wasUsedFlag=true;
                
                fillDataStructure(indexCounter+1, 2, u, v);
                
                BubbleSD[indexCounter+1].createdBy[0]=i;
                BubbleSD[indexCounter+1].createdBy[1]=i+1;
                BubbleSD[indexCounter+1].createdBy[2]=0;
                BubbleSD[indexCounter+1].createdBy[3]=0;
                
                BubbleSD[indexCounter+1].isW = true;
                cluster[indexCounter+1] = BubbleSD[indexCounter+1];
            }

        }
        
        
    }
         
    
    
    
}

float Subdivision::distanceBetweenBubbles(PointUV P1, PointUV P2)
{
    float distance = 0.0;
    
    
    distance = sqrt(pow((P1.u-P2.u),2)+pow((P1.v-P2.v),2));
    
    return (distance);
}

void Subdivision::fillDataStructure(int i, int level, float u, float v)
{
    BubbleSD[i].idx = i;   
    BubbleSD[i].u = u;  BubbleSD[i].v = v;
    
    BubbleSD[i].location.u = BubbleSD[i].u;
    BubbleSD[i].location.v = BubbleSD[i].v;
    
    
    BubbleSD[i].isC=false; //it is a node
    BubbleSD[i].isN=false;  BubbleSD[i].isS=false;  BubbleSD[i].isW=false;  BubbleSD[i].isE=false;
    BubbleSD[i].isNW=false; BubbleSD[i].isSW=false; BubbleSD[i].isSE=false; BubbleSD[i].isNE=false;
    
    BubbleSD[i].level= level;
    
    BubbleSD[i].wasUsedFlag = false;
    
    BubbleSD[i].radius = 0.05; //change here
    
    
}


