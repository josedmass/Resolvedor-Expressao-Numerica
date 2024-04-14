#include "ArvoreBinaria.h"
#include "Excecoes.h"

No::No() {
    // Constrói um nó vazio (item vazio e apontando para NULL)
    item = "";
    esq = NULL;
    dir = NULL;
}

No::No(std::string valor) {
    // Constrói um nó com item = valor e apontando para NULL
    item = valor;
    esq = NULL;
    dir = NULL;
}

ArvoreBinaria::ArvoreBinaria() {
    // Constrói uma árvore vazia, cuja raíz aponta pra NULL
    raiz = NULL;
}

ArvoreBinaria::ArvoreBinaria(const ArvoreBinaria& other) {
    // Faz com que a árvore *this fique igual à other
    this->raiz = NULL;
    if(other.raiz == NULL) return;
    this->raiz = new No(other.raiz->item);
    CopiaArvore(this->raiz, other.raiz);
}

ArvoreBinaria& ArvoreBinaria::operator=(const ArvoreBinaria& other) {
    // Faz com que a árvore *this fique igual à other
    
    if(this == &other) return *this; // Se está atribuindo duas árvores iguais

    this->LimpaRecursivo(this->raiz); // Limpa a memória alocada para essa árvore
    if(other.raiz == NULL) return *this; // Se eu está tentando atribuir à uma árvore vazia

    this->raiz = new No(other.raiz->item); // Faço com que this->raiz tenha o mesmo item que a raiz de other
    CopiaArvore(this->raiz, other.raiz); // Copio a árvore
    
    return *this;
}

void ArvoreBinaria::CopiaArvore(No* &dessa, No* other) {
    // Faz com que a árvore *this fique igual à other, recursivamente, a partir de suas raízes

    if(other->esq != NULL) {
        // Se other->esq possui algum elemento, então fazer com que dessa->esq = other->esq
        dessa->esq = new No(other->esq->item);
        CopiaArvore(dessa->esq, other->esq);
    }

    if(other->dir != NULL) {
        // Se other->dir possui algum elemento, então fazer com que dessa->dir = other->dir
        dessa->dir = new No(other->dir->item);
        CopiaArvore(dessa->dir, other->dir);
    }
}

No* ArvoreBinaria::GetRaiz() {
    // Retorna a raiz da função
    return raiz;
}

No* ArvoreBinaria::InsereRecursivo(std::string exp[], int start, int end) {
    // Insere recursivamente uma expressão infixa armazenada em um vetor de strings exp[].
    // start é o índice de onde o vetor começa e end é o índice de onde ele termina.

    if(start > end) return NULL; // 1ª condição de parada
    /*
        int min_precedencia olha qual a menor precedência da operação:
            1: se operador = +, -.
            2: se operador = *, /
            5: se é um número
            10: se não é nem operador, nem número (é um parênteses)
    */
    int min_precedencia = 10; 

    // Conta o balanço de parênteses e em que contexto há o menor balanço (menor precedência de operação)
    int cont_parenteses = 0, min_cont_parenteses = end+1;
    // Guarda o índice de onde está o elemento de menor precedência
    int indice_raiz = -1;

    for(int i = start; i <= end; i++) {

        if(exp[i] == "(") {
            cont_parenteses++;
            continue;
        }
        else if (exp[i] == ")") {
            cont_parenteses--;
            continue;
        }

        if(cont_parenteses >= 0) {
            // Analisa a precedência
            int precedencia;
            if (exp[i] == "+" || exp[i] == "-") {
                precedencia = 1;
            } else if (exp[i] == "*" || exp[i] == "/") {
                precedencia = 2;
            } else if (isdigit(exp[i][0])) {
                precedencia = 5;
            } else {
                precedencia = 10;
            }
    
            // Pega qual é a menor precedência de toda a expressão (min_precedencia) e guarda seu índice (indice_raiz)
            if (precedencia < 10) {
                // Se a precedência é menor que a mínima e o contador de parênteses é menor ou igual
                // ao min_cont_parenteses, então estamos em um local de baixa precedência
                if(precedencia <= min_precedencia && cont_parenteses <= min_cont_parenteses) {
                    min_precedencia = precedencia;
                    indice_raiz = i;
                }
                // Se a precedência não é estritamente menor, então estamos lidando com elementos de mesmo
                // valor de precedencia. Analisamos então o cont_parenteses, pra sabermos qual é o local de
                // menor precedência
                else if(cont_parenteses < min_cont_parenteses) {
                    min_precedencia = precedencia;
                    indice_raiz = i;
                }
            }
        }

        // Se min_cont_parenteses for maior, então o igualamos ao atual cont_parenteses
        if(min_cont_parenteses > cont_parenteses) min_cont_parenteses = cont_parenteses;

    }

    if(indice_raiz == -1) return NULL; // Nenhum índice foi armazenado (2ª condição de parada)
    else {
        // Se é um dígito, armazená-lo adequadamente (Nós com itens numéricos não possuem filhos)
        if(isdigit(exp[indice_raiz][0])) {
            No* numero = new No(exp[indice_raiz]);
            numero->esq = NULL;
            numero->dir = NULL;
            raiz = numero;
            return numero; // 3ª condição de parada
        }
    }

    // Aqui, significa que é um operador
    // Subdividimos o vetor exp em duas partes, inserindo o que está à sua esquerda e o que está à sua direita
    No* raiz_exp = new No(exp[indice_raiz]);
    raiz_exp->esq = InsereRecursivo(exp, start, indice_raiz - 1);
    raiz_exp->dir = InsereRecursivo(exp, indice_raiz + 1, end);
    raiz = raiz_exp;
    return raiz_exp; // 4ª condição de parada

}

