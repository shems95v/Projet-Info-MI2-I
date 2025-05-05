// === affichage.c ===
#include <stdio.h>
#include <string.h>
#include "affichage.h"


void afficher_scores_tries(Joueur joueurs[], int nbJoueurs) {
    for (int i = 0; i < nbJoueurs; i++) {
        joueurs[i].score = 0;
        for (int j = 0; j < joueurs[i].tailleMain; j++) {
            joueurs[i].main[j].visible = 1;
            joueurs[i].score += joueurs[i].main[j].valeur;
        }
    }

    for (int i = 0; i < nbJoueurs - 1; i++) {
        for (int j = i + 1; j < nbJoueurs; j++) {
            if (joueurs[j].score < joueurs[i].score) {
                Joueur tmp = joueurs[i];
                joueurs[i] = joueurs[j];
                joueurs[j] = tmp;
            }
        }
    }

    printf("\nClassement :\n");
    for (int i = 0; i < nbJoueurs; i++) {
        printf("%s : %d points\n", joueurs[i].nom, joueurs[i].score);
    }
}
