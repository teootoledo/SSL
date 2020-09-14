// Scanner --> GetChar --> SO
// Analizador Léxico

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "scanner.h"

typedef enum
{
    Q0_inicial,
    Q1_constante,
    Q2_identificador,
    Q3_adicion,
    Q4_producto,
    Q5_err
} Estado;

token GetNextToken(void);

token scanner(void)

{
    static Estado estadoActual = Q0_inicial;
    char c;
    while ((c = getchar()) != EOF)
    {
        switch (estadoActual)
        {
            //------------------------------ESTADO INICIAL------------------
        case Q0_inicial:
            if (isdigit(c))
            {
                estadoActual = Q1_constante;
                break;
            }
            if (isalpha(c))
            {
                estadoActual = Q2_identificador;
                break;
            }
            if (c == '+')
            {
                estadoActual = Q3_adicion;
                break;
            }
            if (c == '*')
            {
                estadoActual = Q4_producto;
                break;
            }
            estadoActual = err;
            break;
            //------------------------------ESTADO CONSTANTE------------------
        case Q1_constante:
            if (!isdigit(c))
            {
                estadoActual = Q0_inicial;
                ungetc(c, stdin);
                return constante;
            }
            break;
            //------------------------------ESTADO IDENTIFICADOR--------------
        case Q2_identificador:
            if ((!isalpha(c)) || (!isdigit(c)))
            {
                estadoActual = Q0_inicial;
                ungetc(c, stdin);
                return identificador;
            }
            break;
            //------------------------------ESTADO ADICIÓN--------------------
        case Q3_adicion:
            estadoActual = Q0_inicial;
            ungetc(c, stdin);
            return adicion;
            break;
            //------------------------------ESTADO PRODUCTO-------------------
        case Q4_producto:
            estadoActual = Q0_inicial;
            ungetc(c, stdin);
            return producto;
            break;
            //------------------------------ESTADO ERROR----------------------
        case Q5_err:
            printf("Lexical ERROR");
            exit(1);
            break;

        default:
            estadoActual = fdt;
            break;
        }
    }
}

token GetNextToken(void)
{
    return scanner();
}