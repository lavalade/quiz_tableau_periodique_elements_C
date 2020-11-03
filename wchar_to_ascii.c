/**
 * Suppression des diacritiques (quand c’est implémenté) d’une chaine.
 * J’ai développé originellement ce programme dans
 * ~/dev/C/wchar_to_ascii.v1/
 *
 * 2020-11-01,21:29:49, Création :
 *     lava@macta
 *     /Users/lava/dev/C/wchar_to_ascii/wchar_to_ascii.c
 **/

//#include <locale.h>
#include <stdbool.h>
#include <wchar.h>

#include "wchar_to_ascii.h"


bool in(wchar_t input, const wchar_t *letter_like) {
    /**
     * Renvoie  true  si  input  est dans  letter_like
     **/
    wchar_t wc;
    while ((wc = *letter_like++))
        if (input == wc)
            return true;
    return false;
}


char wchr_to_chr(wchar_t input) {
    /**
     * Renvoie un  char  correspondant au  wchar_t  en entrée :
     * - caractère ascii : ne fait rien,
     * - caractère non-ascii :
     *   - remplacement par a-zA-Z s’il est dans la table, sinon
     *   - remplacement par _
     **/
    if (input == 0 || (32 <= input && input <= 126)) return input;
    if (in(input, L"ÀÁÂÃÄÅÆĀĂĄ")) return 'A';
    if (in(input, L"àáâãäåæāăą")) return 'a';
    if (in(input, L""          )) return 'B';
    if (in(input, L""          )) return 'b';
    if (in(input, L"ÇĆĈĊČ"     )) return 'C';
    if (in(input, L"çćĉċč"     )) return 'c';
    if (in(input, L"ÐĎĐ"       )) return 'D';
    if (in(input, L"ďđ"        )) return 'd';
    if (in(input, L"ÈÉÊËĒĔĖĘĚ" )) return 'E';
    if (in(input, L"èéêëðēĕėęě")) return 'e';
    if (in(input, L""          )) return 'F';
    if (in(input, L""          )) return 'f';
    if (in(input, L"ĜĞĠĢ"      )) return 'G';
    if (in(input, L"ĝğġģ"      )) return 'g';
    if (in(input, L"ĤĦ"        )) return 'H';
    if (in(input, L"ĥħ"        )) return 'h';
    if (in(input, L"ÌÍÎÏĨĪĬĮİĲ")) return 'I';
    if (in(input, L"ìíîïĩīĭįıĳ")) return 'i';
    if (in(input, L"Ĵ"         )) return 'J';
    if (in(input, L"ĵ"         )) return 'j';
    if (in(input, L"Ķ"         )) return 'K';
    if (in(input, L"ķĸ"        )) return 'k';
    if (in(input, L"ĹĻĽĿŁ"     )) return 'L';
    if (in(input, L"ĺļľŀł"     )) return 'l';
    if (in(input, L""          )) return 'M';
    if (in(input, L""          )) return 'm';
    if (in(input, L"ÑŃŅŇŊ"     )) return 'N';
    if (in(input, L"ñńņňŉŋ"    )) return 'n';
    if (in(input, L"ÒÓÔÕÖØŌŎŐŒ")) return 'O';
    if (in(input, L"òóôõöøōŏőœ")) return 'o';
    if (in(input, L"Þ"         )) return 'P';
    if (in(input, L"þ"         )) return 'p';
    if (in(input, L""          )) return 'Q';
    if (in(input, L""          )) return 'q';
    if (in(input, L"ŔŖŘ"       )) return 'R';
    if (in(input, L"ŕŗř"       )) return 'r';
    if (in(input, L"ŚŜŞŠ"      )) return 'S';
    if (in(input, L"ßśŝşšſ"    )) return 's';
    if (in(input, L"ŢŤŦ"       )) return 'T';
    if (in(input, L"ţťŧ"       )) return 't';
    if (in(input, L"ÙÚÛÜŨŪŬŮŰŲ")) return 'U';
    if (in(input, L"ùúûüũūŭůűų")) return 'u';
    if (in(input, L""          )) return 'V';
    if (in(input, L""          )) return 'v';
    if (in(input, L"Ŵ"         )) return 'W';
    if (in(input, L"ŵ"         )) return 'w';
    if (in(input, L""          )) return 'X';
    if (in(input, L""          )) return 'x';
    if (in(input, L"ÝŸŶ"       )) return 'Y';
    if (in(input, L"ýÿŷ"       )) return 'y';
    if (in(input, L"ŹŻŽ"       )) return 'Z';
    if (in(input, L"źżž"       )) return 'z';
    return '_';
}


void wcstr_to_str(wchar_t *wcstr, char *str) {
    /**
     * Convertie une string  wchar_t  en  char  en utilisant  wchr_to_chr
     **/
    while ((*str++ = wchr_to_chr(*wcstr++)))
        ;
}


void wcstr_to_ascii(wchar_t *wcstr, wchar_t *asciistr) {
    /**
     * Renvoie une chaine composée uniquement de a-zA-Z_ et '\0' (terminateur),
     * exactement comme  wcstr_to_str  sauf que la chaine destination est
     * aussi en  wchar_t
     * Cela permetra d’avoir le même code dans  main.c  qu’on soit 
     * en mode approximatif ou non.
     **/
    while ((*asciistr++ = wchr_to_chr(*wcstr++)))
        ;
}


void AZ_to_az(wchar_t wcstr[]) {
    /**
     * Remplace A-Z par a-z, les caractères diacritiqués ne sont pas modifiés
     **/
    for (; *wcstr; ++wcstr)
        if (L'A' <= *wcstr && *wcstr <= L'Z')
            *wcstr += -L'A' + L'a';
    /*
    for (; *wcstr; ++wcstr) {
        wprintf(L"wcstr = %p  -->  *wcstr = '%lc' = %d\n", wcstr, *wcstr, *wcstr);
        if (L'A' <= *wcstr && *wcstr <= L'Z') {
            *wcstr += -L'A' + L'a';
            // *wcstr = L'_';
            wprintf(L"wcstr = %p  -->  *wcstr = '%lc' = %d\n", wcstr, *wcstr, *wcstr);
        }
        printf("\n");
    }
    */
}
