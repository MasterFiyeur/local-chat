#pragma once

#include "../utils/client-structures.h"

/**
 * @brief Manage messages sent by users (broadcast)
 * 
 * @param msgid The message queue ID to receive events from
 */
void collectMessages(int msgid);

/**
 * @brief Manage users joining and leaving the chat
 * 
 * @param msgid The message queue ID to receive events from
 */
void collectMoves(int msgid);

/**
 * @brief Manage specific signals (user connected/disconnected, board closing)
 * 
 * @param msgid The message queue ID to receive events from
 */
void collectSignals(int msgid);
