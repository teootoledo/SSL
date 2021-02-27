#include "../inc/scanner.h"
#include <stdio.h>  //printf
#include <stdlib.h> //exit
#include <ctype.h>  //isalpha isdigit
#include <string.h> //strcpy

// Prototipos de funciones privadas ----------------
// Prototipos para el manejo del buffer
char buffer[MAX_NAME_LENGTH] = {};
void AddCharacter(char); //Agrega caracter al buffer
void CleanBuffer();      //Limpia el buffer
int bufferIndex = 0;

// Prototipo para la creación de TOKENs
TOKEN CreateToken(tipoDeToken);

// 
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
    Q8_definicion,
    Q9_fds,
    Q10_fdt,
    Q11_lexError
} State;

//---------- GetNextToken -----------//
TOKEN GetNextToken(void)
{
    static State actualState = Q0_inicial;
    TOKEN incomingToken;
    char c;
    CleanBuffer();
    while ((c = getchar()) != '#' ) // ! Simboliza nuestro EOF
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
                actualState = Q8_definicion;
                break;
            }
            if (c == ';')
            {
                actualState = Q9_fds;
                break;
            }
            if (c == '\n')
            {
                actualState = Q10_fdt;
                break;
            }
            actualState = Q11_lexError;
            break;

        case Q1_identificador:
            if ((!isalpha(c)) && (!isdigit(c)))
            {
                actualState = Q0_inicial;
                ungetc(c, stdin);
                return CreateToken(IDENTIFICADOR);

            }
            AddCharacter(c);
            break;
        case Q2_constante:
            if (!isdigit(c))
            {
                actualState = Q0_inicial;
                ungetc(c, stdin);
                return CreateToken(CONSTANTE);
            }
            AddCharacter(c);
            break;

        case Q3_adicion:
            actualState = Q0_inicial;
            ungetc(c, stdin);
            return CreateToken(SUMA);

        case Q4_producto:
            actualState = Q0_inicial;
            ungetc(c, stdin);
            return CreateToken(PRODUCTO);


        case Q5_parizquierdo:
            actualState = Q0_inicial;
            ungetc(c, stdin);
            return CreateToken(PARENIZQUIERDO);

        case Q6_parderecho:
            actualState = Q0_inicial;
            ungetc(c, stdin);
            return CreateToken(PARENDERECHO);

        case Q7_igual:
            actualState = Q0_inicial;
            ungetc(c, stdin);
            return CreateToken(IGUAL);

        case Q8_definicion:
            actualState = Q0_inicial;
            ungetc(c, stdin);
            return CreateToken(DEFINICION);

        case Q9_fds:
            actualState = Q0_inicial;
            ungetc(c, stdin);
            return CreateToken(FDS);

        case Q10_fdt:
            if (c == '!')
                return CreateToken(FDT);
            actualState = Q0_inicial;
            ungetc(c, stdin);
            break;

        case Q11_lexError:
        default:
            printf("\n[Scanner] Lexical error. El caracter no pertenece al alfabeto soportado.\n\n");
            c = '#';
            ungetc(c, stdin);
            break;
        }
    }
    exit(1);
}

//---------- BUFFER ------------//
void AddCharacter(char c)
{
    buffer[bufferIndex] = c;
    bufferIndex++;
}

void CleanBuffer()
{
    memset(buffer, 0, sizeof buffer);
    bufferIndex = 0;
}

//---------- MANEJO DE TOKENS ------//

TOKEN CreateToken(tipoDeToken tipo)
{
    TOKEN newToken;
    if (tipo == IDENTIFICADOR)
        strcpy(newToken.data.name, buffer);
    if (tipo == CONSTANTE)
        newToken.data.value = atoi(buffer);
    newToken.type = tipo;
    return newToken;
}