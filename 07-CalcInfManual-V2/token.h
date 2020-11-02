#ifndef TOKEN_H
#define TOKEN_H

static int punteroDeToken = 0; //Apunta al ultimo token de la lista de tokens
int *pDTptr = &punteroDeToken;
extern int global;

//$A=23
//23+A=
//46

typedef enum
{
    NAT,
    IDENTIFICADOR,
    CONSTANTE,
    ASIGNACION,
    IGUAL,
    PARENIZQUIERDO,
    PARENDERECHO,
    SUMA,
    MULTIPLICACION,
    EXP,
    FDS,
    FDT
} tipoDeToken;

struct TOKEN //resolver en scanner
{
    tipoDeToken tipo;
    // union{
    int id[8];    //string
    int valor[8]; //double
    // }
} listaDeTokens[100];
#endif

/*
A:=3

A -> tipo -> IDENT, id -> "A"
:= -> tipo -> ASIGNACION
3 -> tipo -> CONST, valor -> "3"
*/

typedef struct TOKEN TOKEN;

void AgregarToken(tipoDeToken, int[]);
void MostrarToken(int);
void MostrarListaDeTokens(void);
void SetID(int[]);
void SetValor(int[]);
void SetTipo(tipoDeToken);
void MostrarValor(int[]);
void MostrarID(int[]);
void CargarArray(int[], int[]);
