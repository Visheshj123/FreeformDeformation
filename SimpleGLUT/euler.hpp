//
//  euler.hpp
//  SimpleGlut
//
//  Created by Vishesh Javangula on 12/2/20.
//  Copyright © 2020 lab. All rights reserved.
//

#ifndef euler_hpp
#define euler_hpp

#include <stdio.h>
#include <iomanip>
#include <stdio.h>
#include <GLUT/GLUT.h>
#include <Eigen/Dense>
#include <vector>
#include <iostream>

void matrixToArray(Eigen::Matrix4f &m, GLfloat rotationMatrix[]);
Eigen::Matrix4f rotateEuler(GLfloat eAngles[3], GLfloat x, GLfloat y, GLfloat z);
Eigen::Matrix3f rotatelocal(GLfloat eAngles[3]);

#endif /* euler_hpp */
