#include "scanner.h"
#include "parser.h"

void Match(TOKEN tokenEsperado)
{
    TOKEN tokenActual = scanner();
    if (tokenActual != tokenEsperado)
    {
        //ErrorSintactico();
        printf("\n\nERROR SINTACTICO MATCH - Esperado: %u - Recibido: %u", tokenEsperado, tokenActual);
    }
}

void Objetivo()
{
    /* <objetivo> -> <programa> FDT */
    Programa();
    Match(FDT);
    printf("\n\n\t\t--- SINTAXIS CORRECTA ---");
}

void Programa()
{
    ListaDeSentencias();
}

void ListaDeSentencias()
{
    /* <listaSentencias>*/
    Sentencia();
    while (1)
    {
        switch (scanner())
        {
        case IDENTIFICADOR:
        case CONSTANTE:
        case PARENIZQUIERDO:
            Sentencia();
            break;
        default:
            return;
        }
    }
}

void Sentencia()
{
    TOKEN token = scanner();
    switch (token)
    {
    case IDENTIFICADOR: /* <sentencia> -> ID := <expresion>; */
        printf("MATCH ID OK");
        token = scanner();
        switch (token)
        {
        case ASIGNACION:
            printf("MATCH ASIGNACION OK");
            Definicion();
            break;
        default:
            break;
        }
        break;
    default:
        //ErrorSintactico(token);
        printf("\n\nERROR SINTACTICO");
        break;
    }
}

void Definicion()
{
    Match(CONSTANTE);
    printf("MATCH CONSTANTE OK");
    Match(FDS);
    printf("MATCH FDS OK");
}

// void Expresion(void)
// {
//     /* <expresion> -> <primaria> {<operadorAditivo> <primaria>} */
//     TOKEN t;
//     Primaria();
//     for (t = GetNextToken(); t == SUMA || t == MULTIPLICACION; t = GetNextToken())
//     {
//         OperadorAditivo();
//         Primaria();
//     }
// }

// void Primaria(void)
// {
//     /* <identificador> || <constante> || <parenizquierdo> <expresion> <parenderecho> */
//     TOKEN t = GetNextToken();
//     if (t == IDENTIFICADOR || t == CONSTANTE)
//         Match(t);
//     else
//         ErrorSintactico(t);
// }

// void OperadorAditivo(void)
// {
//     /* <operadorAditivo> -> uno de SUMA RESTA */
//     TOKEN t = GetNextToken();
//     if (t == SUMA)
//         Match(t);
//     else
//         ErrorSintactico(t);
// }