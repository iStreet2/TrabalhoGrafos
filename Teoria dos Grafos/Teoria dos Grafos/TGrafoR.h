//
//  TGrafoR.h
//  Teoria dos Grafos
//
//  Created by Gabriel Vicentin Negro on 14/09/23.
//

#ifndef TGrafoR_h
#define TGrafoR_h



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

#endif /* TGrafoR_h */
