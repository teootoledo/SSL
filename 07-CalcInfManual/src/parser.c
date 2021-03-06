/* parser.c
 - Análisis sintáctico de tokens proveeidos por GetNextToken.
 - TOLEDO, Teo Martin - 171.891-5 - UTN FRBA - ft (MARECO, RUBIN)
 - 20210301
*/

#include "../inc/scanner.h"
#include "../inc/parser.h"
#include "../inc/memory.h"
#include <stdlib.h> //exit

TOKEN tok; // Token actual

// Prototipos de funciones privadas -------------------------
static void Match(tipoDeToken);
void ListaSentencias(void);
void Sentencia(void);
void Definicion(void);
int Expresion(void);
int Termino(void);
int Factor(void);

// Definición de función pública ----------------------------
void Parser()
{
    ListaSentencias();
    Match(FDT);
    printf("[Parser] Finalizado de manera exitosa.");
}

// Definiciones de funciones privadas -----------------------
// Subrutinas semánticas.
// Subrutinas de la lista de sentencias.
void ListaSentencias()
{
    do
    {
        Sentencia();
        Match(FDS);
    } while (GetNextToken().type != FDT);
}

void Sentencia()
{
    int resultado;
    switch (GetNextToken().type)
    {
    case DEFINICION:
        Match(DEFINICION);
        Definicion(); // Asigna una constante al nombre de una variable.
        break;
    case IGUAL:
        Match(IGUAL);
        resultado = Expresion();              // Expresión devuelve un resultado.
        printf("Resultado: %d\n", resultado); // Muestra resultado de la expresión.
        break;
    default:
        printf("[Parser] Sintaxis incorrecta.\n");
        exit(2);
        break;
    }
}

// Subrutina para definir variables.
void Definicion()
{
    Match(IDENTIFICADOR);
    unsigned position = GetPosition(tok.data.name);
    Match(IGUAL);
    Match(CONSTANTE);
    Assign(position, tok.data.value);
}

// Subrutina para resolver una expresión.
int Expresion(void)
{
    int resultado = Termino();
    while (GetNextToken().type == SUMA)
    {
        Match(SUMA);
        resultado = resultado + Termino();
    }
    return resultado;
}

// Subrutina para resolver un término.
int Termino(void)
{
    int resultado = Factor();
    while (GetNextToken().type == PRODUCTO)
    {
        Match(PRODUCTO);
        resultado = resultado * Factor();
    }
    return resultado;
}

// Subrutina para resolver un factor.
int Factor(void)
{
    int resultado;
    switch (GetNextToken().type)
    {
    case IDENTIFICADOR:
        Match(IDENTIFICADOR);
        resultado = GetValue(tok.data.name);
        break;
    case CONSTANTE:
        Match(CONSTANTE);
        resultado = tok.data.value;
        break;
    case PARENIZQUIERDO:
        Match(PARENIZQUIERDO);
        resultado = Expresion();
        Match(PARENDERECHO);
        break;
    default:
        printf("[Parser] Sintaxis incorrecta.\n");
        exit(3);
    }
    return resultado;
}

// Definición de función Match()
static void Match(tipoDeToken tipoEsperado)
{
    if ((tok = GetNextToken()).type != tipoEsperado)
    {
        printf("[Parser] Sintaxis incorrecta.\n");
        exit(4);
    }
    keepLastToken = 0;
}