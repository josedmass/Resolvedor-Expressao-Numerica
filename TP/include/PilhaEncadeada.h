#ifndef PILHA_H
#define PILHA_H

#include <iostream>
#include <string>

class Celula {
    public:
        // Construtores
        Celula();
    private:
        // Variáveis do Célula (item e apontador para a próxima célula)
        std::string item;
        Celula *prox;
        friend class PilhaEncadeada;
};

class PilhaEncadeada {
    public:
        // Construtor
        PilhaEncadeada();
        // Sobrecarga da atribuição de duas pilhas
        PilhaEncadeada(const PilhaEncadeada& other);
        PilhaEncadeada& operator=(const PilhaEncadeada& other);
        // Destrutor
        ~PilhaEncadeada();
        // Funções auxiliares que retornam, respectivamente, o topo da pilha e o seu tamanho
        Celula* GetTopo();
        int GetTamanho();
        // Funções que empilham elementos na pilha
        void Empilha_Exp(std::string exp[], int end);
        void Empilha_Item(std::string s);
        // Função para concatenar duas pilhas, a pilha other fica sob a pilha *this
        void Concatena(PilhaEncadeada& other);
        // Função para desempilhar elementos da pilha
        std::string Desempilha();
        // Função pra percorrer os elementos da pilha, sem desempilhar
        std::string Percorre();
        // Função para limpar a pilha
        void Limpa();
    private:
        // Tamanho da pilha
        int tamanho;
        // Topo da pilha
        Celula* topo;
};

#endif