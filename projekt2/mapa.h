#ifndef _MAPA_H
#define _MAPA_H

#define size_x 30
#define size_y 30

#define N 5
#define P 2

typedef struct _mapa {
    int x, y;
    char tab[size_x][size_y];
    char *nazwa, *field, *sesja, *kierunek;
    int steps;

    int x1, y1;
    int x2, y2;
    int x3, y3;

    char *pole1;
    char *pole2;
    char *pole3;

} mapa;

typedef struct _dynamiczna{
    char *kierunekd;
    int a, b;
    char **elementy;
    int x1, x2, x3;
    int y1, y2, y3;
    int current_x, current_y;
    int delta_x, delta_y;
    char *field;

} dynamiczna;

void zwolnij_dynamiczna(dynamiczna *d);

void wypisz_info(dynamiczna *d, mapa *m);

dynamiczna *wczytaj();

char tlumacz_podloze(char *pole);

dynamiczna *aktualizuj_mape(char *argument, mapa *m);

dynamiczna *alokuj_mape(int a, int b);

void zapisz_mape(dynamiczna*m);

int check_border(dynamiczna*d);

void wypisz();

void wypiszstan_obrot(mapa *m);

void wypiszstan_dynamiczna(dynamiczna *d);

dynamiczna *offset(dynamiczna *d, mapa *m);

dynamiczna *tworz_mape_poczatek(mapa*m);

dynamiczna *prawo(dynamiczna *stara);

dynamiczna *gora(dynamiczna *stara);

dynamiczna *dol(dynamiczna *stara);

dynamiczna *lewo(dynamiczna *stara);

void doklej_mape(int border);

#endif