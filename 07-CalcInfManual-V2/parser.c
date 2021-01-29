#include "scanner.h"
#include "parser.h"
#include "memory.h"
#include <stdlib.h>

void ShowType(tipoDeToken);

TOKEN t; //TOKEN OBTENIDO

//Prototipos de funciones privadas
static void Match(tipoDeToken);
static void ActualMatch(tipoDeToken tipoEsperado);
void Sentencias(void);
void unaSentencia(void);
void Definicion(void);
int Expresion(void);
int Termino(void);
int Factor(void);
void SyntaxError(void);

//Definición de función pública
void Parser()
{
    Sentencias();
    printf("\n\n\t\t--- FIN DEL PROGRAMA ---\n\n");
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
    case PARENIZQUIERDO:
        resultado = Expresion();                //Expresión
        printf("\n Resultado = %d", resultado); //Expresión que luego será evaluada
        break;
    case FDT:
        return;
    default:
        break;
    }
    ActualMatch(FDS);
    printf("\nEsperando nueva sentencia...\n");
}

void Definicion()
{
    Match(IDENTIFICADOR);                         //Matcheo IDENTIFICADOR
    unsigned position = GetPosition(t.data.name); //t es el último token obtenido. Busco si existe en memoria
    Match(IGUAL);                                 //Matcheo IGUAL
    Match(CONSTANTE);                             //Matcheo CONSTANTE a ser asignada.
    Assign(position, t.data.value);               //Asignacion
    t = GetNextToken();
}

int Expresion(void)
{
    int resultado = Termino();
    while (t.type == SUMA)
    {
        t = GetNextToken();
        resultado = resultado + Termino();
    }
    return resultado;
}

int Termino(void)
{
    int resultado = Factor();
    while (t.type == MULTIPLICACION)
    {
        t = GetNextToken();
        resultado = resultado * Factor();
    }
    return resultado;
}

int Factor(void)
{
    int resultado;
    switch (t.type)
    {
    case IDENTIFICADOR: //Matcheo IDENTIFICADOR
        resultado = GetValue(t.data.name);
        t = GetNextToken();
        break;                    //Retorno el valor de la variable en memoria.
    case CONSTANTE:               //Matcheo CONSTANTE
        resultado = t.data.value; //Obtengo valor de la constante
        t = GetNextToken();
        break;
    case PARENIZQUIERDO:
        t = GetNextToken();
        resultado = Expresion(); //Por gramática: <factor> | PARENIZQUIERDO <expresion> PARENDERECHO
        ActualMatch(PARENDERECHO);
        t = GetNextToken();
        break;
    default:
        SyntaxError();
    }
    return resultado;
}

//--------------------------------------------------------------------
static void Match(tipoDeToken tipoEsperado)
{
    t = GetNextToken();
    ActualMatch(tipoEsperado);
}

static void ActualMatch(tipoDeToken tipoEsperado)
{
    if (t.type != tipoEsperado)
    {
        printf("\nRecibido ");
        ShowType(t.type);
        printf("\nEsperado ");
        ShowType(tipoEsperado);

        SyntaxError();
    }
}
void SyntaxError()
{
    printf("\n[PARSER] SYNTAX ERROR\n");
    exit(1);
}

void ShowType(tipoDeToken tipo)
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
