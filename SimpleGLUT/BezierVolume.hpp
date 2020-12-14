//
//  BezierVolume.hpp
//  SimpleGlut
//
//  Created by Vishesh Javangula on 12/7/20.
//  Copyright © 2020 lab. All rights reserved.
//

#ifndef BezierVolume_hpp
#define BezierVolume_hpp

#include <stdio.h>
#include <Eigen/Dense>
#include <vector>
extern std::vector<std::vector<double> > tVertices;
extern std::vector<Eigen::Vector3f> localVerts;
extern std::vector<Eigen::Vector3f> cp;
void deformObject();

#endif /* BezierVolume_hpp */
