/**
 * 2020:10:17t23:04:12, Création :
 *     lava@macta
 *     /Users/lava/quiz/quiz_tableau_periodique_elements_C/io.h
 **/

#include "constants.h"

#define MAX_LEN_SYMBOL 3
#define MAX_LEN_NAME 14

#define LANGUAGES 4

#define FILE_DATA "tpe.txt"

typedef struct Element Element;
struct Element {
    unsigned char Z;
    wchar_t symbol[MAX_LEN_SYMBOL];
    wchar_t names[LANGUAGES][MAX_LEN_NAME];
};

Element *tpe[TPE_LEN];

void load_data(void);
void display_data(void);
