#include "parser.h"
#include "scanner.h"
#include <stdlib.h>

static void Programa(void);
static void Expresion(void);
static void Primaria(void);
static void ErrorSintactico(token esperado, token alternativa);

void parser(void)
{
    Expresion();
    printf("[Parser] Expresión Válida\n");
}

static void Expresion(void)
{
    Termino();

    while (1)
    {
        switch (GetNextToken())
        {
        case adicion:
        case producto:
            Termino();
            break;
        case fdt:
            return;
        default:
            break;
        }
    }
}

static void Termino(void)
{
    token t = GetNextToken();
    if (t == lpar)
        if (t == identificador || t == constante)
            return;
        else
            ErrorSintactico(identificador, constante);
}

static void ErrorSintactico(token esperado, token alternativa)
{
    printf("[Parser] Error Sintáctico\n");
    exit(0);
}