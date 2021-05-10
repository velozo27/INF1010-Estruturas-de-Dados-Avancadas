/*.
Nome:Lucas Simoes de Almeida, Pedro Antonio Tibau Velozo
Matriculas Reespectivamente: 1712101, 1812013
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pilha_vet.h"
#include "arvExp.h"


int atoiPessoal(char *dado)  //Sabe-se que existe a funcao atoi, porem nao estava funcionando em nossas aplicacoes, logo criamos um atoi para adaptar char para int
{
    int save;
    int tot = 0, i = 0;
    for (; i < strlen(dado); i++)
    {
        save = dado[i] - '0';
        tot += save * pow(10, strlen(dado) - i - 1);
    }
    return tot;
}


//A funcao retornaNGrande existe para facilitar a coleta de dados de uma dada string, segue o ex abaixo:
//"10+203" -> Sem essa funcao iriamos coletar caracter a caracter
//"10+203" -> Com essa funcao iriamos coletar o numero ate encontrar um operador ou o caracter finalizador e armazenar em string
//"10+203" -> essa funcao ira retornar a string "10" que podemos armazenar na pilha em um so elemento
char *retornaNGrande(char *dado, int etapa)
{                                          
                                           
    int index_temp = 0;                    
    char *temp = (char *)malloc(10);

    for (; etapa <= strlen(dado); etapa++)
    {
        if (!isOperator(dado[etapa]) && dado[etapa] != '\0')        
        {
            if (dado[etapa] != '(' && dado[etapa] != ')')
            {
                temp[index_temp] = dado[etapa];
                index_temp++;
            }
        }
        else if (isOperator(dado[etapa]))
        {
            temp[index_temp] = '\0';
            return temp;
        }
    }
    temp[index_temp] = '\0';
    return temp;
}

int verifica_precedencia(char c)
{
    /*
    vamos usar a seguinte precedencia de simbolos
    4 => ( )
    3 => ^
    2 => / *
    1 => + - 
    */
    if (c == '(' || c == ')')
        return 4;
    else if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
    {
        return -1;
    }
}


//A funcao infix_to_postfix ira pegar uma equacao com a Notação Convencional(infix) e retonar uma equacao com a Notação Polonesa Inversa(postfix)
//Realizamos essa conversao de infix para postfix atraves do algoritmo Shunting-Yard
Pilha *infix_to_postfix(char *exp_matematica)
{
    Pilha *pilha_operadores = pilha_cria();      // Criamos uma pilha para separar os operadores dos numeros,o que eh necessario no algoritmo de Shunting-Yard
    Pilha *pilha_exp_mat_posfix = pilha_cria();  // Criamos uma pilha para armazenar a equacao completa em (postfix)
    char *temp = (char *)malloc(10);             // Esse temp recebe o resultado da funcao anteriormente comentada retornaNGrande
    // As variaveis declaradas em seguida sao apenas variaveis auxiliares
    char x;                                     
    int armazenaTemp = 0;
    int i = 0;
    while (exp_matematica[i] != '\0')
    {
        if (!isOperator(exp_matematica[i]) && exp_matematica[i] != '\0')  //Verifica-se exp_matematica[i] nao eh operador e nao eh o caracter finalizador
        {
            while (!isOperator(exp_matematica[i]) && exp_matematica[i] != '\0')
            {
                //Caso contrario Se simbolo = '(' entao:
                //Push('(') para pilha;
                if (exp_matematica[i] == '(')
                {
                    x = exp_matematica[i];
                    pilha_push(pilha_operadores, x);
                }

                //Caso contrario Se simbolo = ')' entao:
                else if (exp_matematica[i] == ')')
                {
                    //Enquanto o si­mbolo no topo da pilha for = '(',
                    while (pilha_topo(pilha_operadores) != '(' && !pilha_vazia(pilha_operadores))
                    {
                        //Pop si­mbolo da pilha e insira no buffer de sai­da;
                        char simbolo_da_pilha = pilha_pop(pilha_operadores);
                        pilha_push(pilha_exp_mat_posfix, simbolo_da_pilha);
                    }
                    if (pilha_topo(pilha_operadores) == '(')
                    {
                        pilha_pop(pilha_operadores);
                    }
                }

                else //Caso seja um numero
                {
                    temp = retornaNGrande(exp_matematica, i);
                    i = i + strlen(temp) - 1;
                    armazenaTemp = atoiPessoal(temp);
                    pilha_push(pilha_exp_mat_posfix, armazenaTemp);
                    armazenaTemp = 0;
                }

                i++; //Caminhamos no indice da exp_matematica
            }
        }
        if (isOperator(exp_matematica[i]) && exp_matematica[i] != '\0') //Verifica-se exp_matematica[i] eh operador e nao eh o caracter finalizador
        {
            x = exp_matematica[i]; //Char do operador

            //Verificamos o topo da pilha de operadores caso ele seja um paratenses aberto
            if (x == '(')
            {
                //Nesse caso (x) sempre tera a maior precedencia
                while (!pilha_vazia(pilha_operadores) && (verifica_precedencia(x) >= verifica_precedencia(pilha_topo(pilha_operadores)))) //Apenas verificamos precedencia neste caso para seguir o algoritmo 
                {
                    //Pop(y) da pilha
                    //Adicione(y) no buffer de sai­da;
                    char y = pilha_pop(pilha_operadores);

                    int y_int = y;

                    if (y != '(') // caso x e y sejam parenteses apenas armazenamos os dados, mas nao adicionamos '(' no buffer de sai­da;
                    {
                        pilha_push(pilha_exp_mat_posfix, y_int);
                    }
                }
            }

            else
            {
                 //Enquanto existir um operador (y) no topo da pilha de operadores e (x) for associativo a esquerda sua precedencia for <= a (y)
                while (!pilha_vazia(pilha_operadores) && (verifica_precedencia(x) <= verifica_precedencia(pilha_topo(pilha_operadores))))
                {
                    //Pop(y) da pilha
                    //Adicione(y) no buffer de sai­da;
                    char y = pilha_pop(pilha_operadores);

                    int y_int = y;
                    if (y != '(') 
                    {
                        pilha_push(pilha_exp_mat_posfix, y_int); // Nunca inserimos  '(' no buffer de saida
                    }
    
                }
            }
            //Push(x) para pilha
            pilha_push(pilha_operadores, x);

            i++; //Caminhamos no indice da exp_matematica
        }
    }
    while (!pilha_vazia(pilha_operadores)) //Caso tenha sobrado algo na pilha de operadores inserimos no buffer de saida
    {
        char simbolo = pilha_pop(pilha_operadores);
        int simbolo_int = simbolo;
        pilha_push(pilha_exp_mat_posfix, simbolo_int);
    }

    //Libera pilha
    pilha_libera(pilha_operadores);

    return pilha_exp_mat_posfix;
}

