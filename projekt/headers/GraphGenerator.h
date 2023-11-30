
#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class GraphGenerator {

public:
    static vector<vector<int>> generateGraphMatrix(int,int,int);
    static vector<list<vector<int>>> generateGraphList(int,int,int);
};


#endif
