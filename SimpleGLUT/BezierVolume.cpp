//
//  BezierVolume.cpp
//  SimpleGlut
//
//  Created bytishesh Javangula on 12/7/20.
//  Copyright © 2020 lab. All rights reserved.
//

#include "BezierVolume.hpp"


//takes in local coordinates ofterticies and control pointuorld coordinates and output newterticies
//modifies tVerticies[]
void deformObject(){
    float BU[4], BV[4], BW[4];
    for(int i=0;i<localVerts.size();i++){
        
        float s = localVerts[i](0);
        float t = localVerts[i](1);
        float u = localVerts[i](2);
        
        BU[0] = (1.0f -s) * (1.0f -s) * (1.0f -s);

        BU[1] = 3.0f *s * (1 -s) * (1.0f -s);

        BU[2] = 3.0f *s *s * (1.0f -s);

        BU[3] =s *s *s;

        BV[0] = (1.0f -t) * (1.0f -t) * (1.0f -t);

        BV[1] = 3.0f *t * (1 -t) * (1.0f -t);

        BV[2] = 3.0f *t *t * (1.0f -t);

        BV[3] =t *t *t;

        BW[0] = (1.0f -u) * (1.0f -u) * (1.0f -u);

        BW[1] = 3.0f *u * (1 -u) * (1.0f -u);

        BW[2] = 3.0f *u *u * (1.0f -u);

        BW[3] =u *u *u;
        
        Eigen::Vector3f Ret;
        Ret << 0,0,0;
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    Ret += cp[i*16 + j*4 + k] * (BU[i] * BV[j] * BW[k]);
                }
            }
        }
        tVertices[i] = {Ret(0), Ret(1), Ret(2)};
    }

    

    
}
