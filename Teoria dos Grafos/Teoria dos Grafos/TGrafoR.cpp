#include "TGrafoR.h"
#include "pilha.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include <set>

using namespace std;

TGrafoR::TGrafoR(int n) {
    this->n = n;
    this->m = 0;
    std::string **adjac = new std::string *[n];
    for (int i = 0; i < n; i++)
        adjac[i] = new std::string[n];
    adj = adjac;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = "false";
}

TGrafoR::~TGrafoR() {
    n = 0;
    m = 0;
    delete[] * adj;
    std::cout << "espaco liberado";
}

int TGrafoR::getN() {
    return n;
}

int TGrafoR::getM() {
    return m;
}

void TGrafoR::insereA(int v, int w, std::string ra) {
    // testa se nao temos a aresta
    if (adj[v][w] == "false") {
        if (ra == "null"){
            adj[v][w] = "Sem rotulo";
        }
        else{
            adj[v][w] = ra;
        }
        m++; // atualiza qtd arestas
    }
}

// remove uma aresta v->w do Grafo
void TGrafoR::removeA(int v, int w) {
    // testa se temos a aresta
    if (adj[v][w] != "false") {
        adj[v][w] = "false";
        m--; // atualiza qtd arestas
    }
}
void TGrafoR::insereV(int v) {
    if (v <= n) {
        cout << "Vértice já existe!";
    } else {
        // Alocar uma matriz nova com um vértice a mais
        std::string **adjac = new std::string *[n + 1];
        for (int i = 0; i < n + 1; i++) {
            adjac[i] = new std::string[n + 1];
        }

        // Copiar a matriz antiga para a nova
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                adjac[i][j] = adj[i][j];
            }
        }

        // Definir os novos elementos para "∞"
        for (int i = 0; i < n + 1; i++) {
            adjac[i][n] = "false";
            adjac[n][i] = "false";
        }
        adjac[n][n] = "false";

        // Liberar a memória da matriz antiga
        for (int i = 0; i < n; i++) {
            delete[] adj[i];
        }
        delete[] adj;

        // Atualizar o atributo adj e n
        this->adj = adjac;
        this->n++;
    }
}

void TGrafoR::removeV(int v) {
    if (v >= n || v < 0) {
        cout << "Vértice inválido!";
    } else {
        // Alocar uma nova matriz com um vértice a menos
        std::string **adjac = new std::string *[n - 1];
        for (int i = 0; i < n - 1; i++) {
            adjac[i] = new std::string[n - 1];
        }

        // Copiar os dados da matriz antiga para a nova, excluindo o vértice
        int ii = 0;
        for (int i = 0; i < n; i++) {
            if (i == v) continue;
            int jj = 0;
            for (int j = 0; j < n; j++) {
                if (j == v) continue;
                adjac[ii][jj] = adj[i][j];
                jj++;
            }
            ii++;
        }

        // Liberar a memória da matriz antiga
        for (int i = 0; i < n; i++) {
            delete[] adj[i];
        }
        delete[] adj;

        // Atualizar o atributo adj e n
        this->adj = adjac;
        this->n--;
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
            if (adj[i][w] != "false")
                std::cout << "Adj[" << i << "," << w << "]= " << adj[i][w] << " ";
            else
                std::cout << "Adj[" << i << "," << w << "]= false" << " ";
    }
    cout << "\nfim da impressao do grafo." << endl;
}

int TGrafoR::inDegree(int v) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (adj[i][v] != "false") {
            count++;
        }
    }
    return count;
}

int TGrafoR::outDegree(int v) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (adj[v][i] != "false") {
            count++;
        }
    }
    return count;
}

bool TGrafoR::f_conexo() {
    for (int v = 0; v < n; ++v) {
        std::vector<bool> visitado(n, false);
        std::queue<int> q;
        q.push(v);
        visitado[v] = true;
        int cnt = 1;

        while (!q.empty()) {
            int atual = q.front(); q.pop();
            for (int i = 0; i < n; ++i) {
                if (adj[atual][i] != "false" && !visitado[i]) {
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

bool TGrafoR::sf_conexo() {
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
                    if (adj[atual][i] != "false" && !visitado[i]) {
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
                        if (adj[atual][i] != "false" && !visitado[i]) {
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

bool TGrafoR::desconexo() {
    std::vector<bool> visitado(n, false);
    std::queue<int> q;
    q.push(0);
    visitado[0] = true;
    int cnt = 1;

    while (!q.empty()) {
        int atual = q.front(); q.pop();
        for (int i = 0; i < n; ++i) {
            if (adj[atual][i] != "false" && !visitado[i]) {
                q.push(i);
                visitado[i] = true;
                ++cnt;
            }
        }
    }
    return cnt != n;
}

int TGrafoR::categoria() {
if (m == 0) return 0;
    if (f_conexo()) return 3;
    if (sf_conexo()) return 2;
    if (!desconexo()) return 1;
    return 0;
}

void TGrafoR::FCONEX() { // Mostra o grafo reduzido
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
                        if (adj[x][j] != "false" && !Rplus.count(j)) {
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
                        if (adj[j][x] != "false" && !Rminus.count(j)) {
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

bool TGrafoR::euleriano() {
    if (!f_conexo()) {
        return false; // Não é Euleriano se não for fortemente conexo
    }
    for (int v = 0; v < n; ++v) {
        if (inDegree(v) != outDegree(v)) {
            return false; // Não é Euleriano se o grau de entrada for diferente do grau de saída
        }
    }
    return true; // É Euleriano se todas as condições acima forem satisfeitas
}

std::vector<int> TGrafoR::obterVizinhos(int v) {
    std::vector<int> vizinhos;
    for (int w = 0; w < n; w++) {
        if (adj[v][w] != "false") { 
            vizinhos.push_back(w);
        }
    }
    for (int w = 0; w < n; w++) {
        if (adj[w][v] != "false") { 
            vizinhos.push_back(w);
        }
    }
    return vizinhos;
}

void TGrafoR::coloracaoClasses() {
    std::vector<int> cores(n, -1);
    int k = 0;
    std::set<int> verticesNaoColoridos;
    for (int i = 0; i < n; i++) {
        verticesNaoColoridos.insert(i);
    }
    while (!verticesNaoColoridos.empty()) {
        std::set<int> verticesAtuais(verticesNaoColoridos);
        for (int v : verticesAtuais) {
            std::vector<int> vizinhos = obterVizinhos(v);
            bool podeColorir = true;
            for (int vizinho : vizinhos) {
                if (cores[vizinho] == k) {
                    podeColorir = false;
                    break;
                }
            }
            if (podeColorir) {
                cores[v] = k;
                verticesNaoColoridos.erase(v);
            }
        }
        k++;
    }
    for (int i = 0; i < n; i++) {
        int ve = 0;
        for (int j = 0; j < n; j++) {
            if (cores[j] == i) {
                ve++;
            }
        }
        if (ve != 0){
            std::cout << "Cor " << i << " eh atribuida aos vertices: ";
            for (int j = 0; j < n; j++) {
                if (cores[j] == i) {
                    std::cout << j << " ";
                }
            }
            std::cout << std::endl;
        }
    }
}