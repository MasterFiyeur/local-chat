/*!
*\file user_management.h
*\brief Fichier d'entête des fonctions de gestion des utilisateurs
*/

#pragma once

// Number of user that can be connected at the same time
#define MAX_USERS_CONNECTED 3
// User's username length
#define MAX_USER_USERNAME_LENGTH 10

#include <sys/mman.h>
#include <stdio.h>
#include <string.h>

struct user{
    char username[MAX_USER_USERNAME_LENGTH]; //Username of the user
    char ip_add[16]; //IP address of the user 
};


/**
*\brief Add user to the shared_memory (array of connected users)
*
*\param shared_memory Array of connected users
*\param username Username of the user to add
*\param ip_add IP adress of the user to add
*\return 0 User successfully added
*\return 1 Username already taken
*\return 2 Users array is full (No index available)
*/
int add_user(struct user *shared_memory, char username[MAX_USER_USERNAME_LENGTH], char ip_add[16]);