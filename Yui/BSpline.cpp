//
//  BSpline.cpp
//  Nerv
//
//  Created by Diego Andrade on 7/17/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//
// These procedures and functions were based on THE BURBS BOOK, Springer 1997

#include <iostream>

#include <fstream>
#include "BSpline.h"



BSPline::BSPline()
{
    
}

BSPline::~BSPline()
{
    
     cout << "BSPline::BSPline() \n"; 
    
    
}

void BSPline::InitializeControlPoints()
{
    
    //myPoint3D a(0,0,0);
    //controlPoints[0].push_back(a);    //Need 20 points 4i 5j
    
    /*controlPoints[0][0].x = 3.0;  controlPoints[0][0].y = -1.0;  controlPoints[0][0].z = 2.0;
    controlPoints[0][1].x = 2.0;  controlPoints[0][1].y = -1.0;  controlPoints[0][1].z = 2.0;
    controlPoints[0][2].x = 1.0;  controlPoints[0][2].y = -1.0;  controlPoints[0][2].z = 4.0;
    controlPoints[0][3].x = 0.0;  controlPoints[0][3].y = -1.0;  controlPoints[0][3].z = 4.0;
   
    
    controlPoints[1][0].x = 3.0;  controlPoints[1][0].y = 0.0;  controlPoints[1][0].z = 2.0;
    controlPoints[1][1].x = 2.0;  controlPoints[1][1].y = 0.0;  controlPoints[1][1].z = 2.0;
    controlPoints[1][2].x = 1.0;  controlPoints[1][2].y = 0.0;  controlPoints[1][2].z = 4.0;
    controlPoints[1][3].x = 0.0;  controlPoints[1][3].y = 0.0;  controlPoints[1][3].z = 4.0;
    
    
    controlPoints[2][0].x = 3.0;  controlPoints[2][0].y = 1.0;  controlPoints[1][0].z = 0.0;
    controlPoints[2][1].x = 2.0;  controlPoints[2][1].y = 1.0;  controlPoints[1][1].z = 0.0;
    controlPoints[2][2].x = 1.0;  controlPoints[2][2].y = 1.0;  controlPoints[1][2].z = 2.0;
    controlPoints[2][3].x = 0.0;  controlPoints[2][3].y = 1.0;  controlPoints[1][3].z = 2.0;
      
    controlPoints[3][0].x = 3.0;  controlPoints[3][0].y = 2.0;  controlPoints[1][0].z = 0.0;
    controlPoints[3][1].x = 2.0;  controlPoints[3][1].y = 2.0;  controlPoints[1][1].z = 0.0;
    controlPoints[3][2].x = 1.0;  controlPoints[3][2].y = 2.0;  controlPoints[1][2].z = 2.0;
    controlPoints[3][3].x = 0.0;  controlPoints[3][3].y = 2.0;  controlPoints[1][3].z = 2.0;
    
    controlPoints[4][0].x = 3.0;  controlPoints[4][0].y = 3.0;  controlPoints[4][0].z = 0.0;
    controlPoints[4][1].x = 2.0;  controlPoints[4][1].y = 3.0;  controlPoints[4][1].z = 0.0;
    controlPoints[4][2].x = 1.0;  controlPoints[4][2].y = 3.0;  controlPoints[4][2].z = 2.0;
    controlPoints[4][3].x = 0.0;  controlPoints[4][3].y = 3.0;  controlPoints[4][3].z = 2.0;
      */ 
    
   controlPointsArray = new myPoint3D * [5];
    for(int i=0;i<5;i++)
    {
        controlPointsArray[i] = new myPoint3D [5];
        for(int j=0;j<5;j++)
        {
            controlPointsArray[i][j].x = 0.0;
            controlPointsArray[i][j].y = 0.0;
            controlPointsArray[i][j].z = 0.0;
        }
    }
    
    
    
     controlPointsArray[0][0].x = -1.0;  controlPointsArray[0][0].y = -1.0;  controlPointsArray[0][0].z = 4.0;
     controlPointsArray[0][1].x = -1.5;  controlPointsArray[0][1].y = -1.0;  controlPointsArray[0][1].z = 3.0;
     controlPointsArray[0][2].x = -1.5;  controlPointsArray[0][2].y = 1.0;  controlPointsArray[0][2].z = 2.0;
     controlPointsArray[0][3].x = -2.0;  controlPointsArray[0][3].y = 1.0;  controlPointsArray[0][3].z = 1.0;
     controlPointsArray[0][4].x = -1.5;  controlPointsArray[0][4].y = 2.0;  controlPointsArray[0][4].z = 0.0;
     controlPointsArray[0][5].x = -2.0;  controlPointsArray[0][5].y = 2.0;  controlPointsArray[0][5].z = -1.0;
     
     
     controlPointsArray[1][0].x = 0.0;  controlPointsArray[1][0].y = -1.0;  controlPointsArray[1][0].z = 4.0;
     controlPointsArray[1][1].x = 0.0;  controlPointsArray[1][1].y = -0.5;  controlPointsArray[1][1].z = 3.0;
     controlPointsArray[1][2].x = 0.0;  controlPointsArray[1][2].y = 1.0;  controlPointsArray[1][2].z = 2.0;
     controlPointsArray[1][3].x = 0.0;  controlPointsArray[1][3].y = 1.0;  controlPointsArray[1][3].z = 1.0;
     controlPointsArray[1][4].x = 0.0;  controlPointsArray[1][4].y = 2.0;  controlPointsArray[1][4].z = 0.0;
     controlPointsArray[1][5].x = 0.0;  controlPointsArray[1][5].y = 2.0;  controlPointsArray[1][5].z = -1.0;
     
     
     controlPointsArray[2][0].x = 1.0;  controlPointsArray[2][0].y = -1.0;  controlPointsArray[2][0].z = 4.0;
     controlPointsArray[2][1].x = 1.0;  controlPointsArray[2][1].y = 0.0;  controlPointsArray[2][1].z = 3.0;
     controlPointsArray[2][2].x = 1.0;  controlPointsArray[2][2].y = 0.0;  controlPointsArray[2][2].z = 2.0;
     controlPointsArray[2][3].x = 1.0;  controlPointsArray[2][3].y = 1.0;  controlPointsArray[2][3].z = 1.0;
     controlPointsArray[2][4].x = 1.0;  controlPointsArray[2][4].y = 1.0;  controlPointsArray[2][4].z = 0.0;
     controlPointsArray[2][5].x = 1.0;  controlPointsArray[2][5].y = 1.0;  controlPointsArray[2][5].z = -1.0;
 
     
     controlPointsArray[3][0].x = 2.0;  controlPointsArray[3][0].y = -1.0;  controlPointsArray[3][0].z = 4.0;
     controlPointsArray[3][1].x = 2.0;  controlPointsArray[3][1].y = 0.0;  controlPointsArray[3][1].z = 3.0;
     controlPointsArray[3][2].x = 2.0;  controlPointsArray[3][2].y = 0.0;  controlPointsArray[3][2].z = 2.0;
     controlPointsArray[3][3].x = 2.0;  controlPointsArray[3][3].y = 1.0;  controlPointsArray[3][3].z = 1.0;
     controlPointsArray[3][4].x = 2.0;  controlPointsArray[3][4].y = 1.0;  controlPointsArray[3][4].z = 0.0;
     controlPointsArray[3][5].x = 2.0;  controlPointsArray[3][5].y = 1.0;  controlPointsArray[3][5].z = -1.0;
 
     
     controlPointsArray[4][0].x = 3.0;  controlPointsArray[4][0].y = -1.0;  controlPointsArray[4][0].z = 4.0;
     controlPointsArray[4][1].x = 3.0;  controlPointsArray[4][1].y = -0.5;  controlPointsArray[4][1].z = 3.0;
     controlPointsArray[4][2].x = 3.0;  controlPointsArray[4][2].y = 0.0;  controlPointsArray[4][2].z = 2.0;
     controlPointsArray[4][3].x = 3.0;  controlPointsArray[4][3].y = 1.0;  controlPointsArray[4][3].z = 1.0;
     controlPointsArray[4][4].x = 3.0;  controlPointsArray[4][4].y = 1.0;  controlPointsArray[4][4].z = 0.0;
     controlPointsArray[4][5].x = 3.0;  controlPointsArray[4][5].y = 1.0;  controlPointsArray[4][5].z = 1.0;
    
    
   

    
    controlPointsWeightsArray = new float * [15];
    for(int i=0;i<15;i++)
    {
        controlPointsWeightsArray[i] = new float [15];
        for(int j=0;j<15;j++)
        {
            controlPointsWeightsArray[i][j] = 1.0;
        }
    }
  
    pts = new float [3];
    pts[0]=pts[1]=pts[2]=0.0;
    
}

