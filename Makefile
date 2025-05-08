# === Makefile pour CardYard ===

# Compilateur utilisé
CC = gcc

# Options de compilation :
# -Wall : active tous les avertissements courants
# -Wextra : active des avertissements supplémentaires
# -std=c99 : utilise la norme C99
CFLAGS = -Wall -Wextra -std=c99

# Options de l’éditeur de liens (ici vide, peut servir pour -lm, -lSDL2, etc.)
LDFLAGS =

# Liste des fichiers sources
SRC = main.c affichage.c initialisation.c jeu.c

# Transformation des fichiers sources .c en objets .o
OBJ = $(SRC:.c=.o)

# Nom de l’exécutable final
EXEC = cardyard

# Cible par défaut : génère l’exécutable
all: $(EXEC)

# Cible pour créer l'exécutable à partir des fichiers objets
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Règle de compilation des fichiers .c vers .o
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

# Cible pour supprimer les fichiers objets
clean:
	rm -f *.o

# Cible pour tout nettoyer : objets + exécutable
mrproper: clean
	rm -f $(EXEC)

# Spécifie que ces cibles ne sont pas des fichiers
.PHONY: all clean mrproper
