#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"
#include "../cJSON/cJSON.h"
#include "komunikacja.h"

void info(char *token) {
    char url1[100] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/";
    strcat(url1, token);
    make_request(url1);
    //free(url1);
}

void move(char *token) {
    char url1[100] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/";
    strcat(url1, token);
    make_request(url1);
    // free(url1);
}

void explore(char *token) {
    char url1[100] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/";
    strcat(url1, token);
    make_request(url1);
    //free(url1);
}

void reset(char *token) {
    char url1[100] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/reset/";
    strcat(url1, token);
    make_request(url1);
    //free(url1);
}

void right(char *token) {
    char url1[100] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/";
    char *lol="/right";
    strcat(url1, token);
        strcat(url1, lol);

    make_request(url1);
   // free(url1);
}

void left(char *token) {
    char url1[100] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/";
    char *lol="/left";
    strcat(url1, token);
        strcat(url1, lol);
    make_request(url1);
   // free(url1);
}

mapa *pobierz_info(const char * const dzejson)
{
    const cJSON *payload = NULL;
    const cJSON *status = NULL;
    mapa *m;

    cJSON *dzejson_json = cJSON_Parse(dzejson);
    if (dzejson_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }      
    }
    status = cJSON_GetObjectItemCaseSensitive(dzejson_json, "status");
    payload = cJSON_GetObjectItemCaseSensitive(dzejson_json, "payload");
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
    cJSON_Delete(dzejson_json);         
    return m;
}

mapa *pobierz_info_explore(const char * const dzejson)
{
    const cJSON *element = NULL;
    const cJSON *payload = NULL;
    const cJSON *status = NULL;
    const cJSON *lista = NULL;
    mapa *m;

    cJSON *dzejson_json = cJSON_Parse(dzejson);
    if (dzejson_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
      
    }
    status = cJSON_GetObjectItemCaseSensitive(dzejson_json, "status");
    payload = cJSON_GetObjectItemCaseSensitive(dzejson_json, "payload");
    lista = cJSON_GetObjectItemCaseSensitive(payload, "list");
    {
        cJSON_ArrayForEach(element, lista){
                cJSON *x = cJSON_GetObjectItemCaseSensitive(element, "x");
                cJSON *y = cJSON_GetObjectItemCaseSensitive(element, "y");
                cJSON *field_type = cJSON_GetObjectItemCaseSensitive(element, "type");
                    printf("Blok:\n"); 
                    printf("x = %d\n", x->valueint); 
                    printf("y = %d\n", y->valueint); 
                    printf("Typ podloza: %s\n", field_type->valuestring);        
            }
        printf("\n");
        payload = cJSON_GetObjectItemCaseSensitive(dzejson_json, "payload");

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
    cJSON_Delete(dzejson_json);
    return m;
}

void pobierz_info_info(const char * const dzejson)
{
    const cJSON *payload = NULL;
    const cJSON *status = NULL;
   
    cJSON *dzejson_json = cJSON_Parse(dzejson);
    if (dzejson_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
      
        goto end;
    }

    status = cJSON_GetObjectItemCaseSensitive(dzejson_json, "status");
    payload = cJSON_GetObjectItemCaseSensitive(dzejson_json, "payload");
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
            printf("Liczba krokow: %d\n", steps->valueint-1);
           
        goto end;     
    }
    end:
        cJSON_Delete(dzejson_json);
}
