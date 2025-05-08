// === affichage.c ===
#include <stdio.h>
#include <string.h>
#include "affichage.h"

// Fonction qui calcule et affiche les scores des joueurs, triés par ordre croissant
void afficher_scores_tries(Joueur joueurs[], int nbJoueurs) {

    // Étape 1 : calculer les scores de chaque joueur
    for (int i = 0; i < nbJoueurs; i++) {
        joueurs[i].score = 0; // Initialisation du score

        // Toutes les cartes sont rendues visibles pour affichage final
        for (int j = 0; j < joueurs[i].tailleMain; j++) {
            joueurs[i].main[j].visible = 1; // Carte révélée
            joueurs[i].score += joueurs[i].main[j].valeur; // Ajout de la valeur au score
        }
    }

    // Étape 2 : tri des joueurs selon leur score (ordre croissant)
    for (int i = 0; i < nbJoueurs - 1; i++) {
        for (int j = i + 1; j < nbJoueurs; j++) {
            if (joueurs[j].score < joueurs[i].score) {
                // Échange des structures Joueur pour trier
                Joueur tmp = joueurs[i];
                joueurs[i] = joueurs[j];
                joueurs[j] = tmp;
            }
        }
    }

    // Étape 3 : affichage du classement final
    printf("\nClassement :\n");
    for (int i = 0; i < nbJoueurs; i++) {
        printf("%s : %d points\n", joueurs[i].nom, joueurs[i].score);
    }
    printf("\nLe vainqueur est : %s avec %d points !\n", joueurs[0].nom, joueurs[0].score);
}

