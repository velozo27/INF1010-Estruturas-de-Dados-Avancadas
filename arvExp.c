#include <stdio.h>
#include <stdlib.h>
#include "arvExp.h"


int isOperator(char c) //Verifica se o caracter c eh um dos operadores
{
    if (c == '+' || c == '-' ||
        c == '*' || c == '/' ||
        c == '^')
        return 1;
    return 0;
}

ArvExp *arvExp_cria()
{
    return NULL;
}

ArvExp *cria_filho(ArvExp *pai, char oper)
{
    ArvExp *no = (ArvExp *)malloc(sizeof(ArvExp));
    int armazenaV = oper;
    no->tipo = isOperator(oper);
    if (no->tipo == 0)  //Caso seja um numero
    {
        no->valor = armazenaV;
    }
    else   //Caso seja um operador
    {
        no->valor = 0;
    }
    no->oper = oper;
    no->pai = pai;
    no->esq = no->dir = NULL;
    return no;
}

ArvExp *arvExp_insere(ArvExp *r, char oper)
{
    if (r == NULL)//Caso primeiro no, criacao de raiz
        return cria_filho(r, oper);
    else if (r->tipo == 1) //Se a raiz for um operador
    {
        if (r->dir == NULL)
            r->dir = cria_filho(r, oper);
        else if (r->esq == NULL)
        {
            r->esq = cria_filho(r, oper);
        }
    }
    return r;
}

void arvExp_imprime(ArvExp *a)
{
    if (a != NULL)
    {
        if (a->tipo == 1) //Se a for um operador
            printf("(%c ", a->oper);
        else              //Se a for um numero
            printf("(%d ", a->valor);
        arvExp_imprime(a->esq);
        arvExp_imprime(a->dir);
        printf(")");
    }
    else
        printf("() ");
}