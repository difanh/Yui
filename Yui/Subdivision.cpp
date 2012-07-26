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
    nPointInitial = 5;
    
    pointInitial = new BubbleDSalfa * [nPointInitial];
    for(int i=0;i<nPointInitial;i++){
        pointInitial[i] = new BubbleDSalfa  [nPointInitial];
        for(int j=0;j<nPointInitial;j++){
            pointInitial[i][j].idx = i*nPointInitial+j;
        }
        
    }

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
    
    BubbleSD[0].wasUsedFlag = true;
    
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
    
    //BUBBLE CENTER SE
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
    
    //BUBBLE CENTER NE
    BubbleSD[4].idx = 4;
    
    BubbleSD[4].u = 1;  BubbleSD[4].v = 0;
    
    BubbleSD[4].location.u = BubbleSD[4].u;
    BubbleSD[4].location.v = BubbleSD[4].v;
    
    BubbleSD[4].isC=false; //it is a node
    BubbleSD[4].isN=false; BubbleSD[4].isS=false;  BubbleSD[4].isW=false;  BubbleSD[4].isE=false;
    BubbleSD[4].isNW=false; BubbleSD[4].isSW=false; BubbleSD[4].isSE=false; BubbleSD[4].isNE=true;
    
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
    float distanceInside = 0.0;
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
                
                distanceInside = distanceBetweenBubblesParam(BubbleSD[i].location, BubbleSD[i+1].location,
                                                             BubbleSD[i].radius, BubbleSD[i+1].radius);
                
                if(distanceInside > (BubbleSD[i].radius + BubbleSD[i+1].radius))
                {
                
                    u = (BubbleSD[i+1].u+BubbleSD[i].u)/(float)2;
                    v = (BubbleSD[i+1].v+BubbleSD[i].v)/(float)2;

                    
                    cout << "distance : " << distance << endl;
                    cout << "distanceInside : " << distanceInside << endl;
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
                
                indexCounter++;
            }
            
            if(BubbleSD[i].isSW==true && BubbleSD[i].wasUsedFlag==false)
            {
                //NW and SW locations
                distance = distanceBetweenBubbles(BubbleSD[i].location, BubbleSD[i+1].location); 
                
                distanceInside = distanceBetweenBubblesParam(BubbleSD[i].location, BubbleSD[i+1].location,
                                                             BubbleSD[i].radius, BubbleSD[i+1].radius);
               
                if(distanceInside > (BubbleSD[i].radius + BubbleSD[i+1].radius))
                {
                    u = (BubbleSD[i+1].u+BubbleSD[i].u)/(float)2;
                    v = (BubbleSD[i+1].v+BubbleSD[i].v)/(float)2;
                    
                    
                    cout << "distance : " << distance << endl;
                    cout << "distanceInside : " << distanceInside << endl;
                    cout << "u : " << u << endl;
                    cout << "v : " << v << endl;

                    
                    BubbleSD[i].wasUsedFlag=true;
                    
                    fillDataStructure(indexCounter+1, 2, u, v);
                    
                    BubbleSD[indexCounter+1].createdBy[0]=0;
                    BubbleSD[indexCounter+1].createdBy[1]=i;
                    BubbleSD[indexCounter+1].createdBy[2]=i+1;
                    BubbleSD[indexCounter+1].createdBy[3]=0;
                    
                    BubbleSD[indexCounter+1].isS = true;
                    cluster[indexCounter+1] = BubbleSD[indexCounter+1];
                }
                
                indexCounter++;
            }
            
            if(BubbleSD[i].isSE==true && BubbleSD[i].wasUsedFlag==false )
            {
                //NW and SW locations
                distance = distanceBetweenBubbles(BubbleSD[i].location, BubbleSD[i+1].location); 
                
                distanceInside = distanceBetweenBubblesParam(BubbleSD[i].location, BubbleSD[i+1].location,
                                                             BubbleSD[i].radius, BubbleSD[i+1].radius);
               
                
                
                if(distanceInside > (BubbleSD[i].radius + BubbleSD[i+1].radius))
                {
                    u = (BubbleSD[i+1].u+BubbleSD[i].u)/(float)2;
                    v = (BubbleSD[i+1].v+BubbleSD[i].v)/(float)2;

                    
                    
                    cout << "distance : " << distance << endl;
                    cout << "distanceInside : " << distanceInside << endl;
                    cout << "u : " << u << endl;
                    cout << "v : " << v << endl;
                    
                    
                    BubbleSD[i].wasUsedFlag=true;
                    
                    fillDataStructure(indexCounter+1, 2, u, v);
                    
                    BubbleSD[indexCounter+1].createdBy[0]=0;
                    BubbleSD[indexCounter+1].createdBy[1]=0;
                    BubbleSD[indexCounter+1].createdBy[2]=i;
                    BubbleSD[indexCounter+1].createdBy[3]=i+1;
                    
                    BubbleSD[indexCounter+1].isE = true;
                    cluster[indexCounter+1] = BubbleSD[indexCounter+1];
                }
                
                indexCounter++;
            }
            
            if(BubbleSD[i].isNE==true && BubbleSD[i].wasUsedFlag==false)
            {
                //NW and SW locations
                distance = distanceBetweenBubbles(BubbleSD[i].location, BubbleSD[i-3].location); 
                
                distanceInside = distanceBetweenBubblesParam(BubbleSD[i].location, BubbleSD[i-3].location,
                                                             BubbleSD[i].radius, BubbleSD[i-3].radius);
                    
                if(distanceInside > (BubbleSD[i].radius + BubbleSD[i-3].radius))
                {
                    u = (BubbleSD[i-3].u+BubbleSD[i].u)/(float)2;
                    v = (BubbleSD[i-3].v+BubbleSD[i].v)/(float)2;
                    
                    cout << "distance : " << distance << endl;
                    cout << "distanceInside : " << distanceInside << endl;
                    cout << "u : " << u << endl;
                    cout << "v : " << v << endl;
                    
                    
                    BubbleSD[i].wasUsedFlag=true;
                    
                    fillDataStructure(indexCounter+1, 2, u, v);
                    
                    BubbleSD[indexCounter+1].createdBy[0]=i-3;
                    BubbleSD[indexCounter+1].createdBy[1]=0;
                    BubbleSD[indexCounter+1].createdBy[2]=0;
                    BubbleSD[indexCounter+1].createdBy[3]=i;
                    
                    BubbleSD[indexCounter+1].isN = true;
                    cluster[indexCounter+1] = BubbleSD[indexCounter+1];
                }
                
                indexCounter++;
            }



        }
        
        
    }
         
    
    BubbleDSalfa Qd0 [5]; 
    BubbleDSalfa Qd1 [5]; 
    BubbleDSalfa Qd2 [5]; 
    BubbleDSalfa Qd3 [5]; 
    
    quadrant(BubbleSD, 2, Qd0, Qd1, Qd2, Qd3);
    
    
            
    int level = 3;
    
    createrCenterKnot(Qd0[0].location, Qd0[2].location, indexCounter, level,0);
    indexCounter++;
    
    createWSENinQuadrant( Qd0,  indexCounter++);
    indexCounter++;
    
    //Matrix initialization to stared all the points in the animation for each time step for all bubbles
    int nPoints = 5; //numebr of points in the subdivision
    
    float **U = new float * [nPoints];
    for(int i=0;i<nPoints;i++){
        U[i] = new float  [nPoints];
        for(int j=0;j<nPoints;j++){
            U[i][j] = 0.0;
        }
        
    }
    
    float **V = new float * [nPoints];
    for(int i=0;i<nPoints;i++){
        V[i] = new float  [nPoints];
        for(int j=0;j<nPoints;j++){
            V[i][j] = 0.0;
        }
        
    }
    
    BubbleDSalfa QPo[nPoints*nPoints];
    
    subdivisionHardCode(nPoints, U, V, QPo);
    
    
    
       
}

