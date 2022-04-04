/*!
*\file request.h
*\brief Fichier d'entête des fonctions de gestion des utilisateurs
*/

#pragma once

#define UDP_PORT 2058

struct request
{
    int type;
    /** Type correpondence
    * 1 log in
    * -1 log out
    * 2 create account
    * -2 delete account
    * 0 get current connected users
    */
    char data[128];
};
