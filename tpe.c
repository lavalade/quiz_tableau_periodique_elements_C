/**
 * 2020:10:17t23:03:27, Création :
 *     lava@macta
 *     /Users/lava/quiz/quiz_tableau_periodique_elements_C/io.c
 **/

#include <assert.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "tpe.h"

void load_data(void) {
    setlocale(LC_ALL, "");
    unsigned char i;
    for (i = 0; i < TPE_LEN; ++i)
        tpe[i] = malloc(sizeof(Element));
    FILE *fr = fopen(FILE_DATA, "r");
    assert(fr != NULL);
    for (i = 0; i < TPE_LEN; ++i) {
        fwscanf(fr, L"%hhu %ls %ls %ls %ls %ls\n",
                &tpe[i]->Z,
                tpe[i]->symbol,
                tpe[i]->names[0],
                tpe[i]->names[1],
                tpe[i]->names[2],
                tpe[i]->names[3]);
        /** Le simple oubli du « l » dans « %ls » pour « tpe[i]->symbol »
         * faisait apparaitre sinogrammes au lieu des symboles !
         **/
    }
    fclose(fr);
    fr = NULL;
}

void display_data(void) {
    setlocale(LC_ALL, "");
    unsigned char i;
    for (i = 0; i < TPE_LEN; ++i) {
        wprintf(L"%hhu, %ls, %ls, %ls, %ls, %ls\n",
                tpe[i]->Z,
                tpe[i]->symbol,
                tpe[i]->names[0],
                tpe[i]->names[1],
                tpe[i]->names[2],
                tpe[i]->names[3]);
    }
}

