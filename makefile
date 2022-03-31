#Nom des programme
CLIENT = client
BOARD = board
SERVER = server

#Repertoire des sources et entete du projet partie client
clientdir=client
#Repertoire des sources et entete du projet affichage des messages
boarddir=board
#Repertoire des sources et entete du projet partie serveur
serverdir=server

#Repertoire qui contient les fichiers objets et executable
bindir=./output/

#Commande pour effacer des fichiers
RM=find . -name "*.bak" -type f -delete && find . -name "*.o" -type f -delete && find . -name "*.old" -type f -delete && find . -name "*~" -type f -delete

all : compile

compile : 
	cd $(clientdir) && $(MAKE)
	cd $(boarddir) && $(MAKE)
	cd $(serverdir) && $(MAKE)

.PHONY : clean execute

clean : 
	$(RM)

#Executer le programme
execute :
	@$(bindir)$(CLIENT)
	@$(bindir)$(BOARD)
	@$(bindir)$(SERVER)
