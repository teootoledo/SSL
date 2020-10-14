#ifndef TOKEN_H
#define TOKEN_H

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
    int id[20];
    int valor[20];
} listaDeTokens[100];
#endif

typedef struct TOKEN TOKEN;

void AgregarToken(TOKEN);
void MostrarToken(struct TOKEN);
void MostrarListaDeTokens(void);
void SetID(int[]);
void SetValor(int[]);
void SetTipo(tipoDeToken);
void MostrarValor(int[]);
void MostrarID(int[]);
void CargarArray(int[], int[]);
