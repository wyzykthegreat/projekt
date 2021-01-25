#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"
#include "komunikacja.h"
#include "dzejson.h"

int main(int argc, char **argv)
{   
    char *test= argv[1];
    mapa *m;
    dynamiczna *robocza;

    int border, i;
	char buffer[2048];
	
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;

    for (i = 2; i< argc; i++){
        if(strcmp(argv[i], "start")==0){
            printf("\nStartuje swiat.\n");
            ruch(argv[1], argv[i]);
            m = otworz_json(argv[i], buffer);
            robocza = tworz_mape_poczatek(m);
            wypiszstan_dynamiczna(robocza);
            wypisz(robocza);
            zapisz_mape(robocza);
        }
        if(strcmp(argv[i], "reset")==0){
            printf("\nResetuje swiat.\n");
            ruch(argv[1], argv[i]);
            m = otworz_json(argv[i], buffer);
            robocza = tworz_mape_poczatek(m);
            wypiszstan_dynamiczna(robocza);
            wypisz(robocza);
            zapisz_mape(robocza);
        }
        if(strcmp(argv[i], "info")==0){
            printf("\nInformacje o swiecie:\n");
            ruch(argv[1], argv[i]);
            m = otworz_json(argv[i], buffer);
            robocza = wczytaj();
            wypisz_info(robocza, m);
            zapisz_mape(robocza);
        }
        if(strcmp(argv[i], "move")==0){
            printf("\nWykonuje ruch do przodu.\n");
            ruch(argv[1], argv[i]);
            m = otworz_json(argv[i], buffer);
            robocza = aktualizuj_mape(argv[i], m);
            border = check_border(robocza);
                if(border ==0){
                    wypiszstan_dynamiczna(robocza);
                    wypisz(robocza);
                }
            zapisz_mape(robocza);
                if(border != 0){
                    doklej_mape(border);
                }
            zwolnij_dynamiczna(robocza);
        }
        if(strcmp(argv[i], "explore")==0){
            printf("\nInformacje o trzech blokach przed czolgiem, kolejno od lewej do prawej:\n");
            ruch(argv[1], argv[i]);
            m = otworz_json(argv[i], buffer);
            robocza = aktualizuj_mape(argv[i], m);
            wypisz(robocza);
            zapisz_mape(robocza);
            zwolnij_dynamiczna(robocza);
        }
        if(strcmp(argv[i], "right")==0){
            printf("\nObracam w prawo.\n");
            ruch(argv[1], argv[i]);
            m = otworz_json(argv[i], buffer);
            wypiszstan_obrot(m);
        }
        if(strcmp(argv[i], "left")==0){
            printf("\nObracam w lewo.\n");
            ruch(argv[1], argv[i]);
            m = otworz_json(argv[i], buffer);
            wypiszstan_obrot(m);
        }
    }  
    printf("\n");
    return 0;
}