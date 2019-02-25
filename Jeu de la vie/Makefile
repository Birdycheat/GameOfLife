# Définition des variables

CC = gcc                      # compilo
CFLAGS = -Werror              # Flags (Warnings)
EXEC_NAME = jeu.exe           # nom de l'executable
LIBS = -lSDL2 -lm             # libs
OBJ_FILES = arith.o cadre.o main.o  # fichiers

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

clean:
	rm -rf *.o
mrproper: clean
	rm -rf main.exe
