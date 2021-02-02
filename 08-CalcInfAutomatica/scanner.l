%{
  #include "scanner.h"
  #include <stdio.h>
  #include <stdlib.h>
  static TOKEN arrivingToken;

}%

%option noyywrap

%%

[a-zA-Z][a-zA-Z]* {
                    strcpy(yylval.string, yytext);
                    return IDENTIFICADOR;
                  }
[0-9]+            {
                    yylval.number=atoi(yytext);
                    return CONSTANTE;
                  }
\)        return PARENDERECHO;
\(        return PARENIZQUIERDO;
\*        return MULTIPLICACION;
\+        return SUMA;
\$        return DEFINICION;
\=        return IGUAL;
\{        return INICIO;
\}        return FIN;
\;        return PUNTO_Y_COMA;
<<EOF>>   return FDT;
[ ]+ ;
.                       {
                          Error("[Scanner] Error Léxico, carácter inválido: %s\n", yytext);
                          return ERROR_LEXICO;
                        }

%%

TOKEN GetNextToken(){
  
}
