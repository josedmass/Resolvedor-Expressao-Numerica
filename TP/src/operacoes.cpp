#include <iostream>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "operacoes.h"
#include "Expressao.h"
#include "Excecoes.h"

bool valido_infx(std::string s[], int tam) {
    /* 
        Uma expressão na notação infixa é considerada válida quando:
            1. Possui o mesmo número de parênteses abertos e fechados;
            2. Não possui dois operadores seguidos;
            3. Não possui dois números seguidos, sem um operador entre eles;
            4. Possui apenas, parênteses, números e/ou operadores.
    */

    int proporcao_de_parenteses = 0; // Olha a proporção entre o número de parênteses abertos e fechados.
    int number_time = 1; // É igual a 1 se for a vez de um número e igual a 0 se for a vez de um operador.

    for(int i = 0; i<tam; i++) {
        
        if(proporcao_de_parenteses < 0) return false;

        if(number_time == 1) {
            if(s[i] == "(") {
                proporcao_de_parenteses++;
                continue;
            }
            else if(s[i] == ")") {
                proporcao_de_parenteses--;
                continue;
            }
            // Se estava na vez de aparecer um número e apareceu um operador, retornar que é inválido
            else if(s[i] == "+" || s[i] == "-" || s[i] == "/" || s[i] == "*") return false;
            else if(!(isdigit(s[i][0]))) return false; // Se não for um número, i.e, for algo inesperado
            number_time = 0;
        }
        else {
            if(s[i] == "(") {
                proporcao_de_parenteses++;
                continue;
            }
            else if(s[i] == ")") {
                proporcao_de_parenteses--;
                continue;
            }
            // Se estava na vez de aparecer um operador e apareceu um número, retornar que é inválido
            else if(isdigit(s[i][0])) return false;
            else if(!(s[i] == "+" || s[i] == "-" || s[i] == "/" || s[i] == "*")) return false; // Se não for um dígito, i.e, for algo inesperado
            number_time = 1;
        }
    }
    if(proporcao_de_parenteses != 0) return false; // Significa que há algum parênteses que não é fechado ou não é aberto.
    if(number_time == 1) return false;

    return true;
}

bool valido_posfx(std::string s[], int tam) {
    /*
        Uma expressão na notação pós-fixa é considerada válida quando:
            1. Se, lendo da esquerda pra direita, o número de operadores não for maior ou igual ao de dígitos;
            2. Se, no final, o número de dígitos for uma unidade a mais do que o número de operadores;
            3. Possui apenas números e/ou operadores.
    */
    
    int digitos = 0, operadores = 0; // contadores

    for(int i = 0; i < tam; i++) {

        if(isdigit(s[i][0])) digitos++;
        else if(s[i] == "+" || s[i] == "-" || s[i] == "/" || s[i] == "*") operadores++;
        else return false; // Se houver parênteses, por exemplo

        if (operadores >= digitos) return false; // Se, em algum momento, houver um número de operadores maior ou igual ao de números
    }
    if(digitos != (operadores+1)) return false; // Se a quantidade de números não for uma unidade maior que a de operadores

    return true;

}

void ler(std::string s[], int tam, Expressao& exp, std::string notacao) {

    if(notacao == "INFIXA") {
        if(valido_infx(s, tam)) {
            // Se for infixa e válida, limpamos o que tinha armazenado e armazenamos a nova expressão em uma árvore binária
            exp.A.Limpa();
            exp.P.Limpa();
            exp.A.InsereRecursivo(s, 0, tam-1);
        }
        else {
            // Se for infixa, mas não for válida
            EXPRESSAO_INVALIDA E;
            for (int i = 0; i < tam; i++) {
                E.expressao[i] = s[i];
            }
            throw E;
        }
    }
    else if(notacao == "POSFIXA") {
        if(valido_posfx(s, tam)) {
            // ERRO: Se for pós-fixa e válida, limpamos o que tinha armazenado e armazenamos a nova expressão em uma pilha
            exp.A.Limpa();
            exp.P.Limpa();
            exp.P.Empilha_Exp(s, tam-1);  
        }
        else {
            // ERRO: Se for pós-fixa, mas não for válida
            EXPRESSAO_INVALIDA E;
            for (int i = 0; i < tam; i++) {
                E.expressao[i] = s[i];
            }
            throw E;
        }
    }
    else {
        // ERRO: Caso a notação escrita pelo usuário for diferente de "INFIXA" e "POSFIXA"
        NOTACAO_INVALIDA E{notacao};
        throw E;
    }
}

std::string imprime_infx(ArvoreBinaria A) {
    /*
        1. Colocar um "(" inicial
        2. Fazer o caminhamento InOrdem para imprimir
        3. Finalizar com ")" final
    */
    No* raiz_da_exp = A.GetRaiz();
    std::string aux = A.InOrdem(raiz_da_exp, true);
    return "( " + aux + " )";
}

std::string imprime_posfx(PilhaEncadeada& P) {
    // Imprime na notação pós-fixa, a partir da função PilhaEncadeada::Percorre()
    std::string exp;
    exp = P.Percorre();
    return exp;
}

