# === Makefile ===

# Nom du compilateur utilisé
CC = gcc

# Options de compilation :
# -Wall : active tous les avertissements standards
# -Wextra : active des avertissements supplémentaires
# -std=c99 : utilise le standard C99
CFLAGS = -Wall -Wextra -std=c99

# Liste des fichiers objets à compiler (issus des .c)
OBJS = main.o affichage.o initialisation.o jeu.o

# Cible principale : génère l'exécutable 'cardyard' à partir des fichiers objets
cardyard: $(OBJS)
	$(CC) $(CFLAGS) -o cardyard $(OBJS)

# Règle générique pour compiler chaque .c en .o
# $< : nom du fichier source (.c)
# $@ : nom du fichier objet (.o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cible 'clean' : supprime l'exécutable et tous les fichiers objets générés
clean:
	rm -f cardyard *.o
