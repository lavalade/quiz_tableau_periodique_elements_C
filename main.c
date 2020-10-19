/**
 * Quiz sur les éléments chimiques du tableau périodique,
 * portage en C du script bash ~/cmd/qtpe
 *
 * TODO:
 * - Compatibilité avec les caractères non-ascii
 * - Options :
 *   - mode approximatif
 *   - mode léger
 *   - documentation
 *   - ...
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
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "manual.h"
#include "table_empty.h"
#include "tpe.h"
#include "utils.h"

#define FILE_SCORES "scores.md"
#define MAX_LEN_ANSWER 17
#define MAX_LEN_PSEUDO 17
/**
 * Longueur du nom le plus long dans chaque langue :
 * Fr : len(Rutherfordium) = 13
 * En : len(Rutherfordium) = 13
 * De : len(Rutherfordium) = 13
 * It : len(Rutherfordio) = 12
 *
 * Longueur de la date au format iso-8601 : 19
 * aaaa-mm-jj,hh:mm:ss
 **/

int main(int argc, char *argv[]) {
    //printf("sizeof(bool) = %zu\n", sizeof(bool));
    unsigned char i = 0;
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
    /*
    // Traitement des options, cf
    // https://www.geeksforgeeks.org/getopt-function-in-c-to-parse-command-line-arguments/
    bool mode_apprx = false;
    bool mode_light = false;
    char opt;
    while ((opt = getopt(argc, argv, ":alho:")) != -1) {
        switch (opt) {
            case 'a':
                printf("Mode approximatif\n");
                mode_apprx = true;
                break;
            case 'l':
                printf("Mode léger\n");
                mode_light = true;
                break;
            case 'h':
                printf("%s\n", manual);
                return EXIT_SUCCESS;
            case 'o':
                printf("Sauvegarde du tableau dans : %s\n", optarg);
                break;
            case ':':
                printf("L’option '-%c' a besoin d’une valeur (argument)\n", opt);
                break;
            case '?':
                printf("Option inconnue : '-%c'\n", opt);
                break;
        }
    }
    for (; optind < argc; ++optind)
        printf("Arg. sup.: %s\n", argv[optind]);
    */
    // Acquisition des données sur les éléments
    load_data();
    //display_data();
    // Tentative de remplacement dans  table
    table[198] = 'H';
    printf("%s", table);
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
                // Pour la pédagogie, on doit rentrer le <symbole> <nom>
                // de l’élément (jusqu’à ce que ce soit exact)
                // TODO
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
    if (0)
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
        fprintf(fscores, "| Pseudo           | AAAA-MM-JJ,hh:mm:ss | #el |    MS |    MN | #tt | #ko | #ok | Tps, s |\n");
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
