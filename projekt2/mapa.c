#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

dynamiczna *wczytaj(){
    FILE * fin = fopen("save.txt", "r+");
    dynamiczna *m = (dynamiczna*) malloc(sizeof(dynamiczna));

    fscanf(fin, "%d %d\n", &m->a, &m->b);
    fscanf(fin, "%d %d\n", &m->delta_x, &m->delta_y);
    fscanf(fin, "%d %d\n", &m->current_x, &m->current_y);

    m->elementy = (char**) calloc(m->a, sizeof(char*));
        for (int i = 0; i < m->a; i++){
            m->elementy[i] = (char*) calloc(m->b, sizeof(char));
        }

    for (int i = 0; i < m->a; i++){
        for (int j = 0; j < m->b; j++){
            fscanf(fin, "%c ", &m->elementy[m->a-1-i][j]);
        }    
    }

    fclose(fin);
    return m;
}

void zapisz_mape(dynamiczna*m){
    FILE * fout = fopen("save.txt", "w+");

    fprintf(fout, "%d %d\n", m->a, m->b);
    fprintf(fout, "%d %d\n", m->delta_x, m->delta_y);
    fprintf(fout, "%d %d\n", m->current_x, m->current_y);

    for (int i = 0; i < m->a; i++){
        for (int j = 0; j < m->b; j++){
            fprintf(fout, "%c ", m->elementy[m->a-1-i][j]);
        }
        fprintf(fout, "\n");   
    }

    fclose(fout);
}

void wypisz(dynamiczna*d) {

    for (int i = 0; i < d->a; i++){
        for (int j = 0; j < d->b; j++){
            printf("%c ", d->elementy[d->a-1-i][j]);
        }
        printf("\n");   
    }
}

void wypiszstan_obrot(mapa *m){
    printf("Kierunek: %s\n", m->kierunek); 
    printf("Typ podloza: %s\n", m->field);
    printf("\n");
}

void wypiszstan_dynamiczna(dynamiczna *m){
    printf("x = %d\n", m->current_x); 
    printf("y = %d\n", m->current_y); 
    printf("\n");
}

void wypisz_info(dynamiczna *d, mapa *m){
        printf("Nazwa świata: %s\n", m->nazwa); 
        printf("x = %d\n", m->x - d->delta_x); 
        printf("y = %d\n", m->y - d->delta_y); 
        printf("Typ podloza: %s\n", m->field); 
        printf("Obecna sesja: %s\n", m->sesja); 
        printf("Kierunek: %s\n", m->kierunek); 
        printf("Liczba krokow: %d\n", m->steps-2);
}

dynamiczna *offset(dynamiczna*d, mapa *m){
        
    d->delta_x = m->x - P;
    d->delta_y = m->y - P;

    return d;
}

dynamiczna *alokuj_mape(int a, int b){

    dynamiczna *d = (dynamiczna*) malloc(sizeof(dynamiczna));

    d->elementy = (char**) malloc(sizeof(char*) * (a+1));
        for(int i = 0; i < a; i++){
            d->elementy[i] = (char*) malloc(sizeof(char) * (b+1));
            for(int j = 0; j < b; j++){
            d->elementy[i][j]  = 'x';
            }
        }
    return d;
}

dynamiczna *tworz_mape_poczatek(mapa*m){

    dynamiczna *d= alokuj_mape(N, N);

    d->a = N; // wartosci y
    d->b = N; //wartosci x

    offset(d, m);
    d->current_x = P;
    d->current_y = P;

    d->elementy[d->a-1-d->current_y][d->current_x] = tlumacz_podloze(m->field); 
    d->kierunekd = m->kierunek;
    d->field = m->field;

    return d;
}

dynamiczna *aktualizuj_mape(char *argument, mapa* m) {

    dynamiczna *nowa =(dynamiczna*)malloc(sizeof(dynamiczna));
    nowa = wczytaj();

    nowa->current_x = m->x - nowa->delta_x;
    nowa->current_y = m->y - nowa->delta_y;
    nowa->x1 = m->x1- nowa->delta_x;
    nowa->x2 = m->x2- nowa->delta_x;
    nowa->x3 = m->x3- nowa->delta_x;
    nowa->y1 = m->y1 - nowa->delta_y;
    nowa->y2 = m->y2 - nowa->delta_y;
    nowa->y3 = m->y3 - nowa->delta_y;

    if(strcmp(argument, "move") == 0){
        nowa->elementy[nowa->current_y][nowa->current_x] = tlumacz_podloze(m->field); 
    }
    else if (strcmp(argument, "explore")==0){
        nowa->elementy[nowa->y1][nowa->x1] = tlumacz_podloze(m->pole1);
        nowa->elementy[nowa->y2][nowa->x2] = tlumacz_podloze(m->pole2);
        nowa->elementy[nowa->y3][nowa->x3] = tlumacz_podloze(m->pole3);
    }

    nowa->kierunekd = m->kierunek;
    nowa->field = m->field;

    return nowa;
}

dynamiczna *prawo(dynamiczna *stara){

    dynamiczna *nowa = alokuj_mape(stara->a, 2*stara->b);

    nowa->a = stara->a; //wymiar y
    nowa->b = 2*stara->b; //wymiar x
    int i, j;

    
    for(int i = 0; i < nowa->a; i++){
        for(int j = 0; j < nowa->b; j++){
            if(j<stara->a){
                nowa->elementy[i][j] = stara->elementy[i][j];
            }
            // else{
            //     nowa->elementy[i][j] = 'x'; 
            // }
        }
    }

    nowa->delta_x = stara->delta_x;
    nowa->delta_y = stara->delta_y;

    nowa->kierunekd = stara->kierunekd;
    nowa->field = stara->field;
    
    nowa->current_x = stara->current_x;
    nowa->current_y = stara->current_y;

    return nowa;
}

