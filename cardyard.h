#ifndef CARDYARD_H
#define CARDYARD_H

#define MAX_JOUEURS 8
#define MAX_CARTES_MAIN 12
#define TAILLE_DECK 150

typedef struct {
    int valeur;
    int visible; // 0 = face cachée, 1 = face visible
} Carte;

typedef struct {
    char nom[50];
    Carte main[MAX_CARTES_MAIN];
    int tailleMain;
    Carte defausse[MAX_CARTES_MAIN];
    int sommetDefausse;
} Joueur;

typedef struct {
    Carte cartes[TAILLE_DECK];
    int sommet;
} Pioche;

#endif
