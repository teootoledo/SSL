#include "scanner.h"
#include "parser.h"
#include <stdlib.h>

TOKEN t;

void Parser()
{
Sentencias();
printf("\n\n\t\t--- SINTAXIS CORRECTA ---\n");
}

void Sentencias()
{
    t = Scanner();
    switch (t)
    {
    case IDENTIFICADOR: 
        Definicion();
        Match(FDS);
        break;
    case EXP:
        Expresion();    
        TokenActual(FDS);
        break;
    case FDT:
        return;    
    default:
        ErrorSintactico();          
    }
    Sentencias();
}

void Definicion()
{
    Match(ASIGNACION);
    Match(CONSTANTE);
}

void Expresion (void) {
 Primaria();
 for (t = Scanner(); t == SUMA || t == MULTIPLICACION ; t = Scanner())
    Primaria();
}

void Primaria(){
    t = Scanner(); 
    switch (t)
    {
        case IDENTIFICADOR:
        return;
        case CONSTANTE:
        return;
        case PARENIZQUIERDO:
        while(t == PARENIZQUIERDO){
                Expresion();
                TokenActual(PARENDERECHO);
        }   
        return;
        default:
        ErrorSintactico();
    }     
}
void Match(TOKEN tokenEsperado)
{
    TOKEN actualToken = Scanner();
    if (actualToken != tokenEsperado)
    {
      printf("\n\nTOKEN ESPERADO: ");
      MostrarToken(tokenEsperado);
      printf("TOKEN RECIBIDO: ");
      MostrarToken(actualToken);
      printf("\n");
      ErrorSintactico();
    }
}

void TokenActual(TOKEN tokenEsperado){
    if (tokenEsperado != t)
    {
      printf("\n\nTOKEN ESPERADO: ");
      MostrarToken(tokenEsperado);
      printf("TOKEN RECIBIDO: ");
      MostrarToken(t);
      printf("\n");
      ErrorSintactico();
    }
}

void ErrorSintactico(){
    printf("\nERROR SINTACTICO\n");
    exit(1);
}

