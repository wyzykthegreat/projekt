#ifndef _KOMUNIKACJA_H
#define _KOMUNIKACJA_H
#include "mapa.h"
#include <curl/curl.h>

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp);

void zapisz_dzejsona(char nazwa[], char *wynik);

char * make_request(char *url);

void info(char *token);

void move(char *token);

void explore(char *token);

void reset(char *token);

void right(char *token);

void left(char *token);

mapa *pobierz_info(const char * const dzejson);

mapa *pobierz_info_explore(const char * const dzejson);

void pobierz_info_info(const char * const dzejson);

#endif