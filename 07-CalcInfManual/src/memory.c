#include "../inc/memory.h"
#include <stdio.h> //printf
#include <stdlib.h> //exit
#include <string.h> //strcmp

// Declaración de variables
unsigned memoryLastPosition = 0;
variable Memory[MEMORY_SIZE];

// Definición de funciones públicas para el manejo de memoria

// GetPosition devuelve la posición si existe, sino, declara y devuelve esa posición.
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

// Assign le asigna a la posición pasada por parámetro el valor requerido.
void Assign(unsigned position, int value)
{
    Memory[position].value = value;
}

//GetValue busca por nombre la variable y devuelve su valor.
int GetValue(char name[])
{
    for (unsigned i = 0; i <= memoryLastPosition; ++i)
    {
        if (strcmp(Memory[i].name, name) == 0)
        {
            return Memory[i].value;
        }
    }
    exit(2);
}