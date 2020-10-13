/**
 * Quiz sur les éléments chimiques du tableau périodique,
 * portage en C du script bash ~/cmd/qtpe
 * ----------------------------------------------------------------------------
 * 2020:10:13t17:31:31, Création :
 *     lava@macta
 *     /Users/lava/quiz/qtpe_c/qtpe_c.c
 **/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define LEN_TPE 118
#define MAX_LEN_SYMBOL 3
#define MAX_LEN_NAME 14
#define LANGUAGES 4
#define MAX_LEN_LINE 128
/**
 * Longueur du nom le plus long dans chaque langue :
 * Fr : len(Rutherfordium) = 13
 * En : len(Rutherfordium) = 13
 * De : len(Rutherfordium) = 13
 * It : len(Rutherfordio) = 12
 **/

typedef struct Element Element;
struct Element {
    unsigned char Z;
    unsigned char symbol[MAX_LEN_SYMBOL];
    unsigned char names[LANGUAGES][MAX_LEN_NAME];
};

Element *tpe[LEN_TPE];

int main(void) {
    unsigned char i = 0, j = 0;
    char line[MAX_LEN_LINE] = "", *token;
    const char *sep = " ";
    FILE *fr = NULL;
    /*
    // Acquisition du tableau : test 1
    fr = fopen("tpe.dat", "r");
    assert(fr != NULL);
    Element H;
    fscanf(fr, "%hhu %s %s\n", &H.Z, H.symbol, H.name);
    printf("%hhu, %s, %s\n", H.Z, H.symbol, H.name);
    fclose(fr);
    // Acquisition du tableau : test 2
    fr = fopen("tpe.dat", "r");
    assert(fr != NULL);
    Element *pH = malloc(sizeof(*pH));
    fscanf(fr, "%hhu %s %s\n", &pH->Z, pH->symbol, pH->name);
    printf("%hhu, %s, %s\n", pH->Z, pH->symbol, pH->name);
    fclose(fr);
    // Acquisition du tableau : test 3
    for (i = 0; i < LEN_TPE; ++i)
        tpe[i] = malloc(sizeof(Element));
    fr = fopen("tpe.dat", "r");
    assert(fr != NULL);
    for (i = 0; i < LEN_TPE; ++i) {
        fscanf(fr, "%hhu %s %s\n", &tpe[i]->Z, tpe[i]->symbol, tpe[i]->name);
        printf("%hhu %s %s\n", tpe[i]->Z, tpe[i]->symbol, tpe[i]->name);
    }
    fclose(fr);
    */
    // Acquisition du tableau : test 4
    for (i = 0; i < LEN_TPE; ++i)
        tpe[i] = malloc(sizeof(Element));
    fr = fopen("tpe.dat", "r");
    assert(fr != NULL);
    for (i = 0; i < LEN_TPE; ++i) {
        fscanf(fr, "%hhu %s %s %s %s %s\n",
                &tpe[i]->Z,
                tpe[i]->symbol,
                tpe[i]->names[0],
                tpe[i]->names[1],
                tpe[i]->names[2],
                tpe[i]->names[3]);
        printf("%hhu, %s, %s, %s, %s, %s\n",
                tpe[i]->Z,
                tpe[i]->symbol,
                tpe[i]->names[0],
                tpe[i]->names[1],
                tpe[i]->names[2],
                tpe[i]->names[3]);
    }
    // Libération
    fclose(fr);
    fr = NULL;
    for (i = 0; i < LEN_TPE; ++i) {
        free(tpe[i]);
        tpe[i] = NULL;
    }
    //
    return EXIT_SUCCESS;
}
