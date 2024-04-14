#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "operacoes.h"
#include "ArvoreBinaria.h"
#include "PilhaEncadeada.h"
#include "Excecoes.h"

#define MAXTAM 1000

// Executa o comando solicitado pelo usuário
void exe_comando(std::istringstream& cmd, Expressao& E);

int main(int argc, char* argv[]) {   // Passa o nome do arquivo na linha de compilação

    if (argc < 2) {
        // Caso não tenha passado o nome do arquivo
        std::cout << "ERRO: NÃO PASSOU O NOME DO ARQUIVO" << std::endl;
        return 1;
    }

    std::fstream arquivo;
    std::string nome_do_arquivo = argv[1];
    arquivo.open(nome_do_arquivo, std::ios::in);

    if (!arquivo.is_open()) {
        // Caso o arquivo não tenha sido aberto adequadamente
        // ATENÇÃO: O arquivo DEVE estar no diretório ./TP
        std::cout << "ERRO: O ARQUIVO NÃO ABRIU" << std::endl;
        return 1;
    }

    Expressao Armazenamento; // Vai armazenar a expressão
    std::string linha; // captura as linhas do arquivo de entrada

    while(std::getline(arquivo, linha)) {
        
        if (linha.empty()) {
            continue; // linha vazia, passa para a próxima iteração do while
        }
        try {
            std::istringstream comando(linha);
            exe_comando(comando, Armazenamento); // Pega qual comando passou (LER, INFIXA, POSFIXA, RESOLVE)
        }
        catch (EXPRESSAO_INVALIDA E) {
            // Tratamento do caso da expressão escrita ser inválida
            std::cout << "ERRO: ";
            for(int i = 0; i < MAXTAM; i++) {
                std::cout << E.expressao[i] << " ";
                if(E.expressao[i] == "") break;
            }
            std::cout << "NAO VALIDA" << std::endl;
            continue;
        }
        catch (DIVISAO_POR_ZERO E) {
            // Tratamento do caso de ocorrer uma divisão por zero
            std::cout << "ERRO: DIVISÃO POR ZERO" << std::endl;
            continue;
        }
        catch (COMANDO_INVALIDO E) {
            // Tratamento do caso de o usuário escrever algo diferente de "LER", "INFIXA", "POSFIXA" e "RESOLVE"
            std::cout << "COMANDO INVALIDO: " << E.comando << std::endl;
            continue;
        }
        catch (ARMAZENAMENTO_VAZIO E) {
            // Tratamento do caso de o usuário tentar realizar uma operação sem haver nada armazenado
            std::cout << "ERRO: EXP NAO EXISTE" << std::endl;
            continue;
        }
        catch (NOTACAO_INVALIDA E) {
            // Tratamento do caso de o usuário usar o comando "LER" seguido de algo diferente de "INFIXA" e "POSFIXA"
            std::cout << "NOTACAO INVALIDA: " << E.notacao << std::endl;
        }
    }

    arquivo.close(); // fecha o arquivo
    return 0;

}

void exe_comando(std::istringstream& cmd, Expressao& E) {
    std::string acao;
    cmd >> acao;
    
    if(acao == "LER") {
        // Caso o comando seja "LER", captura a notação solicitada
        std::string notacao;
        cmd >> notacao;
        std::string word; // captura cada termo da expressão
        std::string exp[MAXTAM]; // armazena a expressao
        int tam = 0; // irá armazena o tamanho da espressao
        while(tam < MAXTAM && cmd >> word) {
            exp[tam] = word;
            tam++;
        }
        ler(exp, tam, E, notacao);

        // Caso a expressão lida seja válida, imprime que a leitura foi um sucesso
        std::cout << "EXPRESSAO OK: ";
        for (int i = 0; i < tam; i++) {
            std::cout << exp[i] << " ";
        }
        std::cout << std::endl;
        return;
        
    }
    else if(acao == "INFIXA") {
        // Caso o comando seja "INFIXA"
        std::string expressao;
        expressao = converte_infixa(E);
        // Converte e imprime na notação infixa
        std::cout << "INFIXA: "<< expressao << std::endl;
        return;
    }
    else if(acao == "POSFIXA") {
        // Caso o comando seja "POSFIXA"
        std::string expressao;
        expressao = converte_posfixa(E);
        // Converte e imprime na notação pós-fixa
        std::cout << "POSFIXA: "<< expressao << std::endl;
        return;
    }
    else if(acao == "RESOLVE") {
        // Resolve a expressão armazenada
        double resultado;
        resultado = resolve(E);
        // Caso tenha resolvido com sucesso, imprime o resultado com 6 casas decimais
        std::cout << std::fixed << std::setprecision(6) << "VAL: " << resultado << std::endl;
        return;
    }

    else {
        // Caso o comando seja diferente de "LER", "INFIXA", "POSFIXA" e "RESOLVE"
        COMANDO_INVALIDO E{acao};
        throw E;
    }
    return;
    
}