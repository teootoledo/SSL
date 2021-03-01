/* memory.h
 - Declaración de estructura variable y prototipos de funciones.
 - TOLEDO, Teo Martin - 171.891-5 - UTN FRBA - ft (MARECO, RUBIN)
 - 20210301
*/

#define MEMORY_SIZE 200

#ifndef MEMORY_H
#define MEMORY_H

// Definición de la estructura variable
typedef struct variable
{
    char name[10];
    int value;
} variable;

#endif

// Prototipos de funciones públicas para el manejo de memoria.
unsigned GetPosition(char[]);
void Assign(unsigned, int);
int GetValue(char[]);
