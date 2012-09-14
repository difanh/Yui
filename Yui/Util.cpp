//
//  Util.cpp
//  Yui
//
//  Created by Diego Andrade on 9/10/12.
//  Copyright (c) 2012 Carnegie Mellon University. All rights reserved.
//

#include "Util.h"

Util::Util()
{
    
}

Util::~Util()
{

}

void Util::printMatrix (bubble** Mat, int IMAX)
{
    
    //char file2[] = "/Users/Serenity/Dropbox/CMU 2012/Pmat2XYZ";
    //char buffer[33]="a";
    
    
    // itoa(val,buffer,10);
    
    //strncat (file2,"txt");
    //strncat (file,".txt");
    
    //cout << file2;
    ofstream outfile ("/Users/Serenity/Dropbox/CMU 2012/Pmat2XYZ.txt"); //Check is there is a file functionlaity does not exist
    
    for(int m=0;m<IMAX;m++){
        for(int n=0;n<IMAX;n++){
            //outfile  << "\n[" << m << "]"<< "["<< n << "]:" <<endl;
            
            // outfile  << "X[" << m << "]"<< "["<< n << "]= "<< Mat[m][n].x <<"\t";
            // outfile  << "Y[" << m << "]"<< "["<< n << "]= "<< Mat[m][n].y <<"\t";
            // outfile  << "Z[" << m << "]"<< "["<< n << "]= "<< Mat[m][n].z <<"\t";
            
            
            outfile  << Mat[m][n].x <<"\t" << Mat[m][n].z <<"\t"<< endl;
            
            
        }
    }
    
    
    outfile.close();
    
    
}

void Util::printVect (bubble* Vect, int numBubble)
{
    char* file = "/Users/Serenity/Dropbox/CMU 2012/Vect.txt";
    
    ofstream outfile (file); //Check is there is a file functionlaity does not exist
    
    for(int m=0;m<numBubble;m++){
        
        outfile  << Vect[m].x << "\t" << Vect[m].y << "\t" << Vect[m].z << "\t" << Vect[m].u<< "\t" << Vect[m].v<<endl;
        
    }
    
    
    outfile.close();
    
    
}

void Util::printVectPoints (point_t* Vect, int numBubble, char* file)
{
    
    //char* file = "/Users/Serenity/Dropbox/CMU 2012/VectPoints.txt";
    
    ofstream outfile (file); //Check is there is a file functionlaity does not exist

    
    for(int m=0;m<numBubble;m++){
        
        outfile  << Vect[m].x << "\t" << Vect[m].y << "\t" << Vect[m].z <<endl;
        
    }
    
    
    outfile.close();
    
    
}