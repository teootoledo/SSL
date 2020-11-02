#include "memory.h"
#include <stdio.h>

int vtIndex = 0;

void ShowName(char[]);

void ShowMemory(void)
{
    for (unsigned i = 0; i < vtIndex; ++i)
    {
        ShowName(variablesTable[i].name);
    }
}

void ShowName(char name[])
{
    printf("SHOW");
    for (int i = 0; i < 10; i++)
        printf("%c", name[i]);
    printf("\t");
}