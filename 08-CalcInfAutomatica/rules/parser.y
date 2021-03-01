%{
#include "memory.h"
#include "scanner.h"
#include "parser.h"
#include <stdio.h> //printf
#include <stdlib.h> //exit

/* Prototipos de funciones privadas */
static void mostrarResultado(int);
static int yylex();
static void yyerror();

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
%type <name> listaSentencias
%type <name> sentencia
%type <value> expresion
%type <value> definicion
%type <value> termino
%type <value> factor
%start parser

%%
parser: listaSentencias FDT {printf("Sentencia");}

listaSentencias: sentencia FDS {printf("Sentencia");}
          | listaSentencias sentencia FDS
;

sentencia: DEF definicion
         | IGUAL expresion { mostrarResultado($2); }
;

definicion: IDENTIFICADOR IGUAL CONSTANTE { Assign(GetPosition($1), $3); }

expresion: termino { $$ = $1; }
         | expresion SUMA termino { $$ = $1 + $3; }
;

termino: factor { $$ = $1; }
       | termino MULTIPLICACION factor { $$ = $1 * $3; }
 ;

factor: IDENTIFICADOR { int aux = GetValue($1); $$=aux;}
      | CONSTANTE { $$ = $1; }
      | PARENIZQUIERDO expresion PARENDERECHO { $$ = $2; }
;

%%

/* Definición de funciones privadas */
// yyerror es utilizada para mostrar que ocurrió un error y cerrar el programa.
void yyerror(){
  printf("[Parser] Sintaxis incorrecta.");
  exit(3);
}

int yylex(void){   
    return GetNextToken();
}

// mostrarResultado imprime por pantalla el resultado de la expresión parseada.
static void mostrarResultado(int valor) {
    printf("Resultado: %d\n", valor);
}

/* Definición de funciones públicas */
// Definición de Parser()
void Parser(void){
  switch(yyparse()){
    case 0:
      printf("[Parser] Finalizado de manera exitosa.");
      return;
    case 1:
    default:
      printf("Error\n");
      return;
  }
}
// yyparse lee tokens y ejecuta acciones. Retorna al matchear FDT
