#include "scanner.h"
#include "parser.h"
#include "memory.h"
#include <stdlib.h>

void mostrarTipo(tipoDeToken);

TOKEN t; //TOKEN OBTENIDO

//Prototipos de funciones privadas
static void Match(tipoDeToken);
void Sentencias(void);
void unaSentencia(void);
void Definicion(void);
int Expresion(void);
int Termino(void);
int Factor(void);
void ErrorSintactico(void);

//Definición de función pública
void Parser()
{
    Sentencias();
    printf("\n\n\t\t--- SINTAXIS CORRECTA ---\n\n");
}

//Definiciones de funciones privadas
void Sentencias()
{
    unaSentencia();
    t = GetNextToken();
    mostrarTipo(t.type);

    switch (t.type)
    {
    case DEF:
    case IDENTIFICADOR:
    case CONSTANTE:
        Expresion();
        break;
    default:
        Match(FDT);
        mostrarTipo(t.type);

        return;
    }
}

void unaSentencia()
{
    t = GetNextToken();
    mostrarTipo(t.type);
    switch (t.type)
    {
    case DEF:         //Definición
        Definicion(); //Se asocia valor a identificador.
        break;
    case IDENTIFICADOR:                      //Expresión
    case CONSTANTE:                          //Expresión
        printf("Resultado = ", Expresion()); //Expresión que luego será evaluada
        break;
    default:
        break;
    }
    Match(FDS);
    printf("\nEsperando nueva sentencia...\n");
}

void Definicion()
{
    Match(IDENTIFICADOR);                         //Matcheo IDENTIFICADOR
    unsigned position = GetPosition(t.data.name); //t es el último token obtenido. Busco si existe en memoria
    Match(IGUAL);                                 //Matcheo IGUAL
    Match(CONSTANTE);                             //Matcheo CONSTANTE a ser asignada.
    Assign(position, t.data.value);               //Asignacion
}

int Expresion(void)
{
    printf("Llegue EXPRESION\n");

    int resultado;
    resultado = Termino();
    printf("%d", resultado);
    t = GetNextToken();

    switch (t.type)
    {
    case SUMA: //Matcheo SUMA
        printf("Llegue SUMA\n");

        return (resultado + Expresion()); //Por gramática: <termino> { SUMA <expresión> }*
        break;
    default:
        return resultado; //Devuelvo resultado si lo único expresado fue el término
        break;
    }
}

int Termino(void)
{
    int resultado = Factor();
    t = GetNextToken();

    switch (t.type)
    {
    case MULTIPLICACION:                //Matcheo MULTIPLICACIÓN
        return (resultado * Termino()); //Por gramática: factor { MULTIPLICACION <término> }*
    default:
        return resultado; //Devuelvo resultado si lo único expresado fue el factor
    }
}

int Factor(void)
{
    int resultado;
    printf("Llegue FACTOR\n");
    mostrarTipo(t.type);

    switch (t.type)
    {
    case CONSTANTE:          //Matcheo CONSTANTE
        return t.data.value; //Retorno el valor de la CONSTANTE
        break;
    case IDENTIFICADOR: //Matcheo IDENTIFICADOR
        printf("Match ident");
        printf("%s", t.data.name);
        if (resultado = GetValue(t.data.name) != -1)
        {
            return resultado;
        } //Obtengo el valor de la variable en memoria.
        printf("%d", resultado);
        ErrorSintactico();

        break;
    case PARENIZQUIERDO:         //Matcheo PARENIZQUIERDO
        resultado = Expresion(); //Por gramática: <factor> | PARENIZQUIERDO <término> PARENDERECHO
        Match(PARENDERECHO);     //Matcheo PARENDERECHO
        break;
    default:
        ErrorSintactico();
        break;
    }
}

//--------------------------------------------------------------------
static void Match(tipoDeToken tipoEsperado)
{
    t = GetNextToken();
    if (t.type != tipoEsperado)
    {
        printf("\nR ");
        mostrarTipo(t.type);
        printf("\nE ");
        mostrarTipo(tipoEsperado);

        ErrorSintactico();
    }
    mostrarTipo(t.type);
}

void ErrorSintactico()
{
    printf("\nERROR SINTACTICO\n");
    exit(1);
}

void mostrarTipo(tipoDeToken tipo)
{

    switch (tipo)
    {
    case IDENTIFICADOR:
        printf("IDENTIFICADOR\n");
        break;
    case CONSTANTE:
        printf("CONSTANTE\n");
        break;
    case SUMA:
        printf("SUMA\n");
        break;
    case MULTIPLICACION:
        printf("MULTIPLICACION\n");
        break;
    case IGUAL:
        printf("IGUAL\n");
        break;
    case PARENDERECHO:
        printf("PARENDERECHO\n");
        break;
    case PARENIZQUIERDO:
        printf("PARENIZQUIERDO\n");
        break;
    case DEF:
        printf("DEF\n");
        break;
    case FDS:
        printf("FDS\n");
        break;
    case FDT:
        printf("FDT\n");
        break;
    default:
        printf("NAT\n");
        break;
    }
}