#include "../headers/Prim.h"

Prim::Prim() = default;

Prim::~Prim() = default;

void Prim::matrixAlg(vector<vector<int>> table, int start) {
    vector<int> vec;
    for (int i = 0; i < table.size(); ++i) {
        key.emplace_back(9999);
        previous.emplace_back(-1);

        adj.push_back(vec);
    }
    key[start] = 0;
    for (int i = 0; i < table.size(); ++i) {
        pq.push({i, key[i]});
        for (int j = 1; j < table.size(); ++j) {
            if (table[j][i] != 0) adj[i].emplace_back(j);
        }
    }
    while (!pq.empty()) {
        int u = pq.top()[0];
        pq.pop();
        done.emplace_back(u);
        for (int v: adj[u]) {
            auto it = find(done.begin(), done.end(), v);
            if (it == done.end()) {
                if (key[v]>table[v][u]) {
                    key[v] = table[v][u];
                    previous[v] = u;
                }
            }
        }

        for (int i = 0; i < pq.size(); ++i) {
            pq.pop();
        }
        for (int i = 0; i < table.size(); ++i) {
            auto it = find(done.begin(), done.end(), i);
            if (it == done.end()) {
                pq.push({i, key[i]});
            }
        }
        if (!pq.empty()) resultsPQMatrix.push({previous[pq.top()[0]], pq.top()[0], pq.top()[1]});
    }

    key.clear();
    previous.clear();
    adj.clear();
    done.clear();
}

void Prim::listAlg(vector<list<vector<int>>> table, int start) {
    vector<int> vec;
    for (int i = 0; i < table.size(); ++i) {
        key.emplace_back(9999);
        previous.emplace_back(-1);

        adj.push_back(vec);
    }
    key[0] = 0;
    for (int i = 0; i < table.size(); ++i) {
        pq.push({i, key[i]});
        if (!table[i].empty()) {
            auto it = table[i].begin();

            for (; it != table[i].end(); it++) {
                if (!(*it).empty()) {
                    adj[i].emplace_back((*it)[0]);
                }
            }
        }
    }

    while (!pq.empty()) {
        int u = pq.top()[0];
        pq.pop();
        done.emplace_back(u);
        for (int v: adj[u]) {
            auto it = find(done.begin(), done.end(), v);
            if (it == done.end()) {
                auto it1 = find_if(table[v].begin(), table[v].end(),
                                   [u](const vector<int> &vec1) {
                                       return vec1.front() == u;
                                   });
                if (key[v] > (*it1)[1]) {
                    key[v] = (*it1)[1];
                    previous[v] = u;
                }
            }
        }

        for (int i = 0; i < pq.size(); ++i) {
            pq.pop();
        }
        for (int i = 0; i < table.size(); ++i) {
            auto it = find(done.begin(), done.end(), i);
            if (it == done.end()) {
                pq.push({i, key[i]});
            }
        }
        if (!pq.empty()) resultsPQList.push({previous[pq.top()[0]], pq.top()[0], pq.top()[1]});
    }

    key.clear();
    previous.clear();
    adj.clear();
    done.clear();
}

void Prim::result(int start) {
    cout << "----- Algorytm Prima na macierzy sasiedztwa -----" << endl;
    cout << "Edge     Weight" << endl;
    int counter = 0;
    int pqSize = (int)resultsPQMatrix.size();
    for (int i = 0; i < pqSize; i++) {
        vector<int> vec = resultsPQMatrix.top();
        resultsPQMatrix.pop();
        cout << "(" << setw(2) << setfill(' ') << vec[0] << ",";
        cout << setw(2) << setfill(' ') << vec[1] << ")  ";
        cout << setw(2) << setfill(' ') << vec[2] << endl;
        counter += vec[2];
    }
    cout << "MST = " << counter << endl << endl;

    pqSize = (int)resultsPQList.size();
    cout << "----- Algorytm Prima na liscie sasiedztwa -----" << endl;
    cout << "Edge        Weight" << endl;
    counter = 0;

    for (int i = 0; i < pqSize; i++) {
        vector<int> vec = resultsPQList.top();
        resultsPQList.pop();
        cout << "(" << setw(2) << setfill(' ') << vec[0] << ",";
        cout << setw(2) << setfill(' ') << vec[1] << ")  ";
        cout << setw(2) << setfill(' ') << vec[2] << endl;
        counter += vec[2];
    }
    cout << "MST = " << counter << endl << endl;
}

void Prim::test(vector<int> values, vector<int> densities, int repeat) {
    long long int frequency, start, elapsed;
    double sum, time;
    ofstream resultFile;
    resultFile.open("..\\resultsFiles\\resultsPrim");

    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);

    resultFile << "---- Algorytm Prima na macierzy sąsiedztwa ---" << endl;
    resultFile << "Ilość wierzchołków;Gęstość;Czas średni [us];";
    for (int i = 0; i < values.size(); ++i) {
        for (int k = 0; k < densities.size(); ++k) {
            sum = 0;
            resultFile << endl << values[i] << ";" << densities[k] << ";";
            for (int j = 0; j < repeat; ++j) {
                vector<vector<int>> table = GraphGenerator::generateGraphMatrix(1,values[i],densities[k]);

                start = read_QPC();
                matrixAlg(table,0);
                elapsed = read_QPC() - start;

                time = (1000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(1) << time << ";";
                sum += time;
            }
            resultFile << fixed << setprecision(1) << sum/repeat << ";";
        }
    }
    resultFile << endl << endl;

    resultFile << "---- Algorytm Prima na liscie sąsiedztwa ---" << endl;
    resultFile << "Ilość wierzchołków;Gęstość;Czas średni [us];";
    for (int i = 0; i < values.size(); ++i) {
        for (int k = 0; k < densities.size(); ++k) {
            sum = 0;
            resultFile << endl << values[i] << ";" << densities[k] << ";";
            for (int j = 0; j < repeat; ++j) {
                vector<list<vector<int>>> table = GraphGenerator::generateGraphList(1,values[i],densities[k]);

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