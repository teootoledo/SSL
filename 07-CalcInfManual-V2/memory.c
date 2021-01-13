#include "memory.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

unsigned memoryLastPosition = 0;
variable Memory[MEMORY_SIZE]

    //Prototipos funciones privadas
    int
    Exists(char[]);

//Definiciones de funciones privadas
int Exists(char name[])
{

    for (unsigned i = 0; i <= memoryLastPosition; ++i)
    {
        if (Memory[i].name == name)
        {
            return i;
        }
    }
    return -1;
}

//FUNCIONES PARA MANEJO DE MEMORIA
//Definición de funciones públicas
unsigned GetPosition(char name[])
{
    if (Exists(name) != -1)
    {
        strcpy(Memory[memoryLastPosition].name, name);
        ++memoryLastPosition;
        return memoryLastPosition - 1;
    }
    else
    {
        return memoryLastPosition;
    }
}

void Assign(unsigned position, int value)
{
    Memory[position].value = value;
}

int GetValue(char name[])
{
    if (Exists(name) != -1)
    {
        return GetPosition(name);
    }
    else
    {
        printf("\n\nEl identificador %s no existe\n\n", name);
        return -1;
    }
}