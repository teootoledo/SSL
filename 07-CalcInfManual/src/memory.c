#include "../inc/memory.h"
#include <stdio.h> //printf
#include <stdlib.h> //exit
#include <string.h> //strcmp

unsigned memoryLastPosition = 0;
variable Memory[MEMORY_SIZE];

//Prototipos funciones privadas

//Definiciones de funciones privadas

//FUNCIONES PARA MANEJO DE MEMORIA

void mostrarVariable(int);
void mostrarNombre(char[]);

//Definición de funciones públicas
unsigned GetPosition(char name[])
{
    for (unsigned i = 0; i <= memoryLastPosition; ++i)
    {
        if (strcmp(Memory[i].name, name) == 0)
        {
            return i;
        }
    }
    strcpy(Memory[memoryLastPosition].name, name);
    ++memoryLastPosition;
    return memoryLastPosition - 1;
}

void Assign(unsigned position, int value)
{
    Memory[position].value = value;
}

int GetValue(char name[])
{
    for (unsigned i = 0; i <= memoryLastPosition; ++i)
    {
        if (strcmp(Memory[i].name, name) == 0)
        {
            return Memory[i].value;
        }
    }
    printf("\n\nEl identificador %s no existe\n\n", name);
    exit(1);
}