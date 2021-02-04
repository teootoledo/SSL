%{
#include <stdlib.h> //atoi()
#include <stdio.h>  //printf()

int yylval;

%}
%option noyywrap

CONSTANTE    [0-9]+
IDENTIFICADOR    [a-zA-Z][a-zA-Z | 0-9]*
SUMA  \+
MULTIPLICACION  \*
DEF $
IGUAL =
FDS ;
FDT \\n\\n

%%

{CONSTANTE} {
            printf( "Constante: %s\n", yytext);
            yylval = atoi(yytext);
            }

{IDENTIFICADOR}  printf( "An identifier: %s\n", yytext );

{SUMA}  printf( "An operator: %s\n", yytext );

{MULTIPLICACION}  printf( "An operator: %s\n", yytext );

.           printf( "Caracter no reconocido: %s\t LEXICAL ERROR\n", yytext );

%%

int main( argc, argv )
int argc;
char **argv;
    {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;

    yylex();
    }