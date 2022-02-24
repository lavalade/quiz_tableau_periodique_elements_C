/**
 * Quiz sur les éléments chimiques du tableau périodique,
 * portage en C du script bash ~/cmd/qtpe
 *
 * BUGS:
 * - Quand on donne sa langue au chat dès la première question :
$ ./quiz
109 ? :
La réponse doit être de la forme "Un Unobtainium"
109 ? :
La réponse était : "Mt Meitnerium"
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
#include <ctype.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

#include "main.h"
//#include "manual.h"
#include "table_empty.h"
#include "tpe.h"
#include "utils.h"
#include "wchar_to_ascii.h"

#define MAX_ANSWER_LEN 17
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


// ============================================================================


int main(int argc, char *argv[]) {
    /** 
     * Traitement des options
     **/
    setlocale(LC_ALL, "");
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
                printf("Sauvegarde du tableau dans : '%s'\n", optarg);
                break;
            case ':':
                if (optopt == 'o')
                    fprintf(stderr, "/!\\ L'option '-o' a besoin d'un argument.\n");
                else if (isprint(optopt))
                    fprintf(stderr, "/!\\ Option '-%c' inconnue.\n", optopt);
                else
                    fprintf(stderr, "/!\\ Caractere d'option inconnu: '\\x%x'.\n",
                            optopt);
                return EXIT_FAILURE;
            case '?':
                fprintf(stderr, "/!\\ Option inconnue : '-%c'\n", optopt);
                return EXIT_FAILURE;
            default:
                fprintf(stderr, "/!\\\n");
                fprintf(stderr, "%s", manual);
                return EXIT_FAILURE;
        }
    }
    if (optind < argc) {
        fprintf(stderr, "/!\\ Arguments exedentaites :");
        for (unsigned char index = optind; index < argc; ++index)
            fprintf(stderr, " '%s'", argv[index]);
        fprintf(stderr, "\n");
        return EXIT_FAILURE;
    }
    unsigned char i;
    unsigned char x;
    bool pursue;
    /*
    // Test tolower
    wchar_t test[] = L"CoNnArD ÉcariSSeur";
    wprintf(L"%ls\n", test);
    AZ_to_az(test);
    wprintf(L"%ls\n", test);
    return 0;
    */
    // Acquisition des données sur les éléments
    load_data();
    //display_data();
    // Tentative de remplacement dans  table
    /*
    table[198] = 'H';
    printf("%s", table);
    */
    // Chronométrage, cf
    // https://koor.fr/C/ctime/time.wp
    time_t tic = time(NULL);
    // Boucle du jeu
    srand(time(NULL));
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
        pursue = symbol_name_from_Z(x);
    } while (!all(answered) && pursue);
    // Chronométrage
    time_t toc = time(NULL);
    // Langue au chat  ==>  note 0/1
    for (i = 0; i < TPE_LEN; i++)
        if (giveup_counter[i] > 0) {
            symbol_marks[i] = 0.;
            name_marks[i] = 0.;
        }
    // Affichage détaillé
    if (0)
        for (i = 0; i < TPE_LEN; i++) {
            wprintf(L"%2ls : %.3f %.3f\n",
                    tpe[i]->symbol, symbol_marks[i], name_marks[i]);
        }
    // Sauvegarde du score dans le fichier d’historique
    archive_score(meanf(symbol_marks),
                  meanf(name_marks), 
                  sumhhu(try_counter),
                  sumhhu(giveup_counter),
                  sumhhu(answered),
                  mode_apprx,
                  mode_light,
                  (unsigned short)difftime(toc, tic));
    // Libération
    for (i = 0; i < TPE_LEN; ++i) {
        free(tpe[i]);
        tpe[i] = NULL;
    }
    //
    return EXIT_SUCCESS;
}


// ============================================================================


