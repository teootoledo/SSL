#include "../inc/scanner.h"
#include "../inc/parser.h"
#include "../inc/memory.h"
#include <stdlib.h> //exit

void ShowType(tipoDeToken);

TOKEN tok; //Token actual

//Prototipos de funciones privadas
static void Match(tipoDeToken);
void ListaSentencias(void);
void Sentencia(void);
void Definicion(void);
int Expresion(void);
int Termino(void);
int Factor(void);

//Definición de función pública
void Parser()
{
    ListaSentencias();
    printf("[Parser] Finalizado de manera exitosa.");
}

//Definiciones de funciones privadas
void ListaSentencias()
{
    Sentencia();
    while (GetNextToken().type != FDT)
    {
        Sentencia();
    }
    //printf("despues del while");
}

void Sentencia()
{
    int resultado;
    switch (GetNextToken().type)
    {
    case DEFINICION:
        Match(DEFINICION);
        Definicion(); //Asocia valor a identificador.
        break;
    case IGUAL:
        Match(IGUAL);
        resultado = Expresion();               //Expresión devuelve un resultado.
        printf("Resultado = %d\n", resultado); //Muestra resultado de la expresión.
        break;
    default:
        printf("[Parser] Error en la sintaxis.");
        exit(1);
        break;
    }
    //ShowType(t.type);
    Match(FDS);
}

void Definicion()
{
    Match(IDENTIFICADOR);                           //Matcheo IDENTIFICADOR
    unsigned position = GetPosition(tok.data.name); //t es el último token obtenido. Busco si existe en memoria
    Match(IGUAL);                                   //Matcheo IGUAL
    Match(CONSTANTE);                               //Matcheo CONSTANTE a ser asignada.
    Assign(position, tok.data.value);               //Asignacion
}

int Expresion(void)
{
    int resultado = Termino();
    switch (GetNextToken().type)
    {
    case SUMA:
        return resultado + Expresion();
    default:
        return resultado;
    }
    return resultado;
}

int Termino(void)
{
    int resultado = Factor();
    switch (GetNextToken().type)
    {
    case PRODUCTO:
        return resultado * Termino();
    default:
        return resultado;
    }
}

int Factor(void)
{
    int resultado;
    switch (GetNextToken().type)
    {
    case IDENTIFICADOR:
        Match(IDENTIFICADOR);
        resultado = GetValue(tok.data.name);
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
        printf("[Parser] Error en la sintaxis.");
    }
    return resultado;
}

//--------------------------------------------------------------------
static void Match(tipoDeToken tipoEsperado)
{
    if ((tok = GetNextToken()).type != tipoEsperado)
    {
        printf("[Parser] Error en la sintaxis.\n");
        exit(3);
    }
    keepLastToken = 0;
}

void ShowType(tipoDeToken tipo)
{
    printf(" ");
    switch (tipo)
    {
    case IDENTIFICADOR:
        printf("IDENTIFICADOR");
        break;
    case CONSTANTE:
        printf("CONSTANTE");
        break;
    case SUMA:
        printf("SUMA");
        break;
    case PRODUCTO:
        printf("PRODUCTO");
        break;
    case IGUAL:
        printf("IGUAL");
        break;
    case PARENDERECHO:
        printf("PARENDERECHO");
        break;
    case PARENIZQUIERDO:
        printf("PARENIZQUIERDO");
        break;
    case DEFINICION:
        printf("DEFINICION");
        break;
    case FDS:
        printf("FDS");
        break;
    case FDT:
        printf("FDT");
        break;
    default:
        printf("NAT");
        break;
    }
}
