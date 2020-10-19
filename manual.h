/**
 * 2020:10:19t02:20:32, Création :
 *     lava@macta
 *     /Users/lava/quiz/quiz_tableau_periodique_elements_C/manual.h
 **/

char manual[] = "\n\
NAME\n\
    \033[1mqtpe\033[0m -- Quiz sur le Tableau Périodique des Éléments\n\
\n\
SYNOPSIS\n\
    \033[1mqtpe\033[0m [\033[1m-aiplh\033[0m] [\033[1m-c\033[0m | \033[1m-f\033[0m | \033[1m-n\033[0m] [\033[1m-q\033[0m \033[4mtous\033[0m | \033[4munistable\033[0m | \033[4muninaturel\033[0m] [\033[1m-t\033[0m [\033[1m-o\033[0m \033[4mfichier\033[0m]]\n\
\n\
DESCRIPTION\n\
    Quiz sur les éléments du tableau périodique.\n\
    Pour chacun des 118 éléments découverts, le numéro atomique (Z) est donné et il faut taper son symbole et son nom séparés par un espace.\n\
\n\
    Les options disponibles sont :\n\
\n\
    \033[1m-a\033[0m    Approximatif : les majuscules et accents sont facultatif, ainsi, « sn etain » sera considéré comme correct pour « Sn Étain ».\n\
\n\
    \033[1m-i\033[0m    Informations : à chaque fois que l’on donne une réponse exacte, des informations complémentaires sont données sur l’élément (isotopes, utilisations,…)\n\
\n\
    \033[1m-p\033[0m    Affiche le tableau périodique des éléments à l’écran sans lancer le quiz.\n\
\n\
    \033[1m-l\033[0m    Mode « light » : le tableau n’est pas affiché, cela permet de rendre le quiz plus rapide quand l’objectif est de viser le record de rapidité.\n\
\n\
    \033[1m-h\033[0m    Affiche cette documentation\n\
\n\
    \033[1m-c\033[0m    Caractères colorés : les caractères des éléments (symbole et numéro atomique Z) du tableau périodique sont colorés selon leur catégorie chimique (alcalin, halogène, noble,…) Cette option est excluante avec -f, si les deux sont données, alors -c l’emporte.\n\
    \033[1m-f\033[0m    Fonds colorés : le fond des cases du tableau périodique est coloré selon la catégorie chimique (alcalin, halogène, noble,…) de l’élément. Cette option est excluante avec -c, si les deux sont données, alors -c l’emporte.\n\
    \033[1m-n\033[0m    Pas de coloration (cette option l’emporte sur -c et -f).\n\
\n\
    \033[1m-q\033[0m    Choix du quiz ::\n\
          \033[4mtous\033[0m       : par défaut, il faut donner le symbole et le nom des 118 éléments découverts\n\
          \033[4munistable\033[0m  : il faut donner le symbole et le nom des 26 éléments monoisotopiques, cad ceux ayant un seul isotope stable\n\
          \033[4muninaturel\033[0m : il faut donner le symbole et le nom des 22 éléments mononucléidiques, cad ceux ayant un seul isotope naturel\n\
\n\
    \033[1m-t\033[0m    Écriture du tableau périodique des éléments au format texte (cad tel qu’il est affiché dans le terminal par ce script) dans un fichier, par défaut :\n\
          \033[4m$fichier_tpe\033[0m\n\
          Cette option annule le quiz (et donc toutes les autres options).\n\
    \033[1m-o\033[0m \033[4mfichier\033[0m    Adresse du fichier (cette option active automatiquement \033[1m-t\033[0m)\n\
\n\
EXAMPLES\n\
    Par défaut, les deux lignes suivantes sont équivalentes :\n\
    \033[32m$\033[0m \033[31mqtpe\033[0m\n\
    \033[32m$\033[0m \033[31mqtpe -c -q\033[0m \033[34mtous\033[0m\n\
\n\
    Quiz sans les majuscules et accents (non-nécessaire en BÉPO, nécessaire en AZERTY, QWERTY,…)\n\
    \033[32m$\033[0m \033[31mqtpe -a\033[0m\n\
\n\
    Afficher le tableau périodique des éléments avec coloration des caractères, des fonds et sans coloration :\n\
    \033[32m$\033[0m \033[31mqtpe -p\033[0m\n\
    \033[32m$\033[0m \033[31mqtpe -pf\033[0m\n\
    \033[32m$\033[0m \033[31mqtpe -pn\033[0m\n\
\n\
    Sauvegarde dans un fichier du tableau périodique des éléments\n\
    \033[32m$\033[0m \033[31mqtpe -t -o\033[0m \033[34m~/mendeleiev.txt\033[0m\n\
";
