// jeu.c

#include <stdio.h>
#include "cartes.h"

void afficher_carte(Carte carte) {
    if (carte.visible)
        printf("[ %2d ]", carte.valeur);
    else
        printf("[ ?? ]");
}

void afficher_joueur(Joueur joueur) {
    printf("Joueur %s : ", joueur.nom);
    for (int i = 0; i < joueur.tailleMain; i++) {
        afficher_carte(joueur.main[i]);
    }
    printf(" | Défausse : ");
    if (joueur.sommetDefausse > 0)
        printf("[ %2d ]\n", joueur.defausse[joueur.sommetDefausse - 1].valeur);
    else
        printf("[ vide ]\n");
}

void afficher_etat_jeu(Joueur joueurs[], int nbJoueurs, Pioche *pioche) {
    printf("\n==== État actuel du jeu ====\n");
    for (int i = 0; i < nbJoueurs; i++) {
        afficher_joueur(joueurs[i]);
    }
    printf("Pioche centrale : %d cartes restantes\n", pioche->sommet);
}

int toutes_cartes_visibles(Joueur joueur) {
    for (int i = 0; i < joueur.tailleMain; i++) {
        if (!joueur.main[i].visible)
            return 0;
    }
    return 1;
}

int calculer_score(Joueur joueur) {
    int score = 0;
    for (int i = 0; i < joueur.tailleMain; i++) {
        score += joueur.main[i].valeur;
    }
    return score;
}