void ArvoreBinaria::Insere_Da_Pilha(std::string exp[], int end) {
    // Insere uma expressão na notação pós-fixa, armazenada em um vetor de strings, em uma árvore
    
    // Cria um vetor de ponteiros de nós de tamanho end+1 (tamanho da expressão)
    No* arvore[end+1];
    int topo = -1;
    for (int i = 0; i <= end; i++) {
        std::string valor = exp[i];
        
        if(valor == "+" || valor == "-" || valor == "*" || valor == "/") {
            // Se for um operador, retiramos os dois números antecessores e os armazenamos em uma subárvore
            No* Filho_Direita = arvore[topo--];
            No* Filho_Esquerda = arvore[topo--];
            No* NovoNo = new No(valor);
            NovoNo->esq = Filho_Esquerda;
            NovoNo->dir = Filho_Direita;
            arvore[++topo] = NovoNo;
            raiz = NovoNo; // A raíz da árvore muda iterativamente, conforme colocamos novos operadores
        }
        
        else {
            // Se for um dígito, o armazenamos no vetor
            No* NovoNo = new No(valor);
            arvore[++topo] = NovoNo;
            raiz = NovoNo;
            // OBS: mudamos aqui a raíz da árvore, pois, se a expressão tiver números e operadores, isso é obsoleto,
            // mas se a expressão for apenas um número, então a raíz fica adequadamente definida.
        }
    }

} 

void ArvoreBinaria::Limpa() {
    // Limpa a árvore e defique que a raiz = NULL.
    LimpaRecursivo(raiz);
    raiz = NULL;
}

void ArvoreBinaria::LimpaRecursivo(No* p) {
    if(p != NULL) {
        // Enquanto houver elementos na árvore, apagamos recursivamente os nós alocados, a partir da raiz No* p
        LimpaRecursivo(p->esq);
        LimpaRecursivo(p->dir);
        delete p;
    }
}

PilhaEncadeada ArvoreBinaria::PosOrdem(No* p) {
    // Aplicação: Transformar em Pilha, a partir da raiz No* p
    PilhaEncadeada aux;
    if(p != NULL) {
        // O que é de maior prioridade fica mais embaixo
        PilhaEncadeada esq = PosOrdem(p->esq);
        PilhaEncadeada dir = PosOrdem(p->dir);
        aux.Empilha_Item(p->item);
        aux.Concatena(dir);
        aux.Concatena(esq);
    }

    return aux;
}

std::string ArvoreBinaria::InOrdem(No* p, bool primeiroNo) {
    // Aplicação: retornar a notação infixa
    std::string expr;
    if(p != NULL) {
        // Se estivermos aprofundando na árvore, colocar "("
        if (!primeiroNo) {
            expr += "( ";
        }
        // colocamos, recursivamente, o elemento do filho da esquerda, o do pai e então o do filho da direita
        expr += InOrdem(p->esq, false);
        expr += " " + p->item + " ";
        expr += InOrdem(p->dir, false);
        // Se estivermos subindo na árvore, colocar ")"
        if (!primeiroNo) {
            expr += " )";
        }
    }
    return expr;
}

double ArvoreBinaria::resolve(No* p) {
    
    if(p == NULL) return 0; // 1ª condição de parada

    // Guardamos quem são os operandos da esquerda e da direita de um nó pai (operador)
    double operand_esq, operand_dir;
    operand_esq = resolve(p->esq);
    operand_dir = resolve(p->dir);

    if(p->item == "+") {
        // soma
        return operand_esq + operand_dir;
    } else if(p->item == "-") {
        // subtração
        return operand_esq - operand_dir;
    } else if(p->item == "/") {
        // divisão
        if (operand_dir == 0) {
            // ERRO: DIVISÃO POR ZERO
            DIVISAO_POR_ZERO E;
            throw E;
        }
        return operand_esq / operand_dir;
    } else if(p->item == "*") {
        // multiplicação
        return operand_esq * operand_dir;
    } else {
        return std::stod(p->item); // 2ª condição de parada
        // OBS: A função std::stod transforma uma string em um double
    }
    
}

ArvoreBinaria::~ArvoreBinaria() {
    // Destrói a árvore, a partir da função Limpa()
    Limpa();
}