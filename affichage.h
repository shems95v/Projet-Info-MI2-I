// === affichage.h ===
#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "cartes.h"

#define RESET       "\x1b[0m"
#define NOIR        "\x1b[30m"
#define ROUGE       "\x1b[31m"
#define VERT        "\x1b[32m"
#define JAUNE       "\x1b[33m"
#define BLEU        "\x1b[34m"
#define MAGENTA     "\x1b[35m"
#define CYAN        "\x1b[36m"
#define BLANC       "\x1b[37m"

#define BG_NOIR     "\x1b[40m"
#define BG_ROUGE    "\x1b[41m"
#define BG_VERT     "\x1b[42m"
#define BG_JAUNE    "\x1b[43m"
#define BG_BLEU     "\x1b[44m"
#define BG_MAGENTA  "\x1b[45m"
#define BG_CYAN     "\x1b[46m"
#define BG_BLANC    "\x1b[47m"

void afficher_carte_colorée(Carte carte);
void afficher_plateau(Joueur joueurs[], int nbJoueurs, Pioche *pioche);
void afficher_scores_tries(Joueur joueurs[], int nbJoueurs);

#endif
