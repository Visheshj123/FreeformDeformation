//
//  readShape.cpp
//  SimpleGlut
//
//  Created by Vishesh Javangula on 10/6/20.
//  Copyright © 2020 lab. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <iostream>
#include "readShape.hpp"
using namespace std;

void storeVerticies(std::string line,  std::vector<std::vector<double> >&vertices, int lineCount){
      std::vector<double> side;
      // cout << line << endl;
       std::smatch m;
       std::regex vertex ("[-]?[[:digit:]].[[:digit:]]+(e[-][[:digit:]]+)?");
       //regex dim ("")
       //regex r ("[[:digit:]]");
    int termCount = 1;

    
       while(regex_search(line,m,vertex)){ //returns true and ONLY writes first match to m then stops
           //cout << m[0] << " ";
           std::stringstream ss(m[0]);
           double x = 0.0;
           ss >> x;
           side.push_back(x);
           line = m.suffix(); //everything after the full match
           termCount++;
       }
      cout << endl;
       vertices.push_back(side);
}
void storePointers(std::string line, std::vector< std::vector<int> >& vertptrs){
    std::smatch m;
       std::vector<int> side;
       std::regex pointers ("[[:space:]][[:digit:]]+(?!\\.)");
       while(regex_search(line, m, pointers)){
           //cout << m.str(0) << " ";
           //cout << m[1];
           std::string s1 = m.str(0);
           //s1 = s1.substr(1,1);
           std::stringstream ss(s1);
           double x = 0.0;
           ss >> x;
           //cout << "Adding " << x << " as a ptr" << endl;
           side.push_back(x);
            line = m.suffix(); //everything after the full match
       }
       
       
           vertptrs.push_back(side);
    
}

void initializeShape(std::string type){
      std::ifstream myfile;
                   std::string line;
                   int lineCount = 0;
                //std::string filename = "/Users/vishesh.javangula@ibm.com/Downloads/D-files/knight.d";
               std::string filename = "/Users/vishesh.javangula@ibm.com/Code_Proj/FFD/knight-copy.d";
                       myfile.open(filename);
                   if(myfile.is_open()){
                       while(getline(myfile, line)){
                           
                           if(lineCount <= 2137){
                                storeVerticies(line, vertices, lineCount);
                           }else if(lineCount >= 2138){
                               storePointers(line,vertptrs);
                           }
                               
                           lineCount++;
                       }
                   }
                    myfile.close();
}
