#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <windows.h>
#include <vector>
#include <list>
#include <queue>
#include <bits/stdc++.h>
#include "GraphGenerator.h"

using namespace std;

class Algorithm {
protected:

    /// Algorytm na grafie przechowywanym w postaci macierzy
    virtual void matrixAlg(vector<vector<int>>, int) = 0;

    /// Algorytm na grafie przechowywanym w postaci listy
    virtual void listAlg(vector<list<vector<int>>>, int) = 0;

    /// Wyświetlenie wyniku działania algorytmu
    virtual void result(int) = 0;

    /// Funkcja do przeprowadzenia testów
    virtual void test(vector<int>, vector<int>, int) = 0;

    /// Sprawdzenie aktualnego czasu
    virtual long long int read_QPC() {
        LARGE_INTEGER count;
        QueryPerformanceCounter(&count);
        return ((long long int) count.QuadPart);
    }
};


#endif
