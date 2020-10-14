/**
 * Quiz sur les éléments chimiques du tableau périodique,
 * portage en C du script bash ~/cmd/qtpe
 *
 * TODO:
 * - Modes approximatif en option
 * - Modes léger en option
 * - Distance de Levenshein
 * - Affichage du tableau périodique des éléments mis à jour à chaque question
 * - Autres modes de jeu :
 *   - Z depuis "symbole nom"
 *   - éléments monoisotopiques,
 *   - éléments mononucléidiques,
 *   - ...
 * - ...
 * ----------------------------------------------------------------------------
 * 2020:10:13t17:31:31, Création :
 *     lava@macta
 *     /Users/lava/quiz/qtpe_c/qtpe_c.c
 **/

#include <assert.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TPE_LEN 118
//#define TPE_LEN 2
#define TPE_COLUMNS 32
#define MAX_LEN_SYMBOL 3
#define MAX_LEN_NAME 14
#define LANGUAGES 4
#define MAX_LEN_LINE 128
#define TABLE_LEN 4269
#define TABLE_COLUMNS 194
#define TABLE_LINES 22
#define CELL_WIDTH 6
#define CELL_HEIGHT 3
#define FILE_TABLE "table.txt"
#define FILE_DATA "tpe.txt"
#define FILE_SCORES "qtpe_c.scores.md"
#define MAX_LEN_ANSWER 17
#define MAX_LEN_PSEUDO 17
#define DATE_LEN 20
/**
 * Longueur du nom le plus long dans chaque langue :
 * Fr : len(Rutherfordium) = 13
 * En : len(Rutherfordium) = 13
 * De : len(Rutherfordium) = 13
 * It : len(Rutherfordio) = 12
 *
 * Longueur de la date au format iso-8601 : 19
 * aaaa:mm:jjthh:mm:ss
 **/

typedef struct Element Element;
struct Element {
    unsigned char Z;
    char symbol[MAX_LEN_SYMBOL];
    char names[LANGUAGES][MAX_LEN_NAME];
};

Element *tpe[TPE_LEN];

char table[TABLE_LEN];

void load_table(void) {
    /**
     * Longueur d’une ligne : 32 * 6 + 1 + 1 = 194
     * Nombre de lignes : 7 * 3 + 1 = 22
     * Taille totale : 194 * 22 = 4268
     * Taille avec octet nul terminal : 4269
     **/
    FILE *file_table = fopen(FILE_TABLE, "r");
    int c;
    unsigned short i;
    for (i = 0, c = fgetc(file_table);
            c != EOF;
            ++i, c = fgetc(file_table)) {
        table[i] = c;
    }
    table[i] = '\0';
    fclose(file_table);
    //printf("%s", table);
}

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

bool all(unsigned char *array) {
    for (unsigned char i = 0; i < TPE_LEN; i++)
        if (!array[i])
            return false;
    return true;
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
    strftime(date, DATE_LEN, "%Y-%m-%dt%H:%M:%S", pTime);
}

