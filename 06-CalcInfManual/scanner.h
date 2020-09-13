// HEADER DEL ANALIZADOR LÉXICO
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define cEst 15
#define cTran 10

typedef enum
{
    operando,
    operador
} token;

enum
{
    IN,
    OUT
} estado;
typedef enum estado Estado;

token scanner(void);

token scanner(void)
{
    int tT[cEst][cTran] =

        {//         0  1  2  3  4
         //         L  D  +  * EOF*/
         /* Q0  */ {2, 1, 4, 4, 3},
         /* Q1  */ {4, 1, 0, 0, 3},
         /* Q2  */ {2, 2, 0, 0, 3},
         /* FDT */ {3, 3, 3, 3, 3},
         /* ERR */ {4, 4, 4, 4, 4}};
}

token scanner(void)
{
    int c;
    Estado estado = Estado.OUT;
    while ((c = getchar()) != EOF)
    {

        if (isdigit(c))
        {
            e
        }
        switch (c)
        {
        case:
            /* code */
            break;

        default:
            break;
        }
    }
};
