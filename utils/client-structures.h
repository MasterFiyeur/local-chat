#pragma once

#include <stdlib.h>

#ifndef bool
    #define bool unsigned int
    #define true 1
    #define false 0
#endif

typedef struct {
    long type;
    char* username;
    char* message;
} message;

typedef struct {
    long type;
    char* username;
    bool is_join;
} move;

