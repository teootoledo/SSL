#include "scanner.h"
#include <stdio.h>  //printf
#include <stdlib.h> //exit
#include <ctype.h>  //isalpha isdigit
#include <string.h> //strcpy

//void mostrarTipo(TOKEN);

//-------------- PROTOTIPOS BUFFER ---------------//
void AddCharacter(char);
char buffer[10] = {
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0'};
void ShowBuffer();
void CleanBuffer();
int bufferIndex = 0;

//-------------- PROTOTIPOS TOKENS ---------------//
TOKEN CreateToken(tipoDeToken, char[]);

//----------------- ESTADOS ---------------//
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
    Q9_definicion,
    Q10_fds,
    Q11_fdt,
    Q12_error
} State;

//----------MAIN PARA DEBUG-- ------- //
// int main(void)
// {
//     TOKEN t;
//     while ((t = GetNextToken()).type != FDT)
//     {
//         mostrarTipo(t);
//     };
//     printf("\n\n");
//     return 0;
// }

//---------- GetNextToken -----------//
TOKEN GetNextToken(void)
{
    static State actualState = Q0_inicial;
    static TOKEN incomingToken;
    char c;
    while ((c = getchar()) != EOF)
    {
        switch (actualState)
        {
        case Q0_inicial:
            if (isalpha(c))
            {
                actualState = Q1_identificador;
                AddCharacter(c);
                break;
            }
            if (isdigit(c))
            {
                actualState = Q2_constante;
                AddCharacter(c);
                break;
            }
            if (c == '+')
            {
                actualState = Q3_adicion;
                break;
            }
            if (c == '*')
            {
                actualState = Q4_producto;
                break;
            }
            if (c == '(')
            {
                actualState = Q5_parizquierdo;
                break;
            }
            if (c == ')')
            {
                actualState = Q6_parderecho;
                break;
            }
            if (c == '=')
            {
                actualState = Q7_igual;
                break;
            }
            if (c == '$')
            {
                actualState = Q9_definicion;
                break;
            }
            if (c == ';')
            {
                actualState = Q10_fds;
                break;
            }
            if (c == '\n')
            {
                actualState = Q11_fdt;
                break;
            }
            actualState = Q12_error;
            break;

        case Q1_identificador:
            if ((!isalpha(c)) && (!isdigit(c)))
            {
                actualState = Q0_inicial;
                ungetc(c, stdin);
                incomingToken = CreateToken(IDENTIFICADOR, buffer);
                CleanBuffer();
                return incomingToken;
            }
            AddCharacter(c);
            break;
        case Q2_constante:
            if (!isdigit(c))
            {
                actualState = Q0_inicial;
                ungetc(c, stdin);
                incomingToken = CreateToken(CONSTANTE, buffer);
                CleanBuffer();
                return incomingToken;
            }
            AddCharacter(c);
            break;

        case Q3_adicion:
            actualState = Q0_inicial;
            ungetc(c, stdin);
            incomingToken = CreateToken(SUMA, buffer);
            return incomingToken;

        case Q4_producto:
            actualState = Q0_inicial;
            ungetc(c, stdin);
            incomingToken = CreateToken(MULTIPLICACION, buffer);
            CleanBuffer();
            return incomingToken;

        case Q5_parizquierdo:
            actualState = Q0_inicial;
            ungetc(c, stdin);
            incomingToken = CreateToken(PARENIZQUIERDO, buffer);
            return incomingToken;

        case Q6_parderecho:
            actualState = Q0_inicial;
            ungetc(c, stdin);
            incomingToken = CreateToken(PARENDERECHO, buffer);
            return incomingToken;

        case Q7_igual:
            actualState = Q0_inicial;
            ungetc(c, stdin);
            incomingToken = CreateToken(IGUAL, buffer);
            return incomingToken;

        case Q9_definicion:
            actualState = Q0_inicial;
            ungetc(c, stdin);
            incomingToken = CreateToken(DEF, buffer);
            return incomingToken;

        case Q10_fds:
            actualState = Q0_inicial;
            ungetc(c, stdin);
            incomingToken = CreateToken(FDS, buffer);
            return incomingToken;

        case Q11_fdt:
            if (c == '\n')
            {
                incomingToken = CreateToken(FDT, buffer);
                return incomingToken;
            }
            actualState = Q0_inicial;
            ungetc(c, stdin);
            break;

        case Q12_error:
            printf("[SCANNER] LEXICAL ERROR");
            c = EOF;
            exit(1);
            break;

        default:
            printf("[SCANNER] LEXICAL ERROR");
            exit(1);
            break;
        }
    }
}

//---------- BUFFER ------------//
void AddCharacter(char c)
{
    buffer[bufferIndex] = c;
    bufferIndex++;
}
void ShowBuffer()
{
    for (int i = 0; i < 8; i++)
    {
        printf(" [%d]", buffer[i]);
    }
}
void CleanBuffer()
{
    for (int i = 0; i < 8; ++i)
    {
        buffer[i] = 0;
    }
    bufferIndex = 0;
}

//---------- MANEJO DE TOKENS ------//

TOKEN CreateToken(tipoDeToken tipo, char buffer[])
{
    TOKEN newToken;
    if (tipo == IDENTIFICADOR)
        strcpy(newToken.data.name, buffer);
    if (tipo == CONSTANTE)
        newToken.data.value = atoi(buffer);
    newToken.type = tipo;
    return newToken;
}

// void mostrarTipo(TOKEN t)
// {

//     switch (t.type)
//     {
//     case IDENTIFICADOR:
//         printf("IDENTIFICADOR");
//         break;
//     case CONSTANTE:
//         printf("CONSTANTE");
//         break;
//     case SUMA:
//         printf("SUMA");
//         break;
//     case MULTIPLICACION:
//         printf("MULTIPLICACION");
//         break;
//     case IGUAL:
//         printf("IGUAL");
//         break;
//     case PARENDERECHO:
//         printf("PARENDERECHO");
//         break;
//     case PARENIZQUIERDO:
//         printf("PARENIZQUIERDO");
//         break;
//     case DEF:
//         printf("DEF");
//         break;
//     case FDS:
//         printf("FDS");
//         break;
//     case FDT:
//         printf("FDT");
//         break;
//     default:
//         printf("NAT");
//         break;
//     }
// }
