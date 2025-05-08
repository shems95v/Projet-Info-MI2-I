// === main.c ===
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cartes.h"
#include "affichage.h"

// Prototypes des fonctions d'initialisation (définies ailleurs)
void initialiser_pioche(Pioche *pioche);
void distribuer_cartes(Joueur joueurs[], int nbJoueurs, Pioche *pioche, int cartesParJoueur);

// Vérifie si toutes les cartes d'un joueur sont visibles (condition de fin de partie)
int toutes_cartes_visibles(Joueur j) {
    for (int i = 0; i < j.tailleMain; i++) {
        if (!j.main[i].visible) return 0;
    }
    return 1;
}

// Sauvegarde l’état complet de la partie dans un fichier texte
void sauvegarder_partie(Joueur joueurs[], int nbJoueurs, Pioche *pioche, int cartesParJoueur) {
    FILE *f = fopen("sauvegarde.txt", "w");
    if (!f) return;

    fprintf(f, "%d %d\n", nbJoueurs, cartesParJoueur); // En-tête : nb de joueurs et cartes/joueur
    for (int i = 0; i < nbJoueurs; i++) {
        fprintf(f, "%s\n", joueurs[i].nom);
        for (int j = 0; j < cartesParJoueur; j++)
            fprintf(f, "%d %d\n", joueurs[i].main[j].valeur, joueurs[i].main[j].visible);
        fprintf(f, "%d\n", joueurs[i].sommetDefausse);
        for (int j = 0; j < joueurs[i].sommetDefausse; j++)
            fprintf(f, "%d %d\n", joueurs[i].defausse[j].valeur, joueurs[i].defausse[j].visible);
    }

    fprintf(f, "%d\n", pioche->sommet);
    for (int i = 0; i < pioche->sommet; i++)
        fprintf(f, "%d %d\n", pioche->cartes[i].valeur, pioche->cartes[i].visible);

    fclose(f);
}

// Recharge une partie précédemment sauvegardée
int charger_partie(Joueur joueurs[], int *nbJoueurs, Pioche *pioche, int *cartesParJoueur) {
    FILE *f = fopen("sauvegarde.txt", "r");
    if (!f) return 0;

    fscanf(f, "%d %d", nbJoueurs, cartesParJoueur);
    for (int i = 0; i < *nbJoueurs; i++) {
        fscanf(f, "%s", joueurs[i].nom);
        joueurs[i].tailleMain = *cartesParJoueur;
        for (int j = 0; j < *cartesParJoueur; j++)
            fscanf(f, "%d %d", &joueurs[i].main[j].valeur, &joueurs[i].main[j].visible);
        fscanf(f, "%d", &joueurs[i].sommetDefausse);
        for (int j = 0; j < joueurs[i].sommetDefausse; j++)
            fscanf(f, "%d %d", &joueurs[i].defausse[j].valeur, &joueurs[i].defausse[j].visible);
    }
    fscanf(f, "%d", &pioche->sommet);
    for (int i = 0; i < pioche->sommet; i++)
        fscanf(f, "%d %d", &pioche->cartes[i].valeur, &pioche->cartes[i].visible);

    fclose(f);
    return 1;
}

