// === jeu.c ===

#include <stdio.h>
#include <string.h>
#include "cartes.h"
#include "affichage.h"

// Affiche un nom centré par rapport à la largeur du bloc de cartes
void afficher_nom_centre(const char *nom, int nbCartes) {
    int largeur = nbCartes * 13; // 13 caractères par carte (largeur graphique)
    int espaces = (largeur - (int)strlen(nom)) / 2; // Calcul des espaces à gauche pour centrer
    for (int i = 0; i < espaces; i++)
        printf(" ");
    printf("%s\n", nom);
}

// Affiche une ligne d'une carte (en 3 lignes graphiques)
void afficher_carte_ligne(Carte carte, int ligne) {
    if (carte.visible) {
        // Définition des couleurs selon la valeur de la carte
        char *couleurTexte, *couleurFond;
        switch (carte.valeur) {
            case -20: couleurTexte = BLANC; couleurFond = "\x1b[48;5;17m"; break;
            case -19: couleurTexte = BLANC; couleurFond = "\x1b[48;5;18m"; break;
            case -18: couleurTexte = BLANC; couleurFond = "\x1b[48;5;19m"; break;
            case -17: couleurTexte = BLANC; couleurFond = "\x1b[48;5;20m"; break;
            case -16: couleurTexte = BLANC; couleurFond = "\x1b[48;5;21m"; break;
            case -15: couleurTexte = BLANC; couleurFond = "\x1b[48;5;22m"; break;
            case -14: couleurTexte = BLANC; couleurFond = "\x1b[48;5;23m"; break;
            case -13: couleurTexte = BLANC; couleurFond = "\x1b[48;5;24m"; break;
            case -12: couleurTexte = BLANC; couleurFond = "\x1b[48;5;25m"; break;
            case -11: couleurTexte = BLANC; couleurFond = "\x1b[48;5;26m"; break;
            case -10: couleurTexte = BLANC; couleurFond = "\x1b[48;5;27m"; break;
            case -9:  couleurTexte = BLANC; couleurFond = "\x1b[48;5;28m"; break;
            case -8:  couleurTexte = BLANC; couleurFond = "\x1b[48;5;29m"; break;
            case -7:  couleurTexte = BLANC; couleurFond = "\x1b[48;5;30m"; break;
            case -6:  couleurTexte = BLANC; couleurFond = "\x1b[48;5;31m"; break;
            case -5:  couleurTexte = BLANC; couleurFond = "\x1b[48;5;32m"; break;
            case -4:  couleurTexte = BLANC; couleurFond = "\x1b[48;5;33m"; break;
            case -3:  couleurTexte = BLANC; couleurFond = "\x1b[48;5;34m"; break;
            case -2:  couleurTexte = BLANC; couleurFond = "\x1b[48;5;35m"; break;
            case -1:  couleurTexte = BLANC; couleurFond = "\x1b[48;5;36m"; break;
            case 0:   couleurTexte = BLANC; couleurFond = "\x1b[48;5;37m"; break;
            case 1:   couleurTexte = NOIR;  couleurFond = "\x1b[48;5;38m"; break;
            case 2:   couleurTexte = NOIR;  couleurFond = "\x1b[48;5;39m"; break;
            case 3:   couleurTexte = NOIR;  couleurFond = "\x1b[48;5;40m"; break;
            case 4:   couleurTexte = NOIR;  couleurFond = "\x1b[48;5;41m"; break;
            case 5:   couleurTexte = NOIR;  couleurFond = "\x1b[48;5;42m"; break;
            case 6:   couleurTexte = NOIR;  couleurFond = "\x1b[48;5;43m"; break;
            case 7:   couleurTexte = NOIR;  couleurFond = "\x1b[48;5;44m"; break;
            case 8:   couleurTexte = NOIR;  couleurFond = "\x1b[48;5;45m"; break;
            case 9:   couleurTexte = NOIR;  couleurFond = "\x1b[48;5;46m"; break;
            case 10:  couleurTexte = NOIR;  couleurFond = "\x1b[48;5;47m"; break;
            case 11:  couleurTexte = NOIR;  couleurFond = "\x1b[48;5;48m"; break;
            case 12:  couleurTexte = NOIR;  couleurFond = "\x1b[48;5;49m"; break;
            case 13:  couleurTexte = NOIR;  couleurFond = "\x1b[48;5;50m"; break;
            case 14:  couleurTexte = NOIR;  couleurFond = "\x1b[48;5;51m"; break;
            case 15:  couleurTexte = BLANC;  couleurFond = "\x1b[48;5;52m"; break;
            case 16:  couleurTexte = NOIR;  couleurFond = "\x1b[48;5;53m"; break;
            case 17:  couleurTexte = NOIR;  couleurFond = "\x1b[48;5;54m"; break;
            case 18:  couleurTexte = NOIR;  couleurFond = "\x1b[48;5;55m"; break;
            case 19:  couleurTexte = NOIR;  couleurFond = "\x1b[48;5;56m"; break;
            case 20:  couleurTexte = NOIR;  couleurFond = "\x1b[48;5;57m"; break;
            default:  couleurTexte = BLANC; couleurFond = BG_NOIR; break;
        }

        // Affichage ligne par ligne de la carte visible
        switch (ligne) {
            case 0: printf("╭────────────╮ "); break; // bord supérieur
            case 1: {
                char buffer[8];
                snprintf(buffer, sizeof(buffer), "%d", carte.valeur);
                int totalWidth = 12;
                int len = strlen(buffer);
                int pad = (totalWidth - len) / 2;
                printf("│%s%s", couleurFond, couleurTexte);
                for (int i = 0; i < pad; i++) printf(" ");
                printf("%s", buffer);
                for (int i = 0; i < totalWidth - len - pad; i++) printf(" ");
                printf("%s│ ", RESET);
                break;
            }
            case 2: printf("╰────────────╯ "); break; // bord inférieur
        }
    } else {
        // Affichage de dos (carte non visible)
        switch (ligne) {
            case 0: printf("╭────────────╮ "); break;
            case 1: printf("│  CARD YARD │ "); break;
            case 2: printf("╰────────────╯ "); break;
        }
    }
}

