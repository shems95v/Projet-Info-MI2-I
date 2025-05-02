// === cartes.h ===
#ifndef CARTES_H
#define CARTES_H

#define MAX_JOUEURS 8
#define MAX_CARTES_MAIN 12
#define TAILLE_DECK 200

typedef struct {
    int valeur;
    int visible;
} Carte;

typedef struct {
    char nom[50];
    Carte main[MAX_CARTES_MAIN];
    int tailleMain;
    Carte defausse[MAX_CARTES_MAIN];
    int sommetDefausse;
    int score;
} Joueur;

typedef struct {
    Carte cartes[TAILLE_DECK];
    int sommet;
} Pioche;

#endif
