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

struct
{
    char name[10]; //string
    int value;     //int o double
} var;

typedef struct var var;

static var Memory[200];