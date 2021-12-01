#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "trie.h"

#define TAM 26 // numero de letras no alfabeto

// retorna 1 se c for minusculo, 0 se nao
int char_eh_minusculo(char c)
{
    return (c >= 'a' && c <= 'z');
}

Trie *criaNo(char v)
{
    /* Cria nó da árvore */

    Trie *no_novo = (Trie *)malloc(sizeof(Trie));

    // inicialmente os 26 filhos (que representam as letras do alfabeto)
    // do no_novo serao NULL
    for (int i = 0; i < TAM; i++)
    {
        no_novo->filhos[i] = NULL;
    }

    // estou arbitrando que termino = 1 representa o msm que o $
    // ,ou seja, eh o termino de uma palavra
    // logo termino = 0 ocorre quando nao eh o termino
    no_novo->termino = 0;

    // insiro o caracter passado no campo letra do no
    no_novo->letra = v;

    // chutando
    no_novo->ocupacao = 0;

    return no_novo;
}

Trie *criaTrie()
{
    Trie *t = criaNo(' ');
    t->termino = 1;
    return t;
}

void inserePalavra(Trie *t, char *palavra)
{
    /* implementar a insercao de palavras */

    // quero inserir um caracter da palavra no No *t, para isso preciso
    // descobrir em que posicao do vetor t->filhos vou botar
    // as letras dessa palavra;
    // utilizarei uma funcao "hash" que retorna o indice do
    // vetor no qual a palavras deve ser inserida
    // hash = (int) char da palavra passada - (int) 'a'
    // ex:  (int) 'a' - (int) 'a' = 0
    //      (int) 'b' - (int) 'a' = 1
    // OBS: o (int) nao eh necessario mas ajuda a entender

    int palavra_tam = strlen(palavra);

    t->termino = 0;

    // para cada char da palavra
    for (int i = 0; i < palavra_tam; i++)
    {
        char caracter_analisado = palavra[i];

        int index_letra_no_vetor;
        if (char_eh_minusculo(caracter_analisado))
        {
            index_letra_no_vetor = (int)caracter_analisado - (int)'a';
        }
        else
        {
            index_letra_no_vetor = (int)caracter_analisado - (int)'A';
        }

        // com o index calculado posso verificar se a posicao
        // do vetor ja esta ocupado ou nao
        // - se estiver ocupado quer dizer que alguma palavra foi
        // inserida previamente com essa letra
        // - caso nao esteja ocupado, nenhuma palavra foi inserida
        // com essa letra ainda, entao devo inserir na arvore
        if (t->filhos[index_letra_no_vetor] == NULL)
        {
            // quer dizer que nao ha caracter nessa posicao do vetor
            // vou criar e inserir No novo aqui
            Trie *no_novo = criaNo(caracter_analisado);

            no_novo->ocupacao = index_letra_no_vetor;

            // se for o ultimo char da palavra tenho que indicar que eh o fim desse galho
            if (i == palavra_tam - 1)
            {
                no_novo->termino = 1;
            }

            t->filhos[index_letra_no_vetor] = no_novo;
            t = no_novo;
        }

        else
        {
            // quer dizer que ja tem um char nessa posicao do vetor do No
            // apenas ando pelos Nos da arvore
            t = t->filhos[index_letra_no_vetor];

            if (i == palavra_tam - 1)
            {
                t->termino = 1;
            }
        }
    }
}

int buscarPalavra(Trie *t, char *palavra)
{
    /* implementar a busca de palavras */

    // ideia: percorrer a arvore e ver se a palavra existe

    int palavra_tam = strlen(palavra);

    for (int i = 0; i < palavra_tam; i++)
    {
        char caracter_analisado = palavra[i];

        int index_letra_no_vetor;
        if (char_eh_minusculo(caracter_analisado))
        {
            index_letra_no_vetor = (int)caracter_analisado - (int)'a';
        }
        else
        {
            index_letra_no_vetor = (int)caracter_analisado - (int)'A';
        }

        if (i == palavra_tam - 1)
        {
            // estamos na ultima letra da palavra,
            // temos que ver se eh terminal

            t = t->filhos[index_letra_no_vetor]; // passa t para o no da letra

            if (t->termino == 1)
            {
                return 1;
            }
        }

        if (t->filhos[index_letra_no_vetor] != NULL)
        {
            t = t->filhos[index_letra_no_vetor]; // passa t para o no da letra
        }
        else
        {
            // palavra nao existe
            return 0;
        }
    }
    return 0; // nunca chega aqui, mas da warning se nao tiver
}

