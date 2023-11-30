#ifndef KRUSKAL_H
#define KRUSKAL_H


#include <bits/stdc++.h>
#include "Algorithm.h"

class Kruskal : Algorithm{

public:
    Kruskal();     // konstruktor

    ~Kruskal();    // destruktor

    void matrixAlg(vector<vector<int>>, int) override;

    void listAlg(vector<list<vector<int>>>, int) override;

    void result(int) override;

    void test(vector<int>,vector<int>, int) override;

private:

    struct cmp3{
        bool operator() (const vector<int>&a, const vector<int>&b){
            return a[2] > b[2];
        }
    };

    vector<int> setNumber;

    priority_queue<vector<int>, vector<vector<int>>, cmp3> sortedEdges;

    priority_queue<vector<int>, vector<vector<int>>, cmp3> resultsPQMatrix;
    priority_queue<vector<int>, vector<vector<int>>, cmp3> resultsPQList;

    void findSet(int);

    void unionSets(int, int);


};


#endif
