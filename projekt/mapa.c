#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

void nadpisz_mape(mapa*m){
    FILE * fout = fopen("mapka.txt", "w+");
   
    for (int i = 0; i < size_x; i++){
        for (int j = 0; j < size_y; j++){
            fprintf(fout, "%c ", m->tab[i][j]);
        }
        fprintf(fout, "\n");    
    }
    fclose(fout);
}

void tworzmape(){
    
    mapa *m;
    m = (mapa*) malloc(sizeof(mapa));
    for (int i = 0; i < size_x; i++){
        for (int j = 0; j < size_y; j++){
            m->tab[i][j]= 'x';
        }
    }
    nadpisz_mape(m);
    //free(m);
}

char tlumacz_podloze(char *pole) {
    char znak;
        if(strcmp(pole, "sand")==0){
            znak = 'S';
        }
        else if(strcmp(pole, "grass")==0){
            znak = 'G';
        }
        else if(strcmp(pole, "wall")==0){
            znak = 'W';
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

mapa *aktualizuj_mape(mapa*m, char *argument) {

    FILE * fout = fopen("mapka.txt", "r+");
        for (int i = 0; i < size_x; i++){
            for (int j = 0; j < size_y; j++){
                fscanf(fout, "%c  ", &m->tab[i][j]);
            }
        }
    
    if (strcmp(argument, "move")==0){
        m->tab[size_x-1-m->y][m->x] = tlumacz_podloze(m->field); 
    }
    else if (strcmp(argument, "explore")==0){
        m->tab[size_x-1-m->y1][m->x1] = tlumacz_podloze(m->pole1);
        m->tab[size_x-1-m->y2][m->x2] = tlumacz_podloze(m->pole2);
        m->tab[size_x-1-m->y3][m->x3] = tlumacz_podloze(m->pole3);
    }
    fclose(fout);
    return m;
}

void wypisz() {
    FILE * fout = fopen("mapka.txt", "r+");
    mapa *m;
    m = (mapa*) malloc(sizeof(mapa));

    for (int i = size_x; i > 0; i--){
        for (int j = 0; j < size_x; j++){
            fscanf(fout, "%c  ", &m->tab[i][j]);
            printf("%c ", m->tab[i][j]);
        }
        printf("\n");   
    }
    fclose(fout);
   // free(m);
}

void wypiszstan(mapa *m){
    printf("x = %d\n", m->x); 
    printf("y = %d\n", m->y); 
    printf("Kierunek: %s\n", m->kierunek); 
    printf("Typ podloza: %s\n", m->field);
    printf("\n");
}

void zwolnij(mapa *m){
    for (int i = 0; i < size_x; i++) 
        free( m->tab[i] );
        free(m->tab);
        free(m);
}
