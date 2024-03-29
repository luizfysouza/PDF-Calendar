#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "Header.h"
#include "pdfgen.h"
#include <locale.h>

int main() {
    setlocale (LC_ALL, "Portuguese"); //alfabeto da lingua portuguesa
    
    //delcaracao de todas as variaveis, arranjos, etc
    int i;
    int lingua;
    char arquivo[31]; //string para nome do arquivo
    int eano, emes; //mes e ano escolhidos
    // strings com nomes dos meses nas duas linguas
    char* mesport[] = {"Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
    char* mesing[] = {"January", "February", "Mars", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    TipoItem Eventos; // cria item (Eventos) para a lista
    TipoLista *Datas = malloc(sizeof(TipoLista)); //Datas eh a lista encadeada com os eventos
    TipoLista *datas0 = malloc(sizeof(TipoLista)); // datas0 eh a lista encadeada com eventos de dia 0
    char buffer[100], e[26], a; // buffer, string com especificacao, caractere do tipo de evento (A F V O)
    int b, c, x, k = 0; //b e dia, c e mes, x e ano, k chave
    int an=0, fe=0, vi=0, ou=0;
    int xx2=0, yy2=0; //auxiliares para mexer na impressao do pdf
    Apontador Busca, Busca2;  //para colocar os dados da lista em outro vetor
    int month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //# de dias/mes para calculo do dia da semana
    //nomes dos dias da semana nas duas linguas
    char* day[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    char* dia[] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"};
    int d=1, m, y; //dias, mes e ano para calculod os dias da semana
    int contador = 1, aux = d, aux2, aux3, aux4 = d%7, aux5, lulu, lulu2, luiz, luiz2, xx, yy, j, variavel; //variaveis auxiliares para manipulacao do pdf
    //strings para colocar nomes dos meses no pdf com espaço e ano
    char str2[15], str3[] = {" "}, strm[20]; //mes escolhido
    char str2a[15], str3a[] = {" "}, strma[20];//mes anterior
    char str2p[15], str3p[] = {" "}, strmp[20];//mes proximo
    int oo, oo1; //ordenar: opcao de ordenar
    int pp, pp1, dpp; char E; //pesquisa: pp se vai ou nao pesquisar, pp1 pra tipo de pesquisa, dpp dia pesquisa, E tipo evento
    //arranjos dos meses para o pdf
    int month2[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int month3[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // esses outros 2 months pro caso de dar conflito em algum mes, por causa do bissexto
    int da = 1, dp = 1, ma = m - 1, mp = m + 1, yp=y, ya=y; //variaveis para os meses no pdf
    int cc; //variavel para esolhas no pdf
    char num[4]; //aqui vai ficar o dia em numero do mes, pq o programa so aceita string pra printar no pdf
    
    
    
    printf("Lingua/Language: 0 para portugues, 1 for english\n");
    scanf("%d", &lingua);
    if (lingua==0)
        printf("insira nome do arquivo de eventos.txt: \n");
    if (lingua==1)
        printf("type event file's name.txt: \n");
    scanf("%s", &arquivo);
    if (lingua==0)
        printf("insira mes e ano: \n");
    if (lingua==1)
        printf("type month and year: \n");
    scanf("%d %d", &emes, &eano);
    
    if (lingua==0)
        printf("%s %d\n", mesport[emes-1], eano);
    if (lingua==1)
        printf("%s %d\n", mesing[emes-1], eano);
    FLVazia(Datas);
    FLVazia(datas0);
    
    FILE *file;
    file = fopen(arquivo, "r");
    while (fgets(buffer, 100, file) != NULL){
        sscanf(buffer, "%c %i %i %i %[^\n]s", &a, &b, &c, &x, &e);
        if ((c!=emes && c!=0) || (x!=eano && x!=0))
          if (lingua == 0)
              printf("Evento '%s' nao corresponde a mes ou ano especificado.\n", e);
          else
              printf("Event '%s' does not match month or year chosen.\n", e);
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
    
    Busca = Datas->Primeiro->Prox; //iguala ele a lista principal
    Busca2 = datas0->Primeiro->Prox; //iguala ele a lista dos dias 0
    TipoItem Aniversarios[an], Feriados[fe], Viagens[vi], Outros[ou]; // cria itens de arranjos especificos para cada evento - lista linear
    InsereLinear (Aniversarios, Feriados, Viagens, Outros, Busca, Busca2); //insere esses itens em uma lista linear
    
    //abaixo o calculo do dia da semana
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
    contador = 1, aux = d, aux4 = d%7;
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
    printf("\n");
    
    //strings para nome do mes no pdf
    sprintf(str2, "%i", eano); //coloca o ano (int) numa string
    if (lingua == 0) {
        strcpy(strm, mesport[emes - 1]);    //coloca o a string do mes numa string em pt ou en
    } else
        strcpy(strm, mesing[emes - 1]);
    strcat(strm, str3);  //concatena a string do espaco junto com a da string do mes
    strcat(strm, str2);  //concatena a string criada contendo o ano com a do mes
    if (lingua == 0) {
        if (emes==1){
            strcpy(strma, mesport[11]);    //coloca o a string do mes numa string em pt ou en
            sprintf(str2a, "%i", eano-1); //coloca o ano (int) numa string
            strcat(strma, str3a);
            strcat(strma, str2a);
        }
        else {
            sprintf(str2a, "%i", eano);
            strcpy(strma, mesport[emes - 2]);    //coloca o a string do mes numa string em pt ou en
            strcat(strma, str3a);  //concatena a string do espaco junto com a da string do mes
            strcat(strma, str2a);  //concatena a string criada contendo o ano com a do mes
            
        }
        if (emes==12){
            strcpy(strmp, mesport[0]);    //coloca o a string do mes numa string em pt ou en
            sprintf(str2p, "%i", eano+1); //coloca o ano (int) numa string
            strcat(strmp, str3p);
            strcat(strmp, str2p);
        }
        else {
            sprintf(str2p, "%i", eano);
            strcpy(strmp, mesport[emes]);    //coloca o a string do mes numa string em pt ou en
            strcat(strmp, str3p);  //concatena a string do espaco junto com a da string do mes
            strcat(strmp, str2p);
        }
    }
    else {
        if (emes==1){
            strcpy(strma, mesing[11]);    //coloca o a string do mes numa string em pt ou en
            sprintf(str2a, "%i", eano-1); //coloca o ano (int) numa string
            strcat(strma, str3a);
            strcat(strma, str2a);
        }
        else {
            sprintf(str2a, "%i", eano);
            strcpy(strma, mesing[emes - 2]);    //coloca o a string do mes numa string em pt ou en
            strcat(strma, str3a);  //concatena a string do espaco junto com a da string do mes
            strcat(strma, str2a);  //concatena a string criada contendo o ano com a do mes
        }
        if (emes==12){
            strcpy(strmp, mesing[0]);    //coloca o a string do mes numa string em pt ou en
            sprintf(str2p, "%i", eano+1); //coloca o ano (int) numa string
            strcat(strmp, str3p);
            strcat(strmp, str2p);
        }
        else {
            sprintf(str2p, "%i", eano);
            strcpy(strmp, mesing[emes]);    //coloca o a string do mes numa string em pt ou en
            strcat(strmp, str3p);  //concatena a string do espaco junto com a da string do mes
            strcat(strmp, str2p);
        }
    }
    
    
    //ordenacao
    if (lingua == 0)
        printf("Ordenar eventos: 1 para sim, 0 para nao\n");
    else
        printf("Sort events: 1 for yes, 0 for no\n");
    scanf("%d", &oo);
    if (oo){
        if (lingua == 0)
            printf("Para ordenar na ordem aniversarios, feriados, viagens, outros: 0\nPara ordenar por ordem cronologica de eventos: 1\n");
        else printf("To sort by birthdays, holidays, trips, others: 0\nTo sort events by chronological order: 1\n");
        scanf("%d", &oo1);
        if (oo1){
            Busca = Datas->Primeiro->Prox;
            Busca2 = datas0->Primeiro->Prox;
            while (Busca2 != NULL){
                printf("%c 0 %d %d ", Busca2->Item.Evento, Busca2->Item.Mes, Busca2->Item.Ano);
                printf("%s\n", Busca2->Item.Especificacao);
                Busca2 = Busca2->Prox;
            }
            for (i=1;i<=month[m-1]; i++){
                while (Busca != NULL){
                    if (i == Busca->Item.Dia){
                        printf("%c %d %d %d ", Busca->Item.Evento, Busca->Item.Dia, Busca->Item.Mes, Busca->Item.Ano);
                        printf("%s\n", Busca->Item.Especificacao);
                    }
                    Busca = Busca->Prox;
                }
            Busca = Datas->Primeiro->Prox;
            Busca2 = datas0->Primeiro->Prox;
            }
        }
        else {
            Ordena (Aniversarios, an);
            Ordena (Feriados, fe);
            Ordena (Viagens, vi);
            Ordena (Outros, ou);
        }
    }
    
    //pesquisa
    if (lingua==0)
        printf("Pesquisar eventos: 0 para nao; 1 para sim\n");
    if (lingua==1)
        printf("Search events: 0 for no; 1 for yes\n");
    scanf("%d", &pp);
    if (pp){
        if (lingua == 0)
            printf("Para pesquisar por dia, digite 0.\nPara pesquisar por tipo de evento, digite 1.\n");
        else
            printf("To search by especific day, type 0\nTo search by type of event, type 1.\n");
        scanf("%d", &pp1);
        if (pp1==0){
            if (lingua == 0)
                printf("Digite o dia do mes escolhido que deseja pesquisar: ");
            else
                printf("Type the day to be searched: ");
            scanf("%d", &dpp);
            if (dpp==0 || dpp > month[m-1]){
                if (lingua == 0)
                    printf("Dia digitado invalido.\n");
                else
                    printf("Typed day not valid\n");
            }
            else {
                Busca = Datas->Primeiro->Prox;
                for (i=1;i<=month[m-1]; i++){
                    while (Busca != NULL){
                        if (Busca->Item.Dia == dpp){
                            printf("%c %d %d %d ", Busca->Item.Evento, Busca->Item.Dia, Busca->Item.Mes, Busca->Item.Ano);
                            printf("%s\n", Busca->Item.Especificacao);
                        }
                        Busca = Busca->Prox;
                    }
                }
            }
        }
        else {
            if (lingua == 0)
                printf("Para pesquisa por evento, digite A (aniversarios), F (feriados), V (viagens) ou O (outros):\n");
            else
                printf("To search by event, type A (birthdays), F (holidays), V (trips) ou O (others):\n");
            scanf("%c", &E);
            scanf("%c", &E);
            if (E=='A') PesquisaEvento (Aniversarios, an); if (E=='F') PesquisaEvento (Feriados, fe);
            if (E=='V') PesquisaEvento (Viagens, vi); if (E=='O') PesquisaEvento (Outros, ou);
        }
    }
        fclose (file); //encerram-se manipulacoes com arquivo de texto
    
    //fim da ordenacao e pesquisa
    printf("\n\n");
    
    //retorna os apontadores para o comeco
    Busca = Datas->Primeiro->Prox;
    Busca2 = datas0->Primeiro->Prox;
    
    //calculos para o pdf
    
    //aqui pega os 2 outros meses: anterior e proximo
    da = 1, dp = 1, ma = m - 1, mp = m + 1, yp=y, ya=y;
    if (m==12){
        yp = y+1;
        mp=1;
    }
    if (m==1){
        ya = y-1;
        ma = 12;
    }
        
    //mes anterior
    if (ya % 4 == 0 && (ya % 100 != 0 || ya % 400 == 0))
        month2[1] = 29;
    for (i = 1900; i < ya; i++)
        if (i % 4 == 0 && (i % 100 != 0 || i % 400 == 0))
            da += 366;
        else
            da += 365;
    for (i = 0; i < ma - 1; i++)
        da += month2[i];
    
    //mes proximo
    if (yp % 4 == 0 && (yp % 100 != 0 || yp % 400 == 0))
        month3[1] = 29;
    for (i = 1900; i < yp ;i++)
        if (i % 4 == 0 && (i % 100 != 0 || i % 400 == 0))
            dp += 366;
        else
            dp += 365;
    for (i = 0; i < mp - 1; i++)
        dp += month3[i];
    
    luiz2 = da%7; luiz = dp%7;
    
    //criacao do arquivo pdf
    
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
    
    //escolhas para o calendario
    
    if (lingua==0){
        printf("Calendario com mes anterior presente: digite 1\nCalendario com mes posterior presente: digite 2\nSomente o mes desejado: digite 3\nCalendario com mes anterior e posterior: digite 4\n");
        scanf("%d", &cc);
        switch (cc) {
            case 1:{
                pdf_add_jpeg (pdf, NULL, 20, 0, 800, 595, "calendarios/port1e.jpg");
                pdf_add_text(pdf, NULL, strma, 20, 27, 568, PDF_BLACK);
                break;
            }
            case 2:{
                pdf_add_jpeg (pdf, NULL, 20, 0, 800, 595, "calendarios/port1.jpg");
                pdf_add_text(pdf, NULL, strmp, 20, 650, 568, PDF_BLACK);
                break;
            }
            case 3:{
                pdf_add_jpeg (pdf, NULL, 20, 0, 800, 595, "calendarios/port.jpg");
                break;
            }
            case 4:{
                pdf_add_jpeg (pdf, NULL, 20, 0, 800, 595, "calendarios/port2.jpg");
                pdf_add_text(pdf, NULL, strma, 20, 27, 568, PDF_BLACK);
                pdf_add_text(pdf, NULL, strmp, 20, 650, 568, PDF_BLACK);
                break;
            }
            default:
                break;
        }
    }
    else{
        printf("Calendar with previous month: type 1\nCalendar with next month: type 2\nOnly given month: type 3\nBoth preivous and next months: type 4\n");
        scanf("%d", &cc);
        switch (cc) {
            case 3:{
                pdf_add_jpeg (pdf, NULL, 20, 0, 800, 595, "calendarios/ingles.jpg");
                break;
            }
            case 1:
                pdf_add_jpeg (pdf, NULL, 20, 0, 800, 595, "calendarios/ingles1e.jpg");
                pdf_add_text(pdf, NULL, strma, 20, 27, 568, PDF_BLACK);
                break;
            case 2:
                pdf_add_jpeg (pdf, NULL, 20, 0, 800, 595, "calendarios/ingles1.jpg");
                pdf_add_text(pdf, NULL, strmp, 20, 650, 568, PDF_BLACK);
                break;
            case 4:
                pdf_add_jpeg (pdf, NULL, 20, 0, 800, 595, "calendarios/ingles2.jpg");
                pdf_add_text(pdf, NULL, strma, 20, 27, 568, PDF_BLACK);
                pdf_add_text(pdf, NULL, strmp, 20, 650, 568, PDF_BLACK);
                break;
            default:
                break;
        }
    }
    
    Busca = Datas->Primeiro->Prox;
    Busca2 = datas0->Primeiro->Prox;
    
    aux5 = aux%7;
    aux = 6 - (aux4%7), aux2 = 6 - d % 7, contador = 1;
    // 6 - d&7 eh o numero de dias que falta pra fechar a semana
    //se o 1 dia for segunda, por ex, d%7 vai ser 1, entao vao faltar 5 dias pra fechar a semana
    //se o 1 dia for sexta, d&7 vai ser 5, entao 6-5=1, vai faltar 1 dia pra fechar a semana
    
    sprintf(num, "%i", contador);  //transforma o int em string, o programa so aceita printar string, usa asc 2
    xx = 27 + (aux5 * 115), yy = 410; // 27+aux*115 pega quantos dias da semana jah se passaram na 1 linha e multiplica a distancia vertical entre as semanas por ela
    
    for (i = aux5; i <= 6; i++) {  //esse for aqui pega do 6-d&7, que eh o numero correspondente ao 1 dia do mes, e vai ate o 6, que seria o sabado
        //ai, se comecar no domingo, por exemplo, printa 1 vez soh, pq d&7 seria 6, que eh o correspondente ao domingo
        lulu=yy-15;
        lulu2=yy-15;
        while (Busca != NULL){
            if (Busca->Item.Dia  == contador){
                if (Busca->Item.Evento != 'O'){
                    switch (Busca->Item.Evento) {
                        case 'A':
                            pdf_add_jpeg (pdf, NULL, xx, lulu-3, 15, 12, "icones/A.jpg");
                            break;
                        case 'F':
                            pdf_add_jpeg (pdf, NULL, xx, lulu-3, 15, 12, "icones/F.jpg");
                            break;
                        case 'V':
                            pdf_add_jpeg (pdf, NULL, xx, lulu-3, 15, 12, "icones/v.jpg");
                            break;
                    }
                    pdf_add_text(pdf, NULL,  Busca->Item.Especificacao, 10, xx+18, lulu, PDF_BLACK);
                }
                else
                    pdf_add_text(pdf, NULL,  Busca->Item.Especificacao, 10, xx, lulu, PDF_BLACK);
                lulu-=15;
            }
            Busca = Busca->Prox;
        }
        while (Busca2 != NULL){
            if (Busca2->Item.Evento != 'O'){
                switch (Busca2->Item.Evento) {
                    case 'A':
                        pdf_add_jpeg (pdf, NULL, xx, lulu-3, 15, 12, "icones/A.jpg");
                        break;
                    case 'F':
                        pdf_add_jpeg (pdf, NULL, xx, lulu-3, 15, 12, "icones/F.jpg");
                        break;
                    case 'V':
                        pdf_add_jpeg (pdf, NULL, xx, lulu-3, 15, 12, "icones/v.jpg");
                        break;
                }
                pdf_add_text(pdf, NULL,  Busca2->Item.Especificacao, 10, xx+15, lulu, PDF_BLACK);
            }
            else
                pdf_add_text(pdf, NULL,  Busca2->Item.Especificacao, 10, xx, lulu, PDF_BLACK);
            Busca2 = Busca2->Prox;
            lulu-=15;
        }
        Busca = Datas->Primeiro->Prox;
        Busca2 = datas0->Primeiro->Prox;
        pdf_add_text(pdf, NULL, num, 16, xx, 410, PDF_BLACK);
        xx += 115, contador++; //corrige o x pra ir pra proxima parte da tabela e aumenta o contador, q eu voltei pra 1 ali em cima, pra printar os dias
        sprintf(num, "%i", contador); //ai aqui troca o valor da string que printa no pdf pra contador++, entao iria do dia 1 pro dia 2, por ex
    }
    contador--; //decrementa pq ele incrementa no final do for de cima, mesmo nao usando nada
    variavel = -1;
    for (i = contador; i < month[m - 1]; i++) {
        yy -= 70.5;
        xx = 27; //reseta o x a cada 7 vezes, troca de linha
        if (contador < month[m-1]) //eixar a ultima linha em branco em certos casos
            variavel++;
        for (j = 0; j < 7; j++) { //esse for aqui imprime em sequencia na mesma linha
            if (contador < month[m-1]){
                contador++;
                sprintf(num, "%i", contador);
                pdf_add_text(pdf, NULL, num, 16, xx, yy, PDF_BLACK);
                lulu=yy-15;
                lulu2=yy-15;
                while (Busca != NULL){
                    if (Busca->Item.Dia  == contador){
                        if (Busca->Item.Evento != 'O'){
                            switch (Busca->Item.Evento) {
                                case 'A':
                                    pdf_add_jpeg (pdf, NULL, xx, lulu-3, 15, 12, "icones/A.jpg");
                                    break;
                                case 'F':
                                    pdf_add_jpeg (pdf, NULL, xx, lulu-3, 15, 12, "icones/F.jpg");
                                    break;
                                case 'V':
                                    pdf_add_jpeg (pdf, NULL, xx, lulu-3, 15, 12, "icones/v.jpg");
                                    break;
                            }
                            pdf_add_text(pdf, NULL,  Busca->Item.Especificacao, 10, xx+18, lulu, PDF_BLACK);
                        }
                        else
                            pdf_add_text(pdf, NULL,  Busca->Item.Especificacao, 10, xx, lulu, PDF_BLACK);
                        lulu-=15;
                    }
                    Busca = Busca->Prox;
                }
                while (Busca2 != NULL){
                    if (Busca2->Item.Evento != 'O'){
                        switch (Busca2->Item.Evento) {
                            case 'A':
                                pdf_add_jpeg (pdf, NULL, xx, lulu-3, 15, 12, "icones/A.jpg");
                                break;
                            case 'F':
                                pdf_add_jpeg (pdf, NULL, xx, lulu-3, 15, 12, "icones/F.jpg");
                                break;
                            case 'V':
                                pdf_add_jpeg (pdf, NULL, xx, lulu-3, 15, 12, "icones/v.jpg");
                                break;
                        }
                        pdf_add_text(pdf, NULL,  Busca2->Item.Especificacao, 10, xx+15, lulu, PDF_BLACK);
                    }
                    else
                        pdf_add_text(pdf, NULL,  Busca2->Item.Especificacao, 10, xx, lulu, PDF_BLACK);
                    Busca2 = Busca2->Prox;
                    lulu-=15;
                }
                Busca = Datas->Primeiro->Prox;
                Busca2 = datas0->Primeiro->Prox;
                xx += 114;
                xx2 = xx;
                yy2=yy;
            }
        }

    }
    xx = 27;
     contador = month2[ma-1] - aux4 +1;
    aux4++;
     for (i = 1; i<aux4; i++ ){
     sprintf (num, "%i", contador);
     pdf_add_text(pdf, NULL, num, 16, xx, 410 , PDF_ARGB(0x80, 0, 0, 0	));
         xx += 114;
     contador++;
     }
    
    if (d%7 !=  0){
        for (i = 1; i<=aux2+1; i++){
            sprintf (num, "%i", i);
            pdf_add_text(pdf, NULL, num, 16, xx2, yy2 , PDF_ARGB(0x80, 0, 0, 0	));
            xx2 += 114;
        }
        if (yy2!=55){
            yy2-=70.5;
            xx2=27;
            for (j=0; j<7; j++){
                sprintf (num, "%i", i);
                pdf_add_text(pdf, NULL, num, 16, xx2, yy2 , PDF_ARGB(0x80, 0, 0, 0	));
                xx2 += 114;
                i++;
            }
        }
    }
    else{
            yy2-=70.5;
            xx2=27;
            for (j=1; j<=7; j++){
                sprintf (num, "%i", j);
                pdf_add_text(pdf, NULL, num, 16, xx2, yy2 , PDF_ARGB(0x80, 0, 0, 0	));
                xx2 += 114;
            }
    }
    pdf_add_text(pdf, NULL, strm, 35, 300, 515, PDF_BLACK); //nome do mes

    
    if (cc==4 || cc==1){
        contador = 1, xx=27 + (luiz2 * 25), yy=530;
        for (i = luiz2; i <= 6; i++) {  //esse for aqui pega do 6-d&7, que eh o numero correspondente ao 1 dia do mes, e vai ate o 6, que seria o sabado
        //ai, se comecar no domingo, por exemplo, printa 1 vez soh, pq d&7 seria 6, que eh o correspondente ao domingo
            sprintf(num, "%i", contador);
            pdf_add_text(pdf, NULL, num, 16, xx, yy, PDF_ARGB(0x80, 0, 0, 0	));
            xx += 25, contador++; //corrige o x pra ir pra proxima parte da tabela e aumenta o contador, q eu voltei pra 1 ali em cima, pra printar os dias
            sprintf(num, "%i", contador); //ai aqui troca o valor da string q eu to printando no pdf pra contador++, entao iria do dia 1 pro dia 2, por ex
        }
        contador--;
        for (i = contador; i < month2[ma - 1]; i++) {
            yy -= 15;
            xx = 27; //reseta o x a cada 7 vezes, troca de linha
            if (contador < month2[ma-1]) //aqui eh pra fazer aquilo q vc disse de deixar a ultima linha em branco em certos casos
            //depois podemos fazer, se variavel < = 3, nao imprime nada do proximo mes, pq ai so vai ter a 1 linha do for de cima + 3 dessas
                variavel++;
            for (j = 0; j < 7; j++) { //esse for aqui imprime em sequencia na mesma linha
                if (contador < month2[ma-1]){
                    contador++;
                    sprintf(num, "%i", contador);
                    pdf_add_text(pdf, NULL, num, 16, xx, yy, PDF_ARGB(0x80, 0, 0, 0	));
                    xx += 25;
                }
            }
        }
    }
    
    
    if (cc==4 || cc==2){
    contador = 1, xx=650 + (luiz * 25), yy=530;
    for (i = luiz; i <= 6; i++) { 
        sprintf(num, "%i", contador);
        pdf_add_text(pdf, NULL, num, 16, xx, yy, PDF_ARGB(0x80, 0, 0, 0	));
        xx += 25, contador++;
        sprintf(num, "%i", contador);
    }
    contador--;
    for (i = contador; i < month3[mp - 1]; i++) {
        yy -= 15;
        xx = 650;
        if (contador < month3[mp-1])
            variavel++;
        for (j = 0; j < 7; j++) {
            if (contador < month3[mp-1]){
                contador++;
                sprintf(num, "%i", contador);
                pdf_add_text(pdf, NULL, num, 16, xx, yy, PDF_ARGB(0x80, 0, 0, 0	));
                xx += 25;
            }
        }
    }
    }
    
        pdf_save(pdf, "output.pdf");
        pdf_destroy(pdf);
    
    return 0;
    
}