int BSPline::findSpan (int n, int p, float u, float* U)
// INPUT: n number of control points, u independent variable, U knot vector
//
{
    if(u==U[n+1]) return (n);  //special case
    
    //Do binary search
    
    int low = p; 
    int high = n+1;
    
    int mid = (low+high)/(int)2;
    
    while(u < U[mid] || u>=U[mid+1])
    {
        if(u<U[mid]) high = mid;
           else low = mid;
        
        mid = (low+high)/2;
    }
    
    return (mid);
}


float*  BSPline::basisFuns(int i, float u, int p, float* U)
// INPUT: i knot span index, p degree of the curve, u independent variable, U knot vector
{
   // vector<float> N;
   // vector<float> left;
   // vector<float> right;
    
    float* N = new float [p+1];
    float* left = new float [p+1];
    float* right = new float [p+1];
    
    for(int l =0; l<=p;l++)
    {
        N[l]=1.0;
        left[l]=0.0;
        right[l]=0.0;
    }

    
    

    
    float saved=0.0;
    float temp = 0.0;
    float temp2=0.0;
    
    
    for (int j=1; j<=p;j++)
    {
        left[j]=u-U[i+1-j];
        right[j]=U[i+j]-u;
              
        saved = 0.0;
        
        
        for(int r=0; r<j; r++)
        {
            temp2 =  (float)(right[r+1]+left[j-r]);
           // cout << "temp2: " << temp2;
            
          if (temp2==0)
          { temp = 0.0;
          }else {
               temp = N[r]/(float)(right[r+1]+left[j-r]);
          }
           
       
            
            N[r]=saved+right[r+1]*temp;
            saved=left[j-r]*temp;
            
        }
        
        N[j] = saved;
       
    }
    
    for (int j=0; j<=p;j++)
    {                
     //   cout << "N[" << j << "]:" << N[j]  << endl;
    }
    

    delete [] left;
    delete [] right;
    return (N);
}

