#include "../headers/GraphGenerator.h"


vector<vector<int>> GraphGenerator::generateGraphMatrix(int x, int v, int g) {

    vector<vector<int>> adjMatrixND;
    vector<vector<int>> adjMatrixD;

    struct cmp2{
        bool operator() (const vector<int>&a, const vector<int>&b){
            return a[1] > b[1];
        }
    };

    priority_queue<vector<int>, vector<vector<int>>, cmp2> pq;

    if (x == 1){
        for (int i = 0; i < v; i++) {
            adjMatrixND.emplace_back(v, 0);
        }
    } else {
        for (int i = 0; i < v; i++) {
            adjMatrixD.emplace_back(v, 0);
        }
    }

    int minG = v-1;
    int maxG;
    int e;

    if (x == 2){    // skierowany
        maxG = v*(v-1);
    } else {    // nieskierowany
        maxG = v*(v-1)/2;
    }
    e = round(double(maxG-minG))*((double)g/100.0) + minG;

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
        edges.emplace_back(tmp);
        if (x == 1){
            adjMatrixND[tmp[0]][tmp[1]] = tmp[2];
            adjMatrixND[tmp[1]][tmp[0]] = tmp[2];

        } else {
            adjMatrixD[tmp[0]][tmp[1]] = tmp[2];
        }
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
    for (int i = 0; i < e-minG; i++) {
        sortedEdges.push_back({edges[i][0],edges[i][1],edges[i][2]});
    }
    sort(sortedEdges.begin(),sortedEdges.end());

    if (x == 1){
        for (int i = 0; i < e-minG; i++) {
            vector<int> edge = sortedEdges[i];
            adjMatrixND[edge[0]][edge[1]] = edge[2];
            adjMatrixND[edge[1]][edge[0]] = edge[2];
        }
    } else {
        for (int i = 0; i < e-minG; i++) {
            vector<int> edge = sortedEdges[i];
            adjMatrixD[edge[0]][edge[1]] = edge[2];
        }
    }

    if (x == 1) return adjMatrixND;
    else return adjMatrixD;
}


vector<list<vector<int>>> GraphGenerator::generateGraphList(int x, int v, int g) {

    vector<list<vector<int>>> adjListND;
    vector<list<vector<int>>> adjListD;

    struct cmp2{
        bool operator() (const vector<int>&a, const vector<int>&b){
            return a[1] > b[1];
        }
    };

    priority_queue<vector<int>, vector<vector<int>>, cmp2> pq;

    list<vector<int>> li;

    if (x == 1){
        for (int i = 0; i < v; i++) {
            adjListND.emplace_back(li);
        }
    } else {
        for (int i = 0; i < v; i++) {
            adjListD.emplace_back(li);
        }
    }


    int minG = v-1;
    int maxG;
    int e;

    if (x == 2){    // skierowany
        maxG = v*(v-1);
    } else {    // nieskierowany
        maxG = v*(v-1)/2;
    }
    e = round(double(maxG-minG))*((double)g/100.0) + minG;

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
        edges.emplace_back(tmp);
        vector<int> tmp1;
        if (x == 1){
            tmp1 = {tmp[1],tmp[2]};
            adjListND[tmp[0]].emplace_back(tmp1);
            tmp1 = {tmp[0],tmp[2]};
            adjListND[tmp[1]].emplace_back(tmp1);

        } else {
            tmp1 = {tmp[1],tmp[2]};
            adjListD[tmp[0]].emplace_back(tmp1);
        }
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
    for (int i = 0; i < e-minG; i++) {
        sortedEdges.push_back({edges[i][0],edges[i][1],edges[i][2]});
    }
    sort(sortedEdges.begin(),sortedEdges.end());

    if (x == 1){
        for (int i = 0; i < e-minG; i++) {
            vector<int> edge = sortedEdges[i];
            vec = {edge[1],edge[2]};
            adjListND[edge[0]].emplace_back(vec);
            vec = {edge[0],edge[2]};
            adjListND[edge[1]].emplace_back(vec);
        }
    } else {
        for (int i = 0; i < e-minG; i++) {
            vector<int> edge = sortedEdges[i];
            vec = {edge[1],edge[2]};
            adjListD[edge[0]].emplace_back(vec);
        }
    }

    if (x == 1) return adjListND;
    else return adjListD;
}
