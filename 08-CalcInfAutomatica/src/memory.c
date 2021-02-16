#include "../inc/memory.h"
#include <stdio.h>  //printf
#include <string.h> //strcmp
#include <stdlib.h> //exit

unsigned memoryLastPosition = 0;
variable Memory[MEMORY_SIZE];

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
            // printf("\nEncontre la variable %s con el valor %d", name, Memory[i].value);
            return i;
        }
    }
    strcpy(Memory[memoryLastPosition].name, name);
    // printf("\nDeclare la variable %s", name);
    ++memoryLastPosition;
    return memoryLastPosition - 1;
}

void Assign(unsigned position, int value)
{
    Memory[position].value = value;
    // printf("\nAsigno %d a la posicion %d", value, position);
}

int GetValue(char name[])
{
    for (unsigned i = 0; i <= memoryLastPosition; ++i)
    {
        if (strcmp(Memory[i].name, name) == 0)
        {
            //printf("\Encuentro variable %s en la posicion %d, con valor %d", name, i, Memory[i].value);
            return Memory[i].value;
        }
    }
    printf("\nEl identificador %s no existe\n", name);
    exit(1);
}

void mostrarMemoria()
{
    printf("\n--------------MEMORIA---------------\n");
    for (int i = 0; i < 5; i++)
        mostrarVariable(i);
}

void mostrarVariable(int i)
{
    mostrarNombre(Memory[i].name);
    printf("valor: %d", Memory[i].value);
}

void mostrarNombre(char nombre[])
{
    printf("\nnombre: ");
    for (int i = 0; i < 10; i++)
    {
        printf("%c", nombre[i]);
    }
    printf("\t");
}
