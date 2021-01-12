#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../cJSON/cJSON.h"

typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;

typedef struct _mapa {
    int x, y;
    char tab[20][20];
     char *nazwa;
           char *field;
            char *sesja; 
           char *kierunek;
           char *steps;

    int x1, y1;
    int x2, y2;
    int x3, y3;

    char *pole1;
    char *pole2;
    char *pole3;

} mapa;

void zapiszmape(){
    
    FILE * fout = fopen("mapka.txt", "w+");
    mapa *m;
 
    m = (mapa*) malloc(sizeof(mapa));
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            m->tab[i][j]= 'x';
            fprintf(fout, "%c ", m->tab[i][j]);
        }
        fprintf(fout, "\n");    
    }
    fclose(fout);
    //free(m);
}

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp)
{
    /* to jest rzeczywista liczba bajtów przekazanych przez curl */
    size_t realsize = size * nmemb;

    /* jawnie konwertujemy (void*) na naszą strukturę, bo wiemy, że będziemy ją tutaj otrzymywać */
    Memory *mem = (Memory *) userp;

    char *ptr = NULL;

    /* Sprawdzamy czy pierwszy raz wywołujemy funkcję i trzeba zaalokować pamięć po raz pierwszy,
    czy trzeba zrobić reallokację (która kopiuje automatycznie starą zawartość w nowe miejsce) */
    if (mem->response != NULL)
        ptr = realloc(mem->response, mem->size + realsize + 1);
    else
        ptr = malloc(mem->size + realsize + 1);

    if (ptr == NULL)
        return 0; /* brak pamięci! */

    /* teraz zapamiętujemy nowy wskaźnik i doklejamy na końcu dane przekazane przez curl w 
       obszarze pamięci wskazywanym przez data */
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0; // to na końcu dodajemy bo to w końcu string, i zawsze powinien się skończyć!

    return realsize;
}

void zapisz(char nazwa[], char *wynik){
    FILE * fout = fopen(nazwa, "w");
    fprintf(fout, "%s\n", wynik);
    fclose(fout);
}

char * make_request(char *url){
   
    CURL *curl;
    CURLcode res;
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        // curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

        /* to jest funkcja 'callback', która będzie wywołana przez curl gdy odczyta on kawałek danych
       ta funkcja musi mieć wywołanie zgodne z wymaganiami, które możesz sprawdzić tutaj:
       https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        /* to jest adress struktury, który będzie przekazywany do naszej funkcji 'callback',
       do tej struktury nasz funkcja 'callback' będzie dopisywać wynik */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        /* Wykonaj zapytanie 'synchronicznie', to znaczy następna linijka kodu nie wykona się
       dopóki nie nadejdzie odpowiedź z serwera. */
        res = curl_easy_perform(curl);

        /* Sprawdzamy czy wystapił jakis błąd? */
        if (res != CURLE_OK)
            fprintf(stderr, "Błąd! curl_easy_perform() niepowodzenie: %s\n", curl_easy_strerror(res));
        else
        {
            zapisz("a.json", chunk.response);
        }

        /* zawsze po sobie sprzątaj */
        free(chunk.response);
        curl_easy_cleanup(curl);
    }
    return 0;
}

void info(char *token) {
    char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/qwerty_2";

    make_request(url1);
    //free(url1);
}

void move(char *token) {
     char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/qwerty_2";

    make_request(url1);
    // free(url1);
}

void explore(char *token) {
     char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/qwerty_2";

    make_request(url1);
    //free(url1);
}

void reset(char *token) {
     char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/reset/qwerty_2";

    make_request(url1);
    //free(url1);
}

void right(char *token) {
     char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/qwerty_2/right";

    make_request(url1);
   // free(url1);
}

void left(char *token) {
     char *url1 = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/qwerty_2/left";

    make_request(url1);
   // free(url1);
}

mapa *aktualizuj(mapa*m) {

FILE * fout = fopen("mapka.txt", "r");

    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            fscanf(fout, "%c  ", &m->tab[i][j]);
            
         }
    }  
    if(strcmp(m->field, "grass")==0){
     m->tab[m->x-1][m->y-1] = 'G'; 
    }
    else if(strcmp(m->field, "sand")==0){
     m->tab[m->x-1][m->y-1] = 'S'; 
    }
   
    fclose(fout);
    return m;
}

