#include "../headers/Dijkstra.h"

Dijkstra::Dijkstra() = default;

Dijkstra::~Dijkstra() = default;

void Dijkstra::matrixAlg(vector<vector<int>> table, int start) {

    // czyszczenie struktur
    adj.clear();
    d1.clear();
    p1.clear();
    done1.clear();

    vector<int> vec;
    for (int i = 0; i < table.size(); ++i) {
        d1.emplace_back(9999);
        p1.emplace_back(-1);

        adj.push_back(vec);
    }
    d1[start] = 0;
    for (int i = 0; i < table.size(); ++i) {
        pq.push({i, d1[i]});
        for (int j = 0; j < table.size(); ++j) {
            if (table[i][j] != 0) adj[i].emplace_back(j);
        }
    }

    while (!pq.empty()) {

        int u = pq.top()[0];
        pq.pop();
        done1.emplace_back(u);

        for (int v: adj[u]) {
            if (d1[v] > d1[u] + table[u][v]) {
                d1[v] = d1[u] + table[u][v];
                p1[v] = u;
            }
        }
        int pqSize = pq.size();
        for (int i = 0; i < pqSize; ++i) {
            pq.pop();
        }
        for (int i = 0; i < table.size(); ++i) {
            auto it = find(done1.begin(), done1.end(), i);
            if (it == done1.end()) {
                pq.push({i, d1[i]});
            }
        }
    }
}

void Dijkstra::listAlg(vector<list<vector<int>>> table, int start) {
    // czyszczenie struktur
    adj.clear();
    d2.clear();
    p2.clear();
    done2.clear();

    vector<int> vec;
    for (int i = 0; i < table.size(); ++i) {
        d2.emplace_back(9999);
        p2.emplace_back(-1);

        adj.push_back(vec);
    }
    d2[start] = 0;
    for (int i = 0; i < table.size(); ++i) {
        pq.push({i, d2[i]});
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
        done2.emplace_back(u);

        for (int v: adj[u]) {
            auto it = find_if(table[u].begin(), table[u].end(),
                               [v](const vector<int> &vec1) {
                                   return vec1.front() == v;
                               });
            if (d2[v] > d2[u] + (*it)[1]) {
                d2[v] = d2[u] + (*it)[1];
                p2[v] = u;
            }
        }
        int pqSize = pq.size();
        for (int i = 0; i < pqSize; ++i) {
            pq.pop();
        }
        for (int i = 0; i < table.size(); ++i) {
            auto it = find(done2.begin(), done2.end(), i);
            if (it == done2.end()) {
                pq.push({i, d2[i]});
            }
        }
    }
}


void Dijkstra::result(int start) {
    cout << "----- Algorytm Dijktry na macierzy sasiedztwa -----" << endl;
    cout << "Start = " << start << endl;
    cout << "End  Dist  Path" << endl;
    for (int i = 0; i < done1.size(); i++) {
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

    cout << endl << "----- Algorytm Dijktry na liscie sasiedztwa -----" << endl;
    cout << "Start = " << start << endl;
    cout << "End  Dist  Path" << endl;
    for (int i = 0; i < done2.size(); i++) {
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

void Dijkstra::test(vector<int> values, vector<int> densities, int repeat) {
    long long int frequency, start, elapsed;
    double sum, time;
    ofstream resultFile;
    resultFile.open("..\\resultsFiles\\resultsDijkstra");

    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);

    resultFile << "---- Algorytm Dijkstry na macierzy sąsiedztwa ---" << endl;
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

    resultFile << "---- Algorytm Dijkstry na liscie sąsiedztwa ---" << endl;
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
