#include "scanner.h"
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
void agregarSimbolo(int[], int[], TOKEN);
void agregarCaracter(int);
void SetNombre(int[]);
void SetValor(int[]);
void SetTipo(TOKEN);
void mostrarBuffer();
void limpiarBuffer();
extern int buffer[8] = {0};
extern int punteroDeBuffer = 0;
int punteroDeSimbolo = 0;

struct simbolo
{
    TOKEN tipo;
    int nombre[8];
    int valor[8];
} tablaDeSimbolos[32];

struct simbolo auxiliar;

void agregarSimbolo(int nombre[], int valor[], TOKEN tipo)
{
    if (tipo == IDENTIFICADOR)
    {
        SetNombre(nombre);
    }
    SetValor(valor);
    SetTipo(tipo);
    ++punteroDeSimbolo;
}

void SetNombre(int nombre[])
{
    for (unsigned i = 0; tablaDeSimbolos[punteroDeSimbolo].nombre[i] != 0; ++i)
        tablaDeSimbolos[punteroDeSimbolo].nombre[i] = nombre[i];
}

void SetValor(int valor[])
{
    for (unsigned i = 0; tablaDeSimbolos[punteroDeSimbolo].valor[i] != 0; ++i)
        tablaDeSimbolos[punteroDeSimbolo].valor[i] = valor[i];
}

void SetTipo(TOKEN tipo)
{
    tablaDeSimbolos[punteroDeSimbolo].tipo = tipo;
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

void mostrarTablaSimbolos(struct simbolo tabla[])
{
    for (unsigned i = 0; tabla[i].tipo != NAT; ++i)
    {
    }
}

int main(void)
{
    TOKEN t;

    while ((t = scanner()) != FDT)
    {
        mostrar(t);
        printf("\t");
        mostrarBuffer();
        limpiarBuffer();
        printf("\n\n");
    }
}

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
                break;
            }

            estadoActual = Q11_error;
            break;

        case Q1_identificador:
            if ((!isalpha(c)) && (!isdigit(c)))
            {
                estadoActual = Q0_inicial;
                ungetc(c, stdin);
                agregarSimbolo();
                return IDENTIFICADOR;
            }
            agregarCaracter(c);
            break;
        case Q2_constante:
            if (!isdigit(c))
            {
                estadoActual = Q0_inicial;
                ungetc(c, stdin);
                agregarSimbolo(CONSTANTE);
                return CONSTANTE;
            }
            agregarCaracter(c);
            break;

        case Q3_adicion:
            estadoActual = Q0_inicial;
            ungetc(c, stdin);
            return SUMA;

            agregarSimbolo() case Q4_producto : estadoActual = Q0_inicial;
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

        case Q9_fds:
            estadoActual = Q0_inicial;
            if (c == '\n')
                return FDT;
            ungetc(c, stdin);
            return FDS;
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