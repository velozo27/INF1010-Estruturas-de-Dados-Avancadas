struct trie
{
    char letra;
    int termino;

    struct trie *filhos[26];
    int ocupacao;
};

typedef struct trie Trie;

Trie *criaNo(char v);

Trie *criaTrie();
void inserePalavra(Trie *t, char *palavra);
int buscarPalavra(Trie *t, char *palavra);
Trie *buscarPrefixo(Trie *t, char *palavra);
void removerPalavra(Trie *t, char *palavra);

void alphabetize(Trie *t);
void alphabetize2(Trie *t, char str[]);

void liberar(Trie *t);