# CardYard

CardYard est un jeu de cartes multijoueur de commande développé en langage C. Il met en œuvre une logique de pioche, défausse, échange de cartes et classement final selon les scores.

## 🔧 Compilation et exécution

### Compiler le projet

```bash
make
```

### Exécuter le jeu

```bash
./cardyard
```

---

## 🧹 Nettoyage

### Supprimer les fichiers objets (`.o`)

```bash
make clean
```

### Supprimer également l’exécutable

```bash
make mrproper
```

---

## 🕹️ Fonctionnalités

- Jusqu'à **8 joueurs**
- **Distribution aléatoire ou personnalisée** des cartes
- **3 variantes pour générer la pioche** :

  **VALUE_FILE** : lit les valeurs et quantités de cartes depuis un fichier texte (valeurs.txt)

  **VALUE_USER** : l’utilisateur entre lui-même la plage de valeurs (ex. -5 à 15) et les quantités de chaque carte

  **Par défaut** : jeu classique avec les cartes proposées dans le sujet (valeurs de -2 à 12)

- **Sauvegarde** et **rechargement** d’une partie en cours (`sauvegarde.txt`)
- **Affichage visuel stylisé** des cartes et du plateau via **codes couleurs ANSI**
- **Classement final automatique** des joueurs par score

---

## 🗂️ Structure des fichiers

- `main.c` : logique principale du jeu.
- `cartes.h` : définitions des structures `Carte`, `Joueur`, `Pioche`.
- `initialisation.c` : génération et distribution des cartes.
- `affichage.c/h` : affichage du plateau, des couleurs et des scores.
- `jeu.c` : fonctions avancées d’affichage graphique ASCII.
- `Makefile` : automatisation de la compilation.

---

## 💾 Sauvegarde

Une sauvegarde de partie est enregistrée dans le fichier :

```
sauvegarde.txt
```

Elle est générée automatiquement si le joueur choisit l’option "Sauvegarder et quitter".

---

## 👨‍💻 Auteurs

Projet réalisé par :  
**Shems BOUDJEBINA**, **Antoine BOUDON-GUILLOT**, **Taissir RGUIG**  
Dans le cadre du module INFORMATIQUE en C — année universitaire **2024–2025**.

---

