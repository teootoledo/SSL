%{
#include <stdlib.h> //atoi()
#include <stdio.h>  //printf()
#include <string.h>  //strcpy()
#include "token.h" //Incluyo el header generado por bison
%}
%option noyywrap

%%

[0-9]+                  {
                        yylval.value = atoi(yytext);
                        return CONSTANTE;
                        }

[a-zA-Z][a-zA-Z | 0-9]* {
                        strcpy(yylval.name, yytext); //Copio a yylval lo que ingreso a yytext
                        return IDENTIFICADOR;
                        }

\+                      return SUMA;
        
\*                      return MULTIPLICACION;

\$                      return DEF;

\=                      return IGUAL;
                        
\;                      return FDS;

[\n][\n]                return FDT;

[\n]                    ;

.                       return NAT;

%%

int GetNextToken(void){
        int incomingToken = yylex();
        return incomingToken != 0 ? incomingToken
                                    : 1;
}