dynamiczna *gora(dynamiczna *stara){

    dynamiczna *nowa = alokuj_mape(2*stara->a, stara->b);

    nowa->a = 2*stara->a; //wymiar y
    nowa->b = stara->b; //wymiar x
    int i, j;

    for(i = 0; i < nowa->a; i++){
        for(j = 0; j < nowa->b; j++){
            if(i<stara->a){
                nowa->elementy[i][j] = stara->elementy[i][j];
            }    
            // else{
            //     nowa->elementy[i][j] = 'x';
            // }
        }
    }

    nowa->delta_x = stara->delta_x;
    nowa->delta_y = stara->delta_y;

    nowa->kierunekd = stara->kierunekd;
    nowa->field = stara->field;

    nowa->current_x = stara->current_x;
    nowa->current_y = stara->current_y;

    return nowa;
}

dynamiczna *dol(dynamiczna *stara){

    dynamiczna *nowa = alokuj_mape(2*stara->a, stara->b);
    nowa->a = 2*stara->a; //wymiar y
    nowa->b = stara->b; //wymiar x
    int i, j;

    for(int i = 0; i < nowa->a; i++){
        for(int j = 0; j < nowa->b; j++){
            if(i>=stara->a){
                nowa->elementy[i][j] = stara->elementy[i-stara->a][j];
            }
            // else{
            //     nowa->elementy[i][j] = 'x'; 
            // }
        }
    }

    nowa->delta_x = stara->delta_x;
    nowa->delta_y = stara->delta_y- stara->a;

    nowa->current_x = stara->current_x;
    nowa->current_y = stara->current_y + stara->a;

    nowa->kierunekd = stara->kierunekd;
    nowa->field = stara->field;

    return nowa;
}

dynamiczna *lewo(dynamiczna *stara){

    dynamiczna *nowa = alokuj_mape(stara->a, 2*stara->b);
    nowa->a = stara->a; //wymiar y
    nowa->b = 2*stara->b; //wymiar x
    int i, j;

    for(int i = 0; i < nowa->a; i++){
        for(int j = 0; j < nowa->b; j++){
            if(j>=stara->a){
                nowa->elementy[i][j] = stara->elementy[i][j- stara->b];
            }
            // else{
            //     nowa->elementy[i][j] = 'x'; 
            // }
        }
    }

    nowa->delta_x = stara->delta_x - stara->b;
    nowa->delta_y = stara->delta_y;

    nowa->current_x = stara->current_x + stara->b;
    nowa->current_y = stara->current_y;   

    nowa->kierunekd = stara->kierunekd;
    nowa->field = stara->field;

    return nowa;
}

char tlumacz_podloze(char *pole) {

    char znak;

        if(strcmp(pole, "sand")==0){
            znak = 'S';
        }
        else if(strcmp(pole, "grass")==0){
            znak = 'G';
        }
        else if(strcmp(pole, "\"wall\"")==0){
            znak = 'W';
        }
        else if(strcmp(pole, "\"grass\"")==0){
            znak = 'G';
        }
        else if(strcmp(pole, "\"sand\"")==0){
            znak = 'S';
        }

    return znak;
}

int check_border(dynamiczna*d){

    if ((d->current_y == 0) && (d->kierunekd = (char*) 'S')){
        return 1;
    }
    if ((d->current_y == d->a-1) && (d->kierunekd = (char*) 'N')){
        return 2;
    }
    if ((d->current_x == 0) && (d->kierunekd = (char*) 'W')){
        return 3;
    }
    if ((d->current_x == d->b-1) && (d->kierunekd = (char*) 'E')){
        return 4;
    }
    else
        return 0;
    
}

void doklej_mape(int border){

    dynamiczna *wczytana = (dynamiczna*) malloc(sizeof(dynamiczna));
    dynamiczna *doklejona = (dynamiczna*) malloc(sizeof(dynamiczna));

    if(border == 1){
        wczytana = wczytaj();
        doklejona = dol(wczytana);
        wypiszstan_dynamiczna(doklejona);
        wypisz(doklejona);
        zapisz_mape(doklejona);
    }
    else if(border == 2){
        wczytana = wczytaj();
        doklejona = gora(wczytana);
        wypiszstan_dynamiczna(doklejona);
        wypisz(doklejona);
        zapisz_mape(doklejona);
    }
    else if(border == 3){
        wczytana = wczytaj();
        doklejona = lewo(wczytana);
        wypiszstan_dynamiczna(doklejona);
        wypisz(doklejona);
        zapisz_mape(doklejona);
    }
    else if(border == 4){
        wczytana = wczytaj();
        doklejona = prawo(wczytana);
        wypiszstan_dynamiczna(doklejona);
        wypisz(doklejona);
        zapisz_mape(doklejona);
    }

    zwolnij_dynamiczna(wczytana);
    zwolnij_dynamiczna(doklejona);
}

void zwolnij_dynamiczna(dynamiczna*d){

    for (int i = 0; i < d->a; i++)
        free(d->elementy[i]);
    free(d->elementy);
    free(d);
}
