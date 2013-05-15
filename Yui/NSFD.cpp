//
//  NSFD.cpp
//  Yui
//
//  Created by Diego Andrade on 4/4/13.
//  Copyright (c) 2013 Carnegie Mellon University. All rights reserved.
//

#include "NSFD.h"


Matrix * pos;
ChorinProjection::ChorinProjection()
{
    
}

ChorinProjection::~ChorinProjection()
{
    
}

/*---------------------------------------------------------------*/
/* Initialisierung der Anfangswerte fuer U,V,P,TEMP,KA und EP    */
/*---------------------------------------------------------------*/
void ChorinProjection::INIT_UVP(char *problem,
              REAL **U,REAL **V,REAL **P,REAL **TEMP,REAL **KA,
              REAL **EP,int imax,int jmax,REAL delx,REAL dely,
              REAL delxw,REAL delyw,REAL UI,REAL VI,REAL TI,
              REAL KAI,REAL EPI)
{
    int i,j;
    REAL x,y,hoehe,xmue2,ymueob,ymueun;
    
    /* Loop begins traversing ALL cells */
    /*----------------------------------*/
    for(i=0;i<=imax+1;i++)
        for(j=0;j<=jmax+1;j++)
        {
            U[i][j] = UI;
            V[i][j] = VI;
            P[i][j] = 0.0;
            TEMP[i][j] = TI;
            KA[i][j] = KAI;
            EP[i][j] = EPI;
        }
    
    /* When backstep in the lower half is U, KA, EP = 0.0 set         */
    /*----------------------------------------------------------------*/
    hoehe = 0.75;
    if(strcmp(problem, "backstep")==0)
        for(i=0;i<=imax+1;i++)
            for(j=0;j<=jmax+1;j++){
                y = (j-0.5)*dely+delyw;
                if(y <= hoehe){
                    U[i][j] = 0.0;
                    KA[i][j] = 0.0;
                    EP[i][j] = 0.0;
                }
            }
    
    /* When this is to the mouth up and down U = 0.0 and              */
    /*                                   KA, EP equal KAI EPI set     */
    /*----------------------------------------------------------------*/
    xmue2  = 8.;
    ymueob = 6.;
    ymueun = 4.;
    if(strcmp(problem, "duese")==0)
        for(i=0;i<=imax+1;i++){
            x = (i-0.5)*delx+delxw;
            for(j=0;j<=jmax+1;j++){
                y = (j-0.5)*dely+delyw;
                if(x >= xmue2 && (y >= ymueob || y <= ymueun)){
                    U[i][j] = 0.0;
                    KA[i][j] = KAI;
                    EP[i][j] = EPI;
                }
            }
        }
}