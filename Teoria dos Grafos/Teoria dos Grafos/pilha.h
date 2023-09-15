/*
   Pilha estática e sequencial
   Desenvolvimento com classe
   criação: 24/08/2022.
   prof. Dr. Ivan Carlos Alcântara de Oliveira
   pilha.h
*/

#ifndef ___PILHA_H___
#define ___PILHA_H___

// definição de um novo tipo de dado
typedef int Elem; 

// constante que indica o 
// Tamanho alocado para a pilha
const int TAM_PILHA = 10;

// Classe pilha estática e sequencial
class Pilha {
	private:
   		int topoPilha;
   		Elem e[TAM_PILHA];
   	public:
   		Pilha();
   		~Pilha();
   		bool isEmpty();
   		bool isFull();
   		void push(Elem e);
   		Elem pop();
   		Elem topo(); 
		int size();		
};

#endif
