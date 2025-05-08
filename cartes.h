// === cartes.h ===
#ifndef CARTES_H
#define CARTES_H

#define MAX_JOUEURS 8

// Nombre maximal de cartes que peut contenir la main d'un joueur
#define MAX_CARTES_MAIN 12

// Taille maximale du deck (pioche) total du jeu
#define TAILLE_DECK 200

// Représentation d'une carte avec sa valeur et sa visibilité
typedef struct {
    int valeur;     // Valeur de la carte 
    int visible;    // 1 si la carte est visible, 0 sinon
} Carte;

// Représentation d'un joueur
typedef struct {
    char nom[50];                        // Nom du joueur
    Carte main[MAX_CARTES_MAIN];        // Main du joueur (cartes en main)
    int tailleMain;                     // Nombre de cartes actuellement dans la main
    Carte defausse[MAX_CARTES_MAIN];    // Pile de défausse personnelle du joueur
    int sommetDefausse;                 // Index du sommet de la pile de défausse (nombre de cartes défaussées)
    int score;                          // Score total du joueur (calculé à la fin de la partie)
} Joueur;

// Représentation de la pioche centrale
typedef struct {
    Carte cartes[TAILLE_DECK];  // Tableau contenant toutes les cartes disponibles pour la pioche
    int sommet;                 // Index de la prochaine carte à tirer (diminue à chaque pioche)
} Pioche;

#endif
