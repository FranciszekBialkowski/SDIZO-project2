#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "../headers/Menu.h"
#include <random>

using namespace std;

Menu::Menu(Prim *prim, Kruskal *kruskal, Dijkstra *dijkstra, BellmanFord *bellmanFord)
{
    this->prim = *prim;
    this->kruskal = *kruskal;
    this->dijkstra = *dijkstra;
    this->bellmanFord = *bellmanFord;
}

Menu::~Menu()
= default;

void Menu::menuMain() {

    string fileName;

    do {
        cout << endl;
        cout << "==== MENU GLOWNE ====" << endl;
        cout << "1.Wczytaj graf z pliku" << endl;
        cout << "2.Utworz graf w pliku" << endl;
        cout << "3.Wyswietl graf" << endl;
        cout << "4.Algorytm Prima" << endl;
        cout << "5.Algorytm Kruskala" << endl;
        cout << "6.Algorytm Dijkstry" << endl;
        cout << "7.Algorytm Bellmana-Forda" << endl;
        cout << "t.Testy dla wszystkich algorytmow" << endl;
        cout << "0.Wyjscie" << endl;
        cout << "Podaj opcje:";
        cin >> option;
        cout << endl;

        switch (option) {
            case '1':
                cout << "Podaj nazwe pliku:";
                cin >> fileName;
                cout << endl;
                loadFromFile(fileName);
                display();
                option = ' ';
                break;

            case '2':
                cout << "Podaj nazwe pliku:";
                cin >> fileName;
                cout << endl;
                writeToFile(fileName);
                option = ' ';
                break;

            case '3':
                if (!adjMatrixND.empty()) display();
                else cout << "Graf jest pusty" << endl;
                option = ' ';
                break;

            case '4':
                if (!adjMatrixND.empty()) {
                    prim.matrixAlg(adjMatrixND, start);
                    prim.listAlg(adjListND, start);
                    prim.result(start);
                    option = ' ';
                } else cout << "Graf jest pusty" << endl;
                break;

            case '5':
                if (!adjMatrixND.empty()) {
                    kruskal.matrixAlg(adjMatrixND, start);
                    kruskal.listAlg(adjListND, start);
                    kruskal.result(start);
                    option = ' ';
                } else cout << "Graf jest pusty" << endl;
                break;

            case '6':
                if (!adjMatrixND.empty()) {
                    dijkstra.matrixAlg(adjMatrixD, start);
                    dijkstra.listAlg(adjListD, start);
                    dijkstra.result(start);
                    option = ' ';
                } else cout << "Graf jest pusty" << endl;
                break;

            case '7':
                if (!adjMatrixND.empty()) {
                    bellmanFord.matrixAlg(adjMatrixD, start);
                    bellmanFord.listAlg(adjListD, start);
                    bellmanFord.result(start);
                    option = ' ';
                } else cout << "Graf jest pusty" << endl;
                break;

            case 't':
                prim.test(values,densities,repeat);
                kruskal.test(values,densities,repeat);
                dijkstra.test(values,densities,repeat);
                bellmanFord.test(values,densities,repeat);
                option = ' ';
                break;
        }

    } while (option != '0');
}

