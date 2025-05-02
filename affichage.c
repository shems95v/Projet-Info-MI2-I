// === affichage.c ===
#include <stdio.h>
#include <string.h>
#include "affichage.h"

void afficher_carte_colorée(Carte carte) {
    char *couleurTexte, *couleurFond;

    if (!carte.visible) {
        couleurTexte = BLANC;
        couleurFond = BG_NOIR;
    } else {
        switch (carte.valeur) {
            case -2: couleurTexte = NOIR; couleurFond = BG_MAGENTA; break;
            case -1: couleurTexte = NOIR; couleurFond = BG_CYAN; break;
            case 0:  couleurTexte = NOIR; couleurFond = BG_BLEU; break;
            case 1:  couleurTexte = NOIR; couleurFond = BG_VERT; break;
            case 2:  couleurTexte = NOIR; couleurFond = BG_JAUNE; break;
            case 3:  couleurTexte = NOIR; couleurFond = BG_ROUGE; break;
            case 4:  couleurTexte = BLANC; couleurFond = BG_MAGENTA; break;
            case 5:  couleurTexte = NOIR; couleurFond = BG_BLANC; break;
            case 6:  couleurTexte = BLANC; couleurFond = BG_CYAN; break;
            case 7:  couleurTexte = NOIR; couleurFond = BG_VERT; break;
            case 8:  couleurTexte = NOIR; couleurFond = BG_JAUNE; break;
            case 9:  couleurTexte = BLANC; couleurFond = BG_BLEU; break;
            case 10: couleurTexte = NOIR; couleurFond = BG_ROUGE; break;
            case 11: couleurTexte = NOIR; couleurFond = BG_BLANC; break;
            case 12: couleurTexte = BLANC; couleurFond = BG_ROUGE; break;
            default: couleurTexte = BLANC; couleurFond = BG_NOIR; break;
        }
    }

    printf("%s%s│   %2d    │%s\n", couleurFond, couleurTexte, carte.valeur, RESET);
}

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
