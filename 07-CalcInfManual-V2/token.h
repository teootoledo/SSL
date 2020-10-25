#ifndef TOKEN_H
#define TOKEN_H

static int punteroDeToken = 0; //Apunta al ultimo token de la lista de tokens
int *pDTptr = &punteroDeToken;

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

struct TOKEN
{
    tipoDeToken tipo;
    int id[8];
    int valor[8];
} listaDeTokens[100];
#endif

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
