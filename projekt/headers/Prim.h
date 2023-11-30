#ifndef PRIM_H
#define PRIM_H

#include <bits/stdc++.h>
#include "Algorithm.h"

class Prim : Algorithm {

public:
    Prim();     // konstruktor

    ~Prim();    // destruktor

    void matrixAlg(vector<vector<int>>, int) override;

    void listAlg(vector<list<vector<int>>>, int) override;

    void result(int) override;

    void test(vector<int>,vector<int>,int) override;

private:
    struct cmp2{
        bool operator() (const vector<int>&a, const vector<int>&b){
            return a[1] > b[1];
        }
    };
    struct cmp3{
        bool operator() (const vector<int>&a, const vector<int>&b){
            return a[2] > b[2];
        }
    };
    vector<vector<int>> adj;
    vector<int> key;
    vector<int> previous;
    priority_queue<vector<int>, vector<vector<int>>, cmp2> pq;
    vector<int> done;
    priority_queue<vector<int>, vector<vector<int>>, cmp3> resultsPQMatrix;
    priority_queue<vector<int>, vector<vector<int>>, cmp3> resultsPQList;

};
#endif
