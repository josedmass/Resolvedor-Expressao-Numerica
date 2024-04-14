#ifndef ARVORE_H
#define ARVORE_H

#include <iostream>
#include <string>
#include "PilhaEncadeada.h"

class No {
    public: 
        // Construtores
        No();
        No(std::string valor);
    private:
        // Variáveis do Nó (item e apontadores para a direita e para a esquerda do nó)
        std::string item;
        No* esq;
        No* dir;
    friend class ArvoreBinaria;
};

// Armazena expressões em notação infixa
class ArvoreBinaria {
    public:
        // Construtores
        ArvoreBinaria();
        // Sobrecarga da atribuição de árvores
        ArvoreBinaria(const ArvoreBinaria& other);
        ArvoreBinaria& operator=(const ArvoreBinaria& other);
        // Copia duas árvores
        void CopiaArvore(No* &dessa, No* other);
        // Destrutor
        ~ArvoreBinaria();
        // Função auxiliar que retorna a raíz árvore
        No* GetRaiz();
        // Funções para inserirmos elementos na árvore, advindos de uma expressão ou de uma pilha
        No* InsereRecursivo(std::string exp[], int start, int end);
        void Insere_Da_Pilha(std::string exp[], int end);
        // Função para limpar a árvore
        void Limpa();
        void LimpaRecursivo(No* p);
        // Funções de caminhamento na árvore
        PilhaEncadeada PosOrdem(No* p);  // Aplicação: Transformar em pilha
        std::string InOrdem(No* p, bool primeiroNo);  // Aplicação: Imprimir na notação infixa
        // Função que retorna o resultado da expressão
        double resolve(No* p);

    private:
        // Raiz da árvore
        No* raiz;

};

#endif