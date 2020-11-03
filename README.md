<!--
2020-10-13t22:20:19, Création :
	lava@macta
	/Users/lava/quiz/quiz_tableau_periodique_elements/qtpe_c/README.md
-->

<p align="center">
<h1 align="center">
Quiz sur le tableau périodique des éléments
</h1>
<img src="./tpefgcolor.png" height="240"/>
<p align="center">
Implémentation en C d’un quiz (dans un terminal) sur le tableau périodique des éléments.
<br />
<i>
Développement en cours...
</i>
</p>
</p>

## Table des matières

* [Mode d’emploi](#mode-d-emloi)

## Mode d’emploi

Dans un terminal : 

- compilation (avec `gcc`) : `$ make`,
- exécution : `$ ./quiz`,
- afficher l’aide : `$ ./quiz -h`.

Pour chacun des 118 éléments du tableau périodique, le numéro atomique est affiché et il faut donner le *symbole* et le *nom* de l’élément :

```
116 ? : Lv Livermorium
Oui !
```

On peut donner sa langue au chat en frappant directement la touche *entrée*, et on peut arrêter le jeu en avec `q` :

```
74 ? : q
Arrêt du jeu :'(
```

À la fin du jeu (après avoir répondu exactement aux 118 éléments, ou après avoir arrêté avant avec `q`), un pseudo est demandé pour enregistrer le score dans le fichier d’historique `scores.md`, en voici un exemple :

```
| Pseudo           | AAAA-MM-JJ,hh:mm:ss | #el |    MS |    MN | #tt | #ko | #ok | A | L | Tps, s |
|:-----------------|:-------------------:|----:|------:|------:|----:|----:|----:|:-:|:-:|-------:|
| dev-modes        | 2020-11-02,23:03:31 | 118 | 0.017 | 0.015 |   7 |   0 |   3 | 0 | 0 |     30 |
| dev-modes        | 2020-11-02,23:04:55 | 118 | 0.008 | 0.008 |   1 |   0 |   1 | 1 | 0 |      6 |
| dev-modes        | 2020-11-02,23:05:27 | 118 | 0.025 | 0.025 |   3 |   0 |   3 | 0 | 1 |     15 |
| dev-modes        | 2020-11-02,23:05:50 | 118 | 0.017 | 0.017 |   2 |   0 |   2 | 1 | 1 |      9 |
```

Le contenu des colonnes est :

- `Pseudo` : le pseudo donné par le joueur (16 caractères maximum),
- `AAAA-MM-JJ,hh:mm:ss` : date au [format iso-8601](https://xkcd.com/1179/),
- `#el` : nombre d’éléments chimiques (118 au 2020-10-14),
- `MS` : note moyenne sur les *symboles* des éléments,
- `MN` : note moyenne sur les *noms* des éléments,
- `#tt` : nombre de tentatives,
- `#ko` : nombre de langue-au-chat,
- `#ok` : nombre de réponses exactes,
- `A` : mode approximatif ? (`0` : non, `1` : oui),
- `L` : mode léger ? (`0` : non, `1` : oui),
- `Tps, s` : Durée du jeu en secondes.

