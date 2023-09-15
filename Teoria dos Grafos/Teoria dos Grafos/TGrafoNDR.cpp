#include "TGrafo.h"
#include <fstream>
#include <iostream>
#include <limits>
using namespace std;

// Construtor do TGrafoNDR, respons�vel por
// Criar a matriz de adjac�ncia v x v do Grafo
TGrafoNDR::TGrafoNDR(int n) {
  this->n = n;
  // No in�cio dos tempos n�o h� arestas
  this->m = 0;
  // aloca da matriz do TGrafoNDR
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
TGrafoNDR::~TGrafoNDR() {
  n = 0;
  m = 0;
  delete[] * adj;
  std::cout << "espaço liberado";
}

// Insere uma aresta no Grafo tal que
// v � adjacente a w
void TGrafoNDR::insereA(int v, int w, float ra) {
  // testa se nao temos a aresta
  if (adj[v][w] == std::numeric_limits<float>::infinity() &&
      adj[w][v] == std::numeric_limits<float>::infinity()) {
    adj[v][w] = ra;
    adj[w][v] = ra;
    m++; // atualiza qtd arestas
  }
}

// remove uma aresta v->w do Grafo
void TGrafoNDR::removeA(int v, int w) {
  // testa se temos a aresta
  if (adj[v][w] != std::numeric_limits<float>::infinity() &&
      adj[w][v] != std::numeric_limits<float>::infinity()) {
    adj[v][w] = std::numeric_limits<float>::infinity();
    adj[w][v] = std::numeric_limits<float>::infinity();
    m--; // atualiza qtd arestas
  }
}

// Apresenta o Grafo contendo
// n�mero de v�rtices, arestas
// e a matriz de adjac�ncia obtida
void TGrafoNDR::show() {
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

int TGrafoNDR::inDegree(int v) {
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (adj[i][v] != std::numeric_limits<float>::infinity()) {
      count++;
    }
  }
  return count;
}

int TGrafoNDR::outDegree(int v) {
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (adj[i][v] != std::numeric_limits<float>::infinity()) {
      count++;
    }
  }
  return count;
}

int TGrafoNDR::isSimetrico() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (adj[i][j] != adj[j][i])
        return 0;
    }
  }
  return 1;
}

// void TGrafoNDR::arquivo() {}
