#ifndef BELLMANFORD_H
#define BELLMANFORD_H


#include "Algorithm.h"

class BellmanFord : Algorithm{
public:
    BellmanFord();     // konstruktor

    ~BellmanFord();    // destruktor

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

    int size;

    vector<int> d1;
    vector<int> p1;
    vector<int> d2;
    vector<int> p2;
    bool error1 = false;
    bool error2 = false;

};


#endif
