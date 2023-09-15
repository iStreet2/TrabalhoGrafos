/*
   Pilha estática e sequencial
   Desenvolvimento com classe
   criação: 24/08/2022.
   prof. Dr. Ivan Carlos Alcântara de Oliveira
   pilha.cpp
*/

#include <iostream>
#include "pilha.h"

// Construtor da Pilha
Pilha::Pilha(){
  this->topoPilha = -1;
}

// Destrutor da pilha
// Não faz nada, pois
// a alocação é estática e senquencial
Pilha::~Pilha(){};

// Verifica se a pilha
// está vazia
bool Pilha::isEmpty( ) {
  if (this->topoPilha == -1)
       return true;
  else
       return false;
}

// Verifica se a pilha está
// cheia
bool Pilha::isFull( ){
  if (this->topoPilha == TAM_PILHA-1)
       return true;
  else
       return false;
}

// insere um elemento e
// no topo da pilha
void Pilha::push( Elem e ){
  if (! this->isFull( ))
    this->e[++this->topoPilha] = e;
  else
    std::cout << "overflow - Estouro de Pilha";
}

// remove um elemento
// do topo da pilha
Elem Pilha::pop( ){
  if (! this->isEmpty( ))
   return this->e[this->topoPilha--];
  else{
    std::cout << "underflow - Esvaziamento de Pilha";
    return -1;
  }
}

// Retorna o elemento que está
// no topo da pilha
Elem Pilha::topo( ){
  if ( ! this->isEmpty( ))
       return this->e[this->topoPilha];
  else{
    std::cout << "underflow - Esvaziamento de Pilha";
    return -1;
  }
}

/// obtém o total de elementos
// armazenados na Pilha
int Pilha::size( ){
  return topoPilha+1;
}



