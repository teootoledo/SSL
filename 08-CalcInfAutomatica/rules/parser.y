%{
#include "memory.h"
#include "scanner.h"
#include "parser.h"
#include <stdio.h> //printf
#include <stdlib.h> //exit

/* FUNCIONES PRIVADAS */
static void mostrarResultado(int);
static int yylex(void);
static void yyerror(char const *);

%}

%union 
{
  int value;
  char name[20];
}

/* Definición de tokens */
%token <value> CONSTANTE
%token <name> IDENTIFICADOR
%token <name> SUMA
%token <name> MULTIPLICACION
%token <name> IGUAL
%token <name> DEF
%token <name> FDS
%token <name> FDT
%token <name> NAT
%token <name> PARENDERECHO
%token <name> PARENIZQUIERDO
/* Definición de no-terminales */
%type <name> parser
%type <name> sentencias
%type <name> unasentencia
%type <value> expresion
%type <value> definicion
%type <value> termino
%type <value> factor
%start parser

%%
parser: sentencias FDT;

sentencias: unasentencia
          | unasentencia sentencias
;

unasentencia: DEF definicion FDS
         | expresion FDS { mostrarResultado($1); }
;

definicion: IDENTIFICADOR IGUAL CONSTANTE { Assign(GetPosition($1), $3); }

expresion: termino { $$ = $1; }
         | expresion SUMA termino { $$ = $1 + $3; }
;

termino: factor { $$ = $1; }
       | termino MULTIPLICACION factor { $$ = $1 * $3; }
 ;

factor: IDENTIFICADOR { int aux = GetValue($1); if(aux!=(-1)) $$=aux; else exit(1); }
      | CONSTANTE { $$ = $1; }
      | PARENIZQUIERDO expresion PARENDERECHO { $$ = $2; }
;

%%

/* FUNCIONES PUBLICAS */

void yyerror(char const *sentencia){
  printf("SYNTAX ERROR: %s\n", sentencia);
}

int yylex(void){   
    return GetNextToken();
}

void Parser(void){
  switch(yyparse()){
    case 0:
      return;
    case 1:
      return;
    default:
      printf("Error\n");
      return;
  }
}

/* FUNCIONES PRIVADAS */
static void mostrarResultado(int valor) {
    printf("Resultado: %d\n", valor);
}