int main() {
    Joueur joueurs[MAX_JOUEURS];
    Pioche pioche;
    int nbJoueurs = 0, cartesParJoueur = 6, choix;

    // Menu principal
    printf("=== CARDYARD ===\n1. Nouvelle partie\n2. Charger partie\nChoix : ");
    scanf("%d", &choix);

    if (choix == 2) {
        // Chargement d'une partie sauvegardée
        if (!charger_partie(joueurs, &nbJoueurs, &pioche, &cartesParJoueur)) {
            printf("Échec du chargement.\n");
            return 1;
        }
    } else {
        // Configuration d'une nouvelle partie
        do {
            printf("Nombre de joueurs (2-8) : ");
            scanf("%d", &nbJoueurs);
        } while (nbJoueurs < 2 || nbJoueurs > MAX_JOUEURS);

        // Entrée des noms
        for (int i = 0; i < nbJoueurs; i++) {
            printf("Nom du joueur %d : ", i+1);
            scanf("%s", joueurs[i].nom);
        }

        // Sélection du nombre de cartes par joueur
        printf("Nombre de cartes par joueur ?\n1. Par défaut (6)\n2. Choix manuel\n3. Aléatoire\nChoix : ");
        scanf("%d", &choix);
        if (choix == 2) {
            do {
                printf("Combien de cartes ? (1-%d) : ", MAX_CARTES_MAIN);
                scanf("%d", &cartesParJoueur);
            } while (cartesParJoueur < 1 || cartesParJoueur > MAX_CARTES_MAIN);
        } else if (choix == 3) {
            srand(time(NULL));
            cartesParJoueur = 4 + rand() % 5; // entre 4 et 8
        }

        // Initialisation du jeu
        initialiser_pioche(&pioche);
        distribuer_cartes(joueurs, nbJoueurs, &pioche, cartesParJoueur);
    }

    // Boucle principale du jeu
    int partie_terminee = 0;
    int joueur_ayant_termine = -1;

    while (!partie_terminee) {
        for (int i = 0; i < nbJoueurs; i++) {
            // Si un joueur a terminé, on saute son tour
            if (joueur_ayant_termine != -1 && i == joueur_ayant_termine) continue;

            // Affichage du plateau
            afficher_plateau(joueurs, nbJoueurs, &pioche);

            // Tour du joueur
            printf("%s, choisissez :\n1. Piocher\n2. Prendre défausse\n3. Sauvegarder et quitter\n> ", joueurs[i].nom);
            scanf("%d", &choix);

            if (choix == 3) {
                sauvegarder_partie(joueurs, nbJoueurs, &pioche, cartesParJoueur);
                printf("Partie sauvegardée.\n");
                return 0;
            }

            // Carte choisie depuis la pioche ou la défausse d’un autre joueur
            Carte carte;
            if (choix == 1) {
                if (pioche.sommet == 0) {
                    printf("Pioche vide !\n");
                    continue;
                }
                carte = pioche.cartes[--pioche.sommet];
            } else if (choix == 2) {
                int cible;
                do {
                    printf("Quelle défausse ? (0-%d, pas la vôtre [%d]) : ", nbJoueurs-1, i);
                    scanf("%d", &cible);
                } while (cible == i || cible < 0 || cible >= nbJoueurs || joueurs[cible].sommetDefausse == 0);
                carte = joueurs[cible].defausse[joueurs[cible].sommetDefausse-1];
                joueurs[cible].sommetDefausse--;
            } else {
                continue;
            }

            // Action : échanger ou poser dans sa défausse
            printf("Carte : %d\nÉchanger avec quelle carte (0-%d) ou -1 pour poser en défausse ? ", carte.valeur, cartesParJoueur-1);
            int idx;
            scanf("%d", &idx);

            if (idx == -1) {
                // Défausse la carte sans échange
                joueurs[i].defausse[joueurs[i].sommetDefausse++] = carte;
            } else if (idx >= 0 && idx < cartesParJoueur) {
                // Échange avec une carte de la main
                Carte tmp = joueurs[i].main[idx];
                joueurs[i].main[idx] = carte;
                joueurs[i].main[idx].visible = 1;
                joueurs[i].defausse[joueurs[i].sommetDefausse++] = tmp;
            }

            // Fin de partie : toutes les cartes du joueur sont visibles
            if (toutes_cartes_visibles(joueurs[i])) {
                printf("%s a retourné toutes ses cartes ! Fin de la partie.\n", joueurs[i].nom);

                // Rendre toutes les cartes visibles pour tout le monde
                for (int j = 0; j < nbJoueurs; j++) {
                    for (int c = 0; c < joueurs[j].tailleMain; c++) {
                        joueurs[j].main[c].visible = 1;
                    }
                }

                // Affichage final du plateau et des scores
                afficher_plateau(joueurs, nbJoueurs, &pioche);
                afficher_scores_tries(joueurs, nbJoueurs);
                return 0;
            }
        }

        // Si un joueur avait déjà terminé au tour précédent, on sort de la boucle
        if (joueur_ayant_termine != -1)
            partie_terminee = 1;
    }

    // Affichage final si la boucle s’est terminée autrement
    afficher_scores_tries(joueurs, nbJoueurs);
    printf("Fin de partie !\n");
    return 0;
}
