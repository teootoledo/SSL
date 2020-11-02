#include "scanner.h"
#define MAX_VAR_ARRAY_LENGTH 100

// Declaracion de la memoria
extern int vtIndex;
struct variable
{
    char name[10];
    int val;
} variablesTable[MAX_VAR_ARRAY_LENGTH];

void ShowMemory(void);