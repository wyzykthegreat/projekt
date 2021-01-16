#ifndef _KOMUNIKACJA_H
#define _KOMUNIKACJA_H

typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp);

void zapisz_dzejsona(char nazwa[], char *wynik);

char * make_request(char *url);

#endif