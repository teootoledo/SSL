#include "token.h"
#include <stdlib.h>
#include <stdio.h>

//---------- AGREGAR TOKENS ------------//
int punteroDeToken = 0;
void AgregarToken(TOKEN token)
{
    if (token.tipo == IDENTIFICADOR)
        SetID(token.id);

    if (token.tipo == CONSTANTE)
        SetValor(token.valor);

    SetTipo(token.tipo);
    ++punteroDeToken;
}
void SetID(int id[])
{
    for (unsigned i = 0; i < 8; ++i)
        listaDeTokens[punteroDeToken].id[i] = id[i];
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
void MostrarToken(TOKEN token)
{
    switch (token.tipo)
    {
    case IDENTIFICADOR:
        printf("IDENTIFICADOR\t");
        MostrarID(token.id);
        MostrarValor(token.valor);
        break;
    case CONSTANTE:
        printf("CONSTANTE\t\t");
        MostrarID(token.id);
        MostrarValor(token.valor);
        break;
    case SUMA:
        printf("ADICION\t\t");
        MostrarID(token.id);
        MostrarValor(token.valor);
        break;
    case MULTIPLICACION:
        printf("MULTIPLICACION\t");
        MostrarID(token.id);
        MostrarValor(token.valor);
        break;
    case PARENIZQUIERDO:
        printf("PARENIZQUIERDO\t");
        MostrarID(token.id);
        MostrarValor(token.valor);
        break;
    case PARENDERECHO:
        printf("PARENDERECHO\t");
        MostrarID(token.id);
        MostrarValor(token.valor);
        break;
    case IGUAL:
        printf("IGUAL\t\t");
        MostrarID(token.id);
        MostrarValor(token.valor);
        break;
    case ASIGNACION:
        printf("ASIGNACION\t");
        MostrarID(token.id);
        MostrarValor(token.valor);
        break;
    case FDS:
        printf("FDS \t\t");
        MostrarID(token.id);
        MostrarValor(token.valor);
        break;
    case FDT:
        printf("FDT \t\t");
        MostrarID(token.id);
        MostrarValor(token.valor);
        break;
    default:
        printf("Not a token \t");
        MostrarID(token.id);
        MostrarValor(token.valor);
        break;
    }
}
void MostrarListaDeTokens()
{
    printf("\t\t\t--> Tabla de simbolos <--\n\n");
    for (unsigned i = 0; i < 5; ++i)
    {
        TOKEN tok;
        tok.tipo = listaDeTokens[i].tipo;
        CargarArray(listaDeTokens[i].id, tok.id);
        CargarArray(listaDeTokens[i].valor, tok.valor);
        MostrarToken(tok);
    }
}
void MostrarID(int nombre[])
{
    for (int i = 0; i < 8; i++)
        printf("[%d] ", nombre[i]);
    printf("\t");
}
void MostrarValor(int valor[])
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
void CargarArray(int inicio[], int final[])
{
    for (unsigned i = 0; final[i] != 0; ++i)
    {
        final[i] = inicio[i];
    }
}