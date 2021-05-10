typedef struct avrExp
{
    int tipo;
    int valor;
    char oper;
    struct avrExp *esq;
    struct avrExp *dir;
    struct avrExp *pai;
} ArvExp;
// Tipo = 0 : operando
// Tipo = 1 : operador

ArvExp *arvExp_cria(void);

ArvExp *cria_filho(ArvExp *pai, char oper);

ArvExp *arvExp_insere(ArvExp *r, char val);

void arvExp_imprime(ArvExp *a);

int isOperator(char c);