float* BSPline::basisFuns(int p, int n, float u, float *U)
{
    
    float d,e;
    
    float* N = new float [p+1];
    float* tempbf = new float [p+1];
    
    for(int l =0; l<=p;l++)
    {
        N[l]=0.0;
        tempbf[l]=0.0;
    }
    
    
    //maximum number of knot values
    int nplusc = n + p;
    
    /* calculate the first order basis functions n[i][1]	*/
    
	for (int i = 0; i<= nplusc; i++){
    	if (( u >= U[i]) && (u < U[i+1]))
			tempbf[i] = 1;
	    else
			tempbf[i] = 0;
	}

    /* calculate the higher order basis functions */
    
	for (int k = 1; k < p; k++){
    	for (int i = 0; i < nplusc-k; i++){
        	if (tempbf[i] != 0)    /* if the lower order basis function is zero skip the calculation */
           		d = ((u-U[i])*tempbf[i])/(U[i+k-1]-U[i]);
	        else
				d = 0;
            
    	    if (tempbf[i+1] != 0)     /* if the lower order basis function is zero skip the calculation */
        		e = ((U[i+k]-u)*tempbf[i+1])/(U[i+k]-U[i+1]);
	        else
    			e = 0;
            
    	    tempbf[i] = d + e;
		}
	}
    
	if (u == (float)U[nplusc]){		
 		tempbf[n] = 1;
	}

    
    /* put in n array	*/
    
	for (int i = 0; i < n; i++) {
    	N[i] = tempbf[i];
       // cout << "N[" << i << "]:" << N[i] <<endl;
	}
    
    

    return (N);
}


// input: i knot span index, p degree of the curve, u independent variable, U knot vector
// INPUT: 

myPoint3D BSPline::surfacePoint(int n, int p, float* U, 
                              int m, int q, float* V, 
                              myPoint3D** P, float u, float v)
{
    myPoint3D S(0,0,0);
    myPoint3D Sw(0,0,0);

   
    //myPoint3D  ** P = Pa;
    
    int uspan =0;
    int vspan =0;
    
    int uind =0; 
    int vind =0;
    
    float w = 1;
    
       
    
    uspan = findSpan(n, p, u, U);
    
        
    vspan = findSpan(m, q, v, V);
    
    float* Nu = new float [p+1];
    
    for(int l =0; l<=p;l++)
    {
        Nu[l]=0.0;
    }
    
   // Nu = basisFuns(p, n, u, U);
    Nu = basisFuns( uspan,  u, p, U);
    
    float* Nv = new float [q+1];
    
    for(int l =0; l<=p;l++)
    {
        Nv[l]=0.0;
    }

    Nv = basisFuns( vspan,  v, q, V);
    //Nv = basisFuns(q,m,u,V);
    
    uind = uspan - p;
    
    myPoint3D * temp = new myPoint3D[q+1];
    for(int l =0; l<=q;l++)
    {
        temp[l].x = 0.0;
        temp[l].y = 0.0;
        temp[l].z = 0.0;
    }
    
  
    
    for(int l =0; l<=q;l++)
    {
        
        temp[l].x=0.0;
        temp[l].y=0.0;        
        temp[l].z=0.0;
        //cout << "\n> temp["<<l<<"].x : " << temp[l].x << endl; 

        
        vind = vspan-q+l;
        
        for(int k=0; k<p;k++)
        {
            
          //  cout << "l : " <<l<< endl; 
            
            temp[l].x=temp[l].x+Nu[k]*P[uind+k][vind].x;
            temp[l].y=temp[l].y+Nu[k]*P[uind+k][vind].y;
            temp[l].z=temp[l].z+Nu[k]*P[uind+k][vind].z;
           // cout << "Nu["<<k <<"]:" << Nu[k];

        // cout << "\t >> temp["<<k<<"].x : " << temp[k].x << endl;   
        }
        
        
        Sw.x = Sw.x +Nv[l]*temp[l].x; // aqui problema
        Sw.y = Sw.y +Nv[l]*temp[l].y; // aqui problema
        Sw.z = Sw.z +Nv[l]*temp[l].z; // aqui problema
    
    }
    
    delete [] temp;
    delete [] Nu;
    delete [] Nv;
    
    S.x = Sw.x/w;
    S.y = Sw.y/w;
    S.z = Sw.z/w;

    return (S);
    
}

