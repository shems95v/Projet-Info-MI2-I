// === initialisation.c ===
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cartes.h"

// === Variante VALUE_FILE ===
// Initialise la pioche à partir d’un fichier texte contenant les paires "valeur quantité"
void initialiser_pioche_from_file(Pioche *pioche, const char *filename) {
    FILE *f = fopen(filename, "r"); // Ouvre le fichier en lecture
    if (!f) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", filename);
        exit(1);
    }

    int valeur, quantite;
    int index = 0;

    // Lecture des paires (valeur, quantite) tant que le fichier en contient
    while (fscanf(f, "%d %d", &valeur, &quantite) == 2 && index < TAILLE_DECK) {
        for (int i = 0; i < quantite && index < TAILLE_DECK; i++) {
            pioche->cartes[index++] = (Carte){valeur, 0}; // Ajoute la carte à la pioche
        }
    }
    fclose(f);
    pioche->sommet = index; // Mémorise le nombre total de cartes

    // Mélange aléatoire de la pioche
    srand(time(NULL));
    for (int i = 0; i < pioche->sommet; i++) {
        int r = rand() % pioche->sommet;
        Carte temp = pioche->cartes[i];
        pioche->cartes[i] = pioche->cartes[r];
        pioche->cartes[r] = temp;
    }
}

// === Variante VALUE_USER ===
// Demande à l'utilisateur de définir la plage de valeurs et les quantités pour chaque valeur
void initialiser_pioche_from_user(Pioche *pioche) {
    int minVal, maxVal, quantite;

    // Message d'aide
    printf("\n=== VARIANTE VALUE_USER ===\n");
    printf("Vous allez définir les cartes présentes dans la pioche.\n");
    printf("Pour cela, vous indiquerez une plage de valeurs (exemple : -5 à 15),\n");
    printf("et pour chaque valeur, combien de cartes doivent être ajoutées.\n\n");

    // Saisie des bornes
    printf("Valeur minimale : "); scanf("%d", &minVal);
    printf("Valeur maximale : "); scanf("%d", &maxVal);

    int index = 0;

    // Pour chaque valeur de la plage, demander combien de cartes ajouter
    for (int val = minVal; val <= maxVal; val++) {
        printf("Combien de cartes pour la valeur %d ? ", val);
        scanf("%d", &quantite);
        for (int i = 0; i < quantite && index < TAILLE_DECK; i++) {
            pioche->cartes[index++] = (Carte){val, 0};
        }
    }
    pioche->sommet = index;

    // Mélange de la pioche
    srand(time(NULL));
    for (int i = 0; i < pioche->sommet; i++) {
        int r = rand() % pioche->sommet;
        Carte temp = pioche->cartes[i];
        pioche->cartes[i] = pioche->cartes[r];
        pioche->cartes[r] = temp;
    }
}

// === Variante par défaut ===
// Initialise la pioche avec les valeurs classiques définies dans le sujet
void initialiser_pioche(Pioche *pioche) {
    int index = 0;

    // Ajout des cartes spéciales (valeurs -2, -1, 0)
    for (int i = 0; i < 5; i++)  pioche->cartes[index++] = (Carte){-2, 0};
    for (int i = 0; i < 10; i++) pioche->cartes[index++] = (Carte){-1, 0};
    for (int i = 0; i < 15; i++) pioche->cartes[index++] = (Carte){0, 0};

    // Ajout des cartes de 1 à 12 (10 exemplaires de chaque)
    for (int val = 1; val <= 12; val++)
        for (int i = 0; i < 10; i++)
            pioche->cartes[index++] = (Carte){val, 0};

    pioche->sommet = index;

    // Mélange de la pioche
    srand(time(NULL));
    for (int i = 0; i < pioche->sommet; i++) {
        int r = rand() % pioche->sommet;
        Carte temp = pioche->cartes[i];
        pioche->cartes[i] = pioche->cartes[r];
        pioche->cartes[r] = temp;
    }
}

// === Distribution des cartes aux joueurs ===
// Pioche les cartes et les attribue à chaque joueur (en les cachant)
void distribuer_cartes(Joueur joueurs[], int nbJoueurs, Pioche *pioche, int cartesParJoueur) {
    for (int j = 0; j < nbJoueurs; j++) {
        joueurs[j].tailleMain = cartesParJoueur;
        joueurs[j].sommetDefausse = 0;

        // Pioche les cartes pour la main du joueur
        for (int c = 0; c < cartesParJoueur; c++) {
            joueurs[j].main[c] = pioche->cartes[--pioche->sommet];
            joueurs[j].main[c].visible = 0; // elles sont cachées au départ
        }
    }
}
