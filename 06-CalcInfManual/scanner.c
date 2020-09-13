// Scanner --> GetChar --> SO
// Analizador Léxico

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define cEst 15
#define cTran 10
#define MAX_TOKEN_LENGTH 100

typedef enum
{
    operando,
    operador
} token;

typedef enum
{
    IN,
    OUT
} Estado;

void agregarToken(token tokenList[], const token Token, unsigned position);

token *scanner(void);

int main(void)
{
    scanner();
    printf("OK");
}

token *scanner(void)
{
    token resultado[MAX_TOKEN_LENGTH];
    unsigned lastToken = 0;
    int c;
    Estado estado = OUT;
    while ((c = getchar()) != EOF)
    {

        if (isdigit(c) || isalpha(c))
        {
            estado = IN;
        }
        else if (estado == IN)
        {
            agregarToken(resultado, operando, lastToken);
            agregarToken(resultado, operador, ++lastToken);
            ++lastToken;
            estado = OUT;
        }
        else if (estado == OUT)
        {
            agregarToken(resultado, operador, ++lastToken);
            ++lastToken;
        }
    }
};

void agregarToken(token tokenList[], const token Token, unsigned position)
{
    tokenList[position] = Token;
}