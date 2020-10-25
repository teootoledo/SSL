#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//-------------- PROTOTIPOS ---------------//
void AgregarCaracter(int);
void MostrarBuffer();
void LimpiarBuffer();
int buffer[8] = {0};
int punteroDeBuffer = 0;

//----------------- ESTADOS ------, buffer---------//
typedef enum
{
    Q0_inicial,
    Q1_identificador,
    Q2_constante,
    Q3_adicion,
    Q4_producto,
    Q5_parizquierdo,
    Q6_parderecho,
    Q7_igual,
    Q8_asignacion,
    Q9_expresion,
    Q10_fds,
    Q11_fdt,
    Q12_error
} Estado;

/* int main(void)
{
    tipoDeToken t;

    while ((t = Scanner()) != FDT)
    {
    };
    printf("\n\n");
    MostrarListaDeTokens();
    printf("\n\n");
    return 0;
} */

tipoDeToken Scanner(void)
{
    static Estado estadoActual = Q0_inicial;
    static TOKEN token;
    char c;
    while ((c = getchar()) != EOF)
    {
        switch (estadoActual)
        {
        case Q0_inicial:
            if (isalpha(c))
            {
                estadoActual = Q1_identificador;
                AgregarCaracter(c);
                break;
            }
            if (isdigit(c))
            {
                estadoActual = Q2_constante;
                AgregarCaracter(c);
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
            if (c == '(')
            {
                estadoActual = Q5_parizquierdo;
                break;
            }
            if (c == ')')
            {
                estadoActual = Q6_parderecho;
                break;
            }
            if (c == '=')
            {
                estadoActual = Q7_igual;
                break;
            }
            if (c == ':')
            {
                estadoActual = Q8_asignacion;
                break;
            }
            if (c == '$')
            {
                estadoActual = Q9_expresion;
                break;
            }
            if (c == '.')
            {
                estadoActual = Q10_fds;
                break;
            }

            if (c == '\n')
            {
                estadoActual = Q11_fdt;
                break;
            }

            estadoActual = Q12_error;
            break;

        case Q1_identificador:
            if ((!isalpha(c)) && (!isdigit(c)))
            {
                estadoActual = Q0_inicial;
                ungetc(c, stdin);
                AgregarToken(IDENTIFICADOR, buffer);
                LimpiarBuffer();
                return IDENTIFICADOR;
            }
            AgregarCaracter(c);
            break;
        case Q2_constante:
            if (!isdigit(c))
            {
                estadoActual = Q0_inicial;
                ungetc(c, stdin);
                AgregarToken(CONSTANTE, buffer);
                LimpiarBuffer();
                return CONSTANTE;
            }
            AgregarCaracter(c);
            break;

        case Q3_adicion:
            estadoActual = Q0_inicial;
            ungetc(c, stdin);
            AgregarToken(SUMA, buffer);
            return SUMA;

        case Q4_producto:
            estadoActual = Q0_inicial;
            ungetc(c, stdin);
            AgregarToken(MULTIPLICACION, buffer);
            LimpiarBuffer();
            return MULTIPLICACION;

        case Q5_parizquierdo:
            estadoActual = Q0_inicial;
            ungetc(c, stdin);
            AgregarToken(PARENIZQUIERDO, buffer);
            return PARENIZQUIERDO;

        case Q6_parderecho:
            estadoActual = Q0_inicial;
            ungetc(c, stdin);
            AgregarToken(PARENDERECHO, buffer);
            return PARENDERECHO;

        case Q7_igual:
            estadoActual = Q0_inicial;
            ungetc(c, stdin);
            AgregarToken(IGUAL, buffer);
            return IGUAL;

        case Q8_asignacion:
            if (c == '=')
            {
                estadoActual = Q0_inicial;
                AgregarToken(ASIGNACION, buffer);
                return ASIGNACION;
            }
            estadoActual = Q12_error;
            break;
        case Q9_expresion:
            estadoActual = Q0_inicial;
            ungetc(c, stdin);
            AgregarToken(EXP, buffer);
            return EXP;

        case Q10_fds:
            estadoActual = Q0_inicial;
            ungetc(c, stdin);
            AgregarToken(FDS, buffer);
            return FDS;
            break;

        case Q11_fdt:
            if (c == '\n')
            {
                AgregarToken(FDT, buffer);
                return FDT;
            }
            estadoActual = Q0_inicial;
            ungetc(c, stdin);
            break;

        case Q12_error:
            printf("ERROR LEXICO");
            c = EOF;
            exit(0);
            break;

        default:
            printf("Lexical ERROR");
            break;
        }
    }
}

//---------- BUFFER ------------//
void AgregarCaracter(int c)
{
    buffer[punteroDeBuffer] = c;
    punteroDeBuffer++;
}
void MostrarBuffer()
{
    for (int i = 0; i < 8; i++)
    {
        printf(" [%d]", buffer[i]);
    }
}
void LimpiarBuffer()
{
    for (int i = 0; i < 8; ++i)
    {
        buffer[i] = 0;
    }
    punteroDeBuffer = 0;
}
