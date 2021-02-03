%{
  #include <stdio.h>
  #include <stdlib.h>
}%

%option noyywrap

%%

[a-zA-Z][a-zA-Z | 0-9]* {
                    strcpy(yylval.string, yytext);
                    return IDENTIFICADOR;
                  }
[0-9]+            {
                    yylval.number=atoi(yytext);
                    return CONSTANTE;
                  }
")"        return PARENDERECHO;
")"        return PARENIZQUIERDO;
"*"        return MULTIPLICACION;
"+"        return SUMA;
"$"        return DEFINICION;
"="        return IGUAL;
";"        return FDS;
\\n\\n   return FDT;
.                       {
                          printf("Ha ingresado el siguiente caracter no v%clido: %s\n",160, yytext);
                          return FDT;
                        }

%%

main(int argc, char **argv)
{
 int tok;
 while(tok = yylex()) {
 printf("%d", tok);
 if(tok == NUMBER) printf(" = %d\n", yylval);
 else printf("\n");
 }
}
