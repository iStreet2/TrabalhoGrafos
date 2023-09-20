#include <iostream>
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
    
public:
    std::string **adj; // matriz de adjacencia
    TGrafoR(int n);
    int getN();
    int getM();
    void insereA(int v, int w, std::string ra);
    void removeA(int v, int w);
    void show();
    int inDegree(int v);
    int outDegree(int v);
    bool f_conexo();
    bool sf_conexo();
    bool desconexo();
    int categoria();
    void FCONEX();
    ~TGrafoR();
};

#endif /* TGrafoR_h */
