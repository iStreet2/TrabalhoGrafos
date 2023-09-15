#include <iostream>
#include "TGrafo.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Construtor do grafo com a lista de
// adjacencia
TGrafoLista::TGrafoLista( int n ){
    // aloca a estrutura TGrafo
    this->n = n;
    this->m = 0;
    // aloca m vetor para guardar lista de adjacencias
    TNo **adjac = new TNo*[n];
    // Inicia o vetor com NULL
    for(int i = 0; i< n; i++)
        adjac[i]=nullptr;
    adj = adjac;
}

/*
Metodo que cria uma aresta v-w no grafo. O metodo supoe que
v e w sao distintos, positivos e menores que V.
Se o grafo ja tem a aresta v-w, o metodo nao faz nada.
O metodo tambem atualiza a quantidade de arestas no grafo.
*/
void TGrafoLista::insereA( int v, int w){
    TNo *novoNo;
    // anda na lista para chegar ao final
    TNo *no = adj[v];
    TNo *ant = nullptr;
    // anda na lista enquanto no != NULL E w  > no->w
    while( no && w >= no->w ){
        if( w == no->w)
            return;
        ant = no;
        no = no->prox;
    };
    // cria o novo No para guardar w
    novoNo = new TNo;
    novoNo->w = w;
    novoNo->prox = no;
    // atualiza a lista
    if( ant == nullptr){
        // insere no inicio
        adj[v] = novoNo;
    } else
        // insere no final
        ant->prox = novoNo;
    m++;
}
/*
Metodo que libera a memoria utilizada pela
lista de adjacencia.
*/
TGrafoLista::~TGrafoLista(){
    // libera cada um dos nos da lista encadeada
    for( int i = 0; i < n; i++){
        TNo *no = adj[i];
        TNo *ant = nullptr;
        while(no){
            ant = no;
            no = no->prox;
            delete ant;
        }
    }
    n = 0;
    m = 0;
    // libera o vetor onde cada posicao apontava para uma lista encadeada
    delete [] adj;
};
/*
Metodo que remove do grafo a aresta que tem ponta inicial v
e ponta final w. O metodo supoe que v e w sao distintos,
positivos e menores que V. Se nao existe a aresta v-w,
o metodo nao faz nada. O metodo tambem atualiza a
quantidade de arestas no grafo.
*/
void TGrafoLista::removeA(int v, int w){
    // Obtem o inicio da lista do vertice v
    TNo *no = adj[v];
    TNo *ant = nullptr;
    // Percorre a lista do vertice v
    // procurando w (se adjacente)
    while( no != nullptr && no->w != w ){
            ant = no;
            no = no->prox;
    }
    // Se w e adjacente, remove da lista de v
    if (no != nullptr){
        ant->prox = no->prox;
        delete no;
        no = nullptr;
        m--;
    }
}
/*
Para cada vertice v do grafo, este metodo imprime, em
uma linha, todos os vertices adjacentes ao vertice v
(vizinhos ao vertice v).
*/
void TGrafoLista::show(){
    cout << "n: " << n;
    cout << "\nm: " << m;
    for( int i=0; i < n; i++){
        cout << "\n" << i << ": ";
        // Percorre a lista na posicao i do vetor
        TNo *no = adj[i];
        while( no ){
            cout << no->w << " ";
            no = no->prox;
        }
    }
    cout << endl << "fim da impressao do grafo." << endl;
}

bool TGrafoLista::iguais(TGrafoLista &g2){
  if (this->n != g2.n || this->m != g2.m){
        return false;
    }
    for (int i = 0; i < n; ++i){
        TNo *no1 = this->adj[i];
        TNo *no2 = g2.adj[i];

        while (no1 != nullptr && no2 != nullptr){
            if (no1->w != no2->w){
                return false;
            }
            no1 = no1->prox;
            no2 = no2->prox;
        }

        if (no1 != nullptr || no2 != nullptr){
            return false;
        }
    }

    return true;
}

void TGrafoLista::LM() {
  TGrafo GM(this->n);
  for(int i = 0; i < this->n; ++i) {
    TNo* no = this->adj[i];
    while(no != nullptr) {
      GM.insereA(i, no->w);
      no = no->prox;
    }
  }
  GM.show();
}

void TGrafoLista::inverter(){
  for(int i = 0; i < this->n; ++i) {
    TNo* current = adj[i];
    TNo* prev = nullptr;
    TNo* next = nullptr;
    while(current != nullptr) {
      next = current->prox;
      current->prox = prev;
      prev = current;
      current = next;
    }
    adj[i] = prev;
  }
}

int TGrafoLista::isFonte(int v){
  int outDegree = 0;
  TNo* current = adj[v];
  while (current != nullptr) {
    ++outDegree;
    current = current->prox;
  }
  if (outDegree == 0) {
    return 0;
  }
  int inDegree = 0;
  for (int i = 0; i < n; ++i) {
    if (i == v) continue;
    TNo* current = adj[i];
    while (current != nullptr) {
      if (current->w == v) {
        ++inDegree;
        break;
      }
      current = current->prox;
    }
  }
  if (inDegree == 0 && outDegree > 0) {
    return 1;
  } else {
    return 0;
  }
}


int TGrafoLista::isSorvedouro(int v) {
  // Verificando grau de saída
  int outDegree = 0;
  TNo* current = adj[v];
  while (current != nullptr) {
    ++outDegree;
    current = current->prox;
  }
  if (outDegree > 0) {
    return 0;
  }

  // Verificando grau de entrada
  int inDegree = 0;
  for (int i = 0; i < n; ++i) {
    if (i == v) continue;  // Ignorar o próprio vértice v
    TNo* current = adj[i];
    while (current != nullptr) {
      if (current->w == v) {
        ++inDegree;
        break;  // Saindo do loop, pois um vértice não pode ter mais de uma aresta para o mesmo vértice em um grafo simples
      }
      current = current->prox;
    }
  }
  
  if (inDegree > 0) {
    return 1;
  }
  return 0;
}

int TGrafoLista::isSimetrico() {
    // Para cada vértice v
    for(int i = 0; i < n; ++i) {
        // Para cada aresta (i, w)
        TNo* no = adj[i];
        while(no != nullptr) {
            int w = no->w;
            // Verifica se a aresta (w, i) existe
            TNo* checkNo = adj[w];
            bool found = false;
            while(checkNo != nullptr) {
                if (checkNo->w == i) {
                    found = true;
                    break;
                }
                checkNo = checkNo->prox;
            }
            // Se não encontrou a aresta reversa (w, i)
            if (!found) {
                return 0;
            }
            no = no->prox;
        }
    }
    // Se chegou aqui, o grafo é simétrico
    return 1;
}

