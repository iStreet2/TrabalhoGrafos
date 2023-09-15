#include "TGrafo.h"
#include <fstream>
#include <iostream>
using namespace std;

void arquivo(std::string nome) {
    ifstream arq(nome);
    int V, A;
    arq >> V >> A;
    TGrafo g(V);
    for (int i = 0; i < A; i++) {
        int origem, destino;
        arq >> origem >> destino;
        g.insereA(origem, destino);
    }
    g.show();
}

TGrafoLista lerGrafoDeArquivo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        exit(1);
    }
    
    int V, A;
    arquivo >> V >> A;
    
    // Inicializar o grafo com V vértices
    TGrafoLista grafo(V);
    
    int v, w;
    for (int i = 0; i < A; ++i) {
        arquivo >> v >> w;
        grafo.insereA(v, w);
    }
    
    arquivo.close();
    return grafo;
}

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