Trie *buscarPrefixo(Trie *t, char *palavra)
{
    int palavra_tam = strlen(palavra);

    for (int i = 0; i < palavra_tam; i++)
    {
        char caracter_analisado = palavra[i];

        int index_letra_no_vetor;
        if (char_eh_minusculo(caracter_analisado))
        {
            index_letra_no_vetor = (int)caracter_analisado - (int)'a';
        }
        else
        {
            index_letra_no_vetor = (int)caracter_analisado - (int)'A';
        }

        if (i == palavra_tam - 1)
        {
            t = t->filhos[index_letra_no_vetor]; // passa t para o no da letra e o retorna
            return t;
        }

        if (t->filhos[index_letra_no_vetor] != NULL)
        {
            t = t->filhos[index_letra_no_vetor]; // passa t para o no da letra
        }
        else
        {
            return NULL;
        }
    }
    return NULL;
}

void removerPalavra(Trie *t, char *palavra)
{
    int palavra_tam = strlen(palavra);

    int contador = 0;

    int *vetor_posicao_terminais = (int *)malloc(sizeof(int) * palavra_tam); //{0,0,0,1,0,1,0,0,1}

    Trie *raiz = t;

    for (int i = 0; i < palavra_tam; i++)
    {
        char caracter_analisado = palavra[i];

        int index_letra_no_vetor;
        if (char_eh_minusculo(caracter_analisado))
        {
            index_letra_no_vetor = (int)caracter_analisado - (int)'a';
        }
        else
        {
            index_letra_no_vetor = (int)caracter_analisado - (int)'A';
        }

        if (t->filhos[index_letra_no_vetor] != NULL)
        {
            if (t->filhos[index_letra_no_vetor]->termino == 1)
            {
                vetor_posicao_terminais[i] = 1;
                contador++;
            }
            else
            {
                vetor_posicao_terminais[i] = 0;
            }
        }

        t = t->filhos[index_letra_no_vetor]; // passa t para o no da letra
    }

    t = raiz; // volto t para raiz da arvore

    // percorrendo a palavra de novo
    for (int i = 0; i < palavra_tam; i++)
    {
        char caracter_analisado = palavra[i];

        int index_letra_no_vetor;
        if (char_eh_minusculo(caracter_analisado))
        {
            index_letra_no_vetor = (int)caracter_analisado - (int)'a';
        }
        else
        {
            index_letra_no_vetor = (int)caracter_analisado - (int)'A';
        }

        if (t->filhos[index_letra_no_vetor] != NULL)
        {
           
        }
    }
}

void alphabetize2(Trie *t, char prefixo[])
{
    int i;

    if (t->termino == 1)
    {
        printf("%s\n", prefixo);
    }

    for (i = 0; i < TAM; ++i)
    {
        if (t->filhos[i] != NULL)
        {
            char ch = t->filhos[i]->letra;

            int l = strlen(prefixo);
            if (l > 0)
            {
                char novo_prefixo[l];
                strcpy(novo_prefixo, prefixo);
                strncat(novo_prefixo, &ch, 1);
                alphabetize2(t->filhos[i], novo_prefixo);
            }
            else
            {
                char novo_prefixo[] = {ch, '\0'};
                alphabetize2(t->filhos[i], novo_prefixo);
            }
        }
    }
}

void alphabetize(Trie *t)
{
    char prefixo[] = "";
    alphabetize2(t, prefixo);
}

void liberar(Trie *t)
{

    int i;
    for (i = 0; i < TAM; ++i)
        if (t->filhos[i] != NULL)
            liberar(t->filhos[i]);

    free(t);
}