void Menu::loadFromFile(const string& fileName) {

    clearGraph();
    ifstream file("..\\loadFiles\\" + fileName);
    int e, v, vStart, vEnd; // liczba krawędzi, liczba wiearzchołków, wierzchołek startowy, wierzchołek końcowy
    int eStart, eEnd, eWeight;  // początek krawędzi, koniec krawędzi, waga grawędzi
    if (file.is_open()) {
        file >> e;
        file >> v;
        file >> start;
        file >> vEnd;

        vector<int> vec;
        list<vector<int>> li;
        for (int i = 0; i < v; i++) {
            adjMatrixND.emplace_back(v, 0);
            adjMatrixD.emplace_back(v, 0);

            adjListND.emplace_back(li);
            adjListD.emplace_back(li);
        }

        if (file.fail())
            cout << "File error - READ SIZE" << endl;
        else
            for (int i = 0; i < e; i++) {
                file >> eStart;
                file >> eEnd;
                file >> eWeight;
                if (file.fail()) {
                    cout << "File error - READ DATA" << endl;
                    break;
                } else {
                    adjMatrixND[eStart][eEnd] = eWeight;
                    adjMatrixND[eEnd][eStart] = eWeight;

                    adjMatrixD[eStart][eEnd] = eWeight;

                    vec.clear();
                    vec.emplace_back(eStart);
                    vec.emplace_back(eWeight);
                    adjListND[eEnd].push_back(vec);

                    auto it = vec.begin();
                    *it = eEnd;
                    adjListND[eStart].push_back(vec);
                    adjListD[eStart].push_back(vec);
                }
            }
        file.close();
    } else
        cout << "File error - OPEN" << endl;


}

void Menu::display() {
    cout << "------- GRAF NIESKIEROWANY MACIERZOWO -------" << endl;
    cout << "  ||";
    for (int i = 0; i < adjMatrixND.size(); ++i) {
        cout << setw(2) << setfill(' ') << i << "|";
    }
    cout << endl;
    for (int i = 0; i < adjMatrixND.size() * 3 + 4; ++i) {
        cout << "=";
    }
    cout << endl;
    int counter = 0;
    auto it = adjMatrixND.begin();
    for (; it != adjMatrixND.end(); it++) {
        auto j = it->begin();
        cout << setw(2) << setfill(' ') << counter << "||";
        for (; j != it->end(); j++) {
            cout << setw(2) << setfill(' ') << *j << "|";
        }
        cout << endl;
        counter++;
    }

    cout << endl << "------- GRAF NIESKIEROWANY LISTOWO -------" << endl;
    counter = 0;
    int comma;
    auto i1 = adjListND.begin();
    for (; i1 != adjListND.end(); i1++) {
        cout << counter << ": [";
        if (!(*i1).empty()) {
            auto i2 = (*i1).begin();
            comma = 0;
            for (; i2 != (*i1).end(); ++i2) {
                if (!(*i2).empty()) {
                    if (comma != 0) cout << ",";
                    comma++;
                    auto i3 = (*i2).begin();
                    for (; i3 < (*i2).end(); i3 += 2) {
                        cout << "[" << *i3 << "," << *(i3 + 1) << "]";
                    }
                }

            }
            counter++;
        }
        cout << "]" << endl;
    }

    cout << endl << "------- GRAF SKIEROWANY MACIERZOWO -------" << endl;
    cout << "  ||";
    for (int i = 0; i < adjMatrixD.size(); ++i) {
        cout << setw(2) << setfill(' ') << i << "|";
    }
    cout << endl;
    for (int i = 0; i < adjMatrixD.size() * 3 + 4; ++i) {
        cout << "=";
    }
    cout << endl;
    counter = 0;
    it = adjMatrixD.begin();
    for (; it != adjMatrixD.end(); it++) {
        auto j = it->begin();
        cout << setw(2) << setfill(' ') << counter << "||";
        for (; j != it->end(); j++) {
            cout << setw(2) << setfill(' ') << *j << "|";
        }
        cout << endl;
        counter++;
    }

    cout << endl << "------- GRAF SKIEROWANY LISTOWO -------" << endl;
    counter = 0;
    i1 = adjListD.begin();
    for (; i1 != adjListD.end(); i1++) {
        cout << counter << ": [";
        if (!(*i1).empty()) {
            auto i2 = (*i1).begin();
            comma = 0;
            for (; i2 != (*i1).end(); ++i2) {
                if (!(*i2).empty()) {
                    if (comma != 0) cout << ",";
                    comma++;
                    auto i3 = (*i2).begin();
                    for (; i3 < (*i2).end(); i3 += 2) {
                        cout << "[" << *i3 << "," << *(i3 + 1) << "]";
                    }
                }
            }
        }
        counter++;
        cout << "]" << endl;
    }
}

