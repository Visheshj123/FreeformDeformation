//
//  cp.hpp
//  SimpleGlut
//
//  Created by Vishesh Javangula on 12/9/20.
//  Copyright © 2020 lab. All rights reserved.
//

#ifndef cp_hpp
#define cp_hpp

#include <stdio.h>
#include <Eigen/Dense>
#include <GLUT/GLUT.h>
#include <vector>

extern Eigen::Matrix4f translations[64]; //store all transltions done to each cp
extern std::vector<Eigen::Vector3f> cp;

void setControlPoints(Eigen::Vector3f S,  Eigen::Vector3f T,  Eigen::Vector3f U,  Eigen::Vector3f p0);
void isControlPoint(GLfloat x, GLfloat y);
void displayCP();

#endif /* cp_hpp */