// Affiche la dernière carte de la défausse d'un joueur (ou vide si aucune)
void afficher_defausse(Carte *defausse, int sommet) {
    if (sommet > 0) {
        // Affichage en 3 lignes de la carte au sommet de la défausse
        for (int ligne = 0; ligne < 3; ligne++) {
            afficher_carte_ligne(defausse[sommet - 1], ligne);
            printf("\n");
        }
    } else {
        // Message indiquant une défausse vide
        printf("┌──────────┐\n");
        printf("│  vide    │\n");
        printf("└──────────┘\n");
    }
}

// Affiche l'état complet du plateau de jeu
void afficher_plateau(Joueur joueurs[], int nbJoueurs, Pioche *pioche) {
    printf("\n========= ÉTAT DU PLATEAU =========\n");

    for (int i = 0; i < nbJoueurs; i++) {
        printf("\n");
        afficher_nom_centre(joueurs[i].nom, joueurs[i].tailleMain); // Nom du joueur

        // Affichage de la main du joueur (3 lignes par carte)
        for (int ligne = 0; ligne < 3; ligne++) {
            printf("        "); // Décalage horizontal
            for (int c = 0; c < joueurs[i].tailleMain; c++) {
                afficher_carte_ligne(joueurs[i].main[c], ligne);
            }
            printf("\n");
        }

        // Affichage de la défausse du joueur
        printf("Défausse de %s :\n", joueurs[i].nom);
        for (int ligne = 0; ligne < 3; ligne++) {
            printf("                    "); // Alignement à droite
            afficher_carte_ligne(
                joueurs[i].sommetDefausse > 0
                    ? joueurs[i].defausse[joueurs[i].sommetDefausse - 1] // carte au sommet
                    : (Carte){0, 0},  // carte par défaut (vide)
                ligne
            );
            printf("\n");
        }
    }

    // Affichage de la pioche centrale
    printf("\n\nPioche centrale :\n");
    if (pioche->sommet > 0) {
        printf("┌──────────┐\n│  PIOCHE  │\n└──────────┘\n");
    } else {
        printf("┌──────────┐\n│  (vide)  │\n└──────────┘\n");
    }

    printf("\n========= FIN DU PLATEAU =========\n");
}
