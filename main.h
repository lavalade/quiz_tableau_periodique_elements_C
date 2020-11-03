/**
 * 2020-11-02,22:37:06, Création :
 *     lava@macta
 *     /Users/lava/quiz/quiz_tableau_periodique_elements_C/main.h
 **/

#include "constants.h"

unsigned char answered[TPE_LEN] = {0};
unsigned char try_counter[TPE_LEN] = {0};
unsigned char giveup_counter[TPE_LEN] = {0};
float symbol_marks[TPE_LEN] = {0.};
float name_marks[TPE_LEN] = {0.};

bool symbol_name_from_Z(unsigned char x);
bool mode_apprx = false;
bool mode_light = false;

const char *manual = \
"NAME\n"
"    quiz --- Quiz sur les éléments du tableau périodique\n"
"\n"
"SYNOPSIS\n"
"    $ quiz [-alh] [-o fichier]\n"
"\n"
"DESCRIPTION\n"
"    -a  Mode approximatif: les majuscules, accents, diacritiques,… ne sont pas nécessaires\n"
"    -h  Aide: affiche cette documentation.\n"
"    -l  Mode léger: le tableau n’est pas affiché à chaque question\n"
"\n"
"    -o fichier  Sauvegarde le tableau périodique dans fichier\n"
"\n"
"EXEMPLES\n"
"    $ ./quiz\n"
"    $ ./quiz -a\n"
"    $ ./quiz -al\n"
"    $ ./quiz -o ~/tpe.txt\n"
"\n";
