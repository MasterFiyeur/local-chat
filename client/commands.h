#pragma once

#include "../utils/lectureSecurisee.h"
#include "../utils/request.h"
#include <string.h>

/* Constants definition */
//To log in
#define LOGIN_COMMAND "/login"
//To log out
#define LOGOUT_COMMAND "/logout"
//To create an account
#define CREATE_ACCOUNT_COMMAND "/create"
//To delete an account
#define DELETE_ACCOUNT_COMMAND "/delete"
//To get connected users list
#define LIST_COMMAND "/list"
//To exit the program
#define EXIT_COMMAND "/exit"

/**
*\brief Check if a message start with a specific command
*
*\param message String check matching to command
*\param command Command to check
*\return 1 This is the command
*\return 0 This isn't the command
 */
int is_command(char* message, char* command);

void login(char message[REQUEST_DATA_MAX_LENGTH],char* token, struct sockaddr_in adr_s, struct sockaddr_in adr_c, int udp_socket, int tcp_socket);

int commande_detection(char message[REQUEST_DATA_MAX_LENGTH], int* exit_status, char* token, int tcp_sock);