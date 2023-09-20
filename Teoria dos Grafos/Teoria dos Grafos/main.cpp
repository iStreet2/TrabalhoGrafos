#include "TGrafoR.h"
#include <fstream>
#include <iostream>
#include <string>
#include <limits>
using namespace std;

TGrafoR* g = nullptr; //ponteiro para criar o grafo posteriormente
std::string* nomes; //vetor de strings para armazenar os nomes dos vertices
void lerDados();
void gravarDados();
void inserirVertice();
void inserirAresta();
void removerVertice();
void removerAresta();
void mostrarConteudoArquivo();
void mostrarGrafo();
void apresentarConexidade();

int main() {
    char opcao;
    
    do {
        std::cout << "\nMenu:" << std::endl;
        std::cout << "a) Ler dados do arquivo grafo.txt;" << std::endl;
        std::cout << "b) Gravar dados no arquivo grafo.txt;" << std::endl;
        std::cout << "c) Inserir vertice;" << std::endl;
        std::cout << "d) Inserir aresta;" << std::endl;
        std::cout << "e) Remove vertice;" << std::endl;
        std::cout << "f) Remove aresta;" << std::endl;
        std::cout << "g) Mostrar conteudo do arquivo;" << std::endl;
        std::cout << "h) Mostrar grafo;" << std::endl;
        std::cout << "i) Apresentar a conexidade do grafo e o reduzido;" << std::endl;
        std::cout << "j) Encerrar a aplicacao." << std::endl;
        std::cout << "Digite sua opcao: ";
        std::cin >> opcao;

        switch (opcao) {
            case 'a':
                lerDados();
                break;
            case 'b':
                gravarDados();
                break;
            case 'c':
                inserirVertice();
                break;
            case 'd':
                inserirAresta();
                break;
            case 'e':
                removerVertice();
                break;
            case 'f':
                removerAresta();
                break;
            case 'g':
                mostrarConteudoArquivo();
                break;
            case 'h':
                mostrarGrafo();
                break;
            case 'i':
                apresentarConexidade();
                break;
            case 'j':
                std::cout << "Encerrando aplicacao..." << std::endl;
                delete g;
                break;
            default:
                std::cout << "Opcao invalida!" << std::endl;
                break;
        }

    } while (opcao != 'j');
    return 0;
}

void lerDados() {
    std::ifstream arquivo("Grafo.txt");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return;
    }

    int tipoGrafo, numVertices, numArestas;
    arquivo >> tipoGrafo;
    arquivo >> numVertices;

    g = new TGrafoR(numVertices);
    
    nomes = new std::string[numVertices];
    for (int i = 0; i < numVertices; i++) {
        int vertice;
        std::string rotulo;
        arquivo >> vertice;
        arquivo.ignore(); //Ignora a virgula
        std::getline(arquivo, rotulo); // Lê o rótulo até o final da linha
        nomes[vertice] = rotulo;
    }

    arquivo >> numArestas;

    for (int i = 0; i < numArestas; i++) {
        int v, w;
        std::string ra;
        arquivo >> v >> w;
        std::getline(arquivo, ra, '"'); // Ignora o primeiro "
        std::getline(arquivo, ra, '"'); // Lê até o próximo " para pegar o rótulo completo
        arquivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora até o final da linha
        g->insereA(v, w, ra);
    }

    arquivo.close();
    std::cout << "Arquivo lido com sucesso!" << std::endl;
}

void gravarDados() {
     std::ofstream arquivo("Grafo2.txt");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
        return;
    }

    int numVertices = g->getN();
    int numArestas = g->getM();

    // Escrevendo tipo do grafo (no seu exemplo era 7) e o número de vértices
    arquivo << 7 << std::endl;
    arquivo << numVertices << std::endl;

    // Escrevendo vértices e seus rótulos
    for (int i = 0; i < numVertices; i++) {
        arquivo << i << "," << nomes[i] << std::endl;
    }

    // Escrevendo número de arestas
    arquivo << numArestas << std::endl;

    // Escrevendo arestas
    // Escrevendo arestas na matriz de adjacências
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (g->adj[i][j] != "false") { // Se a aresta existir
                arquivo << i << " " << j << " \"" << g->adj[i][j] << "\"" << std::endl;
            }
        }
    }

    arquivo.close();
    std::cout << "Grafo salvo com sucesso no arquivo!" << std::endl;
}

void inserirVertice() {
    cout << "Qual o nome do vértice que deseja inserir? ";
    string nome;
    cin >> nome;
    // Inserir o novo vértice no grafo
    g->insereV(g->getN() + 1);
    
    // Redimensionar o vetor de nomes
    string* novoNomes = new string[g->getN()]; // o novo tamanho é g->getN()
    for (int i = 0; i < g->getN() - 1; ++i) {  // copiar os nomes antigos
        novoNomes[i] = nomes[i];
    }
    novoNomes[g->getN() - 1] = nome; // inserir o novo nome na última posição
    
    delete[] nomes; // liberar memória antiga
    nomes = novoNomes; // atualizar o ponteiro
    
    cout << "Vértice inserido com sucesso!" << endl;
}

void inserirAresta() {
    std::cout << "Vertice de origem: ";
    int origem;
    std::cin >> origem;
    std::cout << "Vertice de destino: ";
    int destino;
    std::cin >> destino;
    std::cout << "Rotulo da aresta (null se nao houver): ";
    std::string rotulo;
    std::cin >> rotulo;
    g->insereA(origem, destino, rotulo);
    std::cout << "Aresta inserida com sucesso!" << std::endl;
}

void removerVertice() {
    
}

void removerAresta() {
    std::cout << "Vertice de origem: ";
    int origem;
    std::cin >> origem;
    std::cout << "Vertice de destino: ";
    int destino;
    std::cin >> destino;
    g->removeA(origem, destino);
    std::cout << "Aresta removida com sucesso!" << std::endl;
}

void mostrarConteudoArquivo() {
    
}

void mostrarGrafo() {
    int numVertices = g->getN();
    for (int i = 0; i < numVertices; i++) {
        std::cout << "Vertice " << nomes[i] << ":" << std::endl;

        for (int j = 0; j < numVertices; j++) {
            if (g->adj[i][j] != "false") {  // Se existe aresta entre os vértices i e j
                std::cout << "- Aresta para " << nomes[j] << ": " << g->adj[i][j] << std::endl;
            }
        }
        std::cout << std::endl;
    }
}

void apresentarConexidade() {
    
}
