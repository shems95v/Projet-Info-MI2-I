// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cartes.h"

// Fonctions déclarées dans les autres fichiers
void initialiser_pioche(Pioche *pioche);
void distribuer_cartes(Joueur joueurs[], int nbJoueurs, Pioche *pioche, int cartesParJoueur);
void afficher_etat_jeu(Joueur joueurs[], int nbJoueurs, Pioche *pioche);
int toutes_cartes_visibles(Joueur joueur);
int calculer_score(Joueur joueur);

int main() {
    int nbJoueurs;
    int cartesParJoueur = 6;
    Joueur joueurs[MAX_JOUEURS];
    Pioche pioche;

    printf("Bienvenue dans le jeu CardYard !\n");
    do {
        printf("Entrez le nombre de joueurs (2 à 8) : ");
        scanf("%d", &nbJoueurs);
    } while (nbJoueurs < 2 || nbJoueurs > MAX_JOUEURS);

    for (int i = 0; i < nbJoueurs; i++) {
        printf("Nom du joueur %d : ", i + 1);
        scanf("%s", joueurs[i].nom);
    }

    initialiser_pioche(&pioche);
    distribuer_cartes(joueurs, nbJoueurs, &pioche, cartesParJoueur);

    int partie_terminee = 0;
    while (!partie_terminee) {
        for (int i = 0; i < nbJoueurs; i++) {
            afficher_etat_jeu(joueurs, nbJoueurs, &pioche);
            printf("Tour de %s. Pioche une carte ? (o/n) : ", joueurs[i].nom);
            char reponse;
            scanf(" %c", &reponse);
            if (reponse == 'o') {
                if (pioche.sommet == 0) {
                    printf("La pioche est vide !\n");
                    continue;
                }
                Carte carte = pioche.cartes[--pioche.sommet];
                printf("Vous avez pioché : %d\n", carte.valeur);
                int indexEchange;
                do {
                    printf("Quelle carte voulez-vous échanger ? (0-%d ou -1 pour défausser) : ", cartesParJoueur - 1);
                    scanf("%d", &indexEchange);
                } while (indexEchange < -1 || indexEchange >= cartesParJoueur);

                if (indexEchange == -1) {
                    joueurs[i].defausse[joueurs[i].sommetDefausse++] = carte;
                } else {
                    Carte temp = joueurs[i].main[indexEchange];
                    joueurs[i].main[indexEchange] = carte;
                    joueurs[i].main[indexEchange].visible = 1;
                    joueurs[i].defausse[joueurs[i].sommetDefausse++] = temp;
                }

                if (toutes_cartes_visibles(joueurs[i])) {
                    printf("%s a retourné toutes ses cartes ! Dernier tour pour les autres joueurs...\n", joueurs[i].nom);
                    partie_terminee = 1;
                    break;
                }
            }
        }
    }

    // Tour final des autres joueurs
    for (int i = 0; i < nbJoueurs; i++) {
        if (toutes_cartes_visibles(joueurs[i])) continue;
        printf("Tour final pour %s.\n", joueurs[i].nom);
        // On pourrait refaire la logique ici si besoin
    }

    // Affichage des scores
    printf("\n===== Résultats =====\n");
    for (int i = 0; i < nbJoueurs; i++) {
        printf("%s : %d points\n", joueurs[i].nom, calculer_score(joueurs[i]));
    }

    printf("Merci d'avoir joué à CardYard !\n");

    return 0;
}
