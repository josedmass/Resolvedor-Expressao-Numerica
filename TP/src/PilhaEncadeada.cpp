#include "PilhaEncadeada.h"

Celula::Celula() {
    // Constrói uma célula vazia
    item = "";
    prox = NULL;
}

PilhaEncadeada::PilhaEncadeada() {
    // Constrói uma pilha de tamanho zero e com topo nulo
    tamanho = 0;
    topo = NULL;
}

PilhaEncadeada::PilhaEncadeada(const PilhaEncadeada& other) {
    // Faz com que a pilha *this fique igual à other
    this->topo = NULL;
    this->tamanho = other.tamanho;

    if(other.topo == NULL) return;

    this->topo = new Celula();
    this->topo->item = other.topo->item;
    Celula* curr = topo;
    Celula* othercurr = topo->prox;

    while (othercurr != nullptr) {
        curr->prox = new Celula();
        curr->prox->item = othercurr->item;
        curr = curr->prox;
        othercurr = othercurr->prox;
    }

}

PilhaEncadeada& PilhaEncadeada::operator=(const PilhaEncadeada& other) {
    // Faz com que a pilha *this fique igual à other
    
    if(this == &other) return *this; // Se está atribuindo duas pilhas iguais

    this->Limpa(); // Limpo o que estava alocado
    
    if(other.topo == NULL) return *this; // Se está tentando atribuir à uma pilha vazia

    // Fazemos com que this->topo seja igual a other->topo
    this->topo = new Celula();
    this->topo->item = other.topo->item;
    tamanho++;

    // Variáveis auxiliares
    Celula* curr = this->topo;
    Celula* othercurr = other.topo->prox;

    while(othercurr != NULL) {
        // iterativamente, vou igualando, "de cima pra baixo", os elementos dessa pilha com
        // os da pilha other
        curr->prox = new Celula();
        curr->prox->item = othercurr->item;
        curr = curr->prox;
        othercurr = othercurr->prox;
        tamanho++;
    }

    return *this;
}

Celula* PilhaEncadeada::GetTopo() {
    // Retorna o topo da pilha
    return topo;
}

int PilhaEncadeada::GetTamanho() {
    // Retorna o tamanho da pilha
    return tamanho;
}

void PilhaEncadeada::Empilha_Exp(std::string exp[], int end) {
    // Empilhamos, elemento por elemento, os itens do vetor de strings exp
    for(int i = end; i >= 0; i--) { 
        // Note que guardamos a expressão "de trás pra frente", para facilitar na hora de resolver
        Celula* nova = new Celula();
        nova->item = exp[i];
        nova->prox = topo;
        topo = nova;
        tamanho++;
    }
}

void PilhaEncadeada::Empilha_Item(std::string s) {
    // Empilhamos uma nova string no topo da pilha
    Celula* nova = new Celula();
    nova->item = s;
    nova->prox = topo;
    topo = nova;
    tamanho++;
}

void PilhaEncadeada::Concatena(PilhaEncadeada& other) {
    // Colocamos a pilha *this em cima da pilha other
  
    if(this->topo == NULL) { // Se a pilha atual estiver vazia
        this->topo = other.topo;
        this->tamanho = other.tamanho;
    }

    else if(other.topo == NULL) { // se a pilha other estiver vazia
        this->topo->prox = NULL;
    }

    else {
        Celula* ultimo = this->topo;
        while(ultimo->prox != NULL) ultimo = ultimo->prox;
        ultimo->prox = other.topo; // O final da pilha *this se liga ao topo da pilha other
        this->tamanho += other.tamanho;
    }

    other.topo = NULL; // other.topo se torna obsoleto
    
}


std::string PilhaEncadeada::Desempilha() {
    // Desempilhamos um elemento do topo da pilha
    std::string aux; 
    Celula *p;
    aux = topo->item;
    p = topo;
    topo = topo->prox; // alteramos o topo, e apagamos o antigo
    delete p;
    tamanho--; // diminuímos o tamanho e retornamos o elemento que estava a priori no topo
    return aux;
}

std::string PilhaEncadeada::Percorre() {
    // Retorna uma string que representa a expressão armazenada em notação pós-fixa
    int tam = tamanho;
    std::string exp;
    Celula* p = topo;
    
    // Cada item de exp representa um elemento da pilha, do 0(topo) até tam-1(base)
    for(int i = 0; i < tam; i++) {
        exp += p->item;
        exp += " ";
        p = p->prox;
    }

    return exp;
}

void PilhaEncadeada::Limpa() {
    // Limpa iterativamente o que está armazenado na pilha encadeada
    Celula* p;
    while(tamanho != 0 && topo != NULL) {
        p = topo;
        topo = topo->prox;
        delete p;
        tamanho--;
    }
    topo = NULL;
}

PilhaEncadeada::~PilhaEncadeada() {
    // Destrói a pilha, chamando a função Limpa()
    Limpa();
}