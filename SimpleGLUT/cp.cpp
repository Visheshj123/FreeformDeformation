//
//  cp.cpp
//  SimpleGlut
//
//  Created by Vishesh Javangula on 12/9/20.
//  Copyright © 2020 lab. All rights reserved.
//

#include "cp.hpp"
#include <Eigen/Dense>
#include <GLUT/GLUT.h>
#include <vector>
#include <iostream>

//sets global coordinates for control points
void setControlPoints(Eigen::Vector3f S,  Eigen::Vector3f T,  Eigen::Vector3f U,  Eigen::Vector3f p0){
    Eigen::Vector3f coord;
    for(double i=0; i<4;i++){
        for(double j=0; j<4; j++){
            for(double k=0; k<4;k++){
                coord = p0 + (i/3.0)*S + (j/3.0)*T + (k/3.0)*U;
                Eigen::Vector4f coord4f;
                coord4f << coord(0), coord(1), coord(2),1;
                int index = (int)i*16+j*4+k;
                coord4f = translations[index] * coord4f;
                if(index == 0){
                    std::cout << translations[index] << std::endl;
                }
                coord << coord4f(0), coord4f(1), coord4f(2);
                cp.push_back(coord);
            }
        }
    }
}


//check if click is control point, translates the cp, and stores the translation matrix to apply after rotation
void isControlPoint(GLfloat x, GLfloat y){
    for(int i=0;i<cp.size();i++){
        //radius of 0.2
        GLfloat dist = sqrt(pow(cp[i](0) - x, 2.0) + pow(cp[i](1) - y, 2.0));
        //std::cout << "dist is: " << dist << std::endl;
        if(dist <= 0.2){
            //std::cout << "YOU HAVE CLICKED ON THE " << i << "th CONTROL POINT" << std::endl;
//            cp[i](0) = x;
//            cp[i](1) = y;
            Eigen::Vector4f cpVec (cp[i](0), cp[i](1), cp[i](2), 1);
            Eigen::Matrix4f translate;
            translate << 1,0,0,x-cp[i](0),
                        0,1,0,y-cp[i](1),
                        0,0,1,0,
                        0,0,0,1;
            cpVec = translate * cpVec;
            cp[i] << cpVec(0), cpVec(1), cpVec(2);
            
            //stores collective translations so when we rotate we can place in correct position
            translations[i](0,3) += translate(0,3);
            translations[i](1,3) += translate(1,3);
            translations[i](2,3) += translate(2,3);
            break;
        }
    }
}


void displayCP(){
    for(int i=0; i<cp.size();i++){
        if(i == 21 || i==22 || i==25 || i==26 || i==37 || i==41 || i==42) continue;
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(cp[i](0), cp[i](1), cp[i](2));
        glutWireCube(0.3);
        glPopMatrix();
    }
}
