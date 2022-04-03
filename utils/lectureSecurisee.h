/*!
*\file lectureSecurisee.h
*\brief Fichier d'entête des fonctions de lecture sécurisée
*\author Theo Julien (julientheo@eisti.eu)
*\version 1 
*\date 2020-10-23
*/

#pragma once

/*! \page ""
 */
#define  _GNU_SOURCE


/*----Importation des bibliothèques de base----*/
#include <stdio.h>/*bibliothèque d'entrée/sortie standard*/
#include <unistd.h>/*Importation de la bibliothèque standard d'unix*/
#include <stdlib.h>/*bibliothèque standard*/
#include <string.h>/* Bibliothèque pour les chaines de caracteres */
#include <time.h>/* Bibliothèque pour le random (creationTab) */
#include <math.h>/* Bibliothèque pour les fonctions mathématiques */
#include <pthread.h>/* Bibliothèque de gestion des threads */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <netdb.h>

/**
*\fn void viderBuffer()
*\author Theo Julien <julientheo@eisti.eu>
*\version 0.1 Initiale
*\date 2020-10-23
*\brief Vidage du buffer jusqu'à la fin du fichier ou jusqu'à un retour à la ligne
*/
void viderBuffer();

/**
*\fn int saisieInt()
*\author Theo Julien <julientheo@eisti.eu>
*\version 1.1 Manière différente de verifier l'entrée d'un entier
*\date 2020-10-23
*\brief Lecture sécurisée d'un entier 
*\return int_ent la valeur saisie correctement par l'utilisateur
*/
int saisieInt();

/**
*\fn float saisieFloat()
*\author Theo Julien <julientheo@eisti.eu>
*\version 1.1 Manière différente de verifier l'entrée d'un réel
*\date 2020-10-23
*\brief Lecture sécurisée d'un réel
*\return float_ent la valeur saisie correctement par l'utilisateur
*/
float saisieFloat();

/**
*\fn int saisieString(char* str_chaine,int int_taille)
*\author Theo Julien <julientheo@eisti.eu>
*\version 0.1 initiale
*\date 2020-11-14
*\brief Lecture d'une chaine de caractère
*\param str_chaine Chaine de caractère à entrer
*\param int_taille Taille de la chaine voulue (Longueur réelle)
*\return Taille actuelle de la chaine
*/
int saisieString(char* str_chaine,int int_taille);

/**
*\fn int * creationTab(int *int_taille)
*\author Theo Julien <julientheo@eisti.eu>
*\version 0.1 Initiale
*\date 2020-11-20
*\brief Creation et remplissage d'un tableau
*\param int_taille Taille du tableau qui sera renvoyée
*\return Tableau créée et initialisé
*/
int * creationTab(int *int_taille);

/**
*\fn int* initTab(int int_taille)
*\author Theo Julien <julientheo@eisti.eu>
*\version 0.1 Initiale
*\date 2020-11-20
*\brief Creation d'un tableau rempli de 0
*\param int_taille Taille du tableau
*\return Tableau créée et initialisé
*/
int* initTab(int int_taille);

/**
*\fn void clrscr()
*\author Theo Julien <julientheo@eisti.eu>
*\version 0.1 initiale
*\date 2020-11-27
*\brief Efface le terminal
*\pre Execution sous linux
*/
void clrscr();
