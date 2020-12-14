//
//  euler.cpp
//  SimpleGlut
//
//  Created by Vishesh Javangula on 12/2/20.
//  Copyright © 2020 lab. All rights reserved.
//

#include "euler.hpp"
#include <stdio.h>
#include <GLUT/GLUT.h>
#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include <math.h>
#include <iomanip>


//multiplies all rotation matrices together then loads it
void matrixToArray(Eigen::Matrix4f &m, GLfloat rotationMatrix[]) {
    int count = 0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            rotationMatrix[count++] = m.coeffRef(j, i);
        }
    }
}


Eigen::Matrix4f rotateEuler(GLfloat eAngles[3], GLfloat x, GLfloat y, GLfloat z){
    
    Eigen::Matrix4f result;
    Eigen::Matrix4f m;
   
    int i=0;
    
    GLfloat rad = 0;
    GLfloat cosine = 0;
    GLfloat sine = 0;
    
    while(i<3){
         rad = (eAngles[i] * M_PI)/180;
        cosine = cos(rad);
         sine = sin(rad);
        if(i == 0){
            m << cosine, -1*sine, 0, 0,
                sine, cosine, 0,0,
                0,0,1,0,
                0,0,0,1;
                result = m;
        }
        if(i == 1){
            m << cosine, 0,sine, 0,
                    0,1,0,0,
                    -1*sine, 0,cosine, 0,
                    0,0,0,1;
            result *= m;
        }
        if(i == 2){
            m << 1,0,0,0,
                0,cosine,-1*sine, 0,
                0,sine,cosine,0,
                0,0,0,1;
            result *= m;
        }
        i++;
        
    }
   
    //add on translation
   result.coeffRef(0,3) = x;
    result.coeffRef(1,3) = y;
   result.coeffRef(2,3) = z;
   
    return result;
//    GLfloat rotationMatrix[16];
    //matrixToArray(result, rotationMatrix);
    

    //glLoadMatrixf(rotationMatrix);
     
}

Eigen::Matrix3f rotatelocal(GLfloat eAngles[3]){
    
    Eigen::Matrix3f result;
    Eigen::Matrix3f m;
   
    int i=0;
    
    GLfloat rad = 0;
    GLfloat cosine = 0;
    GLfloat sine = 0;
    
    while(i<3){
         rad = (eAngles[i] * M_PI)/180;
        cosine = cos(rad);
         sine = sin(rad);
        if(i == 0){
            m << cosine, -1*sine, 0,
                sine, cosine, 0,
                0,0,1;
                result = m;
        }
        if(i == 1){
            m << cosine, 0,sine,
                    0,1,0,
            -1*sine, 0,cosine;
            result *= m;
        }
        if(i == 2){
            m << 1,0,0,
                0,cosine,-1*sine,
            0,sine,cosine;
       
            result *= m;
        }
        i++;
        
    }

   
   
    return result;
//    GLfloat rotationMatrix[16];
    //matrixToArray(result, rotationMatrix);
    

    //glLoadMatrixf(rotationMatrix);
     
}
