#include "TGrafo.h"
#include <fstream>
#include <iostream>
#include <limits>
#include "pilha.h"
using namespace std;

// Construtor do TGrafoND, respons�vel por
// Criar a matriz de adjac�ncia v x v do Grafo
TGrafoND::TGrafoND(int n) {
  this->n = n;
  // No in�cio dos tempos n�o h� arestas
  this->m = 0;
  // aloca da matriz do TGrafoND
  int **adjac = new int *[n];
  for (int i = 0; i < n; i++)
    adjac[i] = new int[n];
  adj = adjac;
  // Inicia a matriz com zeros
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      adj[i][j] = 0;
}

// Destructor, respons�vel por
// liberar a mem�ria alocada para a matriz
TGrafoND::~TGrafoND() {
  n = 0;
  m = 0;
  delete[] * adj;
  std::cout << "espaço liberado";
}

// Insere uma aresta no Grafo tal que
// v � adjacente a w
void TGrafoND::insereA(int v, int w) {
  // testa se nao temos a aresta
  if (adj[v][w] == 0 && adj[w][v] == 0) {
    adj[v][w] = 1;
    adj[w][v] = 1;
    m++; // atualiza qtd arestas
  }
}

// remove uma aresta v->w do Grafo
void TGrafoND::removeA(int v, int w) {
  // testa se temos a aresta
  if (adj[v][w] == 1 && adj[w][v] == 1) {
    adj[v][w] = 0;
    adj[w][v] = 0;
    m--; // atualiza qtd arestas
  }
}

// Apresenta o Grafo contendo
// n�mero de v�rtices, arestas
// e a matriz de adjac�ncia obtida
void TGrafoND::show() {
  std::cout << "n: " << n << std::endl;
  std::cout << "m: " << m << std::endl;
  for (int i = 0; i < n; i++) {
    std::cout << "\n";
    for (int w = 0; w < n; w++)
      if (adj[i][w] == 1)
        std::cout << "Adj[" << i << "," << w << "]= 1"
                  << " ";
      else
        std::cout << "Adj[" << i << "," << w << "]= 0"
                  << " ";
  }
  cout << "\nfim da impressao do grafo." << endl;
}

int TGrafoND::inDegree(int v) {
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (adj[i][v] == 1) {
      count++;
    }
  }
  return count;
}

int TGrafoND::outDegree(int v) {
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (adj[v][i] == 1) {
      count++;
    }
  }
  return count;
}

int TGrafoND::isFonte(int v) {
  if (inDegree(v) == 0 && outDegree(v) != 0) {
    return 1;
  }
  return 0;
}

int TGrafoND::isSorvedouro(int v) {
  if (inDegree(v) != 0 && outDegree(v) == 0) {
    return 1;
  }
  return 0;
}

int TGrafoND::isSimetrico() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (adj[i][j] != adj[j][i])
        return 0;
    }
  }
  return 1;
}

bool TGrafoND::verificarGrafoCompleto() {
   int V = n;
   int arestasContadas = 0;
   for (int i = 0; i < V; ++i) {
     for (int j = i + 1; j < V; ++j) {
       if (adj[i][j] == 1) {
         arestasContadas++;
       }
       else {
         return false;
       }
     }
   }
   return (arestasContadas == (V * (V - 1)) / 2);
}

int TGrafoND::Conexidade() {
    bool* visitei = new bool[n];  // Cria uma matriz dinâmica para armazenar os vértices visitados
    
    // Inicializa todos os elementos como false (não visitados)
    for (int i = 0; i < n; ++i) {
        visitei[i] = false;
    }
    Pilha pilha;  // Instancia uma pilha
    int vInicial = 0;  // Vértice inicial
    pilha.push(vInicial);
    visitei[vInicial] = true;
    
    while (!pilha.isEmpty()) {
        int vAtual = pilha.pop();
        // Verifica todos os vértices adjacentes ao vértice atual
        for (int i = 0; i < n; ++i) {
            if (adj[vAtual][i] == 1 && !visitei[i]) {
                pilha.push(i);
                visitei[i] = true;
            }
        }
    }

    // Verifica se todos os vértices foram visitados
    for (int i = 0; i < n; ++i) {
        if (!visitei[i]) {
            delete[] visitei;  // Libera a memória alocada
            return 0;  // O grafo não é conexo
        }
    }

    delete[] visitei;  // Libera a memória alocada
    return 1;  // O grafo é conexo
}

// void TGrafoND::arquivo() {}

// remove um vértice v do Grafo
void TGrafoND::removeVertice(int v) {
  if (v < 0 || v >= n) {
    std::cout << "Vértice fora do intervalo." << std::endl;
    return;
  }

  // Cria uma nova matriz de adjacência com tamanho n-1 x n-1
  int **novaAdj = new int *[n - 1];
  for (int i = 0; i < n - 1; i++) {
    novaAdj[i] = new int[n - 1];
  }

  // Copia os dados da matriz de adjacência antiga para a nova, excluindo o vértice
  int ii = 0, jj = 0;
  for (int i = 0; i < n; i++) {
    if (i == v) continue;
    jj = 0;
    for (int j = 0; j < n; j++) {
      if (j == v) continue;
      novaAdj[ii][jj] = adj[i][j];
      jj++;
    }
    ii++;
  }

  // Libera a memória da matriz de adjacência antiga
  for (int i = 0; i < n; i++) {
    delete[] adj[i];
  }
  delete[] adj;

  // Atribui a nova matriz de adjacência e atualiza o número de vértices e arestas
  adj = novaAdj;
  n = n - 1;
  // Ajusta o número de arestas, já que todas as arestas relacionadas ao vértice removido também foram removidas
  int novoM = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (adj[i][j] == 1) {
        novoM++;
      }
    }
  }
  m = novoM;
}
