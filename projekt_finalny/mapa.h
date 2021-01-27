#ifndef _MAPA_H
#define _MAPA_H

#define size_x 30
#define size_y 30

#define N 5     //poczatkowy rozmiar mapy
#define P 2     //poczatkowe polozenie x oraz y 

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_CYAN    "\x1b[36m"

typedef struct _mapa {      //struktura do ktorej przekazywane sa dane z serwera
    int x, y;
    char *nazwa, *field, *sesja, *kierunek;
    int steps;

    int x1, y1;
    int x2, y2;
    int x3, y3;     //polozenia blokow przy komendzie explore

    char *pole1;
    char *pole2;
    char *pole3;    //podloza przy komendzie explore

} mapa;

typedef struct _mapa_dynamiczna{    //struktura mapy 
    char *kierunekd;
    int b;               //wymiar x 
    int a;               //wymiar y
    int **elementy;
    int x1, x2, x3;
    int y1, y2, y3;      //wymiary x oraz y przy komendzie explore
    int current_x, current_y;
    int delta_x, delta_y;
    char *field;

} dynamiczna;

void zwolnij_dynamiczna(dynamiczna *d);
void wypisz_info(dynamiczna *d, mapa *m);

dynamiczna *wczytaj();

int tlumacz_podloze(char *pole);

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