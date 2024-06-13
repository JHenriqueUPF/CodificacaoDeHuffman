# CodificacaoDeHuffman
-------------------------------------------------
Esse é um trabalho da materia de **Estrutura de Dados 2**, ministrada pelo professor **Leonardo Costella**
-------------------------------------------------
## Funcionalidades
 



## Objetivos
 * Ler e analisar arquivos de texto Unicode. ✅
 * Extrair tabela de frequências a partir do arquivo recebido. ✅
 * Construir árvore de Huffman a partir da tabela de frequências. ✅
 * Gerar tabela de codificação atribuindo códigos binários únicos com base na árvore de Huffman.
 * Exibir a árvore de Huffman e a tabela codificação.
 * Exibir o tamanho do arquivo origina.
 * (Opcional) Salvar arquivo compactado.
 * (Opcional) Descompactar arquivo.

## Algoritimo de Huffman
 1. A codificação de Huffman é uma técnica de compressão de dados sem perdas. O algoritmo funciona em várias etapas principais:
 2. Análise de Frequência: Analisar a frequência de cada caractere no texto de entrada.
  * Construção da Árvore de Huffman:
  * Criar um nó folha para cada caractere e adicioná-lo a uma fila de prioridade baseada na frequência.
  * Combinar os dois nós com as menores frequências para formar um novo nó, cuja frequência é a soma das duas frequências combinadas.
  * Repetir o processo até que haja apenas um nó na fila, que se torna a raiz da árvore de Huffman.
 3. Gerar Códigos Binários: A partir da árvore de Huffman, gerar códigos binários únicos para cada caractere.
 4. Codificação: Substituir cada caractere do texto original pelo seu código binário correspondente.
 5. Decodificação: Para descompactar, o processo inverso é realizado usando a árvore de Huffman.

## Contribuindo
 * João Henrique Menezes de Souza
 * Eric Mota
 
## Instalação

## ?#?#?#?#?#?#?#?#?#?#?