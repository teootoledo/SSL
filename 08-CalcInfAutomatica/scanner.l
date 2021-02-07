%{
#include <stdlib.h> //atoi()
#include <stdio.h>  //printf()
#include <string.h>  //strcpy()
#include "y.tab.h"

//int yylval;

%}
%option noyywrap

CONSTANTE    [0-9]+
IDENTIFICADOR    [a-zA-Z][a-zA-Z | 0-9]*
SUMA  \+
MULTIPLICACION  \*
DEF \$
IGUAL \=
FDS \;
FDT [\n][\n]
NAT .
%%

{CONSTANTE}             {
                        printf( "Constante: %s\n", yytext);
                        yylval = atoi(yytext);
                        return CONSTANTE;
                        }

{IDENTIFICADOR}         {
                        strcpy(yylval, yytext); //Copio a yylval lo que ingreso a yytext
                        printf( "Identificador: %s\n", yytext);
                        return IDENTIFICADOR;
                        }

{SUMA}                  {
                        printf( "Operador: %s\n", yytext );
                        return SUMA
                        }
        
{MULTIPLICACION}        {
                        printf( "Operador: %s\n", yytext );
                        return MULTIPLICACION
                        }
{DEF}                   {
                        printf( "Operador: %s\n", yytext );
                        return DEF
                        }

{IGUAL}                 {
                        printf( "Operador: %s\n", yytext );
                        return IGUAL
                        }

{FDS}                   return FDS;

{FDT}                   return FDT;

{NAT}                   return NAT;

%%

int GetNextToken(void){
        int incomingToken = yylex();
        return incomingToken != 0 ? incomingToken
                                    : 1;
}