ArvExp *postfix_to_arvore(Pilha *exp_postfix)
{
    ArvExp *raiz_arvore_de_saida = arvExp_cria();
    ArvExp *atual = arvExp_cria();


    char simbolo = pilha_pop(exp_postfix); // Pega o ultimo si­mbolo (a  direita) da notacao postfix,
    raiz_arvore_de_saida = arvExp_insere(raiz_arvore_de_saida, simbolo);//Cria um no para ele e coloque na raiz
    atual = raiz_arvore_de_saida; // Defina o no raiz como no atual.

    while (!pilha_vazia(exp_postfix)) //Para cada elemento da direita para a esquerda (excluindo o ultimo)
    {
        simbolo = pilha_pop(exp_postfix);
        if (!isOperator(simbolo)) //Verificamos se o simbolo nao eh um operador
        {
            arvExp_insere(atual, simbolo);
            if (atual->dir != NULL && atual->esq != NULL) //Caso o no atual nao puder ter mais filhos procure o primeiro pai/avo operador que pode ter mais filhos, defina-o como no atual
            {
                atual = atual->pai;
            }
        }
        else if (isOperator(simbolo))//Verificamos se o simbolo eh um operador
        {
            //Anexe o novo no ao no atual
            if (atual->dir == NULL)
            {
                arvExp_insere(atual, simbolo);
                atual = atual->dir; //Depois defina o novo no como no atual
            }
            else
            {
                arvExp_insere(atual, simbolo);
                atual = atual->esq; //Depois defina o novo no como no atual
            }
        }


    }

    //Libera pilha
    pilha_libera(exp_postfix);

    return raiz_arvore_de_saida;
}

int arv_valorEA(ArvExp *arv)
{
    if (arv == NULL || ((arv->tipo != 0) && (arv->tipo != 1)))
        return 0;

    else if (arv->tipo == 0)
        return arv->valor;

    else
    {
        switch (arv->oper)  //Switch case para saber qual tipo de operador estamos trabalhando
        {
        case '+':
            return arv_valorEA(arv->esq) + arv_valorEA(arv->dir);
            break;

        case '-':
            return arv_valorEA(arv->esq) - arv_valorEA(arv->dir);
            break;

        case '*':
            return arv_valorEA(arv->esq) * arv_valorEA(arv->dir);
            break;

        case '/':
            //Caso denominador seja 0 nao ha erro na expressao
            if (arv_valorEA(arv->dir) == 0)
            {
                printf("\nERRO NA EXPRESSAO DADA (NAO PODE DIVIDIR POR 0)\n\n");
                exit(1);
            }
            //Caso denominador seja diferente de 0
            return arv_valorEA(arv->esq) / arv_valorEA(arv->dir);
            break;

        default:
            break;
        }
    }
    return 0;
}

int main()
{
    char exp_matematica[50];  //Vetor da expressao infix ,que sera um input do usuario
    printf("\nDigite uma expressao matematica: ");
    scanf("%s", exp_matematica); //Input do usuario

    Pilha *pilha_exp_pos_fix = (infix_to_postfix(exp_matematica));//Conversao de infix para postfix, armazenado em pilha

    printf("\nPostfix = ");
    pilha_imprimir(pilha_exp_pos_fix);

    printf("\nArvore de expressao\n");
    ArvExp *arvore = postfix_to_arvore(pilha_exp_pos_fix); //Conversao da pilha contendo o postfix para arvore de expressao, em represetancao aninhada
    arvExp_imprime(arvore);
    printf("\n");

    int resultado_conta = arv_valorEA(arvore);  //Utilizamos da arvore de expressao para calcular o nosso devido resultado

    printf("\nResultado da expressao dada = %d\n\n", resultado_conta);

    return 0;
}
