#include "scanner.h"

void Match(TOKEN tokenEsperado)
{
    TOKEN tokenActual = GetNextToken();
    if (tokenActual != tokenEsperado)
    {
        ErrorSintactico();
    }
}

void Objetivo(void)
{
    /* <objetivo> -> <programa> FDT */
    Programa();
    Match(FDT);
}
void Programa(void)
{
    ListaDeSentencias();
}

void ListaSentencias(void)
{
    /* <listaSentencias>*/
    Sentencia();
    while (1)
    {
        switch (ProximoToken())
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

void Sentencia(void)
{
    TOKEN token = GetNextToken();
    switch (token)
    {
    case IDENTIFICADOR: /* <sentencia> -> ID := <expresion>; */
        token = GetNextToken();
        switch (token)
        {
        case ASIGNACION:
            Definicion();
            break;
        case SUMA:
        case MULTIPLICACION:
            Expresion();
            break;
        case CONSTANTE:
            Expresion();

        default:
            break;
        }
        break;
    case CONSTANTE: /* <sentencia> -> LEER ( <listaIdentificadores> ); */
        Match(LEER);
        Match(PARENIZQUIERDO);
        ListaIdentificadores();
        Match(PARENDERECHO);
        Match(PUNTOYCOMA);
        break;
    case ESCRIBIR: /* <sentencia> -> ESCRIBIR (<listaExpresiones>); */
        Match(ESCRIBIR);
        Match(PARENIZQUIERDO);
        ListaExpresiones();
        Match(PARENDERECHO);
        Match(PUNTOYCOMA);
        break;
    default:
        ErrorSintactico(tok);
        break;
    }
}

void Definicion(void)
{
    Match(CONSTANTE);
    Match(FDS);
}

void Expresion(void)
{
    /* <expresion> -> <primaria> {<operadorAditivo> <primaria>} */
    TOKEN t;
    Primaria();
    for (t = GetNextToken(); t == SUMA || t == MULTIPLICACION; t = GetNextToken())
    {
        OperadorAditivo();
        Primaria();
    }
}

void Primaria(void)
{
    /* <identificador> || <constante> || <parenizquierdo> <expresion> <parenderecho> */
    TOKEN t = GetNextToken();
    if (t == IDENTIFICADOR || t == CONSTANTE)
        Match(t);
    else
        ErrorSintactico(t);
}

void OperadorAditivo(void)
{
    /* <operadorAditivo> -> uno de SUMA RESTA */
    TOKEN t = GetNextToken();
    if (t == SUMA)
        Match(t);
    else
        ErrorSintactico(t);
}