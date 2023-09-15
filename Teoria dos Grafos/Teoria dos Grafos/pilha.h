/*
   Pilha est�tica e sequencial
   Desenvolvimento com classe
   cria��o: 24/08/2022.
   prof. Dr. Ivan Carlos Alc�ntara de Oliveira
   pilha.h
*/

#ifndef ___PILHA_H___
#define ___PILHA_H___

// defini��o de um novo tipo de dado
typedef int Elem; 

// constante que indica o 
// Tamanho alocado para a pilha
const int TAM_PILHA = 10;

// Classe pilha est�tica e sequencial
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
