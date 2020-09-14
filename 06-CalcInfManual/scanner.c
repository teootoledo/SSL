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
    Q5_err,
    Q6_fdt
} Estado;

// void mostrar(token);

token GetNextToken(void);

/* int main(void)
{
    token t;
    for (; (t = scanner()) != fdt;)
    {
        mostrar(t);
    }
}
 */
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
            if (c == '\n')
            {
                estadoActual = Q6_fdt;
                c = EOF;
                return fdt;
                break;
            }
            estadoActual = Q5_err;
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
            if ((isalpha(c)) || (isdigit(c)))
                break;
            else
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
            c = EOF;
            printf("Lexical ERROR");
            exit(0);
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

/* void mostrar(token a)
{
    switch (a)
    {
    case identificador:
        printf("id\n");
        break;
    case constante:
        printf("const\n");
        break;
    case adicion:
        printf("add\n");
        break;
    case producto:
        printf("prod\n");
        break;

    default:
        printf("Not a token");
        break;
    }
}
 */