void Menu::clearGraph() {
    adjMatrixND.clear();
    adjMatrixD.clear();
    adjListND.clear();
    adjListD.clear();
}

void Menu::writeToFile(const string& fileName) {
    clearGraph();
    ofstream file("..\\loadFiles\\" + fileName);
    int x;
    int e, v, g; // liczba krawędzi, liczba wierzchołków, zageszczenie krawedzi

    if (file.is_open()) {
        cout << "Wybierz do jakiego algorytmu potrzebujesz tego grafu:" << endl;
        cout << "1.Minimalne drzewo rozpinajace (graf nieskierowany)" << endl;
        cout << "2.Najkrotsza sciezka Dijkstra (graf skierowany)" << endl;
        cout << "Podaj opcje: ";

        cin >> x;
        cout << endl;
        while (x != 1 && x != 2) {
            cout << "Wybierz numer: ";
            cin >> x;
        }
        cout << endl;

        cout << "Podaj liczbe wierzcholkow grafu: ";
        cin >> v;
        cout << endl;

        cout << "Podaj gestosc grafu (0-100%): ";
        cin >> g;
        cout << endl;

        int minG = v-1;
        int maxG;

        if (x == 2){    // skierowany
            cout << "Podaj wierzcholek startowy: ";
            cin >> start;
            cout << endl;
            maxG = v*(v-1);
        } else {    // nieskierowany
            maxG = v*(v-1)/2;
        }
        e = round(double(maxG-minG))*((double)g/100.0) + minG;

        file << e << " " << v << " " << start << " " << 0 << endl;


        if (file.fail())
            cout << "File error - READ SIZE" << endl;
        else {
            random_device randDev;
            mt19937 generator(randDev());
            uniform_int_distribution<int> distr(1, 99);

            for (int i = 0; i < v; ++i) {
                pq.push({i, distr(generator)});
            }
            vector<vector<int>> edges;
            vector<int> vec;
            vec.emplace_back(pq.top()[0]);
            pq.pop();
            while (!pq.empty()) {
                vector<int> vec1 = pq.top();
                pq.pop();
                vec.emplace_back(vec1[0]);
                vector<int> tmp = {vec1[0],vec[0],vec1[1]};
                file << tmp[0] << " " << tmp[1] << " " << tmp[2] << endl;
                edges.emplace_back(tmp);
                shuffle(vec.begin(), vec.end(), generator);
            }

            vec.clear();
            for (int j = 0; j < v; ++j) {
                for (int k = 0; k < v; ++k) {
                    if (k != j){
                        bool exist = false;
                        for (const auto& edge:edges) {
                            if (x==1)  {    // nieskierowany
                                if ((edge[0] == j && edge[1] == k) || (edge[0]==k && edge[1]==j)) {
                                    exist = true;
                                    break;
                                }
                            } else {    // skierowany
                                if (edge[0]==k && edge[1]==j) {
                                    exist = true;
                                    break;
                                }
                            }
                        }
                        if (!exist){
                            vector<int> tmp = {k,j,distr(generator)};
                            edges.emplace_back(tmp);
                        }
                    }
                }
            }
            shuffle(edges.begin(),edges.end(), generator);
            vector<vector<int>> sortedEdges;
            for (int i = 0; i < e - minG; i++) {
                sortedEdges.push_back({edges[i][0],edges[i][1],edges[i][2]});
            }
            sort(sortedEdges.begin(),sortedEdges.end());
            for (int i = 0; i < e - minG; i++) {
                vector<int> edge = sortedEdges[i];
                file << edge[0] << " " << edge[1] << " " << edge[2] << endl;
            }
        }
        file.close();
    } else
        cout << "File error - OPEN" << endl;
}
