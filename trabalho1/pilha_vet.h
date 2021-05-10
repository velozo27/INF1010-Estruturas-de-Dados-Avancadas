
#define TAM_MAX 100

typedef struct pilha
{
    int topo;
    int vet[TAM_MAX];
} Pilha;

Pilha *pilha_cria(void);
void pilha_push(Pilha *p, int v);
char pilha_pop(Pilha *p);
int pilha_vazia(Pilha *p);
void pilha_libera(Pilha *p);
char pilha_topo(Pilha *p);
void pilha_imprimir(Pilha *p);
