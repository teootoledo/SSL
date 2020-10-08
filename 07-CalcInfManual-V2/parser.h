#include <stdbool.h>
#include <stdio.h>
#include "scanner.h"

//PROTOTIPOS
void Match(TOKEN);
void TokenActual(TOKEN);
void Parser(void);
void Sentencias(void);
void Definicion(void);
void Expresion(void);
void Primaria(void);
void ErrorSintactico(void);