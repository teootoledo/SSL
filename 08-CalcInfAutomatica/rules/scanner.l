%{
/* scanner.l
 - Reglas léxicas y TOKENs. Compilable de Flex.
 - TOLEDO, Teo Martin - 171.891-5 - UTN FRBA - ft (MARECO, RUBIN)
 - 20210301
*/

#include <stdlib.h> //atoi()
#include <stdio.h>  //printf()
#include <string.h>  //strcpy()
#include "token.h" //Incluyo el header generado por bison

#undef YY_DECL
#define YY_DECL int GetNextToken(void)
YY_DECL;
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
        
\*                      return PRODUCTO;

\$                      return DEFINICION;

\=                      return IGUAL;
                        
\;                      return FDS;

\(                      return PARENIZQUIERDO;

\)                      return PARENDERECHO;

\!                      return FDT;

[\s\t\n]                ;

.                       return NAT;

%%