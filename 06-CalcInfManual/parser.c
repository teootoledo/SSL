#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "scanner.h"
#include "parser.h"

typedef enum
{
    Q0_inicio,
    Q1_final,
    Q2_err
} EstadoParser;

bool parser(void)
{
    EstadoParser estadoActual = Q0_inicio;
    token newToken;
    while ((newToken = GetNextToken()) != fdt)
    {
        switch (estadoActual)
        {
        case Q0_inicio:
            if (newToken != identificador || newToken != constante)
            {
                estadoActual = Q2_err;
            }
            estadoActual = Q1_final;
            break;
        case Q1_final:
            if (newToken != adicion || newToken != producto)
            {
                estadoActual = Q2_err;
            }
            estadoActual = Q0_inicio;
        case Q2_err:
            printf("Syntax ERROR");
            exit(1);
            break;

        default:
            break;
        }
    }
}