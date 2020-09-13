// HEADER DEL ANALIZADOR LÉXICO
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

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

token *scanner(void);

void agregarToken(token[], const token, unsigned);
