/*!
*\file user_management.h
*\brief Fichier d'entête des fonctions de gestion des utilisateurs
*/

#pragma once

// Number of user that can be connected at the same time
#define MAX_USERS_CONNECTED 3
// User's username length
#define MAX_USER_USERNAME_LENGTH 10
// User's password length
#define MAX_USER_PASSWORD_LENGTH 10
//Token size
#define TOKEN_SIZE 16
//Separator (char) between username and password
#define USER_SEPARATOR '\t'

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
*\return 0 User successfully added
*\return 1 Username already taken
*\return 2 Users array is full (No index available)
*/
int add_user(struct user *shared_memory, char username[MAX_USER_USERNAME_LENGTH]);