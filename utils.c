/**
 * 2020:10:18t23:47:10, Création :
 *     lava@macta
 *     /Users/lava/quiz/quiz_tableau_periodique_elements_C/utils.c
 **/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "constants.h"
#include "utils.h"

bool all(unsigned char *array) {
    for (unsigned char i = 0; i < TPE_LEN; i++)
        if (!array[i])
            return false;
    return true;
}

void clear_input(char *answer,
                 char *answer_symbol,
                 char *answer_name,
                 char *toomuchspaces) {
    strcpy(answer, "");
    answer_symbol = NULL;
    answer_name   = NULL;
    toomuchspaces = NULL;
    if (false) {
        printf("%14p  -->  \"%s\"\n", answer       , answer       );
        printf("%14p  -->  \"%s\"\n", answer_symbol, answer_symbol);
        printf("%14p  -->  \"%s\"\n", answer_name  , answer_name  );
        printf("%14p  -->  \"%s\"\n", toomuchspaces, toomuchspaces);
    }
}

unsigned char minhhu(unsigned char x, unsigned char y) {
    return x < y ? x : y;
}

unsigned char levenshein(char *solution, char *answer) {
    /**
     * TODO
     * Distance de Levenshein entre deux chaines
     * Algorithme de Wagner et Fisher, cf
     * https://fr.wikipedia.org/wiki/Distance_de_Levenshtein
     **/
    //return 0;
    return (unsigned char)strlen(solution);  // PROVISOIRE
}

float mark(char *solution, char *answer) {
    /**
     * Calcul de la note à partir de la distance de Levenshein,
     * avec la fonction affine suivante :
     * note = 1 - min(distance, len) / len
     * avec `len` la longueur de la solution.
     **/
    unsigned char distance = levenshein(solution, answer);
    unsigned char len = (unsigned char)strlen(solution);
    return 1. - minhhu(distance, len) / len;
}

float update_mean(float old_mean, unsigned char n, float new) {
    /**
     * Mise à jour d’une moyenne de `n - 1` éléments avec un nouvel élément
     **/
    return ((n - 1) * old_mean + new) / n;
}

unsigned short sumhhu(unsigned char *array) {
    /**
     * Somme de TPE_LEN valeurs
     **/
    unsigned short out = 0;
    for (unsigned char i = 0; i < TPE_LEN; i++)
        out += array[i];
    return out;
}

float meanf(float *marks) {
    /**
     * Moyenne de TPE_LEN valeurs
     **/
    float out = 0.;
    for (unsigned char i = 0; i < TPE_LEN; i++)
        out += marks[i];
    return out / TPE_LEN;
}

void getdate_iso8601(char *date) {
    /**
     * Renvoie la date au format iso-8601 (càd : aaaa-mm-jjthh:mm:ss), cf
     * https://xkcd.com/1179/
     * https://koor.fr/C/ctime/strftime.wp
     **/
    time_t timestamp = time(NULL);
    struct tm *pTime = localtime(&timestamp);
    strftime(date, DATE_LEN, "%Y-%m-%d,%H:%M:%S", pTime);
}

void inputstr(char *str, unsigned char maxlen) {
    /**
     * Acquisition d’une chaine de taille inconnue, cf
     * https://stackoverflow.com/a/16871702/9249152
     * Acquisition d’une chaine avec une taille maximale, cf
     * https://stackoverflow.com/a/7898516/9249152
     **/
    int c;
    unsigned char i, j;
    for (i = 0; (c = getchar()) != '\n' && c != EOF; i++) {
        if (i < maxlen - 1) {
            str[i] = c;
            j = i;
        }
    }
    str[++j] = '\0';
}
