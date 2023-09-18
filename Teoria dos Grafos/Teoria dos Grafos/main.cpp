#include "TGrafoR.h"
#include <fstream>
#include <iostream>
using namespace std;


int main() {
    TGrafoR grafo2(3);
    grafo2.insereA(0, 1, 4.0);
    grafo2.insereA(0, 2, 1.0);
    grafo2.insereA(1, 2, 2.0);
    grafo2.insereA(2, 1, 3.0);
    
    cout << "Executando Dijkstra no Grafo 2 a partir do vértice 0:" << endl;
    grafo2.dijkstra(0);
    
    cout << "Executando Bellman-Ford no Grafo 2 a partir do vértice 0:" << endl;
    grafo2.bellmanFord(0);
    
    return 0;
}
