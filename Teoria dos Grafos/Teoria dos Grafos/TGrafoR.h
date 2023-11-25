#include <iostream>
#include <vector>
#ifndef TGrafoR_h
#define TGrafoR_h

class TGrafoR {
private:
    int n;
    int m;
    
public:
    std::string **adj;
    TGrafoR(int n);
    int getN();
    int getM();
    void insereA(int v, int w, std::string ra);
    void removeA(int v, int w);
    void insereV(int v);
    void removeV(int v);
    void show();
    int inDegree(int v);
    int outDegree(int v);
    bool f_conexo();
    bool sf_conexo();
    bool desconexo();
    int categoria();
    void FCONEX();
    bool euleriano();
    void coloracaoClasses();
    std::vector<int> obterVizinhos(int v);
    ~TGrafoR();
};

#endif 
