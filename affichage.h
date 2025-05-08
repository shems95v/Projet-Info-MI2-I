// === affichage.h ===
#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "cartes.h" 

// === Définitions de constantes ANSI pour le texte ===
// Permettent de colorer le texte dans le terminal 
#define RESET       "\x1b[0m"   // Réinitialise la couleur
#define NOIR        "\x1b[30m"
#define ROUGE       "\x1b[31m"
#define VERT        "\x1b[32m"
#define JAUNE       "\x1b[33m"
#define BLEU        "\x1b[34m"
#define MAGENTA     "\x1b[35m"
#define CYAN        "\x1b[36m"
#define BLANC       "\x1b[37m"

// === Définitions de constantes ANSI pour le fond ===
// Permettent de colorer l’arrière-plan du texte
#define BG_NOIR     "\x1b[40m"
#define BG_ROUGE    "\x1b[41m"
#define BG_VERT     "\x1b[42m"
#define BG_JAUNE    "\x1b[43m"
#define BG_BLEU     "\x1b[44m"
#define BG_MAGENTA  "\x1b[45m"
#define BG_CYAN     "\x1b[46m"
#define BG_BLANC    "\x1b[47m"

// === Prototypes de fonctions d'affichage ===

// Affiche tout le plateau de jeu : les cartes des joueurs, leurs défausses, et la pioche centrale
void afficher_plateau(Joueur joueurs[], int nbJoueurs, Pioche *pioche);

// Affiche les scores de tous les joueurs triés par ordre croissant
void afficher_scores_tries(Joueur joueurs[], int nbJoueurs);

#endif