mapa *aktualizuj_explore(mapa*m) {

FILE * fout = fopen("mapka.txt", "r");

    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            fscanf(fout, "%c  ", &m->tab[i][j]);
            
         }
    } 
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
   
    fclose(fout);
    return m;
}

void zapiszmape2(mapa*m){
    FILE * fout = fopen("mapka.txt", "w+");
   
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            
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
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            fscanf(fout, "%c  ", &m->tab[i][j]);
            printf("%c  ", m->tab[i][j]);
        }
        printf("\n");    
    }
    fclose(fout);
   // free(m);
}

mapa *supports_full_hd(const char * const monitor)
{
    const cJSON *resolution = NULL;
    const cJSON *payload = NULL;
    const cJSON *status = NULL;
    mapa *m;

    cJSON *monitor_json = cJSON_Parse(monitor);
    if (monitor_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }      
    }
    status = cJSON_GetObjectItemCaseSensitive(monitor_json, "status");
    payload = cJSON_GetObjectItemCaseSensitive(monitor_json, "payload");
    {    
        cJSON *current_x = cJSON_GetObjectItemCaseSensitive(payload, "current_x");
        cJSON *current_y = cJSON_GetObjectItemCaseSensitive(payload, "current_y");
        cJSON *field_type = cJSON_GetObjectItemCaseSensitive(payload, "field_type");
        cJSON *direction = cJSON_GetObjectItemCaseSensitive(payload, "direction");

    m = malloc(sizeof(mapa));
    m->x=current_x->valueint;
    m->y=current_y->valueint;
    m->field=field_type->valuestring;
    m->kierunek=direction->valuestring;

    m->field = (char*) malloc(sizeof(char) * strlen( field_type->valuestring));
    strcpy(m->field, field_type->valuestring);
     m->kierunek = (char*) malloc(sizeof(char) * strlen( direction->valuestring));
    strcpy(m->kierunek, direction->valuestring);
    }
            // printf("x = %d\n", m->x); 
            // printf("y = %d\n", m->y); 
            // printf("y = %s %s\n", m->field, m->kierunek); 
            

    cJSON_Delete(monitor_json);         
    return m;
}

void wypiszstan(mapa *m){
            printf("x = %d\n", m->x); 
            printf("y = %d\n", m->y); 
            printf("Kierunek: %s\n", m->kierunek); 
            printf("Typ podloza: %s\n", m->field);    
}

mapa *supports_full_hd_explore(const char * const monitor)
{
    const cJSON *resolution = NULL;
    const cJSON *payload = NULL;
    const cJSON *status = NULL;
    const cJSON *lista = NULL;
    mapa *m;

    cJSON *monitor_json = cJSON_Parse(monitor);
    if (monitor_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
      
    }
    status = cJSON_GetObjectItemCaseSensitive(monitor_json, "status");
    payload = cJSON_GetObjectItemCaseSensitive(monitor_json, "payload");
    lista = cJSON_GetObjectItemCaseSensitive(payload, "list");
    {
        cJSON_ArrayForEach(resolution, lista){
                cJSON *x = cJSON_GetObjectItemCaseSensitive(resolution, "x");
                cJSON *y = cJSON_GetObjectItemCaseSensitive(resolution, "y");
                cJSON *field_type = cJSON_GetObjectItemCaseSensitive(resolution, "type");
                printf("Blok:\n"); 
                printf("x = %d\n", x->valueint); 
                printf("y = %d\n", y->valueint); 
                printf("Typ podloza: %s\n", field_type->valuestring);        
            }
            payload = cJSON_GetObjectItemCaseSensitive(monitor_json, "payload");

    m = malloc(sizeof(mapa));
            m->pole1=cJSON_Print(payload->child->child->child->next->next);
            m->x1=atoi(cJSON_Print(payload->child->child->child));    
            m->y1=atoi(cJSON_Print(payload->child->child->child->next));  
            // printf("%s\n", m->pole1);
            // printf("%d\n", m->x1); 
            // printf("%d\n", m->y1); 
            m->pole2=cJSON_Print(payload->child->child->next->child->next->next);
            m->x2=atoi(cJSON_Print(payload->child->child->next->child));  
            m->y2=atoi(cJSON_Print(payload->child->child->next->child->next)); 
            // printf("%s\n", m->pole2);
            // printf("%d\n", m->x2); 
            // printf("%d\n", m->y2); 
            m->pole3=cJSON_Print(payload->child->child->next->next->child->next->next);
            m->x3=atoi(cJSON_Print(payload->child->child->next->next->child));     
            m->y3=atoi(cJSON_Print(payload->child->child->next->next->child->next)); 
            // printf("%s\n", m->pole3);
            // printf("%d\n", m->x3); 
            // printf("%d\n", m->y3); 
    }
    cJSON_Delete(monitor_json);
    return m;
}

