#ifndef _ODPOWIEDZ_H
#define _ODPOWIEDZ_H
#include "mapa.h"


void zapisz_dzejsona(char nazwa[], char *wynik);

void info(char *token);

void move(char *token);

void explore(char *token);

void reset(char *token);

void right(char *token);

void left(char *token);

mapa *pobierz_info(const char * const dzejson);

mapa *pobierz_info_explore(const char * const dzejson);

mapa *pobierz_info_info(const char * const dzejson);

void ruch(char *token, char *argument);

mapa * otworz_json(char *argument, char buffer[2048]);

#endif