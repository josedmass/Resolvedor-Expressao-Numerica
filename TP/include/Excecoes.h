#ifndef ESCECOES_H
#define ESCECOES_H

#include <string>

#define MAXTAM 1000

// Caso o usuário digite uma expressão inválida
struct EXPRESSAO_INVALIDA {
    std::string expressao[MAXTAM];
};

// Caso o usuário digite um comando diferente de "LER", "INFIXA", "POSFIXA" e "RESOLVE"
struct COMANDO_INVALIDO {
    std::string comando;
};

// Caso o usuário chame "LER" e em sequência digite algo diferente de "INFIXA" e "POSFIXA"
struct NOTACAO_INVALIDA {
    std::string notacao;
};

// Caso o usuário tente realizar alguma operação sem haver nada armazenado
struct ARMAZENAMENTO_VAZIO {};

// Caso o usuário tente resolver a expressão e em algum momento ocorra uma divisão por zero
struct DIVISAO_POR_ZERO {};

#endif