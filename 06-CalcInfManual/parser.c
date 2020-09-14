#include "scanner.h"
#include "parser.h"

typedef enum
{
    Q0_inicio,
    Q1_final
} EstadoParser;

bool parser(void)
{
    EstadoParser estadoActual = Q0_inicio;
    token newToken;
    while ((newToken = GetNextToken()) != fdt)
    {
        switch (estadoActual)
        {
        case Q0_inicio:
            if ((newToken == identificador) || (newToken == constante))
            {
                estadoActual = Q1_final;
                break;
            }
            return false;
        case Q1_final:
            if ((newToken == adicion) || (newToken == producto))
            {
                estadoActual = Q0_inicio;
                break;
            }
            return false;
        }
    }
    if (estadoActual == Q0_inicio)
    {
        return false;
    }
}