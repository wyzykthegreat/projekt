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
	char buffer[2048];
	
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;

    int i;

    for (i =2; i< argc; i++){
        if(strcmp(argv[i], "info")==0){
            printf("\nInformacje o swiecie:\n");
                info(argv[1]);
            FILE *f = fopen("dzejson.json", "r");
	            fread(buffer,1,2048,f);
	        fclose(f);
            pobierz_info_info(buffer);
        }
        if(strcmp(argv[i], "move")==0){
            printf("\nWykonuje ruch do przodu.\n");
                move(argv[1]);
            FILE *f = fopen("dzejson.json", "r");
                fread(buffer,1,2048,f);
	        fclose(f);
            m = (pobierz_info(buffer));
            wypiszstan(m);
            aktualizuj_mape(m, argv[i]);
            nadpisz_mape(m);
            wypisz();
        }
        if(strcmp(argv[i], "explore")==0){
            printf("\nInformacje o trzech blokach przed czolgiem, kolejno od lewej do prawej:\n");
                explore(argv[1]);
            FILE *f = fopen("dzejson.json", "r");
	            fread(buffer,1,2048,f);
	        fclose(f);
            m = pobierz_info_explore(buffer);
            aktualizuj_mape(m, argv[i]);
            nadpisz_mape(m);
            wypisz();
        }
        if(strcmp(argv[i], "right")==0){
            printf("\nObracam w prawo.\n");
                right(argv[1]);
            FILE *f = fopen("dzejson.json", "r");
	            fread(buffer,1,2048,f);
	        fclose(f);
            m = pobierz_info(buffer);
            wypiszstan(m);
        }
        if(strcmp(argv[i], "left")==0){
            printf("\nObracam w lewo.\n");
                left(argv[1]);
            FILE *f = fopen("dzejson.json", "r");
	            fread(buffer,1,2048,f);
	        fclose(f);
            m = pobierz_info(buffer);
            wypiszstan(m);
        }
        if(strcmp(argv[i], "reset")==0){
            printf("\nResetuje swiat.\n");
                reset(argv[1]);
            tworzmape();
        }
    }  
    //zwolnij(m);
    // free(buffer);
    // free(chunk.response);
    // free(test);
    printf("\n");
    return 0;
}