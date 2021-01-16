#ifndef _MAPA_H
#define _MAPA_H

#define size_x 30
#define size_y 30

typedef struct _mapa {
    int x, y;
    char tab[size_x][size_y];
    char *nazwa, *field, *sesja, *kierunek, *steps;

    int x1, y1;
    int x2, y2;
    int x3, y3;

    char *pole1;
    char *pole2;
    char *pole3;

} mapa;

void tworzmape();

char tlumacz_podloze(char *pole);

mapa *aktualizuj_mape(mapa*m, char *argument);

void nadpisz_mape(mapa*m);

void wypisz();

void wypiszstan(mapa *m);

void zwolnij(mapa *m);

#endif