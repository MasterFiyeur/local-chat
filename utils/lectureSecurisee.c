/**
*\file lectureSecurisee.c
*\brief fichier d'entête (fonctions)
*	fonctions de lecture sécurisée
*\author Theo Julien (julientheo@eisti.eu)
*\version 1
*\date 2020-10-23
*/


#include "lectureSecurisee.h"

void viderBuffer()
{
	/* Initialisation du caractère */
    int int_c = 0;
	/* Vidage du buffer caractère par caractère */
    while (int_c != '\n' && int_c != EOF)
    {
        int_c = getchar();
    }
}

int saisieInt()
{
	/* Caractère qui sera lu après l'entier */
    char ch_term;
	/* Entier qui sera lu par la saisie de l'utilisateur */
	int int_ent;
	/* Valeur de retour du scanf */
	int int_retour;
	/* Boucle qui redemande à l'utilisateur une saisie tant qu'elle n'est pas correcte */
	do
	{
		/* La lecture des deux paramètres dans le même scanf pour cette fonction
		est tolérée par le professeur, l'énoncé dit qu'il faut quitter lorsqu'il y a une 
		erreur de saisie mais on a dit que l'utilisateur aurait une autre chance, il aurait
		sinon fallu faire exit(ERREUR_SAISIE_ENTIER) avec la constante définie dans le fichier d'entête */
		/* Lecture d'un entier suivi d'un caractère */
		int_retour = scanf("%d%c",&int_ent,&ch_term);
		/* Vérification de la valeur entrée */
		if (int_retour != 2 || !('\n'==ch_term || ' '==ch_term || '\t'==ch_term)){
			/* Lorsque la saisie est mauvaise on ecrit un message et on vide le buffer */
			fprintf(stderr,"\nErreur de saisie (entier), recommencez :");
			viderBuffer();
		}else{
			/* Vidage du buffer si il n'est pas vide */
			if (ch_term != '\n'){
				viderBuffer();
			}
			/* Tout est OK, la valeur peut être retournée */
			return (int_ent);
		}
	/* Conditions d'une mauvaise saisie */
	} while (int_retour != 2 || !('\n'==ch_term || ' '==ch_term || '\t'==ch_term));
	/* Ne devrait pas arriver */
	return(0);
}

float saisieFloat()
{
	/* Caractère qui sera lu après le réel */
    char ch_term;
	/* réel qui sera lu par la saisie de l'utilisateur */
	float float_ent;
	/* Valeur de retour du scanf */
	int int_retour;
	/* Boucle qui redemande à l'utilisateur une saisie tant qu'elle n'est pas correcte */
	do
	{
		int_retour = scanf("%f%c",&float_ent,&ch_term);
		/* Vérification de la valeur entrée */
		if (int_retour != 2 || !('\n'==ch_term || ' '==ch_term || '\t'==ch_term)){
			/* Lorsque la saisie est mauvaise on écrit un message et on vide le buffer */
			fprintf(stderr,"\nErreur de saisie (réel), recommencez :");
			viderBuffer();
		}else{
			/* Vidage du buffer si il n'est pas vide */
			if (ch_term != '\n'){
				viderBuffer();
			}
			/* Tout est OK, la valeur peut être retournée */
			return (float_ent);
		}
	/* Conditions d'une mauvaise saisie */
	} while (int_retour != 2 || !('\n'==ch_term || ' '==ch_term || '\t'==ch_term));
	/* Ne devrait pas arriver */
	return(0.0);
}

int saisieString(char* str_chaine,int int_taille){
	/* Déclaration de la chaine de caractere */
	char* ligne;
	/* declaration de la taille de la chaine et du nombre alloué */
	size_t size_alloue;
	int int_tailleReelle;
	do{
		/* Initialisation de ligne */
		ligne = NULL;
		/* Lecture de la chaine de caractère */
		int_tailleReelle = getline(&ligne, &size_alloue,stdin);
		/* Prevention erreur de saisie */
		if (int_tailleReelle > int_taille){
			/* Message à l'utilisateur */
			printf("La longueur ne doit pas excéder %d caractères.\n",int_taille-1);
		}
	/* Demande tant que la chaine n'est pas de la bonne taille */
	}while(int_tailleReelle > int_taille || int_tailleReelle==1);
	/* Copie intégrale de la chaine*/
	strcpy(str_chaine,ligne);
	/* Renvoi de la taille */
	return(int_tailleReelle);
}

int * creationTab(int *int_taille){
    /* Declaration du tableau dynamique */
    int *pint_tab;
    /* Choix du remplissage par l utilisateur */
    int int_remplissage;
    /* Declaration de variable de boucle */
    int i;
    /* Boucle pour forcer un nombre positif */
    do{
		/* Demande a l utilisateur la taille du tableau */
		printf("Taille du tableau (positif): ");
		/* Saisie de la taille par l'utilisateur */
		*int_taille = saisieInt();
		/* Declaration dynamique */
		pint_tab = malloc(*int_taille * sizeof(int));
    }while(*int_taille<1);
    /* Demande a l utilisateur si il veut remplir le tableau manuellement */
    printf("Voulez-vous remplir le tableau manuellement ? (1 : oui)\n");
    /* Saisie de l utilisateur */
    int_remplissage = saisieInt();
    if (int_remplissage == 1){
        /* Remplissage manuel */
        for (i = 0; i < *int_taille; i++)
        {
            /* Indication et saisie du nombre par l utilisateur */
            printf("Index %d : ",i);
            pint_tab[i] = saisieInt();
        }
    }else{
        /* Remplissage automatique par defaut */
        for (i = 0; i < *int_taille; i++)
        {
            /* Remplissage de chaque case par un entier entre 0 et 99 */
            pint_tab[i] = rand()%100;
        }
    }
    return(pint_tab);
}

int* initTab(int int_taille){
	/* Déclaration du tableau */
	int* pint_tab;
	/* Allocation et initialisation du tableau avec des 0 */
	pint_tab = calloc(int_taille,sizeof(int));
	/* Renvoi du tableau */
	return(pint_tab);
}

void clrscr()
{	
	/* Effacage du terminal */
	system("clear");
}

int isNumber(char source[])
{
    for (int i = 0; source[i]!= '\0'; i++)
    {
        if (isdigit(source[i]) == 0)
              return 0;
    }
    return 1;
}