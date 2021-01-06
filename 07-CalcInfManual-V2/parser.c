#include "scanner.h"
#include "parser.h"
#include <stdlib.h>
#include "string.h"

TOKEN t;
extern int *pDTptr;

void Parser()
{
    Sentencias();
    printf("\n\n\t\t--- SINTAXIS CORRECTA ---\n\n");
}

// $a+4

void Sentencias()
{
    t = Scanner();
    switch (t.type)
    {
    case IDENTIFICADOR:
        Definicion();
        Match(FDS);
        break;
    case EXP:
        Expresion();
        TokenActual(FDS);
        break;
    case FDT:
        return;
    default:
        ErrorSintactico();
    }
    Sentencias();
}

void Definicion()
{
    { //V1
        unsigned position = SearchPosition(t.data.name);
        Match(ASIGNACION);
        Match(CONSTANTE);
        Asignar(position, t.data.value); //Asignacion
    }
}

void Expresion(void)
{
    Primaria();
    for (t = Scanner(); t == SUMA || t == MULTIPLICACION; t = Scanner())
        Primaria();
}

void Primaria() //3+(4*6)
{
    t = Scanner();
    switch (t)
    {
    case IDENTIFICADOR:
        return;
    case CONSTANTE:
        return;
    case PARENIZQUIERDO:
        while (t == PARENIZQUIERDO)
        {
            Expresion();
            TokenActual(PARENDERECHO);
        }
        return;
    default:
        ErrorSintactico();
    }
}
void Match(tipoDeToken tipoEsperado)
{
    tipoDeToken actualToken = Scanner();
    if (actualToken != tipoEsperado)
    {
        printf("\n\nTOKEN ESPERADO: ");
        MostrarToken(tipoEsperado);
        printf("TOKEN RECIBIDO: ");
        MostrarToken(actualToken);
        printf("\n");
        ErrorSintactico();
    }
}

void TokenActual(tipoDeToken tipoEsperado)
{
    if (tipoEsperado != t)
    {
        printf("\n\nTOKEN ESPERADO: ");
        MostrarToken(tipoEsperado);
        printf("TOKEN RECIBIDO: ");
        MostrarToken(t);
        printf("\n");
        ErrorSintactico();
    }
}

void ErrorSintactico()
{
    printf("\nERROR SINTACTICO\n");
    exit(1);
}

//FUNCIONES PARA MANEJO DE MEMORIA

unsigned SearchPosition(char name[])
{
    for (unsigned i = 0; i <= memoryLastPosition; ++i)
    {
        if (Memory[i].name == name)
        {
            return i;
        }
    }
    strcpy(Memory[memoryLastPosition].name, name);
    ++memoryLastPosition;
    return memoryLastPosition - 1;
}

void Asignar(unsigned position, int value)
{
    Memory[position].value = value;
}
