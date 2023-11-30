#ifndef DIJKSTRA_H
#define DIJKSTRA_H


#include "Algorithm.h"

class Dijkstra : Algorithm {
public:

    Dijkstra();     // konstruktor

    ~Dijkstra();    // destruktor

    void matrixAlg(vector<vector<int>>, int) override;

    void listAlg(vector<list<vector<int>>>, int) override;

    void result(int) override;

    void test(vector<int>, vector<int>, int) override;

private:
    struct cmp2{
        bool operator() (const vector<int>&a, const vector<int>&b){
            return a[1] > b[1];
        }
    };
    vector<vector<int>> adj;
    vector<int> d1;
    vector<int> p1;
    vector<int> done1;
    vector<int> d2;
    vector<int> p2;
    vector<int> done2;
    priority_queue<vector<int>, vector<vector<int>>, cmp2> pq;

};


#endif
