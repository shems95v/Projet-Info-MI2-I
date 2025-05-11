// === main.c ===
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cartes.h"
#include "affichage.h"

// Prototypes des fonctions d'initialisation
void initialiser_pioche(Pioche *pioche);
void initialiser_pioche_from_file(Pioche *pioche, const char *filename);
void initialiser_pioche_from_user(Pioche *pioche);
void distribuer_cartes(Joueur joueurs[], int nbJoueurs, Pioche *pioche, int cartesParJoueur);

// Vérifie si toutes les cartes d'un joueur sont visibles (retournées)
int toutes_cartes_visibles(Joueur j) {
    for (int i = 0; i < j.tailleMain; i++) {
        if (!j.main[i].visible) return 0;
    }
    return 1;
}

// Sauvegarde l'état actuel de la partie dans un fichier texte
void sauvegarder_partie(Joueur joueurs[], int nbJoueurs, Pioche *pioche, int cartesParJoueur) {
    FILE *f = fopen("sauvegarde.txt", "w");
    if (!f) return;

    // Sauvegarde des infos générales
    fprintf(f, "%d %d\n", nbJoueurs, cartesParJoueur);
    for (int i = 0; i < nbJoueurs; i++) {
        fprintf(f, "%s\n", joueurs[i].nom);
        for (int j = 0; j < cartesParJoueur; j++)
            fprintf(f, "%d %d\n", joueurs[i].main[j].valeur, joueurs[i].main[j].visible);
        fprintf(f, "%d\n", joueurs[i].sommetDefausse);
        for (int j = 0; j < joueurs[i].sommetDefausse; j++)
            fprintf(f, "%d %d\n", joueurs[i].defausse[j].valeur, joueurs[i].defausse[j].visible);
    }

    // Sauvegarde de la pioche
    fprintf(f, "%d\n", pioche->sommet);
    for (int i = 0; i < pioche->sommet; i++)
        fprintf(f, "%d %d\n", pioche->cartes[i].valeur, pioche->cartes[i].visible);

    fclose(f);
}

// Charge une partie précédemment sauvegardée
int charger_partie(Joueur joueurs[], int *nbJoueurs, Pioche *pioche, int *cartesParJoueur) {
    FILE *f = fopen("sauvegarde.txt", "r");
    if (!f) return 0;

    // Lecture des données de la sauvegarde
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

// === Fonction principale du programme ===
int main() {
    Joueur joueurs[MAX_JOUEURS];
    Pioche pioche;
    int nbJoueurs = 0, cartesParJoueur = 6, choix;

    // Menu principal
    printf("=== CARDYARD ===\n1. Nouvelle partie\n2. Charger partie\nChoix : ");
    scanf("%d", &choix);

    if (choix == 2) {
        // Reprise d'une partie sauvegardée
        if (!charger_partie(joueurs, &nbJoueurs, &pioche, &cartesParJoueur)) {
            printf("Échec du chargement.\n");
            return 1;
        }
    } else {
        // Création d'une nouvelle partie
        do {
            printf("Nombre de joueurs (2-8) : ");
            scanf("%d", &nbJoueurs);
        } while (nbJoueurs < 2 || nbJoueurs > MAX_JOUEURS);

        // Demande des noms
        for (int i = 0; i < nbJoueurs; i++) {
            printf("Nom du joueur %d : ", i+1);
            scanf("%s", joueurs[i].nom);
        }

        // Choix du nombre de cartes par joueur
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

        // Choix de la variante de pioche
        printf("Choix de la variante pour la pioche :\n");
        printf("1. Valeurs par défaut\n");
        printf("2. Charger depuis un fichier (VALUE_FILE)\n");
        printf("3. Entrer manuellement les valeurs (VALUE_USER)\n");
        printf("Votre choix : ");
        int variante;
        scanf("%d", &variante);

        if (variante == 2) {
            initialiser_pioche_from_file(&pioche, "valeurs.txt");
        } else if (variante == 3) {
            initialiser_pioche_from_user(&pioche);
        } else {
            initialiser_pioche(&pioche);
        }

        distribuer_cartes(joueurs, nbJoueurs, &pioche, cartesParJoueur);
    }

    int partie_terminee = 0;
    int joueur_ayant_termine = -1;

    // Boucle principale du jeu
    while (!partie_terminee) {
        for (int i = 0; i < nbJoueurs; i++) {
            if (joueur_ayant_termine != -1 && i == joueur_ayant_termine) continue;

            afficher_plateau(joueurs, nbJoueurs, &pioche);
            printf("%s, choisissez :\n1. Piocher\n2. Prendre défausse\n3. Sauvegarder et quitter\n> ", joueurs[i].nom);
            scanf("%d", &choix);

            // Sauvegarde et sortie
            if (choix == 3) {
                sauvegarder_partie(joueurs, nbJoueurs, &pioche, cartesParJoueur);
                printf("Partie sauvegardée.\n");
                return 0;
            }

            // Pioche ou prise depuis une défausse
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

            // Choix de l'action avec la carte tirée
            printf("Carte : %d\nÉchanger avec quelle carte (0-%d) ou -1 pour poser en défausse ? ", carte.valeur, cartesParJoueur-1);
            int idx;
            scanf("%d", &idx);

            if (idx == -1) {
                joueurs[i].defausse[joueurs[i].sommetDefausse++] = carte;
            } else if (idx >= 0 && idx < cartesParJoueur) {
                Carte tmp = joueurs[i].main[idx];
                joueurs[i].main[idx] = carte;
                joueurs[i].main[idx].visible = 1;
                joueurs[i].defausse[joueurs[i].sommetDefausse++] = tmp;
            }

            // Fin immédiate si toutes les cartes du joueur sont retournées
            if (toutes_cartes_visibles(joueurs[i])) {
                printf("%s a retourné toutes ses cartes ! Fin de la partie.\n", joueurs[i].nom);
                for (int j = 0; j < nbJoueurs; j++) {
                    for (int c = 0; c < joueurs[j].tailleMain; c++) {
                        joueurs[j].main[c].visible = 1;
                    }
                }
                afficher_plateau(joueurs, nbJoueurs, &pioche);
                afficher_scores_tries(joueurs, nbJoueurs);
                return 0;
            }
        }
    }

    afficher_scores_tries(joueurs, nbJoueurs);
    printf("Fin de partie !\n");
    return 0;
}
