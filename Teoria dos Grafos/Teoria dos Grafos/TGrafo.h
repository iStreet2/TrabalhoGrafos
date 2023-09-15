/*
 Implementacao de uma Classe para grafos denominada TGrafo,
 usando Matriz de Adjacencia
 e metodos para utilizacao de um grafo dirigido.
 */
#ifndef ___GRAFO_MATRIZ_ADJACENCIA___

#define ___GRAFO_MATRIZ_ADJACENCIA___
// definicao de uma estrutura para armezanar um grafo
// Tambem seria possivel criar um arquivo grafo.h
// e fazer a inclusao "#include <grafo.h>"
class TGrafo {
private:
    int n;     // quantidade de vertices
    int m;     // quantidade de arestas
    int **adj; // matriz de adjacencia
    
public:
    TGrafo(int n);
    void insereA(int v, int w);
    void removeA(int v, int w);
    void removeV(int v);
    void show();
    int inDegree(int v);
    int outDegree(int v);
    int isFonte(int v);
    int isSorvedouro(int v);
    int isSimetrico();
    bool isCompleto();
    int **Complementar();
    bool f_conexo();
    bool sf_conexo();
    bool desconexo();
    int categoria();
    void FCONEX();
    ~TGrafo();
};

class TGrafoR {
private:
    int n;       // quantidade de vertices
    int m;       // quantidade de arestas
    float **adj; // matriz de adjacencia
    
public:
    TGrafoR(int n);
    void insereA(int v, int w, float ra);
    void removeA(int v, int w);
    void show();
    int inDegree(int v);
    int outDegree(int v);
    void dijkstra(int startVertex);
    void bellmanFord(int startVertex);
    ~TGrafoR();
};

class TGrafoND {
private:
    int n;     // quantidade de vertices
    int m;     // quantidade de arestas
    int **adj; // matriz de adjacencia
    
public:
    TGrafoND(int n);
    void insereA(int v, int w);
    void removeA(int v, int w);
    void show();
    int inDegree(int v);
    int outDegree(int v);
    int isFonte(int v);
    int isSorvedouro(int v);
    int isSimetrico();
    bool verificarGrafoCompleto();
    int Conexidade();
    void removeVertice(int v);
    ~TGrafoND();
};

class TGrafoNDR {
private:
    int n;
    int m;
    float **adj;
    
public:
public:
    TGrafoNDR(int n);
    void insereA(int v, int w, float ra);
    void removeA(int v, int w);
    void show();
    int inDegree(int v);
    int outDegree(int v);
    int isSimetrico();
    void arquivo();
    ~TGrafoNDR();
};

class TNo{ // define uma struct (registro)
public:
    // vertice que e adjacente ao elemento da lista
    int w;
    TNo *prox;
};

// definicao de uma classe para armezanar um grafo
class TGrafoLista{
private:
    int n; // quantidade de vertices
    int m; // quantidade de arestas
    TNo **adj; // um vetor onde cada entrada guarda o inicio de uma lista
public:
    TGrafoLista( int n );
    void insereA( int v, int w);
    void removeA( int v, int w);
    void show();
    bool iguais(TGrafoLista &g2);
    void LM();
    void inverter();
    int isFonte(int v);
    int isSorvedouro(int v);
    int isSimetrico();
    ~TGrafoLista();
};


#endif
