#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"
#include "komunikacja.h"
#include "odpowiedz.h"
#include "bot.h"

dynamiczna *info_bot(char *test, char buffer[2048]){
  
    mapa *m;
    dynamiczna *info = NULL;
    info = (dynamiczna*) calloc(1, sizeof(dynamiczna));

    ruch(test, "info");
    m = otworz_json("info", buffer);
    info = wczytaj();
        
    return info;                //funkcja pobierajaca info i zwracajaca strukture z informacjami
}

void start_bot(char* test, char buffer[2048]){

    mapa *m;
    dynamiczna *robocza = NULL;
    robocza = (dynamiczna*) calloc(1, sizeof(dynamiczna));

    ruch(test, "start");             
    m = otworz_json("start", buffer);   
    robocza = tworz_mape_poczatek(m);  
    wypiszstan_dynamiczna(robocza);     
    wypisz(robocza);                   
    zapisz_mape(robocza);
    zwolnij_dynamiczna(robocza);
}

void move_bot(char* test, char buffer[2048]){
    mapa *m;
    dynamiczna *robocza = NULL;
    robocza = (dynamiczna*) calloc(1, sizeof(dynamiczna));
    int border;

    ruch(test, "move");             
    m = otworz_json("move", buffer); 
    robocza = aktualizuj_mape("move", m); 
    border = check_border(robocza);      
        if(border ==0){
            wypiszstan_dynamiczna(robocza);
            wypisz(robocza);          
    
        }
    zapisz_mape(robocza);
        if(border != 0){
            doklej_mape(border);
        }
    zwolnij_dynamiczna(robocza);            //funkcja robiaca tylko i wylacznie ruch do przodu potrzbna do kolejnych funkcji
}

dynamiczna *explore_bot(char* test, char buffer[2048]){

    mapa *m;
    dynamiczna *robocza = NULL;
    robocza = (dynamiczna*) calloc(1, sizeof(dynamiczna));

    ruch(test, "explore");
    m = otworz_json("explore", buffer);
    robocza = aktualizuj_mape("explore", m);
    wypisz(robocza);
    zapisz_mape(robocza);

    return robocza;                                 //tworzymy strukture, wykonujemy zapytanie do serwera i zwracamy strukture
}   

void szukaj_sciany(char* test, char buffer[2048]){

    dynamiczna *robocza = NULL;
    robocza = (dynamiczna*) calloc(1, sizeof(dynamiczna));

    do
    {
        move_bot(test, buffer);                     //zaczynamy ruchem do przodu

        robocza = explore_bot(test, buffer);        //sprawdzamy po kazdym ruch co przed nami

    }while (robocza->elementy[robocza->y2][robocza->x2] !=3);       //jezeli sciana to wychodzimy z  petli i zwalniamy strukture
    
    zwolnij_dynamiczna(robocza);
}

dynamiczna *krecenie(char* test, char buffer[2048], int x, int y){

    dynamiczna *robocza = NULL;
    robocza = (dynamiczna*) calloc(1, sizeof(dynamiczna));

    dynamiczna *robocza1 = NULL;
    robocza1 = (dynamiczna*) calloc(1, sizeof(dynamiczna));
        
        do  
        {
            ruch(test, "left");         

            robocza1 = explore_bot(test, buffer);       //zaczynamy krecenie w lewo i sprawdzamy co przed nami 

            if((robocza1->x2 == x) && (robocza1->y2 == y)){     //patrzymy czy doszedl do punktu wyjscia, jezeli tak robimy 2 ostatnie ruchy i konczymy cala funkcję
                
                move_bot(test, buffer);                     

                explore_bot(test, buffer);

                ruch(test, "right");                       

                move_bot(test, buffer); 

                char *emotikona = "😃";
                printf("Koniec! %s\n", emotikona);
                
                return 0;
            }
            else                                    

            if(robocza1->elementy[robocza1->y2][robocza1->x2] ==3){

                krecenie(test, buffer, x, y);
                return robocza1;
            }                                           //jezeli sciana wracamy do samego poczatku
            else 
                
            move_bot(test, buffer);                     //jezeli nie sciana algorytm leci dalej

            ruch(test, "right");                        //ruch w prawo

            move_bot(test, buffer);                     // "walimy" w sciane

            robocza = explore_bot(test, buffer);        //jezeli jednak nie "przywalilismy" tylko przeszlismy dalej patrzymy co przed nami

        }while(robocza->elementy[robocza->y2][robocza->x2] !=1);    //jezaeli nie jest to sciana to wychodzimy z petli

        
        move_bot(test, buffer);  //robimy  dwa razy ruch i o brot w prawo i wracamy do poczatku funkcji
        explore_bot(test, buffer);

        ruch(test, "right");

        move_bot(test, buffer);

        ruch(test, "right");       

        zwolnij_dynamiczna(robocza);

        krecenie(test, buffer, x, y);    

        return robocza1;
}