int BSPline::knotSearch(float *knot, float s, int low, int high)
{
    int middle;
    
    while (1)
    {
        middle = (low + high)/2;
        if (low == middle) break ;
        if ((s >= knot[middle]) && (s < knot[middle+1]))
            break;
        if (s > knot[middle])
            low = middle ;
        else
            high = middle ;
    }
    
    
    return (middle);
}

void BSPline::basis_value(int left, float u, int order, float *knot, float *basis)
{
    /* originally written by Dr. Yu */
    float  term,saved=0.0,delta_r[50],delta_l[50];
      
    /*  --------------- End of Declaretion ------------------ */
    basis[0] = 1.0 ;
    for (int j=1;j< order;j++)
    {
        delta_l[j] = u - knot[left+1-j] ;
        delta_r[j] = knot[left+j] - u ;
        saved = 0.0 ;
        for (int i=0;i<j;i++)
        {
            term=basis[i]/(delta_r[i+1]+delta_l[j-i]);
            basis[i]=saved + delta_r[i+1]*term ;
            saved = delta_l[j-i]*term ;
        }
        basis[j] = saved ;
       // cout << "\t basis["<<j<<"] : " << basis[j] << endl;   
    } /* the non-zero basis function is stored in basis[0~order-1] */ 
    
    
}

void BSPline::ptsNURBS(myPoint3D **P, float ** weight, float *knot_i, float *knot_j, 
                       int orderi, int orderj, int m, int n, 
                       float s, float t, float* pts)
{
    int lowi, highi, lowj, highj;
    int I, J;
    int which_i, which_j, ii, jj;
    float   basis_i[50],basis_j[50];
    float   tempx,tempy,tempz,denominator;
    
    /* ----------- End of Decleration -------------- */
    lowi = orderi - 1 ; highi = m + 1; 
    lowj = orderj - 1 ; highj = n + 1; 
    I = knotSearch(knot_i,s,lowi,highi);
    basis_value(I,s,orderi,knot_i,basis_i);
    
    J = knotSearch(knot_j,t,lowj,highj);
    basis_value(J,t,orderj,knot_j,basis_j) ;
    
    tempx=0.0;tempy=0.0;tempz=0.0;denominator=0.0;
    
    which_i = I - orderi + 1 ; which_j = J - orderj + 1 ; 
    
    for (ii=0;ii<orderi;ii++)
    {
        for (jj=0;jj<orderj;jj++)
        {
            denominator += weight[(ii+which_i)][ jj+which_j]* basis_i[ii]*basis_j[jj] ;
            
            tempx       += weight[(ii+which_i)][ jj+which_j] * P[(ii+which_i)][jj+which_j].x * basis_i[ii] * basis_j[jj] ;
            tempy       += weight[(ii+which_i)][ jj+which_j] * P[(ii+which_i)][jj+which_j].y * basis_i[ii] * basis_j[jj] ;
            tempz       += weight[(ii+which_i)][ jj+which_j] * P[(ii+which_i)][jj+which_j].z * basis_i[ii] * basis_j[jj] ;
           
           // tempx       += weight[(ii+which_i) * (n+1) + jj+which_j]* d[(ii+which_i) * (n+1) + jj+which_j].x * basis_i[ii]*basis_j[jj] ;
          //  tempy       += weight[(ii+which_i) * (n+1) + jj+which_j]* d[(ii+which_i) * (n+1) + jj+which_j].y * basis_i[ii]*basis_j[jj] ;
           // tempz       += weight[(ii+which_i) * (n+1) + jj+which_j]* d[(ii+which_i) * (n+1) + jj+which_j].z * basis_i[ii]*basis_j[jj] ;
        }
    }
    
    pts[0] = tempx/(float)denominator ;
    pts[1] = tempy/(float)denominator ;
    pts[2] = tempz/(float)denominator ;
    
}