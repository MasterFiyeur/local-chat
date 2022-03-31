#Nom des programme
CLIENT = client

#Compilation
CC=gcc

#Options de compilation
CFLAGS=-Wall
#Options d edition de liens
LDFLAGS=-lm -pthread

#Repertoire des sources et entete du projet partie client
clientdir=./
#Repertoire des sources et entete des fichiers utilitaires
utilsdir=../utils/
#Repertoire qui contient les fichiers objets et executable
bindir=../output/

#Fichiers source
SRC_CLIENT=$(wildcard $(clientdir)*.c)
#Fichiers objet
OBJ_CLIENT=$(subst $(clientdir), $(bindir),$(SRC_CLIENT:.c=.o))
OBJ_UTILS=$(subst $(utilsdir), $(bindir),$(SRC_UTILS:.c=.o))

#Commande pour effacer des fichiers
RM=find .. -name "*.bak" -type f -delete && find .. -name "*.o" -type f -delete && find .. -name "*.old" -type f -delete && find .. -name "*~" -type f -delete

all : $(CLIENT)

$(CLIENT) : $(OBJ_CLIENT) $(OBJ_UTILS)
	$(CC) $^ -o $(bindir)$@ $(LDFLAGS)
	make clean

../output/%.o : ./%.c
	$(CC) $(CFLAGS) -c $< -o $@

../output/%.o : ../utils/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean execute

clean : 
	$(RM)