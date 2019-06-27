#ifndef Header_h
#define Header_h

typedef struct TipoItem {
    int Chave;
    char Evento;
    char Especificacao[26];
    int Dia;
    int Mes;
    int Ano;
} TipoItem;

typedef struct Celula_str *Apontador;

typedef struct Celula_str {
    TipoItem Item;
    Apontador Prox;
} Celula;

typedef struct {
    Apontador Primeiro, Ultimo;
} TipoLista;

void FLVazia(TipoLista *Lista);

void Insere(TipoItem x, TipoLista *Lista);

void InsereLinear (TipoItem *A, TipoItem *F, TipoItem *V, TipoItem *O, Apontador Busca, Apontador Busca2);

void Ordena(TipoItem *A, int n);

void PesquisaEvento (TipoItem *P, int t);

int DiasDoMes (int y, int *mes, int x, int m);

void a(int a);

#endif /* Header_h */
