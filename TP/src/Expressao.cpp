#include "Expressao.h"

Expressao::Expressao() {
    // Inicializa com uma árvore e uma pilha vazias.
    ArvoreBinaria Aaux;
    PilhaEncadeada Paux;
    A = Aaux;
    P = Paux;
}

Expressao::Expressao(const Expressao& other) {
    // Faz com que a Expressão *this fique igual à other
    this->A = other.A;
    this->P = other.P;
}


Expressao& Expressao::operator=(const Expressao& other) {
    // Faz com que a Expressão *this fique igual à other
    if(this == &other) return *this; // Se está atribuindo duas expressões armazenadas iguais
    
    this->A.Limpa(); // Desaloco a memória da árvore armazenada
    this->P.Limpa(); // Desaloco a memória da pilha armazenada

    this->A = other.A; // Igualo as árvores (os casos já estão sendo tratados na atribuição de árvores)
    this->P = other.P; // Igualo as pilhas (os casos já estão sendo tratados na atribuição de pilhas)

    return *this;

}

Expressao::~Expressao() {
    // Limpa a árvore armazenada e a pilha armazenada
    A.Limpa();
    P.Limpa();
}
