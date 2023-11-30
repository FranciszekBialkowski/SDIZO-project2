#include "../headers/BellmanFord.h"
BellmanFord::BellmanFord() = default;

BellmanFord::~BellmanFord() = default;

void BellmanFord::matrixAlg(vector<vector<int>> table, int start) {
    // czyszczenie struktur
    d1.clear();
    p1.clear();

    size = table.size();

    vector<int> vec;
    for (int i = 0; i < table.size(); ++i) {
        d1.emplace_back(9999);
        p1.emplace_back(-1);
    }
    d1[start] = 0;

    for (int i = 0; i < table.size()-1; ++i) {
        int counter = 0;
        for (int u = 0; u < table.size(); ++u) {
            for (int v = 0; v < table.size(); ++v) {
                if (table[u][v] != 0){
                    if (d1[u] != 9999 && d1[v] > d1[u] + table[u][v]){
                        d1[v]=d1[u]+table[u][v];
                        p1[v] = u;
                        counter++;
                    }
                }
            }
        }
        if (counter == 0) break;
    }

    // sprawdzenie czy nie ma cyklu ujemnego
    for (int u = 0; u < table.size(); ++u) {
        for (int v = 0; v < table.size(); ++v) {
            if (table[u][v] != 0){
                if (d1[v] > d1[u] + table[u][v]){
                    error1 = true;
                    return;
                }
            }
        }
    }
}

void BellmanFord::listAlg(vector<list<vector<int>>> table, int start) {
    // czyszczenie struktur
    d2.clear();
    p2.clear();

    size = table.size();

    vector<int> vec;
    for (int i = 0; i < table.size(); ++i) {
        d2.emplace_back(9999);
        p2.emplace_back(-1);
    }
    d2[start] = 0;

    for (int i = 0; i < table.size()-1; ++i) {
        int counter = 0;
        for (int u=0;u < table.size();u++) {
            auto it = table[u].begin();
            for (; it != table[u].end() ; it++) {
                if (!(*it).empty()) {
                    int v = (*it)[0];
                    int weight = (*it)[1];

                    if (d2[u] != 9999 && d2[v] > d2[u] + weight){
                        d2[v]=d2[u]+weight;
                        p2[v] = u;
                        counter++;
                    }

                }
            }
        }
        if (counter == 0) break;
    }

    // sprawdzenie czy nie ma cyklu ujemnego
    for (list<vector<int>> vertexEdges:table) {
        auto it = vertexEdges.begin();
        for (; it != vertexEdges.end() ; it++) {
            if (!(*it).empty()) {
                int u = (*it)[0];
                int v = (*it)[1];
                int weight = (*it)[2];

                if (d2[v] > d2[u] + weight){
                    error2 = true;
                    return;
                }
            }
        }
    }
}

void BellmanFord::result(int start) {
    if (error1 && error2) {
        cout << "BLAD - CYKL UJEMNY" << endl;
        return;
    }
    cout << "----- Algorytm Bellmana-Forda na macierzy sasiedztwa -----" << endl;
    cout << "Start = " << start << endl;
    cout << "End  Dist  Path" << endl;
    for (int i = 0; i < size; i++) {
        vector<int> vec;
        cout << setw(6) << setfill(' ') << " " + to_string(i) + " |";

        if (d1[i] == 9999) cout << setw(6) << setfill(' ') << " inf |";
        else cout << setw(6) << setfill(' ') << " " + to_string(d1[i]) + " |";

        int j = i;
        while (p1[j] != -1) {
            vec.emplace_back(p1[j]);
            j = p1[j];
        }
        for (j = (int) vec.size() - 1; j >= 0; j--) {
            cout << setw(2) << setfill(' ') << vec[j] << " ";
        }
        cout << setw(2) << setfill(' ') << i << " ";
        cout << endl;
    }

    cout << endl << "----- Algorytm Bellmana-Forda na liscie sasiedztwa -----" << endl;
    cout << "Start = " << start << endl;
    cout << "End  Dist  Path" << endl;
    for (int i = 0; i < size; i++) {
        vector<int> vec;
        cout << setw(6) << setfill(' ') << " " + to_string(i) + " |";

        if (d2[i] == 9999) cout << setw(6) << setfill(' ') << " inf |";
        else cout << setw(6) << setfill(' ') << " " + to_string(d2[i]) + " |";

        int j = i;
        while (p2[j] != -1) {
            vec.emplace_back(p2[j]);
            j = p2[j];
        }
        for (j = (int) vec.size() - 1; j >= 0; j--) {
            cout << setw(2) << setfill(' ') << vec[j] << " ";
        }
        cout << setw(2) << setfill(' ') << i << " ";
        cout << endl;
    }
}

void BellmanFord::test(vector<int> values, vector<int> densities, int repeat) {
    long long int frequency, start, elapsed;
    double sum, time;
    ofstream resultFile;
    resultFile.open("..\\resultsFiles\\resultsBellmanFord");

    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);

    resultFile << "---- Algorytm Bellmana-Forda na macierzy sąsiedztwa ---" << endl;
    resultFile << "Ilość wierzchołków;Gęstość;Czas średni [us];";
    for (int i = 0; i < values.size(); ++i) {
        for (int k = 0; k < densities.size(); ++k) {
            sum = 0;
            resultFile << endl << values[i] << ";" << densities[k] << ";";
            for (int j = 0; j < repeat; ++j) {
                vector<vector<int>> table = GraphGenerator::generateGraphMatrix(2,values[i],densities[k]);

                random_device randDev;
                mt19937 generator(randDev());
                uniform_int_distribution<int> distr(0, values[i]);

                start = read_QPC();
                matrixAlg(table,distr(generator));
                elapsed = read_QPC() - start;

                time = (1000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(1) << time << ";";
                sum += time;
            }
            resultFile << fixed << setprecision(1) << sum/repeat << ";";
        }
    }
    resultFile << endl << endl;

    resultFile << "---- Algorytm Bellmana-Forda na liscie sąsiedztwa ---" << endl;
    resultFile << "Ilość wierzchołków;Gęstość;Czas średni [us];";
    for (int i = 0; i < values.size(); ++i) {
        for (int k = 0; k < densities.size(); ++k) {
            sum = 0;
            resultFile << endl << values[i] << ";" << densities[k] << ";";
            for (int j = 0; j < repeat; ++j) {
                vector<list<vector<int>>> table = GraphGenerator::generateGraphList(2,values[i],densities[k]);

                start = read_QPC();
                listAlg(table,0);
                elapsed = read_QPC() - start;

                time = (1000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(1) << time << ";";
                sum += time;
            }
            resultFile << fixed << setprecision(1) << sum/repeat << ";";
        }
    }
    resultFile << endl << endl;
}