std::string converte_infixa(Expressao& exp) {
    // Deve converter para a versão infixa da expressão

    if(exp.P.GetTopo() != NULL) {
        // Significa que há uma expressão pós-fixa armazenada
        int tam = exp.P.GetTamanho();
        std::string aloca_exp[tam];
        for(int i = 0; i < tam; i++) {
            aloca_exp[i] = exp.P.Desempilha(); // Pega os elementos da pilha
        }
        
        ArvoreBinaria aux;
        aux.Insere_Da_Pilha(aloca_exp, tam-1);
        // Limpamos o que existia na árvore e armazenamos a pilha 
        exp.P.Limpa();
        exp.A = aux;
        std::string infixa = imprime_infx(aux);
        return infixa;

    }

    else if(exp.A.GetRaiz() != NULL) {
        // Significa que há uma expressão infixa armazenada
        std::string infixa = imprime_infx(exp.A);
        return infixa;
    }
    // ERRO: NÃO HA NADA ARMAZENADO
    else {
        ARMAZENAMENTO_VAZIO E;
        throw E;
    }

}


std::string converte_posfixa(Expressao& exp) {
    // Deve converter para a versão pós-fixa da expressão

    if(exp.P.GetTopo() != NULL) {
        // Significa que há uma expressão pós-fixa armazenada
        std::string posfixa = imprime_posfx(exp.P);
        return posfixa;
    }

    else if(exp.A.GetRaiz() != NULL) {
        // Significa que há uma expressão infixa armazenada
        // Fazemos um caminhamento pós-ordem

        No* raiz_da_exp = exp.A.GetRaiz();
        PilhaEncadeada aux = exp.A.PosOrdem(raiz_da_exp); // Retorna uma pilha referente à árvore armazenada

        // Mas, por decisão de projeto, quero que minha pilha armazene a expressão "de baixo pra cima"
        PilhaEncadeada pilha_final;
        std::string valor;
        int tam = aux.GetTamanho();

        for(int i = 0; i < tam; i++) {
            valor = aux.Desempilha();
            pilha_final.Empilha_Item(valor);
        }

        // Limpamos o que existia na árvore e armazenamos a pilha
        exp.A.Limpa();
        exp.P = pilha_final;

        std::string posfixa;
        posfixa = imprime_posfx(exp.P);
        return posfixa;
    
    }
    // ERRO: NÃO HÁ NADA ARMAZENADO
    else {
        ARMAZENAMENTO_VAZIO E;
        throw E;
    }

}

double resolve(Expressao& exp) {
    // Resolve a expressão numérica armazenada

    if(exp.P.GetTopo() != NULL) {
        // Significa que há uma expressão pós-fixa armazenada

        PilhaEncadeada aux;
        aux = exp.P;
        double operand_esq, operand_dir;
        std::string exp_aux[aux.GetTamanho()];
        // OBS: exp_aux é um vetor de strings utilizado para auxiliar na operação

        for(int i = 0, j=0; j < exp.P.GetTamanho(); i++, j++) {
            exp_aux[i] = aux.Desempilha();

            // OBS: streamObj é utilizado para aumentar a precisão da resposta
            if(exp_aux[i] == "+") {
                // soma
                std::ostringstream streamObj;
                operand_esq = std::stod(exp_aux[i-2]);
                operand_dir = std::stod(exp_aux[i-1]);
                i -= 2;
                streamObj << std::fixed << std::setprecision(30) << (operand_esq + operand_dir);
                exp_aux[i] = streamObj.str();
            
            } else if (exp_aux[i] == "-") {
                // subtração
                std::ostringstream streamObj;
                operand_esq = std::stod(exp_aux[i-2]);
                operand_dir = std::stod(exp_aux[i-1]);
                i -= 2;
                streamObj << std::fixed << std::setprecision(30) << (operand_esq - operand_dir);
                exp_aux[i] = streamObj.str();
                    
            } else if (exp_aux[i] == "*") {       
                // multiplicação        
                std::ostringstream streamObj;
                operand_esq = std::stod(exp_aux[i-2]);
                operand_dir = std::stod(exp_aux[i-1]);
                i -= 2;
                streamObj << std::fixed << std::setprecision(30) << (operand_esq * operand_dir);
                exp_aux[i] = streamObj.str();

            } else if (exp_aux[i] == "/") {
                // divisão
                std::ostringstream streamObj;
                operand_esq = std::stod(exp_aux[i-2]);
                operand_dir = std::stod(exp_aux[i-1]);
                if(operand_dir == 0) {
                    // ERRO: DIVISÃO POR ZERO
                    DIVISAO_POR_ZERO E;
                    throw E;
                }
                i -= 2;
                streamObj << std::fixed << std::setprecision(30) << (operand_esq / operand_dir);
                exp_aux[i] = streamObj.str();
            
            } else {
                continue; // caso seja um número
            }
        }
        
        return std::stod(exp_aux[0]); // exp_aux[0] fica com o resultado da expressão

    } else if(exp.A.GetRaiz() != NULL) {
        // Significa que há uma expressão infixa armazenada
        No* raiz_da_exp = exp.A.GetRaiz();
        double result = exp.A.resolve(raiz_da_exp);
        return result;
    }
    
    else {
        // ERRO: NÃO HÁ NADA ARMAZENADO
        ARMAZENAMENTO_VAZIO E;
        throw E;
    }
}