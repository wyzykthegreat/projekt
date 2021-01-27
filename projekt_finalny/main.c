#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"
#include "komunikacja.h"
#include "odpowiedz.h"
#include "bot.h"

int main(int argc, char **argv)
{   
    char *test= argv[1];
    mapa *m;
    dynamiczna *info = NULL;
    info = (dynamiczna*) calloc(1, sizeof(dynamiczna));
    dynamiczna *robocza = NULL;                             //tworzymy struktury pomocnicze do przekazywania do nich elementow 
    robocza = (dynamiczna*) calloc(1, sizeof(dynamiczna));  //zwroconych z API oraz lokalnych w mapie

    int border, i;
	char buffer[2048];
	
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;

    for (i = 2; i< argc; i++){              //petla for do wykonywania odp liczby komend przy wywolywaniu programu
        if(strcmp(argv[i], "start")==0){
            printf("\nStartuje swiat.\n");
            ruch(argv[1], argv[i]);             //wykonujemy odpowiednie zapytanie do serwera
            m = otworz_json(argv[i], buffer);   //przypisujemy do struktury elementy z serwera
            robocza = tworz_mape_poczatek(m);   //tworzymy mape i przypisujemy elementy do struktury
            wypiszstan_dynamiczna(robocza);     //wypisujemy na ekranie informacje o strukturze
            wypisz(robocza);                    //wypisujemy mape na ekranie
            zapisz_mape(robocza);
            zwolnij_dynamiczna(robocza);               //zapisujemy strukture i mape do pliku i zwalniamy
        }
        else if(strcmp(argv[i], "reset")==0){
            printf("\nResetuje swiat.\n");
            ruch(argv[1], argv[i]);
            m = otworz_json(argv[i], buffer);
            robocza = tworz_mape_poczatek(m);
            wypiszstan_dynamiczna(robocza);
            wypisz(robocza);
            zapisz_mape(robocza);  
            zwolnij_dynamiczna(robocza);         //komenda dziala identycznie jak powyzsza
        }
        else if(strcmp(argv[i], "info")==0){
            printf("\nInformacje o swiecie:\n");
            ruch(argv[1], argv[i]);
            m = otworz_json(argv[i], buffer);
            robocza = wczytaj();
            wypisz_info(robocza, m);
            zapisz_mape(robocza);   
            zwolnij_dynamiczna(robocza);    //komenda jak powyzej
        }
        else if(strcmp(argv[i], "move")==0){
            printf("\nWykonuje ruch do przodu.\n");
            ruch(argv[1], argv[i]);             //wykonujemy odpowiednie zapytanie do serwera
            m = otworz_json(argv[i], buffer);   //przypisujemu jsona do struktury
            robocza = aktualizuj_mape(argv[i], m);  //aktualizujemy strukture mapy dynamicznej
            border = check_border(robocza);         //sprawdzamy czy stoimy na krawedzi mapy

                if(border ==0){
                    wypiszstan_dynamiczna(robocza);
                    wypisz(robocza);                //jezeli nie mapa sie wypisuje i zapisuje do pliku
                }

            zapisz_mape(robocza);

                if(border != 0){
                    doklej_mape(border);
                }

            zwolnij_dynamiczna(robocza);            // jezeli tak, doklejamy mape z odpowiedniej strony, wypisujemy i zapisujemy
        }                                           // po czym zwalniamy strukture
        else if(strcmp(argv[i], "explore")==0){
            printf("\nInformacje o trzech blokach przed czolgiem, kolejno od lewej do prawej:\n");
            ruch(argv[1], argv[i]);
            m = otworz_json(argv[i], buffer);
            robocza = aktualizuj_mape(argv[i], m);
            wypisz(robocza);
            zapisz_mape(robocza);
            zwolnij_dynamiczna(robocza);    //dziala tak jak poprzednia komenda z wyjatkiem sprawdzania krawedzi mapy
        }
        else if(strcmp(argv[i], "right")==0){
            printf("\nObracam w prawo.\n");
            ruch(argv[1], argv[i]);
            m = otworz_json(argv[i], buffer);
            wypiszstan_obrot(m);            
        }
        else if(strcmp(argv[i], "left")==0){
            printf("\nObracam w lewo.\n");
            ruch(argv[1], argv[i]);
            m = otworz_json(argv[i], buffer);
            wypiszstan_obrot(m);            //dwie powyzsze komendy sluza do wyswietlania informacji o kierunku ruchu
        }
        else if(strcmp(argv[i], "bot")==0){
            
            printf("\nRozpoczynam poznawanie świata.\n");
            start_bot(argv[1], buffer);         //przywracamy swiat do rozmiarow 5x5 nie resetujac go
            info = info_bot(argv[1], buffer);   //pobieramy info o obecnym  polozeniu i zapisujemy je do struktury

            szukaj_sciany(argv[1], buffer);     //idziemy botem do przodu szukajac sciany

            krecenie(argv[1], buffer, info->current_x, info->current_y);    //rozpoczynamy algorytm obchodzenia planszy ktory zawiera odpowiedni warunek konczacy

            zwolnij_dynamiczna(robocza);
            zwolnij_dynamiczna(info);
            free(test);
            free(buffer);   //zwalniamy obie struktury, buffera i test  
        }
    }  
    printf("\n");
    return 0;
}