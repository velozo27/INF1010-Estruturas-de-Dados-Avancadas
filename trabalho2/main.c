/******************************************************************************
 Trabalho 2 - EDA INF 1010

*** AUTORES ***
** Lucas Simoes de Almeida - 1712101 **
** Pedro Antonio Tibau Velozo - 812013 **

*******************************************************************************/
#include <stdio.h>
#include "trie.h"

int main()
{
    Trie *t = criaTrie();

    inserePalavra(t, "Joao");
    inserePalavra(t, "Joana");
    inserePalavra(t, "Homen");
    inserePalavra(t, "Homenagem");
    inserePalavra(t, "Bola");
    inserePalavra(t, "Bolao");
    inserePalavra(t, "Carroca");
    inserePalavra(t, "Carro");
    inserePalavra(t, "Careca");
    inserePalavra(t, "Carruagem");

    // Inicio do programa
    printf("Programa Teste Arvore Trie");

    printf("\n---------------------------------\n\n");

    // Apresenta Dicionario
    printf("Dicionario Trie:\n");
    alphabetize(t);

    printf("\n---------------------------------\n\n");

    // Buscar palavra
    char buscar[] = "Carro";
    printf("Buscar palavra: %s\n", buscar);

    if (buscarPalavra(t, buscar))
        printf("palavra '%s' encontrada.\n", buscar);
    else
        printf("nao encontrei a palavra '%s'.\n", buscar);

    printf("\n---------------------------------\n\n");

    // Buscar prefixo
    char buscar_prefixo[] = "Ca";
    printf("Buscar palavras que comecam com: '%s'\n", buscar_prefixo);

    Trie *v = buscarPrefixo(t, buscar_prefixo);
    if (v != NULL)
        alphabetize2(v, "..");

    printf("\n---------------------------------\n\n");

    // Remover palavras e testar busca

    removerPalavra(t, "Carlos");
    removerPalavra(t, "Joao");
    removerPalavra(t, "Joana");
    removerPalavra(t, "Homen");
    removerPalavra(t, "Carroca");

    /* apos a remocao ficam as palavras:
        Bola
        Bolao
        Careca 
        Carro
        Carruagem
        Homenagem
    */

    // Apresenta Dicionario após remoção
    printf("Dicionario Trie Apos Remocao:\n");
    alphabetize(t);

    
    printf("\nBuscar palavra: %s\n", buscar);

    if (buscarPalavra(t, buscar))
        printf("palavra '%s' encontrada.\n", buscar);
    else
        printf("nao encontrei a palavra '%s'.\n", buscar);

    char buscar2[] = "Carroca";
    printf("\nBuscar palavra: %s\n", buscar2);

    if (buscarPalavra(t, buscar2))
        printf("palavra '%s' encontrada.\n", buscar2);
    else
        printf("nao encontrei a palavra '%s'.\n", buscar2);

    liberar(t);

    

    return 0;
}
