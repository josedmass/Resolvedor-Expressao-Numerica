#ifndef EXPRESSAO_H
#define EXPRESSAO_H

#include <iostream>
#include <string>

#include "ArvoreBinaria.h"
#include "PilhaEncadeada.h"

// Armazena a expressão em uma árvore binária (notação infixa) ou em uma pilha (notação pós-fixa)
struct Expressao {
    
    // Construtores
    Expressao();
    // Sobrecarga do operator=
    Expressao(const Expressao& other);
    Expressao& operator=(const Expressao& other);
    // Destrutor
    ~Expressao();
    // Variáveis que armazenarão a expressão
    ArvoreBinaria A;
    PilhaEncadeada P;

};

#endif