bool symbol_name_from_Z(unsigned char x) {
    /**
     * Arguments :
     * unsigned char x : index de l’élément, dans [0, 117]
     * bool givedup ::
     *     - faux : question normale
     *     - vrai : quand on a donné sa langue au chat
     *
     * Tant qu’on n’a pas donné la bonne réponse :
     * - Acquisition de <symbole> <nom> :
     *   - si "q" : quitter
     *   - si "" : langue-au-chat, il faut retaper <symbole> <nom>
     *   - sinon :
     *      - si forme OK :
     *          - symbole OK ? sinon : recommencer
     *          - nom OK ? sinon : recommencer
     *      - sinon : recommencer
     **/
    setlocale(LC_ALL, "");
    unsigned char Z = x + 1;
    wchar_t raw_answer[MAX_ANSWER_LEN];
    wchar_t answer[MAX_ANSWER_LEN];
    wchar_t answer_symbol[MAX_SYMBOL_LEN];
    wchar_t answer_name[MAX_NAME_LEN];
    wchar_t solution_symbol[MAX_SYMBOL_LEN];
    wchar_t solution_name[MAX_NAME_LEN];
    bool symbol_ok = false;
    bool name_ok = false;
    float symbol_mark, name_mark;
    bool givedup = false;
    bool ok;
    // Boucle de répétition de la question
    while (true) {
        printf("%hhu ? : ", Z);
        input_wchars(raw_answer, MAX_ANSWER_LEN);
//fwprintf(stderr, L"raw_answer      = \"%ls\"\n", raw_answer);
        // Mode approximatif ?
        if (mode_apprx) {
            wcstr_to_ascii(raw_answer, answer);
            AZ_to_az(answer);
            wcstr_to_ascii(tpe[x]->symbol, solution_symbol);
            AZ_to_az(solution_symbol);
            wcstr_to_ascii(tpe[x]->names[0], solution_name);
            AZ_to_az(solution_name);
        } else {
            wcscpy(answer, raw_answer);
            wcscpy(solution_symbol, tpe[x]->symbol);
            wcscpy(solution_name, tpe[x]->names[0]);
        }
//fwprintf(stderr, L"answer          = \"%ls\"\n", answer);
//fwprintf(stderr, L"solution_symbol = \"%ls\"\n", solution_symbol);
//fwprintf(stderr, L"solution_name   = \"%ls\"\n", solution_name);
        // Quitter
        if (wcscmp(answer, L"q") == 0) {
            printf("Arrêt du jeu :'(\n");
            return false;
        }
        // Tentatives
        if (!givedup)
            ++try_counter[x];
        // Langue au chat
        if (wcslen(answer) == 0) {
            givedup = true;
            ++giveup_counter[x];
            wprintf(L"La réponse était : \"%ls %ls\"\n",
                    tpe[x]->symbol, tpe[x]->names[0]);
            // Pour la pédagogie, on doit rentrer le <symbole> <nom>
            // de l’élément (jusqu’à ce que ce soit exact)
            continue;
        }
        // Réponse de la forme "<symbole> <nom>" ?
        ok = split(answer, answer_symbol, answer_name);
//fwprintf(stderr, L"answer        = \"%ls\"\n", answer);
//fwprintf(stderr, L"answer_symbol = \"%ls\"\n", answer_symbol);
//fwprintf(stderr, L"answer_name   = \"%ls\"\n", answer_name);
//fprintf(stderr, "%s\n", ok ? "ok" : "ko");
        if (!ok) {
            printf("La réponse doit être de la forme \"Un Unobtainium\"\n");
            clear_input(raw_answer, answer, answer_symbol, answer_name);
            continue;
        }
        // Symbole OK ?
        //wprintf(L"tpe[%hhu]->symbol = \"%ls\"\n", x, tpe[x]->symbol);
        if (wcscmp(answer_symbol, solution_symbol) == 0) {
            symbol_ok = true;
            symbol_mark = 1.;
        } else {
            symbol_mark = mark(solution_symbol, answer_symbol);
            wprintf(L"Non, le symbole de l'élément Z = %hhu n'est pas \"%ls\" !\n",
                    Z, answer_symbol);
        }
        // Nom OK ?
        //wprintf(L"tpe[%hhu]->names[0] = \"%ls\"\n", x, tpe[x]->names[0]);
        if (wcscmp(answer_name, solution_name) == 0) {
            name_ok = true;
            name_mark = 1.;
        } else {
            name_mark = mark(solution_name, answer_name);
            wprintf(L"Non, le nom de l'élément Z = %hhu n'est pas \"%ls\" !\n",
                    Z, answer_name);
        }
        // MàJ des moyennes
        if (!givedup) {
            if (try_counter[x] == 0) {
                symbol_marks[x] = symbol_mark;
                name_marks[x] = name_mark;
            } else {
                symbol_marks[x] = update_mean(symbol_marks[x], try_counter[x],
                                              symbol_mark);
                name_marks[x] = update_mean(name_marks[x], try_counter[x],
                                            name_mark);
            }
        }
        // Symbole | nom KO ?
        if (!symbol_ok || !name_ok) {
            clear_input(raw_answer, answer, answer_symbol, answer_name);
            continue;
        }
        // Symbole & nom OK ?
        if (symbol_ok && name_ok) {
            if (!givedup) {
                printf("Oui !\n");
                answered[x] = 1;
            } else {
                printf("Voilà !\n");
            }
            clear_input(raw_answer, answer, answer_symbol, answer_name);
            break;
        } 
    }
    return true;
}

