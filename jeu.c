// jeu.c

#include <stdio.h>
#include <string.h>
#include "cartes.h"
#include "affichage.h"

// Centrage du nom
void afficher_nom_centre(const char *nom, int nbCartes) {
    int largeur = nbCartes * 13;
    int espaces = (largeur - (int)strlen(nom)) / 2;
    for (int i = 0; i < espaces; i++) printf(" ");
    printf("%s\n", nom);
}

// Une ligne de carte
void afficher_carte_ligne(Carte carte, int ligne) {
    if (carte.visible) {
        // Carte visible en couleurs
        char *couleurTexte, *couleurFond;
        switch (carte.valeur) {
            case -2: couleurTexte = NOIR; couleurFond = BG_MAGENTA; break;
            case -1: couleurTexte = BLANC; couleurFond = BG_MAGENTA; break;
            case 0:  couleurTexte = NOIR; couleurFond = BG_BLEU; break;
            case 4:  couleurTexte = NOIR; couleurFond = BG_VERT; break;
            case 8:  couleurTexte = NOIR; couleurFond = BG_JAUNE; break;
            case 12: couleurTexte = BLANC; couleurFond = BG_ROUGE; break;
            default: couleurTexte = BLANC; couleurFond = BG_NOIR; break;
        }

        if (ligne == 0)
            printf("┌──────────┐ ");
        else if (ligne == 1)
            printf("│%s%s   %2d    %s│ ", couleurFond, couleurTexte, carte.valeur, RESET);
        else if (ligne == 2)
            printf("└──────────┘ ");
    } else {
        // Carte cachée
        if (ligne == 0)
            printf("┌──────────┐ ");
        else if (ligne == 1)
            printf("│ CARD YARD│ ");
        else if (ligne == 2)
            printf("└──────────┘ ");
    }
}

// Affiche la dernière carte de la défausse (ou vide)
void afficher_defausse(Carte *defausse, int sommet) {
    if (sommet > 0) {
        for (int ligne = 0; ligne < 3; ligne++) {
            afficher_carte_ligne(defausse[sommet - 1], ligne);
            printf("\n");
        }
    } else {
        printf("┌──────────┐\n");
        printf("│  vide    │\n");
        printf("└──────────┘\n");
    }
}

// Affiche le plateau complet, chaque joueur verticalement
void afficher_plateau(Joueur joueurs[], int nbJoueurs, Pioche *pioche) {
    printf("\n========= ÉTAT DU PLATEAU =========\n");

    for (int i = 0; i < nbJoueurs; i++) {
        printf("\n");
        afficher_nom_centre(joueurs[i].nom, joueurs[i].tailleMain);
        for (int ligne = 0; ligne < 3; ligne++) {
            printf("        ");
            for (int c = 0; c < joueurs[i].tailleMain; c++) {
                afficher_carte_ligne(joueurs[i].main[c], ligne);
            }
            printf("\n");
        }
        printf("Défausse de %s :\n", joueurs[i].nom);
        for (int ligne = 0; ligne < 3; ligne++) {
            printf("                    "); // 20 espaces ≈ alignement avec début du nom
             afficher_carte_ligne(
             joueurs[i].sommetDefausse > 0 ? joueurs[i].defausse[joueurs[i].sommetDefausse - 1]
                                      : (Carte){0, 0},  // carte vide par défaut
            ligne
    );
    printf("\n");
}

    }

    // Affiche l'état de la pioche à la fin
    printf("\n\nPioche centrale :\n");
    if (pioche->sommet > 0) {
        printf("┌──────────┐\n│  PIOCHE  │\n└──────────┘\n");
    } else {
        printf("┌──────────┐\n│  (vide)  │\n└──────────┘\n");
    }

    printf("\n========= FIN DU PLATEAU =========\n");
}
