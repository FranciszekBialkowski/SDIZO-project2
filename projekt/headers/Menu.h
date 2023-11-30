#ifndef MENU_H

#define MENU_H

#include <iostream>
#include <vector>
#include <list>
#include "Prim.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
#include <bits/stdc++.h>
#include "Algorithm.h"

using namespace std;

class Menu {
    char option{};
    Prim prim;
    Kruskal kruskal;
    Dijkstra dijkstra;
    BellmanFord bellmanFord;

    const int repeat = 100;
    vector<int> values = {50, 100,150,200,250};
    vector<int> densities = {25,50,75,99};
    int start = 0;

    struct cmp2{
        bool operator() (const vector<int>&a, const vector<int>&b){
            return a[1] > b[1];
        }
    };

    priority_queue<vector<int>, vector<vector<int>>, cmp2> pq;

    vector<vector<int>> adjMatrixND;    // macierz sądziedztwa grafu nieskierowanego
    vector<vector<int>> adjMatrixD;    // macierz sądziedztwa grafu skierowanego

    vector<list<vector<int>>> adjListND;     // lista sąsiedzetwa grafu nieskierowanego
    vector<list<vector<int>>> adjListD;     // lista sąsiedzetwa grafu skierowanego

public:

    Menu(Prim *prim, Kruskal *kruskal, Dijkstra *dijkstra, BellmanFord *bellmanFord);   //konstruktor - wywoływany
                                                                                    //automatycznie przy tworzeniu obieku
    ~Menu();            //destrukor - wywływany automatycznie przy usuwaniu obiektu

    /// Menu główne
    void menuMain();

    /// Załadowanie z pliku
    void loadFromFile(const string& fileName);

    /// Utworzenie grafu w pliku
    void writeToFile(const string& fileName);

    /// Wyświetlenie grafu
    void display();

    /// Czyszczenie grafu
    void clearGraph();

};

#endif