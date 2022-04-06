/*!
*\file user_management.h
*\brief Fichier d'entête des fonctions de gestion des utilisateurs
*/

#pragma once

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../utils/request.h"

// Number of user that can be connected at the same time
#define MAX_USERS_CONNECTED 3

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