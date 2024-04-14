#ifndef OPERACOES_H
#define OPERACOES_H

#include <iostream>
#include <string>

#include "ArvoreBinaria.h"
#include "PilhaEncadeada.h"
#include "Expressao.h"

// Checa a validade da expressão.
bool valido_infx(std::string s[], int tam);
bool valido_posfx(std::string s[], int tam);

// Imprime a expressão na sua respectiva notação
std::string imprime_infx(ArvoreBinaria A);
std::string imprime_posfx(PilhaEncadeada& P);

// Lê a expressão e, caso ela seja válida, a armazena
void ler(std::string s[], int tam, Expressao& exp, std::string notacao);

// Converte a notação armazenada para infixa (árvore binária) ou para pós-fixa (pilha) e retorna sua respectiva notação
std::string converte_infixa(Expressao& exp);
std::string converte_posfixa(Expressao& exp);

// Resolve a expressão
double resolve(Expressao& exp);

#endif