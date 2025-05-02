// === initialisation.c ===
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cartes.h"

void initialiser_pioche(Pioche *pioche) {
    int index = 0;
    for (int i = 0; i < 5; i++) pioche->cartes[index++] = (Carte){-2, 0};
    for (int i = 0; i < 10; i++) pioche->cartes[index++] = (Carte){-1, 0};
    for (int i = 0; i < 15; i++) pioche->cartes[index++] = (Carte){0, 0};
    for (int val = 1; val <= 12; val++)
        for (int i = 0; i < 10; i++)
            pioche->cartes[index++] = (Carte){val, 0};
    pioche->sommet = index;

    srand(time(NULL));
    for (int i = 0; i < pioche->sommet; i++) {
        int r = rand() % pioche->sommet;
        Carte temp = pioche->cartes[i];
        pioche->cartes[i] = pioche->cartes[r];
        pioche->cartes[r] = temp;
    }
}

void distribuer_cartes(Joueur joueurs[], int nbJoueurs, Pioche *pioche, int cartesParJoueur) {
    for (int j = 0; j < nbJoueurs; j++) {
        joueurs[j].tailleMain = cartesParJoueur;
        joueurs[j].sommetDefausse = 0;
        for (int c = 0; c < cartesParJoueur; c++) {
            joueurs[j].main[c] = pioche->cartes[--pioche->sommet];
            joueurs[j].main[c].visible = 0;
        }
    }
}
