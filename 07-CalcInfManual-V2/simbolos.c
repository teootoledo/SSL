#include "simbolos.h"
#include <stdlib.h>
#include <stdio.h>

int punteroDeSimbolo = 0;

/*int main(void){
    int nom[8] = {46};
    int val[8] = {1,2,3,4,5,6,7,8};
    TOKEN c = CONSTANTE;
    TOKEN c2 = CONSTANTE;
    TOKEN c3 = IDENTIFICADOR;
    TOKEN c4 = CONSTANTE;
    AgregarSimbolo(nom, val, c);
    AgregarSimbolo(nom, val, c2);
    AgregarSimbolo(nom, val, c3);
    AgregarSimbolo(nom, val, c4);
    MostrarTablaSimbolos();
}*/

void AgregarSimbolo(int valor[8], TOKEN tipo)
{
    if (tipo == IDENTIFICADOR)
        SetNombre(valor);

    if (tipo == CONSTANTE)
        SetValor(valor);

    SetTipo(tipo);
    ++punteroDeSimbolo;
}

void SetNombre(int nombre[])
{
    for (unsigned i = 0; i < 8; ++i)
        tablaDeSimbolos[punteroDeSimbolo].nombre[i] = nombre[i];
}

void SetValor(int valor[])
{
    for (unsigned i = 0; i < 8; ++i)
        tablaDeSimbolos[punteroDeSimbolo].valor[i] = valor[i];
}

void SetTipo(TOKEN tipo)
{
    tablaDeSimbolos[punteroDeSimbolo].tipo = tipo;
}

void MostrarTablaSimbolos()
{
    for (unsigned i = 0; i < 8; ++i)
    {
        if (tablaDeSimbolos[i].tipo == IDENTIFICADOR)
            printf("IDENTIFICADOR \t");
        else if (tablaDeSimbolos[i].tipo == CONSTANTE)
            printf("CONSTANTE \t");
        else
            return;
        MostrarNombre(tablaDeSimbolos[i].nombre);
        printf("\t");
        MostrarValor(tablaDeSimbolos[i].valor);
        printf("\n");
    }
}

void MostrarNombre(int nombre[8])
{
    for (int i = 0; i < 8; i++)
        printf(" [%d]", nombre[i]);
}

void MostrarValor(int valor[8])
{
    for (int i = 0; i < 8; i++)
    {
        if (valor[i] == 0)
            printf("[0]");
        else
            printf("[%d]", (valor[i] - '0'));
    }
}