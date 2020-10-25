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