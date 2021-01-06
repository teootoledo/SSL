#include "scanner.h"
#include "parser.h"
#include <stdlib.h>

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
        unsigned posicion = f(t.id);
        Match(ASIGNACION);
        Match(CONSTANTE);
        LaMemoria[posicion] = t.valor; //Asignacion
    }

    { //V2
        TOKEN identificador = t;
        Match(ASIGNACION);
        Match(CONSTANTE);
        TOKEN constante = t;
        Asignar(identificador, constante);
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

void Asignar(int valor[])
{
    punteroDeToken--;
    int test[8] = {49, 50, 51};
    SetValor(test);
}