void supports_full_hdinfo(const char * const monitor)
{
    const cJSON *resolution = NULL;
    const cJSON *payload = NULL;
    const cJSON *status = NULL;
   
    cJSON *monitor_json = cJSON_Parse(monitor);
    if (monitor_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
      
        goto end;
    }

    status = cJSON_GetObjectItemCaseSensitive(monitor_json, "status");
    payload = cJSON_GetObjectItemCaseSensitive(monitor_json, "payload");
   {    
        cJSON *name = cJSON_GetObjectItemCaseSensitive(payload, "name");
        cJSON *current_x = cJSON_GetObjectItemCaseSensitive(payload, "current_x");
        cJSON *current_y = cJSON_GetObjectItemCaseSensitive(payload, "current_y");
        cJSON *field_type = cJSON_GetObjectItemCaseSensitive(payload, "field_type");
        cJSON *current_session = cJSON_GetObjectItemCaseSensitive(payload, "current_session");
        cJSON *direction = cJSON_GetObjectItemCaseSensitive(payload, "direction");
        cJSON *steps = cJSON_GetObjectItemCaseSensitive(payload, "step");
        cJSON *fieldbonus = cJSON_GetObjectItemCaseSensitive(payload, "field_bonus");
        
            printf("Nazwa świata: %s\n", name->valuestring); 
            printf("x = %d\n", current_x->valueint); 
            printf("y = %d\n", current_y->valueint); 
            printf("Typ podloza: %s\n", field_type->valuestring); 
            printf("Obecna sesja: %s\n", current_session->valuestring); 
            printf("Kierunek: %s\n", direction->valuestring); 
            printf("Liczba krokow: %d\n", steps->valueint);
           
            goto end;     
    }
end:
    cJSON_Delete(monitor_json);
}

void zwolnij(mapa *m){
    for (int i = 0; i < 20; i++) 
    free( m->tab[i] );
    free(m->tab);
    free(m);
}

int main(int argc, char **argv)
{   
    mapa *m;
	char buffer[2048];
	
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;

    int i;
    char *test="qwerty_2";
    for (i =1; i< argc; i++){
    if(strcmp(argv[i], "info")==0){
            printf("\nInformacje o swiecie:\n");
            info(test);
            FILE *f = fopen("a.json", "r");
	        fread(buffer,1,2048,f);
	        fclose(f);
            supports_full_hdinfo(buffer);
        }
    if(strcmp(argv[i], "move")==0){
            printf("\nWykonuje ruch do przodu.\n");
            move(test);
            FILE *f = fopen("a.json", "r");
            fread(buffer,1,2048,f);
	        fclose(f);
            m = (supports_full_hd(buffer));
            wypiszstan(m);
            aktualizuj(m);
            zapiszmape2(m);
            wypisz();
            }
    if(strcmp(argv[i], "explore")==0){
            printf("\nInformacje o trzech blokach przed czolgiem, kolejno od lewej do prawej:\n");
            explore(test);
            FILE *f = fopen("a.json", "r");
	        fread(buffer,1,2048,f);
	        fclose(f);
            m = supports_full_hd_explore(buffer);
            aktualizuj_explore(m);
            zapiszmape2(m);
            wypisz();
            }
    if(strcmp(argv[i], "right")==0){
            printf("\nObracam w prawo.\n");
            right(test);
            FILE *f = fopen("a.json", "r");
	        fread(buffer,1,2048,f);
	        fclose(f);
            m = supports_full_hd(buffer);
            wypiszstan(m);}
    if(strcmp(argv[i], "left")==0){
            printf("\nObracam w lewo.\n");
        left(test);
            FILE *f = fopen("a.json", "r");
	        fread(buffer,1,2048,f);
	        fclose(f);
            m = supports_full_hd(buffer);
            wypiszstan(m);}
    if(strcmp(argv[i], "reset")==0){
            printf("\nResetuje swiat.\n");
            reset(test);
            zapiszmape();
        }
    }  
    //zwolnij(m);
    // free(buffer);
    // free(chunk.response);
    // free(test);
    return 0;
}