float Subdivision::distanceBetweenBubbles(PointUV P1, PointUV P2)
{
    float distance = 0.0;
    
    distance = sqrt(powf(fabs(P2.u-P1.u),2)+powf(fabs(P2.v-P1.v),2));  
    
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

float Subdivision::distanceBetweenBubblesParam(PointUV P1, PointUV P2, float radiusOne, float radiusTwo)
{
    float distance =0.0; //stable distance
    float d=0.0;
    
    //distance between two bubbles in parametric space
    d = distanceBetweenBubbles(P1, P2);
    
    distance = d-radiusOne-radiusTwo;
    
    return (distance);
    
    
}

PointUV Subdivision::crearCenter(PointUV P1, PointUV P2)
{
    
    PointUV CenterPoint;
    
    CenterPoint.u = (P1.u+P2.u)/(float)2;
    CenterPoint.v = (P1.u+P2.u)/(float)2;

    
    return(CenterPoint);
    
}

void Subdivision::quadrant(BubbleDSalfa * initialClusterPoint, int level,  
                                    BubbleDSalfa* Q0,
                                    BubbleDSalfa* Q1,
                                    BubbleDSalfa* Q2,
                                    BubbleDSalfa* Q3) //9 points see algorithm
{
   // BubbleDSalfa* Q0= new BubbleDSalfa [3];
   // BubbleDSalfa* Q1= new BubbleDSalfa [3];
   // BubbleDSalfa* Q2= new BubbleDSalfa [3];
   // BubbleDSalfa* Q3= new BubbleDSalfa [3];
    
    for(int i=0;i<9;i++)
    {
      
        
        if(initialClusterPoint[i].isN)
        {
            Q0[3] = initialClusterPoint[8];
            Q3[0] = initialClusterPoint[8];
        }
        
        if(initialClusterPoint[i].isS)
        {
            Q1[2] = initialClusterPoint[6];
            Q2[1] = initialClusterPoint[6];
        }
        if(initialClusterPoint[i].isE)
        {
            Q2[3] = initialClusterPoint[7];
            Q3[2] = initialClusterPoint[7];
        }
        if(initialClusterPoint[i].isW)
        {
            Q0[1] = initialClusterPoint[5];
            Q1[0] = initialClusterPoint[5];
        }
        if(initialClusterPoint[i].isNW)
        {
            Q0[0] = initialClusterPoint[1];
        }
        if(initialClusterPoint[i].isSW)
        {
            Q1[1] = initialClusterPoint[2];
        }
        if(initialClusterPoint[i].isSE)
        {
            Q2[2] = initialClusterPoint[3];
        }
        if(initialClusterPoint[i].isNE)
        {
            Q3[3] = initialClusterPoint[4];
        }
        
        if(initialClusterPoint[i].isC)
        {
            
            Q0[2] = initialClusterPoint[0];
            Q1[3] = initialClusterPoint[0];
            Q2[0] = initialClusterPoint[0];
            Q3[1] = initialClusterPoint[0];
                        
            Q0[2].level = Q1[2].level = Q2[2].level =  Q3[2].level= level; //check this line
            
            
        }

        
        
    }
    
    Q0[4]=Q0[0];
    Q1[4]=Q1[0];
    Q2[4]=Q2[0];
    Q3[4]=Q3[0];
    
    
}


void Subdivision::createrCenterKnot(PointUV P1, PointUV P2, int currentIndex, int level, int state)
{
    
    PointUV CenterPoint = crearCenter(P1,P2);
    
    cout << "Location u:" << CenterPoint.u << endl;
    cout << "Location v:" << CenterPoint.v << endl;
    
    BubbleSD[currentIndex+1].wasUsedFlag=true;
    
    fillDataStructure(currentIndex+1, level, CenterPoint.u, CenterPoint.v);
    
    if(state==0) //NW
    {
        BubbleSD[indexCounter+1].createdBy[0]=indexCounter-7;
        BubbleSD[indexCounter+1].createdBy[1]=indexCounter-3;
        BubbleSD[indexCounter+1].createdBy[2]=indexCounter-8;
        BubbleSD[indexCounter+1].createdBy[3]=indexCounter;
        BubbleSD[indexCounter+1].isC = true;
    }
    
    
    if(state==1) //SW
    {
        BubbleSD[indexCounter+1].createdBy[0]=indexCounter-7;
        BubbleSD[indexCounter+1].createdBy[1]=indexCounter-3;
        BubbleSD[indexCounter+1].createdBy[2]=indexCounter-8;
        BubbleSD[indexCounter+1].createdBy[3]=indexCounter;
        BubbleSD[indexCounter+1].isC = true;
    }
    
    
    if(state==2) //SE
    {
        BubbleSD[indexCounter+1].createdBy[0]=indexCounter-7;
        BubbleSD[indexCounter+1].createdBy[1]=indexCounter-3;
        BubbleSD[indexCounter+1].createdBy[2]=indexCounter-8;
        BubbleSD[indexCounter+1].createdBy[3]=indexCounter;
        BubbleSD[indexCounter+1].isC = true;
    }
    
    
    if(state==3) //NE
    {
        BubbleSD[indexCounter+1].createdBy[0]=indexCounter-7;
        BubbleSD[indexCounter+1].createdBy[1]=indexCounter-3;
        BubbleSD[indexCounter+1].createdBy[2]=indexCounter-8;
        BubbleSD[indexCounter+1].createdBy[3]=indexCounter;
        BubbleSD[indexCounter+1].isC = true;
    }
    
    /// cluster[indexCounter+1] = BubbleSD[indexCounter+1];
}

void Subdivision::createWSENinQuadrant( BubbleDSalfa * Qd0, int currentIndex)
{
    int indexInQ = 4;
      
    
    
    for (int i=0; i<indexInQ;i++)
    {
        if(Qd0[i].isC==true) 
        {
            cout << "BSda[" << i << "]:" << BubbleSD[currentIndex].isC<< endl;
            cout << "It is in the center : " << endl;
            
        }        
        else {
            cout << "BSda[" << i << "]:" << BubbleSD[i].isC<< endl;
            cout << "It is not in the center : " << endl;
            
            if(Qd0[i].wasUsedFlag==false && Qd0[i+1].wasUsedFlag==false)
            {
                createBubbleInsertion(Qd0,i,currentIndex);
            }
                
            //    indexCounter++;
                   
        
            }
    }
}

void Subdivision::createBubbleInsertion (BubbleDSalfa * Qd0,int i, int currentIndex)
{
    float distance = 0.0;
    float distanceInside = 0.0;
    float u=0.0;
    float v=0.0;        

    //NW and SW locations
    
    distance = distanceBetweenBubbles(Qd0[i].location, Qd0[i+1].location); 
    
    distanceInside = distanceBetweenBubblesParam(Qd0[i].location, Qd0[i+1].location,
                                                 Qd0[i].radius, Qd0[i+1].radius);
    
    if(distanceInside > (Qd0[i].radius + Qd0[i+1].radius))
    {
        
        u = (Qd0[i+1].u+Qd0[i].u)/(float)2;
        v = (Qd0[i+1].v+Qd0[i].v)/(float)2;
        
        
        cout << "Adistance : " << distance << endl;
        cout << "AdistanceInside : " << distanceInside << endl;
        cout << "Au : " << u << endl;
        cout << "Av : " << v << endl;
        
        BubbleSD[i].wasUsedFlag=true;
        
        fillDataStructure(currentIndex+1, 2, u, v);
        
        BubbleSD[currentIndex+1].createdBy[0]=i;
        BubbleSD[currentIndex+1].createdBy[1]=i+1;
        BubbleSD[currentIndex+1].createdBy[2]=0;
        BubbleSD[currentIndex+1].createdBy[3]=0;
        
        //BubbleSD[currentIndex+1].isW = true;
        //cluster[currentIndex+1] = BubbleSD[currentIndex+1];
    }
    
 
    
}

void Subdivision::subdivisionHardCode(int nPoints, float** U, float** V, BubbleDSalfa* P)
{


    for(int i=0; i<nPoints; i++)
    {
        for(int j=0; j<nPoints; j++)
        {
            U[i][j] = 1/(float)(nPoints-1)*i;
            V[i][j] = 1/(float)(nPoints-1)*j;
           // cout << U[i][j] << endl;
          //  cout << V[i][j] << endl;
            
            P[i*nPoints+j].u = U[i][j];
            P[i*nPoints+j].v = V[i][j];
            P[i*nPoints+j].idx = i*nPoints+j;
            P[i*nPoints+j].radius = 0.02; //cahnge here
           
          //  cout << i*nPoints+j << endl;
            
        }
    }
        
    
    //return (U);
}