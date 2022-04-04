#include "user_management.h"

char* token_generation(){
    char *token;
    token = malloc(TOKEN_SIZE*sizeof(char));
    const char *alphanum = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
    for (size_t i = 0; i < TOKEN_SIZE-1; i++)
    {
        token[i] = alphanum[rand()%strlen(alphanum)];
    }
    return token;
}

int add_user(struct user *shared_memory, char username[MAX_USER_USERNAME_LENGTH]){
    int i = 0;

    //User creation
    struct user new_user;
    strcpy(new_user.username,username);
    new_user.sock = 0;

    //Check unique username 
    for (i = 0; i < MAX_USERS_CONNECTED; i++)
    {
        if (strcmp(shared_memory[i].username, username)==0){
            return 1;
        }
    }
    for (i = 0; i < MAX_USERS_CONNECTED; i++)
    {
        if (strcmp(shared_memory[i].username, "")==0){
            strcpy(new_user.token,token_generation());
            shared_memory[i] = new_user;
            return 0;
        }
    }
    return 2;
}




int* tableDocument(char* chemin) {
    FILE* fichier = fopen(chemin,"r");
    int* res;
    int lignes = 0;
    int caractere = 0;
    int ligne;
    int compte;
    if (fichier != NULL) {
        do {
            caractere = fgetc(fichier);
            if (caractere == 10) {lignes+=1;}
        } while (caractere != EOF);
    }
    fclose(fichier);

    res = malloc((lignes+1)*sizeof(int));
    res[0] = lignes;
    fichier = fopen(chemin,"r");
    if (fichier != NULL) {
        for(int i=1;i<=lignes;i++) {
            caractere = 0;
            compte = 0;
            while(caractere != 10) {
                compte += 1;
                caractere = fgetc(fichier);
            }
            res[i] = compte;
        }
    }
    fclose(fichier);

    return(res);
}

char** contenuOrganise(char* chemin, int* tableau) {
    char** res;
    int taille = tableau[0];
    res = malloc(taille*sizeof(char*));
    for(int i=0;i<taille;i++) {
        res[i] = malloc(tableau[i+1]*sizeof(char));
    }
    
    FILE* fichier = NULL;
    fichier = fopen(chemin,"r");
    if (fichier!=NULL) {
        for(int i = 1;i <= taille;i++) {
            fgets(res[i-1],tableau[i],fichier);
        }
    }
    fclose(fichier);
    return(res);
}

int cherchePseudo(char* pseudo,char* chemin) {
    int* tableau = tableDocument(chemin);
    int taille = tableau[0];
    char** couples = contenuOrganise(chemin, tableau);
    int i=0;
    int j=0;
    for(int k=0;k<taille;k++) {
        j=0;
        while (couples[k][j] != '\t') {
            if (pseudo[i] == couples[k][j]) {
                i += 1;
            }
            else {
                i = 0;
            }
            if (pseudo[i] == '\0') {
                return(k);
            }
            j+=1;
        }
    }
    return(-1);
}
