#include <stdio.h>
#include <stdbool.h>
#include "parser.h"

int main()
{
    printf("Comienzo de objetivo\n");
    printf("Ingrese expresion: \n");
    Parser();
    MostrarListaDeTokens();
}