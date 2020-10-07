#include "scanner.h"
#include "simbolos.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//----------------- ESTADOS ---------------
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
    Q9_fds,
    Q10_fdt,
    Q11_error
} Estado;

void mostrar(TOKEN);
TOKEN scanner(void);
void agregarCaracter(int);

void mostrarBuffer();
void limpiarBuffer();
int buffer[8] = {0};
int punteroDeBuffer = 0;

// int main(void)
// {
//     TOKEN t;

//     while ((t = scanner()) != FDT)
//         mostrar(t);

//     mostrarTablaSimbolos();
// }

TOKEN scanner(void)
{
    static Estado estadoActual = Q0_inicial;
    char c;
    while ((c = getchar()) != EOF)
    {
        switch (estadoActual)
        {
        case Q0_inicial:
            if (isalpha(c))
            {
                estadoActual = Q1_identificador;
                agregarCaracter(c);
                break;
            }
            if (isdigit(c))
            {
                estadoActual = Q2_constante;
                agregarCaracter(c);
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
            if (c == '\n')
            {
                estadoActual = Q9_fds;
                return FDS;
                break;
            }
            if (c == '.')
            {
                return FDT;
            }

            estadoActual = Q11_error;
            break;

        case Q1_identificador:
            if ((!isalpha(c)) && (!isdigit(c)))
            {
                estadoActual = Q0_inicial;
                ungetc(c, stdin);
                agregarSimbolo(buffer, IDENTIFICADOR);
                limpiarBuffer();
                return IDENTIFICADOR;
            }
            agregarCaracter(c);
            break;
        case Q2_constante:
            if (!isdigit(c))
            {
                estadoActual = Q0_inicial;
                ungetc(c, stdin);
                agregarSimbolo(buffer, CONSTANTE);
                limpiarBuffer();
                return CONSTANTE;
            }
            agregarCaracter(c);
            break;

        case Q3_adicion:
            estadoActual = Q0_inicial;
            ungetc(c, stdin);
            return SUMA;

        case Q4_producto:
            estadoActual = Q0_inicial;
            ungetc(c, stdin);
            return MULTIPLICACION;

        case Q5_parizquierdo:
            estadoActual = Q0_inicial;
            ungetc(c, stdin);
            return PARENIZQUIERDO;

        case Q6_parderecho:
            estadoActual = Q0_inicial;
            ungetc(c, stdin);
            return PARENDERECHO;

        case Q7_igual:
            estadoActual = Q0_inicial;
            ungetc(c, stdin);
            return IGUAL;

        case Q8_asignacion:
            if (c == '=')
            {
                estadoActual = Q0_inicial;
                return ASIGNACION;
            }
            estadoActual = Q11_error;
            break;

        case Q9_fds:
            if (c == '.')
            {
                return FDT;
            }
            estadoActual = Q0_inicial;
            ungetc(c, stdin);
            break;

        case Q10_fdt:
            break;

        case Q11_error:
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

void mostrar(TOKEN a)
{
    switch (a)
    {
    case IDENTIFICADOR:
        printf("IDENTIFICADOR\n");
        break;
    case CONSTANTE:
        printf("CONSTANTE\n");
        break;
    case SUMA:
        printf("ADICION\n");
        break;
    case MULTIPLICACION:
        printf("MULTIPLICACION\n");
        break;
    case PARENIZQUIERDO:
        printf("PARENIZQUIERDO\n");
        break;
    case PARENDERECHO:
        printf("PARENDERECHO \n");
        break;
    case IGUAL:
        printf("IGUAL \n");
        break;
    case ASIGNACION:
        printf("ASIGNACION \n");
        break;
    case FDS:
        printf("FDS \n");
        break;
    case FDT:
        printf("FDT \n");
        break;
    default:
        printf("Not a token \n");
        break;
    }
}
void agregarCaracter(int c)
{
    buffer[punteroDeBuffer] = c;
    punteroDeBuffer++;
}

void mostrarBuffer()
{
    for (int i = 0; i < 8; i++)
    {
        printf(" [%d]", buffer[i]);
    }
}

void limpiarBuffer()
{
    for (int i = 0; i < 8; ++i)
    {
        buffer[i] = 0;
    }
    punteroDeBuffer = 0;
}