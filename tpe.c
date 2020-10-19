/**
 * 2020:10:17t23:03:27, Création :
 *     lava@macta
 *     /Users/lava/quiz/quiz_tableau_periodique_elements_C/io.c
 **/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "tpe.h"

void load_data(void) {
    unsigned char i;
    for (i = 0; i < TPE_LEN; ++i)
        tpe[i] = malloc(sizeof(Element));
    FILE *fr = fopen(FILE_DATA, "r");
    assert(fr != NULL);
    for (i = 0; i < TPE_LEN; ++i) {
        fscanf(fr, "%hhu %s %s %s %s %s\n",
                &tpe[i]->Z,
                tpe[i]->symbol,
                tpe[i]->names[0],
                tpe[i]->names[1],
                tpe[i]->names[2],
                tpe[i]->names[3]);
    }
    fclose(fr);
    fr = NULL;
}

void display_data(void) {
    unsigned char i;
    for (i = 0; i < TPE_LEN; ++i) {
        printf("%hhu, %s, %s, %s, %s, %s\n",
                tpe[i]->Z,
                tpe[i]->symbol,
                tpe[i]->names[0],
                tpe[i]->names[1],
                tpe[i]->names[2],
                tpe[i]->names[3]);
    }
}

