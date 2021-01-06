#include <stdio.h>
#include "scanner.h"

//PROTOTIPOS
void Match(tipoDeToken);
void TokenActual(tipoDeToken);
void Parser(void);
void Sentencias(void);
void Definicion(void);
void Expresion(void);
void Primaria(void);
void ErrorSintactico(void);
void Asignar(int[]);

//MEMORIA ------------------------

#define MEMORY_SIZE 200
struct var
{
    char name[10]; //string
    int value;     //int o double
};

typedef struct var var;

static var Memory[MEMORY_SIZE];
static unsigned memoryLastPosition = 0;

//PROTOTIPOS MEMORIA
unsigned SearchPosition(char[]);