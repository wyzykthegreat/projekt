#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

void tworzmape(){
    
    FILE * fout = fopen("mapka.txt", "w+");
    mapa *m;
 
    m = (mapa*) malloc(sizeof(mapa));
    for (int i = 0; i < size_x; i++){
        for (int j = 0; j < size_y; j++){
            m->tab[i][j]= 'x';
            fprintf(fout, "%c ", m->tab[i][j]);
        }
        fprintf(fout, "\n");    
    }
    fclose(fout);
    //free(m);
}

mapa *tłumacz(mapa *m, char *argument) {

    if (strcmp(argument, "move")==0){

        if(strcmp(m->field, "grass")==0){
            m->tab[m->x-1][m->y-1] = 'G'; 
        }
        else if(strcmp(m->field, "sand")==0){
            m->tab[m->x-1][m->y-1] = 'S'; 
        }
    }
    else if (strcmp(argument, "explore")==0){
        if(strcmp(m->pole1, "\"grass\"")==0){
            m->tab[m->x1-1][m->y1-1] = 'G'; 
        }
        else if(strcmp(m->pole1, "\"sand\"")==0){
            m->tab[m->x1-1][m->y1-1] = 'S'; 
        }
        else if(strcmp(m->pole1, "\"wall\"")==0){
            m->tab[m->x1-1][m->y1-1] = 'W'; 
        }
        if(strcmp(m->pole2, "\"grass\"")==0){
            m->tab[m->x2-1][m->y2-1] = 'G'; 
        }
        else if(strcmp(m->pole2, "\"sand\"")==0){
            m->tab[m->x2-1][m->y2-1] = 'S'; 
        }
        else if(strcmp(m->pole2, "\"wall\"")==0){
            m->tab[m->x2-1][m->y2-1] = 'W'; 
        }
        if(strcmp(m->pole3, "\"grass\"")==0){
            m->tab[m->x3-1][m->y3-1] = 'G'; 
        }
        else if(strcmp(m->pole3, "\"sand\"")==0){
            m->tab[m->x3-1][m->y3-1] = 'S'; 
        }
        else if(strcmp(m->pole3, "\"wall\"")==0){
            m->tab[m->x3-1][m->y3-1] = 'W'; 
            }
    }
    return m;
}

mapa *aktualizuj_mape(mapa*m, char *argument) {

    mapa *nowa;
    nowa = malloc(sizeof(mapa));
    FILE * fout = fopen("mapka.txt", "r+");
        for (int i = 0; i < size_x; i++){
            for (int j = 0; j < size_y; j++){
                fscanf(fout, "%c  ", &m->tab[i][j]);
            }
        }
    
    nowa = tłumacz(m, argument);
    fclose(fout);
    return nowa;
}

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

void wypisz() {
    FILE * fout = fopen("mapka.txt", "r+");
    mapa *m;
    m = (mapa*) malloc(sizeof(mapa));

    for (int i = 0; i < size_x; i++){
        for (int j = 0; j < size_y; j++){
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
}

void zwolnij(mapa *m){
    for (int i = 0; i < size_x; i++) 
        free( m->tab[i] );
        free(m->tab);
        free(m);
}