int main(void) {
    //printf("sizeof(bool) = %zu\n", sizeof(bool));
    unsigned char i = 0;
    // Acquisition des données sur les éléments
    load_data();
    //display_data();
    // Acquisition de la table (affichage joli)
    load_table();
    //printf("%s", table);
    // Variables de jeu
    unsigned char answered[TPE_LEN] = {0};
    unsigned char try_counter[TPE_LEN] = {0};
    unsigned char giveup_counter[TPE_LEN] = {0};
    float symbol_marks[TPE_LEN] = {0.};
    float name_marks[TPE_LEN] = {0.};
    float symbol_mark, name_mark;
    unsigned char x, Z;
    bool symbol_ok, name_ok;
    bool stop = false;
    char answer[MAX_LEN_ANSWER];
    char *answer_symbol, *answer_name, *toomuchspaces;
    srand(time(NULL));
    // Chronométrage, cf
    // https://koor.fr/C/ctime/time.wp
    time_t tic = time(NULL);
    // Boucle du jeu
    do {
        // Tirage au sort d’un élément
        do {
            x = rand() % TPE_LEN;
        } while (answered[x]);
        /*
        for (i = 0; i < TPE_LEN; i++)
            printf("%hhu", answered[i]);
        printf("\n");
        */
        // Boucle de répétition de la question
        symbol_ok = false;
        name_ok = false;
        Z = x + 1;
        while (true) {
            printf("%hhu ? : ", Z);
            inputstr(answer, MAX_LEN_ANSWER);
            // Quitter
            if (strcmp(answer, "q") == 0) {
                printf("Arrêt du jeu :'(\n");
                //return EXIT_SUCCESS;
                stop = true;  // stoppe la boucle do-while parente
                break;  // stoppe cette boucle while
            }
            // Tentatives
            ++try_counter[x];
            // Langue au chat
            if (strlen(answer) == 0) {
                ++giveup_counter[x];
                printf("La réponse était : \"%s %s\"\n",
                        tpe[x]->symbol, tpe[x]->names[0]);
                break;
            }
            // Réponse de la forme <symbole> <nom> ?
            answer_symbol = strtok(answer, " ");
            answer_name = strtok(NULL, " ");
            toomuchspaces = strtok(NULL, " ");
            if (answer_name == NULL || toomuchspaces != NULL) {
                printf("La réponse doit être de la forme \"Un Unobtainium\"\n");
                clear_input(answer, answer_symbol, answer_name, toomuchspaces);
                continue;
            }
            // Symbole OK ?
            if (strcmp(answer_symbol, tpe[x]->symbol) == 0) {
                symbol_ok = true;
                symbol_mark = 1.;
            } else {
                symbol_mark = mark(tpe[x]->symbol, answer_symbol);
                printf("Non, le symbole de l'élément Z = %hhu n'est pas \"%s\" !\n",
                        Z, answer_symbol);
            }
            // Nom OK ?
            if (strcmp(answer_name, tpe[x]->names[0]) == 0) {
                name_ok = true;
                name_mark = 1.;
            } else {
                name_mark = mark(tpe[x]->names[0], answer_name);
                printf("Non, le nom de l'élément Z = %hhu n'est pas \"%s\" !\n",
                        Z, answer_name);
            }
            // MàJ des moyennes
            if (try_counter[x] == 0) {
                symbol_marks[x] = symbol_mark;
                name_marks[x] = name_mark;
            } else {
                symbol_marks[x] = update_mean(symbol_marks[x], try_counter[x],
                                              symbol_mark);
                name_marks[x] = update_mean(name_marks[x], try_counter[x],
                                            name_mark);
            }
            // Symbole | nom KO ?
            if (!symbol_ok || !name_ok) {
                clear_input(answer, answer_symbol, answer_name, toomuchspaces);
                continue;
            }
            // Symbole & nom OK ?
            if (symbol_ok && name_ok) {
                printf("Oui !\n");
                answered[x] = 1;
                clear_input(answer, answer_symbol, answer_name, toomuchspaces);
                break;
            } 
        }
    } while (!all(answered) && !stop);
    // Chronométrage
    time_t toc = time(NULL);
    unsigned short duration = (unsigned short)difftime(toc, tic);
    printf("duration = %hu\n", duration);
    // Langue au chat  ==>  note 0/1
    for (i = 0; i < TPE_LEN; i++)
        if (giveup_counter[i] > 0) {
            symbol_marks[i] = 0.;
            name_marks[i] = 0.;
        }
    // Affichage détaillé
    for (i = 0; i < TPE_LEN; i++) {
        printf("%2s : %.3f %.3f\n",
                tpe[i]->symbol, symbol_marks[i], name_marks[i]);
    }
    // Moyennes sur tous les éléments
    float symbol_mark_mean = meanf(symbol_marks);
    float name_mark_mean = meanf(name_marks);
    printf("Moyenne symboles : %.3f\n", symbol_mark_mean);
    printf("Moyenne noms     : %.3f\n", name_mark_mean);
    // Compteurs globaux
    unsigned short try_count_global = sumhhu(try_counter);
    unsigned short giveup_count_global = sumhhu(giveup_counter);
    unsigned short answered_count_global = sumhhu(answered);
    // Pseudo ?
    char pseudo[MAX_LEN_PSEUDO] = "";
    do {
        printf("Pseudo [16 caractères maximum] ? : ");
        inputstr(pseudo, MAX_LEN_PSEUDO);
    } while (strcmp(pseudo, "") == 0);
    // Fichiers des scores existant ?
    FILE *fscores;
    fscores = fopen(FILE_SCORES, "r");
    if (fscores == NULL) {
        fclose(fscores);
        fscores = fopen(FILE_SCORES, "w");
        fprintf(fscores, "| Pseudo           | AAAA-MM-JJ@hh:mm:ss | #el |    MS |    MN | #tt | #ko | #ok | Tps, s |\n");
        fprintf(fscores, "|:-----------------|:-------------------:|----:|------:|------:|----:|----:|----:|-------:|\n");
    }
    fclose(fscores);
    // Sauvegarde du score
    char date[DATE_LEN];
    getdate_iso8601(date);
    fscores = fopen(FILE_SCORES, "a");
    fprintf(fscores,
            "| %16s | %19s | %3d | %5.3f | %5.3f | %3hu | %3hu | %3hu | %6hu |\n",
            pseudo, date, TPE_LEN, symbol_mark_mean, name_mark_mean, 
            try_count_global, giveup_count_global, answered_count_global,
            duration);
    fclose(fscores);
    // Libération
    for (i = 0; i < TPE_LEN; ++i) {
        free(tpe[i]);
        tpe[i] = NULL;
    }
    //
    return EXIT_SUCCESS;
}
