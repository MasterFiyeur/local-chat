/*!
*\file user_management.h
*\brief Fichier d'entête des fonctions de gestion des utilisateurs
*/

#pragma once

#include <sys/mman.h>
#include <unistd.h> //cwd for get path to users.csv
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../utils/request.h"
#include "../utils/lectureSecurisee.h"

// Number of user that can be connected at the same time
#define MAX_USERS_CONNECTED 3
//File of account's username/password
#define ACCOUNT_FILE "users.csv"

struct user{
    char username[MAX_USER_USERNAME_LENGTH]; //Username of the user
    int sock; //Socket descriptor or token if first message not sent
    char token[TOKEN_SIZE];
};

/**
*\brief Generate a random token (with alphanumeric characters)
*
*\return char* token of size TOKEN_SIZE
 */
char *token_generation();

/**
*\brief Add user to the shared_memory (array of connected users)
*
*\param shared_memory Array of connected users
*\param username Username of the user to add
*\param token Token generated returned
*\return 0 User successfully added
*\return 1 Username already taken
*\return 2 Users array is full (No index available)
*/
int add_user(struct user *shared_memory, char username[MAX_USER_USERNAME_LENGTH], char** token);

/**
*\brief Remove user from the shared_memory (array of connected users)
*
*\param shared_memory Array of connected users
*\param token Token of the user to remove(got when log in)
*\return 0 User successfully removed
*\return 1 User not found
*/
int remove_user(struct user *shared_memory, char token[TOKEN_SIZE]);

int numberOfLines(char* path); /*returns the number of lines of the csv*/
char** listOfCouples(char* path); /*returns a list having one line per nickname and password of the csv*/
int findNickname(char* pseudo, char* password, char* path, int checkPass); /*checks if the nickname exists, or if the password matches the nickname*/
void creation(char* nickname,char* password,char* path); /*adds a line in the csv containing the datas, if the nickname doesn't exist yet*/
void delete(char* nickname,char* path); /*deletes the line containing the given nickname in the csv*/