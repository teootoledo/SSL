#include "../inc/scanner.h"
#include "../inc/parser.h"
#include "../inc/memory.h"
#include <stdlib.h> //exit

void ShowType(tipoDeToken);

TOKEN t; //Token actual

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
    printf("FIN");
}

//Definiciones de funciones privadas
void Sentencias()
{
    unaSentencia();
    //printf("antes del while");

    while (t.type != FDT)
    {
        unaSentencia();
    //printf("en el while");

    }
    //printf("despues del while");

}

// =1+2*3+4;

void unaSentencia()
{
    int resultado;
    t = GetNextToken();
    switch (t.type)
    {
    case DEFINICION:                            //Definición.
        Definicion();                           //Asocia valor a identificador.
        break;
    case IGUAL:                                 //Expresión.
        resultado = Expresion();                //Expresión devuelve un resultado.
        printf("Resultado = %d\n", resultado);  //Muestra resultado de la expresión.
        break;
    case FDT:
        return;
    default:
        printf("default");
        break;
    }
    //ShowType(t.type);
    Match(FDS);
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
    int resultado = Termino(); //1
    switch (t.type)
    {
        case SUMA:
        resultado = resultado + Expresion(); //1 + 6
    }
    return resultado;
}

int Termino(void)
{
    int resultado = Factor(); //1
    switch (t.type)
    {
        case PRODUCTO:
        resultado = resultado * Termino(); //2 * 3
    }
    return resultado; //6
}

int Factor(void)
{
    int resultado;
    switch ((t=GetNextToken()).type)
    {
    case IDENTIFICADOR: //Matcheo IDENTIFICADOR
        resultado = GetValue(t.data.name);
        break;                    //Retorno el valor de la variable en memoria.
    case CONSTANTE:               //Matcheo CONSTANTE
        resultado = t.data.value; //Obtengo valor de la constante
        break;
    case PARENIZQUIERDO:
        resultado = Expresion(); //Por gramática: <factor> | PARENIZQUIERDO <expresion> PARENDERECHO
        ActualMatch(PARENDERECHO);
        break;
    default:
        SyntaxError();
    }
    //t=GetNextToken();
    return resultado;
}

//--------------------------------------------------------------------
static void Match(tipoDeToken tipoEsperado)
{
    if ((t=GetNextToken()).type != tipoEsperado)
    {
        printf("\nRecibido: ");
        ShowType(t.type);
        printf("\nEsperado ");
        ShowType(tipoEsperado);

        SyntaxError();
    }
}

static void ActualMatch(tipoDeToken tipoEsperado)
{
    if (t.type != tipoEsperado)
    {
        printf("\nRecibido: ");
        ShowType(t.type);
        printf("\nEsperado: ");
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
    case PRODUCTO:
        printf("PRODUCTO\n");
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
    case DEFINICION:
        printf("DEFINICION\n");
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
