#include "TGrafoR.h"
#include <iostream>
#include <limits>
#include "pilha.h"

using namespace std;

// Construtor do TGrafoR, respons�vel por
// Criar a matriz de adjac�ncia v x v do Grafo
TGrafoR::TGrafoR(int n) {
    this->n = n;
    // No in�cio dos tempos n�o h� arestas
    this->m = 0;
    // aloca da matriz do TGrafoR
    float **adjac = new float *[n];
    for (int i = 0; i < n; i++)
        adjac[i] = new float[n];
    adj = adjac;
    // Inicia a matriz com zeros
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = std::numeric_limits<float>::infinity();
}

// Destructor, respons�vel por
// liberar a mem�ria alocada para a matriz
TGrafoR::~TGrafoR() {
    n = 0;
    m = 0;
    delete[] * adj;
    std::cout << "espaço liberado";
}

// Insere uma aresta no Grafo tal que
// v � adjacente a w
void TGrafoR::insereA(int v, int w, float ra) {
    // testa se nao temos a aresta
    if (adj[v][w] == std::numeric_limits<float>::infinity()) {
        adj[v][w] = ra;
        m++; // atualiza qtd arestas
    }
}

// remove uma aresta v->w do Grafo
void TGrafoR::removeA(int v, int w) {
    // testa se temos a aresta
    if (adj[v][w] != std::numeric_limits<float>::infinity()) {
        adj[v][w] = std::numeric_limits<float>::infinity();
        m--; // atualiza qtd arestas
    }
}

// Apresenta o Grafo contendo
// n�mero de v�rtices, arestas
// e a matriz de adjac�ncia obtida
void TGrafoR::show() {
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "\n";
        for (int w = 0; w < n; w++)
            if (adj[i][w] != std::numeric_limits<float>::infinity())
                std::cout << "Adj[" << i << "," << w << "]= " << adj[i][w] << " ";
            else
                std::cout << "Adj[" << i << "," << w << "]= ∞"
                << " ";
    }
    cout << "\nfim da impressao do grafo." << endl;
}

int TGrafoR::inDegree(int v) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (adj[i][v] != std::numeric_limits<float>::infinity()) {
            count++;
        }
    }
    return count;
}

int TGrafoR::outDegree(int v) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (adj[v][i] != std::numeric_limits<float>::infinity()) {
            count++;
        }
    }
    return count;
}

void TGrafoR::dijkstra(int v) {
  float *d = new float[n];
  int *rot = new int[n];
  Pilha pilha;

  for(int i = 0; i < n; i++) {
    d[i] = numeric_limits<float>::infinity();
    rot[i] = -1;
  }
  
  d[v] = 0;
  pilha.push(v);

  while (!pilha.isEmpty()) {
    int u = pilha.pop();

    for (int w = 0; w < n; w++) {
      if (adj[u][w] != numeric_limits<float>::infinity()) {
        float newDist = d[u] + adj[u][w];
        if (newDist < d[w]) {
          d[w] = newDist;
          rot[w] = u;
          pilha.push(w);
        }
      }
    }
  }

  // Exibir os vetores de distâncias e rotas
  cout << "Vetor de distâncias: ";
  for (int i = 0; i < n; i++) {
    cout << d[i] << " ";
  }
  cout << endl;

  cout << "Vetor de rotas: ";
  for (int i = 0; i < n; i++) {
    cout << rot[i] << " ";
  }
  cout << endl;

  delete[] d;
  delete[] rot;
}

void TGrafoR::bellmanFord(int v) {
  float *d = new float[n];
  int *rot = new int[n];

  for(int i = 0; i < n; i++) {
    d[i] = numeric_limits<float>::infinity();
    rot[i] = -1;
  }

  d[v] = 0;

  for (int i = 1; i < n; i++) {
    for (int u = 0; u < n; u++) {
      for (int w = 0; w < n; w++) {
        if (adj[u][w] != numeric_limits<float>::infinity()) {
          float newDist = d[u] + adj[u][w];
          if (newDist < d[w]) {
            d[w] = newDist;
            rot[w] = u;
          }
        }
      }
    }
  }

  // Exibir os vetores de distâncias e rotas
  cout << "Vetor de distâncias: ";
  for (int i = 0; i < n; i++) {
    cout << d[i] << " ";
  }
  cout << endl;

  cout << "Vetor de rotas: ";
  for (int i = 0; i < n; i++) {
    cout << rot[i] << " ";
  }
  cout << endl;

  delete[] d;
  delete[] rot;
}
