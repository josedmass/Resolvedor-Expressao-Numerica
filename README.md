# Resolvedor-Expressao-Numerica
Este projeto foi desenvolvido como Trabalho Prático 1 da disciplina de Estrutura de Dados da UFMG, realizado em 2023/01.

## Autor
- José Eduardo Duarte Massucato

## Descrição
O trabalho proposto tem por objetivo lidar com expressões numéricas, denotadas em notação infixa ou pós-fixa, que utilizam das quatro operações básicas da matemática: soma (+), subtração (-), divisão (/) e multiplicação (*), utilizando a linguagem C++.

## Funcionalidades
- Ler expressões numéricas com o comando "LER"
- Converter de uma formatação para outra com o comando "INFIXA" - caso o usuário queira a expressão na notação infixa - ou "POSFIXA" - caso o usuário a queira na notação pós-fixa.
- Resolver a expressão com o comando "RESOLVE".

OBS: Os detalhes da implementação, bem como as estruturas de dados utilizados e os métodos adotados, encontram0se em "Documentacao.pdf".

## Como usar
1. Navegue até a pasta TP no seu computador
```bash
cd /<caminho_para_a_pasta>/TP
```

2. Adicione o arquivo de entrada desejado em ./TP, cuja formatação deve seguir o exemplo mostrado ao final de "Documentacao.pdf"

3. Compile e execute o programa a partir do arquivo Makefile presente em ./TP
```bash
make run <file_name.txt>
```

4. A saída será direcionada para a saída padrão do sistema.

5. Ao final das execuções, utilize o Makefile para limpar os arquivos gerados
```bash
make clean
```

OBS: Um arquivo de entrada de exemplo, chamado "in.txt", foi adicionado em ./TP.