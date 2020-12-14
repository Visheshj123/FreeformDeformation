//
//  vertices.cpp
//  SimpleGlut
//
//  Created by Vishesh Javangula on 12/9/20.
//  Copyright © 2020 lab. All rights reserved.
//

#include "vertices.hpp"
#include <Eigen/Dense>
#include <GLUT/GLUT.h>

void applyTransform(Eigen::Matrix4f transform){
    for(int i=1; i< vertices.size(); i++){
        Eigen::Vector4f vert;
        vert << vertices[i][0], vertices[i][1], vertices[i][2], 1;
        Eigen::Vector4f result = transform * vert;
        std::vector<double> arr = {result(0), result(1),result(2)};
        tVertices.push_back(arr);
    }

}

void setLocalCoord(Eigen::Vector3f S,  Eigen::Vector3f T,  Eigen::Vector3f U,  Eigen::Vector3f p0){
    for(int i=0; i<tVertices.size(); i++){
        Eigen::Vector3f p;
        p << tVertices[i][0], tVertices[i][1], tVertices[i][2];
        
        GLfloat s = ((T.cross(U)).dot(p-p0))/((T.cross(U)).dot(S));
        GLfloat t = ((U.cross(S)).dot(p-p0))/((U.cross(S)).dot(T));
        GLfloat u = ((S.cross(T)).dot(p-p0))/((S.cross(T)).dot(U));
        Eigen::Vector3f l (s,t,u);
        localVerts.push_back(l);
    }
}

void setP0(Eigen::Matrix4f transform){
    Eigen::Vector4f initP0;
    initP0 << -1.67326, -1.59599, 0,1;
    initP0 = transform * initP0;
    p0 << initP0(0), initP0(1), initP0(2);
    
}
