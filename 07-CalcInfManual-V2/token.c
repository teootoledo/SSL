#include "token.h"
#include <stdlib.h>
#include <stdio.h>

extern int global = 42;

//---------- AGREGAR TOKENS ------------//

TOKEN AgregarToken(tipoDeToken tipo, int buffer[])
{
    TOKEN newToken;
    if (tipo == IDENTIFICADOR)
        SetName(buffer, newToken);

    if (tipo == CONSTANTE)
        SetValor(buffer);

    SetTipo(tipo);
}

void SetName(int id[])
{
    for (unsigned i = 0; i < 8; ++i)
        .id[i] = id[i];
}
void SetValor(int valor[])
{
    for (unsigned i = 0; i < 8; ++i)
        listaDeTokens[punteroDeToken].valor[i] = valor[i];
}
void SetTipo(tipoDeToken tipo)
{
    listaDeTokens[punteroDeToken].tipo = tipo;
}

//---------- MOSTRAR TOKENS ------------//
void MostrarToken(int i)
{
    switch (listaDeTokens[i].tipo)
    {
    case IDENTIFICADOR:
        printf("IDENTIFICADOR\t");
        MostrarID(listaDeTokens[i].id);
        MostrarValor(listaDeTokens[i].valor);
        break;
    case CONSTANTE:
        printf("CONSTANTE\t");
        MostrarID(listaDeTokens[i].id);
        MostrarValor(listaDeTokens[i].valor);
        break;
    case SUMA:
        printf("ADICION\t\t");
        MostrarID(listaDeTokens[i].id);
        MostrarValor(listaDeTokens[i].valor);
        break;
    case MULTIPLICACION:
        printf("MULTIPLICACION\t");
        MostrarID(listaDeTokens[i].id);
        MostrarValor(listaDeTokens[i].valor);
        break;
    case PARENIZQUIERDO:
        printf("PARENIZQUIERDO\t");
        MostrarID(listaDeTokens[i].id);
        MostrarValor(listaDeTokens[i].valor);
        break;
    case PARENDERECHO:
        printf("PARENDERECHO\t");
        MostrarID(listaDeTokens[i].id);
        MostrarValor(listaDeTokens[i].valor);
        break;
    case IGUAL:
        printf("IGUAL\t\t");
        MostrarID(listaDeTokens[i].id);
        MostrarValor(listaDeTokens[i].valor);
        break;
    case ASIGNACION:
        printf("ASIGNACION\t");
        MostrarID(listaDeTokens[i].id);
        MostrarValor(listaDeTokens[i].valor);
        break;
    case EXP:
        printf("EXPRESION\t");
        MostrarID(listaDeTokens[i].id);
        MostrarValor(listaDeTokens[i].valor);
        break;
    case FDS:
        printf("FDS \t\t");
        MostrarID(listaDeTokens[i].id);
        MostrarValor(listaDeTokens[i].valor);
        break;
    case FDT:
        printf("FDT \t\t");
        MostrarID(listaDeTokens[i].id);
        MostrarValor(listaDeTokens[i].valor);
        break;
    default:
        printf("Not a token \t");
        MostrarID(listaDeTokens[i].id);
        MostrarValor(listaDeTokens[i].valor);
        break;
    }
}
void MostrarListaDeTokens()
{
    printf("\t\t\t--> Tabla de tokens <--\n\n");
    for (unsigned i = 0; i < 8; ++i)
    {
        MostrarToken(i);
    }
}
void MostrarID(int nombre[])
{
    for (int i = 0; i < 8; i++)
        printf("[%d] ", nombre[i]);
    printf("\t");
}
void MostrarValor(int valor[8])
{
    for (int i = 0; i < 8; i++)
    {
        if (valor[i] == 0)
            printf("[ ]");
        else
            printf("[%d]", (valor[i] - '0'));
    }
    printf("\n");
}
