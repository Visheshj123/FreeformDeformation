//
//  readShape.hpp
//  SimpleGlut
//
//  Created by Vishesh Javangula on 10/6/20.
//  Copyright © 2020 lab. All rights reserved.
//

#ifndef readShape_hpp
#define readShape_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <regex>
#include <sstream>


extern std::vector<std::vector<int> > vertptrs;
extern  std::vector<std::vector<double> > vertices;
void storeVerticies(std::string line, std::vector<std::vector<double> >&vertices, int lineCount);
void storePointers(std::string line,  std::vector< std::vector<int> >& vertptrs);
void initializeShape(std::string type);


#endif /* readShape_hpp */
