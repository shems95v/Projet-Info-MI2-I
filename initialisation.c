// === initialisation.c ===
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cartes.h"

// Fonction pour initialiser la pioche avec un ensemble défini de cartes
void initialiser_pioche(Pioche *pioche) {
    int index = 0;

    // Ajout de 5 cartes de valeur -2 (effet spécial négatif fort)
    for (int i = 0; i < 5; i++)
        pioche->cartes[index++] = (Carte){-2, 0};

    // Ajout de 10 cartes de valeur -1
    for (int i = 0; i < 10; i++)
        pioche->cartes[index++] = (Carte){-1, 0};

    // Ajout de 15 cartes de valeur 0
    for (int i = 0; i < 15; i++)
        pioche->cartes[index++] = (Carte){0, 0};

    // Pour chaque valeur de 1 à 12, ajouter 10 cartes
    for (int val = 1; val <= 12; val++)
        for (int i = 0; i < 10; i++)
            pioche->cartes[index++] = (Carte){val, 0};

    // Mise à jour de l'index du sommet de la pioche
    pioche->sommet = index;

    // Mélange de la pioche à l’aide de l’algorithme de Fisher-Yates

    srand(time(NULL)); 
    for (int i = 0; i < pioche->sommet; i++) {
        int r = rand() % pioche->sommet; // Position aléatoire
        Carte temp = pioche->cartes[i];
        pioche->cartes[i] = pioche->cartes[r];
        pioche->cartes[r] = temp;
    }
}

// Fonction pour distribuer les cartes aux joueurs à partir de la pioche
void distribuer_cartes(Joueur joueurs[], int nbJoueurs, Pioche *pioche, int cartesParJoueur) {
    for (int j = 0; j < nbJoueurs; j++) {
        joueurs[j].tailleMain = cartesParJoueur;   // Nombre de cartes attribuées
        joueurs[j].sommetDefausse = 0;             // La défausse du joueur commence vide

        // Distribution des cartes une à une depuis le sommet de la pioche
        for (int c = 0; c < cartesParJoueur; c++) {
            joueurs[j].main[c] = pioche->cartes[--pioche->sommet]; // Pioche la carte
            joueurs[j].main[c].visible = 0; // Les cartes sont distribuées face cachée
        }
    }
}
