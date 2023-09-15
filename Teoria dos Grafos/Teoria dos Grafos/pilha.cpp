/*
   Pilha est�tica e sequencial
   Desenvolvimento com classe
   cria��o: 24/08/2022.
   prof. Dr. Ivan Carlos Alc�ntara de Oliveira
   pilha.cpp
*/

#include <iostream>
#include "pilha.h"

// Construtor da Pilha
Pilha::Pilha(){
  this->topoPilha = -1;
}

// Destrutor da pilha
// N�o faz nada, pois
// a aloca��o � est�tica e senquencial
Pilha::~Pilha(){};

// Verifica se a pilha
// est� vazia
bool Pilha::isEmpty( ) {
  if (this->topoPilha == -1)
       return true;
  else
       return false;
}

// Verifica se a pilha est�
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

// Retorna o elemento que est�
// no topo da pilha
Elem Pilha::topo( ){
  if ( ! this->isEmpty( ))
       return this->e[this->topoPilha];
  else{
    std::cout << "underflow - Esvaziamento de Pilha";
    return -1;
  }
}

/// obt�m o total de elementos
// armazenados na Pilha
int Pilha::size( ){
  return topoPilha+1;
}



