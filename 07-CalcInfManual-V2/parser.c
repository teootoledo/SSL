#include "scanner.h"
#include "parser.h"
#include "memory.h"
#include <stdlib.h>

void mostrarTipo(tipoDeToken);

TOKEN t; //TOKEN OBTENIDO

//Prototipos de funciones privadas
static void Match(tipoDeToken);
//void TokenActual(tipoDeToken);
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

    while (t.type != FDT)
    {
        unaSentencia();
    }
}

void unaSentencia()
{
    int resultado;
    t = GetNextToken();
    switch (t.type)
    {
    case DEF:         //Definición
        Definicion(); //Se asocia valor a identificador.
        break;
    case IDENTIFICADOR: //Expresión
    case CONSTANTE:
        resultado = Expresion();                //Expresión
        printf("\n Resultado = %d", resultado); //Expresión que luego será evaluada
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
    int resultado = Termino();
    switch (t.type)
    {
    case SUMA: //Matcheo SUMA
        printf("\n entro a la suma ");
        t = GetNextToken();
        resultado = resultado + Termino();
    default:
        break;
    }

    printf("\n resultado de Expresion %d", resultado);
    return resultado;
}

int Termino(void)
{
    int resultado = Factor();
    switch ((t = GetNextToken()).type)
    {
    case MULTIPLICACION: //Matcheo MULTIPLICACIÓN
        t = GetNextToken();
        resultado = resultado * Factor();
        break; //Por gramática: factor { MULTIPLICACION <factor> }*
    default:
        break;
    }
    printf("\n resultado de Termino %d", resultado);
    return resultado;
}

int Factor(void)
{
    int resultado;
    switch (t.type)
    {
    case IDENTIFICADOR: //Matcheo IDENTIFICADOR
        resultado = GetValue(t.data.name);
        break;                    //Retorno el valor de la variable en memoria.
    case CONSTANTE:               //Matcheo CONSTANTE
        resultado = t.data.value; //Obtengo valor de la constante
        break;
    case PARENIZQUIERDO:         //Matcheo PARENIZQUIERDO
        resultado = Expresion(); //Por gramática: <factor> | PARENIZQUIERDO <expresion> PARENDERECHO
        Match(PARENDERECHO);     //Matcheo PARENDERECHO
        break;
    default:
        break;
    }
    printf("\n resultado de Factor %d", resultado);
    return resultado;
}

//--------------------------------------------------------------------
static void Match(tipoDeToken tipoEsperado)
{
    t = GetNextToken();
    if (t.type != tipoEsperado)
    {
        printf("\nRecibido ");
        mostrarTipo(t.type);
        printf("\nEsperado ");
        mostrarTipo(tipoEsperado);

        ErrorSintactico();
    }
    mostrarTipo(t.type);
}

void ErrorSintactico()
{
    printf("\nERROR SINTACTICO\n");
    //exit(1);
}

void mostrarTipo(tipoDeToken tipo)
{
    printf(" ");
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
