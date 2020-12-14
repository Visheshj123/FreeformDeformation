//
//  vertices.hpp
//  SimpleGlut
//
//  Created by Vishesh Javangula on 12/9/20.
//  Copyright © 2020 lab. All rights reserved.
//

#ifndef vertices_hpp
#define vertices_hpp

#include <stdio.h>
#include <vector>
#include <Eigen/Dense>


extern std::vector<std::vector<double> > vertices;
extern std::vector<std::vector<double> > tVertices;
extern std::vector<Eigen::Vector3f> localVerts;
extern Eigen::Vector3f p0;

void applyTransform(Eigen::Matrix4f transform);
void setLocalCoord(Eigen::Vector3f S,  Eigen::Vector3f T,  Eigen::Vector3f U,  Eigen::Vector3f p0);
void setP0(Eigen::Matrix4f transform);
#endif /* vertices_hpp */
