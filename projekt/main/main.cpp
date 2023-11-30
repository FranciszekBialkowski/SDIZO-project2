#include <iostream>
#include "../headers/Prim.h"
#include "../headers/Kruskal.h"
#include "../headers/Dijkstra.h"
#include "../headers/BellmanFord.h"
#include "../headers/Menu.h"

int main() {
    auto *prim = new Prim;
    auto *kruskal = new Kruskal;
    auto *dijkstra = new Dijkstra;
    auto *bellmanFord = new BellmanFord;

    Menu menu(prim,kruskal,dijkstra,bellmanFord);

    menu.menuMain();

    delete prim;
    delete kruskal;
    delete dijkstra;
    delete bellmanFord;

    return 0;
}
