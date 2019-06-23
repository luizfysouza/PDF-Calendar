#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

void FLVazia(TipoLista *Lista) {
    Lista->Primeiro = (Apontador) malloc(sizeof(Celula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

void Insere(TipoItem x, TipoLista *Lista) {
    Lista->Ultimo->Prox = (Apontador) malloc(sizeof(Celula));
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
    while (Busca2 != NULL){
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
   /* TipoItem key;
    int ji;
    for (int ad = 1; ad<i; ad++){
        key.Dia = A[ad].Dia;
        ji = ji-1;
        while (ji >= 0 && A[ji].Dia > key.Dia){
            A[ji+1] = A[ji];
            ji = ji-1;
        }
        A[ji+1] = key;
    }*/
    for (int g = 0; g < i; g++) {
        printf("%c %d %d %d \n", A[g].Evento, A[g].Dia, A[g].Mes, A[g].Ano);
        printf("%s\n", A[g].Especificacao);
    }
}
