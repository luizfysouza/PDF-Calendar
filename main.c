#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "Header.h"
#include "pdfgen.h"

int main() {
    int lingua;
    printf("Lingua/Language: 0 para portugues, 1 for english\n");
    scanf("%d", &lingua);
    if (lingua==0)
        printf("insira mes e ano: \n");
    if (lingua==1)
        printf("type month and year: \n");
    int eano, emes;
    scanf("%d %d", &emes, &eano);
    char* mesport[] = {"Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
    char* mesing[] = {"January", "February", "Mars", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    if (lingua==0)
        printf("%s %d\n", mesport[emes-1], eano);
    if (lingua==1)
        printf("%s %d\n", mesing[emes], eano);
    TipoItem Eventos;
    TipoLista *Datas = malloc(sizeof(TipoLista));
    TipoLista *datas0 = malloc(sizeof(TipoLista));
    FLVazia(Datas);
    FLVazia(datas0);
    char buffer[100], e[26], a;
    int b, c, x, k = 0; //b e dia, c e mes, x e ano, k chave
    int an=0, fe=0, vi=0, ou=0;
    FILE *file;
    file = fopen("Teste.txt", "r");
    while (fgets(buffer, 100, file) != NULL){
        sscanf(buffer, "%c %i %i %i %[^\n]s", &a, &b, &c, &x, &e);
        if ((c!=emes && c!=0) || (x!=eano && x!=0))
          printf("Evento '%s' nao corresponde a mes ou ano especificado.\n", e);
        else {
          if (a=='A') an++; if (a=='F') fe++; if (a=='V') vi++; if (a=='O') ou++; //conta a qtd de eventos por categoria
          if (b!=0) {
            strcpy(Eventos.Especificacao, e);
            Eventos.Chave = k;
            Eventos.Evento = a;
            Eventos.Dia = b;
            Eventos.Mes = c;
            Eventos.Ano = x;
            Insere(Eventos, Datas);
            k++;
          }
          else { //caso o evento tenha que repetir todo dia (dia=0)
              strcpy(Eventos.Especificacao, e);
              Eventos.Chave = k;
              Eventos.Evento = a;
              Eventos.Dia = b;
              Eventos.Mes = c;
              Eventos.Ano = x;
              Insere(Eventos, datas0);
              k++;
          }
        }
    }
    Apontador Busca;  //coloca os dados da lista em outro vetor
    Busca = Datas->Primeiro->Prox; //iguala ele a lista
    Apontador Busca2;  //coloca os dados da lista em outro vetor
    Busca2 = datas0->Primeiro->Prox; //iguala ele a lista
    TipoItem Aniversarios[an], Feriados[fe], Viagens[vi], Outros[ou];
    InsereLinear (Aniversarios, Feriados, Viagens, Outros, Busca, Busca2);
    
    //abaixo o calculo do dia da semana
    
    int month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char* day[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    char* dia[] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"};
    int d=1, m, y, i;
    y = eano;
    m = emes;
    // correction for leap year - correcao para ano bissexto
    if (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0))
        month[1] = 29;
    for (i = 1900; i < y; i++)
        if (i % 4 == 0 && (i % 100 != 0 || i % 400 == 0))
            d += 366;
        else
            d += 365;
    for (i = 0; i < m - 1; i++)
        d += month[i];
    int contador = 1;
    for (i =0; i<month[m-1]; i++){
        if (lingua==1)
            printf("%d %s\n", contador, day[d % 7]);
        if (lingua==0)
            printf("%d %s\n", contador, dia[d % 7]);
        while (Busca != NULL){
            if (Busca->Item.Dia  == contador){
                if (Busca->Item.Evento=='O')
                    printf("   %s\n", Busca->Item.Especificacao);
                else
                    printf ("   %c %s\n", Busca->Item.Evento, Busca->Item.Especificacao);
            }
            Busca = Busca->Prox;
        }
        while (Busca2 != NULL){
            if (Busca2->Item.Evento=='O')
                printf("   %s\n", Busca2->Item.Especificacao);
            else
                printf("   %c %s\n", Busca2->Item.Evento, Busca2->Item.Especificacao);
            Busca2 = Busca2->Prox;
        }
        Busca = Datas->Primeiro->Prox;
        Busca2 = datas0->Primeiro->Prox;
        contador++;
        d++;
    }
    printf("\n\n");
    
    //ordenacao e pesquisa
    
    printf("Ordenar eventos: 1 para sim, 0 para nao\n");
    int oo, oo1; //opcao de ordenar
    scanf("%d", &oo);
    if (oo){
        printf("Para ordenar na ordem aniversarios, feriados, viagens, outros: 0\nPara ordenar por ordem cronologica de eventos: 1\n");
        scanf("%d", &oo1);
        if (oo1){}
        else {
            Ordena (Aniversarios, an);
            Ordena (Feriados, fe);
            Ordena (Viagens, vi);
            Ordena (Outros, ou);
        }
    }
    char E;
    printf("Para pesquisa por evento, digite A (aniversarios), F (feriados), V (viagens) ou O (outros):\n");
    scanf("%c", &E);
    scanf("%c", &E);
    if (E=='A') PesquisaEvento (Aniversarios, an); if (E=='F') PesquisaEvento (Feriados, fe);
    if (E=='V') PesquisaEvento (Viagens, vi); if (E=='O') PesquisaEvento (Outros, ou);
    printf("fim\n");
    fclose (file);
    
        struct pdf_info info = {
            .creator = "My software",
            .producer = "My software",
            .title = "My document",
            .author = "My name",
            .subject = "My subject",
            .date = "Today"
        };
        struct pdf_doc *pdf = pdf_create(PDF_A4_HEIGHT, PDF_A4_WIDTH, &info);
        pdf_set_font(pdf, "Times-Roman");
        pdf_append_page(pdf);
        pdf_add_jpeg (pdf, NULL, 20, 0, 800, 595, "calendarios/ingles2.jpg");
 //   switch (aux%7){
  //      case 0: aux%7
   // }
        pdf_add_text(pdf, NULL, "1", 16, 27, 410, PDF_BLACK);     //115 eh a dist entre os dias horizontal
        pdf_add_text(pdf, NULL, "2", 16, 142, 410, PDF_BLACK);
        pdf_add_text(pdf, NULL, "10", 16, 27, 340, PDF_BLACK);  //70 eh a dist entre as semanas vertical
        pdf_add_text(pdf, NULL, "1", 16, 27, 530, PDF_BLACK); //primeiro do calendarinho esq
        pdf_add_text(pdf, NULL, "1", 16, 27, 515, PDF_BLACK); //dust vertical entre as semanas do calendarinho eh 15
        pdf_add_text(pdf, NULL, "20", 16, 52, 530, PDF_BLACK); //25 eh a dist horiz no calendarinho
        pdf_add_text(pdf, NULL, "1", 16, 650, 531, PDF_BLACK); // 623 eh a dist entre os 2 calendarinhos primeira posicao
        pdf_add_text(pdf, NULL, "Dezembro 2019", 20, 27, 568, PDF_BLACK); //posicao do mes do calendarinho
        pdf_add_text(pdf, NULL, "Dezembro 2019", 20, 650, 568, PDF_BLACK); //mes do 2 calendarinho
        pdf_add_text(pdf, NULL, "Abril 2019", 35, 300, 515, PDF_BLACK); //posicao do mes grande no centro
        pdf_add_text(pdf, NULL, "ABCDE", 10, 27, 398, PDF_BLACK);
        pdf_save(pdf, "output.pdf");
        pdf_destroy(pdf);
    
    return 0;
    
}
