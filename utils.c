/**
 * 2020:10:18t23:47:10, Création :
 *     lava@macta
 *     /Users/lava/quiz/quiz_tableau_periodique_elements_C/utils.c
 **/

#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

#include "constants.h"
#include "utils.h"


bool all(unsigned char *array) {
    for (unsigned char i = 0; i < TPE_LEN; i++)
        if (!array[i])
            return false;
    return true;
}


void clear_input(wchar_t *raw_answer,
                 wchar_t *answer,
                 wchar_t *answer_symbol,
                 wchar_t *answer_name) {
    wcscpy(raw_answer, L"");
    wcscpy(answer, L"");
    wcscpy(answer_symbol, L"");
    wcscpy(answer_name, L"");
    /*
    answer_symbol = NULL;
    answer_name   = NULL;
    */
    if (false) {
        wprintf(L"%14p  -->  \"%ls\"\n", answer       , answer       );
        wprintf(L"%14p  -->  \"%ls\"\n", answer_symbol, answer_symbol);
        wprintf(L"%14p  -->  \"%ls\"\n", answer_name  , answer_name  );
    }
}


unsigned char minhhu(unsigned char x, unsigned char y) {
    return x < y ? x : y;
}


unsigned char levenshein(wchar_t *solution, wchar_t *answer) {
    /**
     * TODO
     * Distance de Levenshein entre deux chaines
     * Algorithme de Wagner et Fisher, cf
     * https://fr.wikipedia.org/wiki/Distance_de_Levenshtein
     **/
    //return 0;
    return (unsigned char)wcslen(solution);  // PROVISOIRE
}


float mark(wchar_t *solution, wchar_t *answer) {
    /**
     * Calcul de la note à partir de la distance de Levenshein,
     * avec la fonction affine suivante :
     * note = 1 - min(distance, len) / len
     * avec `len` la longueur de la solution.
     **/
    unsigned char distance = levenshein(solution, answer);
    unsigned char len = (unsigned char)wcslen(solution);
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


void input_chars(char *str, unsigned char maxlen) {
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


void input_wchars(wchar_t *wstr, unsigned char maxlen) {
    /**
     * Version wide-char de  input_chars
     **/
    wchar_t c;
    unsigned char i, j;
    for (i = 0; (c = getwchar()) != (wchar_t)'\n' && c != (wchar_t)EOF; i++) {
        if (i < maxlen - 1) {
            wstr[i] = c;
            j = i;
        }
    }
    wstr[++j] = (wchar_t)'\0';
}


bool split(wchar_t *answer, wchar_t *answer_symbol, wchar_t *answer_name) {
    /**
     * Découpe  answer  selon le premier espace en  answer_symbol  et  answer_name
     * Si  answer
     * - n’est pas de la forme "<symbole> <nom>", ou
     * - <symbole> fait 3 caractères ou plus, ou
     * - <nom> fait 14 caractères ou plus,
     * alors cette fonction renvoie FAUX.
     *
     * J’ai développé cette fonction dans
     * ~/zessais/C/non_ascii_input/split.c
     **/
    unsigned char i, j = 0, k = 0;
    unsigned char jj = 0, kk = 0;  /* compteurs pour les tailles de la 1-ère
                                    * et de la 2-ème sous-chaine
                                    */
    size_t len = wcslen(answer);
    unsigned char nos = 0;  // number of spaces
    //printf("split:\n");
    for (i = 0; i < len; ++i) {
        if (answer[i] == L' ') {
            ++nos;
        } else {
            if (nos == 0) {
                ++jj;
                if (i < MAX_SYMBOL_LEN - 1) {
                    //wprintf(L"\tsymbol[%hhu] = '%lc'\n", j, answer[i]);
                    answer_symbol[j++] = answer[i];
                }
            }
            else if (nos == 1) {
                ++kk;
                if (j < MAX_NAME_LEN - 1) {
                    //wprintf(L"\tname[%hhu] = '%lc'\n", k, answer[i]);
                    answer_name[k++] = answer[i];
                }
            }
        }
        if (nos > 1) {
            break;
        }
    }
    //wprintf(L"\tsymbol[%hhu] = '\\0'\n", j);
    answer_symbol[j] = L'\0';
    //wprintf(L"\tname[%hhu] = '\\0'\n", k);
    answer_name[k] = L'\0';
    if (nos == 1 && jj < MAX_SYMBOL_LEN && kk < MAX_NAME_LEN) {
        return true;
    } else {
        answer_symbol[0] = L'\0';
        answer_name[0] = L'\0';
        return false;
    }
}


void archive_score(float symbol_mark_mean,
                   float name_mark_mean, 
                   unsigned short try_count_global,
                   unsigned short giveup_count_global,
                   unsigned short answered_count_global,
                   bool mode_apprx,
                   bool mode_light,
                   unsigned short duration) {
    setlocale(LC_ALL, "");
    printf("Moyenne symboles : %.3f\n", symbol_mark_mean);
    printf("Moyenne noms     : %.3f\n", name_mark_mean);
    // Pseudo ?
    wchar_t pseudo[MAX_LEN_PSEUDO];// = "";
    do {
        printf("Pseudo [16 caractères maximum] ? : ");
        input_wchars(pseudo, MAX_LEN_PSEUDO);
    } while (wcscmp(pseudo, (wchar_t *)"") == 0);
    fprintf(stderr, "pseudo : \"%-16ls\"\n", pseudo);
    // Fichiers des scores existant ?
    FILE *fscores;
    fscores = fopen(FILE_SCORES, "r");
    if (fscores == NULL) {
        fclose(fscores);
        fscores = fopen(FILE_SCORES, "w");
        fprintf(fscores, "| Pseudo           | AAAA-MM-JJ,hh:mm:ss | #el |    MS |    MN | #tt | #ko | #ok | A | L | Tps, s |\n");
        fprintf(fscores, "|:-----------------|:-------------------:|----:|------:|------:|----:|----:|----:|:-:|:-:|-------:|\n");
    }
    fclose(fscores);
    // Sauvegarde du score
    char date[DATE_LEN];
    getdate_iso8601(date);
    fscores = fopen(FILE_SCORES, "a");
    fprintf(fscores,
            "| %-16ls | %19s | %3d | %5.3f | %5.3f | %3hu | %3hu | %3hu | %1hhu | %1hhu | %6hu |\n",
            pseudo, date, TPE_LEN, symbol_mark_mean, name_mark_mean, 
            try_count_global, giveup_count_global, answered_count_global,
            mode_apprx, mode_light,
            duration);
    fclose(fscores);
}
