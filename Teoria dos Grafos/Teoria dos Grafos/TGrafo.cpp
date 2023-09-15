#include "TGrafo.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include <set>
using namespace std;

// Construtor do TGrafo, responsavel por
// Criar a matriz de adjacencia v x v do Grafo
TGrafo::TGrafo(int n) {
  this->n = n;
  // No inicio dos tempos nao ha arestas
  this->m = 0;
  // aloca da matriz do TGrafo
  int **adjac = new int *[n];
  for (int i = 0; i < n; i++)
    adjac[i] = new int[n];
  adj = adjac;
  // Inicia a matriz com zeros
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      adj[i][j] = 0;
}

// Destructor, responsavel por
// liberar a memoria alocada para a matriz
TGrafo::~TGrafo() {
  n = 0;
  m = 0;
  delete[] * adj;
  std::cout << "espaço liberado";
}

// Insere uma aresta no Grafo tal que
// v e adjacente a w
void TGrafo::insereA(int v, int w) {
  // testa se nao temos a aresta
  if (adj[v][w] == 0) {
    adj[v][w] = 1;
    m++; // atualiza qtd arestas
  }
}

// remove uma aresta v->w do Grafo
void TGrafo::removeA(int v, int w) {
  // testa se temos a aresta
  if (adj[v][w] == 1) {
    adj[v][w] = 0;
    m--; // atualiza qtd arestas
  }
}

void TGrafo::removeV(int v) {
  int a = 0, b = 0;
  // aloco uma matriz nova
  int **adjac = new int *[n - 1];
  for (int i = 0; i < n - 1; i++)
    adjac[i] = new int[n - 1];
  // copio só as arestas que ainda serao utilizadas para a matriz nova
  for (int i = 0; i < n; i++) {
    b = 0;
    for (int j = 0; j < n; j++) {
      if (i != v && j != v) {
        adjac[a][b] = adj[i][j];
        b++;
      }
    }
    if (i != v) {
      a++;
    }
  }
  // substituo minha matriz
  adj = adjac;
  // diminuo a quantidade de vertices
  n--;
}

// Apresenta o Grafo contendo
// numero de vertices, arestas
// e a matriz de adjacencia obtida
void TGrafo::show() {
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

int TGrafo::inDegree(int v) {
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (adj[i][v] == 1) {
      count++;
    }
  }
  return count;
}

int TGrafo::outDegree(int v) {
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (adj[v][i] == 1) {
      count++;
    }
  }
  return count;
}

int TGrafo::isFonte(int v) {
  if (inDegree(v) == 0 && outDegree(v) != 0) {
    return 1;
  }
  return 0;
}

int TGrafo::isSorvedouro(int v) {
  if (inDegree(v) != 0 && outDegree(v) == 0) {
    return 1;
  }
  return 0;
}

int TGrafo::isSimetrico() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (adj[i][j] != adj[j][i])
        return 0;
    }
  }
  return 1;
}

bool TGrafo::isCompleto() {
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i!=j) //Se eu nao estiver olhando as diagnonais
            if(adj[i][j] == 0) return false; //E se eu achar algum zero nas outras posições eu retorno false.
        }
    }
    return true; //Se não eu retorno true;
}

int **TGrafo::Complementar(){
    //alocacao da matriz complementar
    TGrafo comple(n);
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(adj[i][j] == 0)
                comple.insereA(i,j);
        }
    }
    comple.show(); //mostro a matriz de adjacencia do grafo complementar
    
    return comple.adj; //retorno a matriz de adjacência do complemento do grafo
}

bool TGrafo::f_conexo() {
    for (int v = 0; v < n; ++v) {
        std::vector<bool> visitado(n, false);
        std::queue<int> q;
        q.push(v);
        visitado[v] = true;
        int cnt = 1;

        while (!q.empty()) {
            int atual = q.front(); q.pop();
            for (int i = 0; i < n; ++i) {
                if (adj[atual][i] && !visitado[i]) {
                    q.push(i);
                    visitado[i] = true;
                    ++cnt;
                }
            }
        }
        if (cnt != n) return false;
    }
    return true;
}

bool TGrafo::sf_conexo() {
    for (int v = 0; v < n; ++v) {
        for (int w = 0; w < n; ++w) {
            if (v == w) continue;

            std::vector<bool> visitado(n, false);
            std::queue<int> q;
            q.push(v);
            visitado[v] = true;
            while (!q.empty()) {
                int atual = q.front(); q.pop();
                for (int i = 0; i < n; ++i) {
                    if (adj[atual][i] && !visitado[i]) {
                        q.push(i);
                        visitado[i] = true;
                    }
                }
            }
            if (!visitado[w]) {
                
                visitado = std::vector<bool>(n, false);
                q.push(w);
                visitado[w] = true;
                while (!q.empty()) {
                    int atual = q.front(); q.pop();
                    for (int i = 0; i < n; ++i) {
                        if (adj[atual][i] && !visitado[i]) {
                            q.push(i);
                            visitado[i] = true;
                        }
                    }
                }
                
                if (!visitado[v]) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool TGrafo::desconexo() {
    std::vector<bool> visitado(n, false);
    std::queue<int> q;
    q.push(0);
    visitado[0] = true;
    int cnt = 1;

    while (!q.empty()) {
        int atual = q.front(); q.pop();
        for (int i = 0; i < n; ++i) {
            if (adj[atual][i] && !visitado[i]) {
                q.push(i);
                visitado[i] = true;
                ++cnt;
            }
        }
    }
    return cnt != n;
}

int TGrafo::categoria() {
if (m == 0) return 0;
    if (f_conexo()) return 3;
    if (sf_conexo()) return 2;
    if (!desconexo()) return 1;
    return 0;
}

void TGrafo::FCONEX() {
    std::vector<std::set<int>> components; // Guardará as componentes fortemente conexas
    std::vector<bool> visited(n, false);   // Indica se o vértice já foi visitado

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            std::set<int> Rplus = {i};
            std::set<int> Rminus = {i};
            std::set<int> W;

            // Fecho Transitivo Direto de s0
            while (true) {
                W.clear();
                for (auto x : Rplus) {
                    for (int j = 0; j < n; ++j) {
                        if (adj[x][j] && !Rplus.count(j)) {
                            W.insert(j);
                        }
                    }
                }
                if (W.empty()) break;
                Rplus.insert(W.begin(), W.end());
            }

            // Fecho Transitivo Inverso de s0
            while (true) {
                W.clear();
                for (auto x : Rminus) {
                    for (int j = 0; j < n; ++j) {
                        if (adj[j][x] && !Rminus.count(j)) {
                            W.insert(j);
                        }
                    }
                }
                if (W.empty()) break;
                Rminus.insert(W.begin(), W.end());
            }

            // Encontra FCC de s0
            std::set<int> FCC;
            for (auto x : Rplus) {
                if (Rminus.count(x)) {
                    FCC.insert(x);
                    visited[x] = true;
                }
            }
            components.push_back(FCC);
        }
    }

    // Exibir as componentes fortemente conexas
    std::cout << "Componentes Fortemente Conexas: \n";
    for (int i = 0; i < components.size(); ++i) {
        std::cout << "W" << (i + 1) << " = {";
        for (auto it = components[i].begin(); it != components[i].end(); ++it) {
            std::cout << *it;
            if (std::next(it) != components[i].end()) {
                std::cout << ", ";
            }
        }
        std::cout << "}\n";
    }
}
