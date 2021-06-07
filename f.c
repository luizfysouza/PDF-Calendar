#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

void FLVazia(TipoLista *Lista)
{
    Lista->Primeiro = (Apontador) malloc(sizeof(Celula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

void Insere(TipoItem x, TipoLista *Lista){
    Lista->Ultimo->Prox =(Apontador) malloc(sizeof(Celula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = x;
    Lista->Ultimo->Prox = NULL;
}

void InsereLinear(TipoItem *A, TipoItem *F, TipoItem *V, TipoItem *O, Apontador Busca, Apontador Busca2) {
    int i = 0, j = 0, k = 0, l = 0;
    while (Busca != NULL) {
        switch (Busca->Item.Evento) {
            case 'A':
                A[i] = Busca->Item;
                i++;
                break;
            case 'F':
                F[j] = Busca->Item;
                j++;
                break;
            case 'V':
                V[k] = Busca->Item;
                k++;
                break;
            case 'O':
                O[l] = Busca->Item;
                l++;
                break;
        }
        Busca = Busca->Prox;
    }
    while (Busca2 != NULL) {
        switch (Busca2->Item.Evento) {
            case 'A':
                A[i] = Busca2->Item;
                i++;
                break;
            case 'F':
                F[j] = Busca2->Item;
                j++;
                break;
            case 'V':
                V[k] = Busca2->Item;
                k++;
                break;
            case 'O':
                O[l] = Busca2->Item;
                l++;
                break;
        }
        Busca2 = Busca2->Prox;
    
    }
}

void Ordena(TipoItem *Z, int n){
   // n-=1;
    int i , j, Min ;
    TipoItem x;
    for ( i = 0; i < n; i++){
        Min = i ;
        for ( j = i+1; j < n; j++)
            if (Z[j].Dia < Z[Min].Dia)
                Min = j ;
        x = Z[Min] ;
        Z[Min] = Z[i] ;
        Z[i] = x;
    }
    for (int g = 0; g < n; g++) {
        printf("%c %d %d %d ", Z[g].Evento, Z[g].Dia, Z[g].Mes, Z[g].Ano);
        printf("%s\n", Z[g].Especificacao);
    }
}

void PesquisaEvento (TipoItem *P, int t){
    for (int v=0; v<t; v++){
        printf("%c %d %d %d ", P[v].Evento, P[v].Dia, P[v].Mes, P[v].Ano);
        printf("%s\n", P[v].Especificacao);
    }
}

int DiasDoMes (int y, int *mes, int x, int m){
    int i;
    if (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0))
        mes[1] = 29;
    for (i = 1900; i < y; i++)
        if (i % 4 == 0 && (i % 100 != 0 || i % 400 == 0))
            x += 366;
        else
            x += 365;
    for (i = 0; i < m - 1; i++)
        x += mes[i];
    return x;
}
