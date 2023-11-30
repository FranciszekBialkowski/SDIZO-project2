#include "../headers/Kruskal.h"

Kruskal::Kruskal() = default;

Kruskal::~Kruskal() = default;

void Kruskal::matrixAlg(vector<vector<int>> table, int) {
    for (int i = 0; i < table.size(); ++i) {
        setNumber.emplace_back(i);
    }

    for (int i = 0; i < table.size(); ++i) {
        for (int j = i+1; j < table.size(); ++j) {
            if (table[i][j] != 0){
                sortedEdges.push({i,j,table[i][j]});
            }
        }
    }

    while (!sortedEdges.empty()){
        vector<int> edge = sortedEdges.top();
        sortedEdges.pop();

        if (setNumber[edge[0]] != setNumber[edge[1]]){
            resultsPQMatrix.push(edge);

            // Union
            int set1 = setNumber[edge[1]];
            for (int &set:setNumber) {
                if (set == set1) set = setNumber[edge[0]];
            }
        }
    }

    setNumber.clear();
}

void Kruskal::listAlg(vector<list<vector<int>>> table, int start) {
    for (int i = 0; i < table.size(); ++i) {
        setNumber.emplace_back(i);
    }

    for (int i = 0; i < table.size(); ++i) {
        if (!table[i].empty()) {
            auto it = table[i].begin();

            for (; it != table[i].end(); it++) {
                if (!(*it).empty()) {
                    sortedEdges.push({i,(*it)[0],(*it)[1]});
                }
            }
        }
    }

    while (!sortedEdges.empty()){
        vector<int> edge = sortedEdges.top();
        sortedEdges.pop();

        if (setNumber[edge[0]] != setNumber[edge[1]]){
            resultsPQList.push(edge);

            // Union
            int set1 = setNumber[edge[1]];
            for (int &set:setNumber) {
                if (set == set1) set = setNumber[edge[0]];
            }
        }
    }

    setNumber.clear();
}

void Kruskal::result(int start) {
    cout << "----- Algorytm Kruskala na macierzy sasiedztwa -----" << endl;
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

    cout << "----- Algorytm Kruskala na liscie sasiedztwa -----" << endl;
    cout << "Edge        Weight" << endl;
    counter = 0;

    pqSize = (int)resultsPQList.size();
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

void Kruskal::test(vector<int> values, vector<int> densities, int repeat) {
    long long int frequency, start, elapsed;
    double sum, time;
    ofstream resultFile;
    resultFile.open("..\\resultsFiles\\resultsKruskal");

    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);

    resultFile << "---- Algorytm Kruskala na macierzy sąsiedztwa ---" << endl;
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

    resultFile << "---- Algorytm Kruskala na liscie sąsiedztwa ---" << endl;
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


