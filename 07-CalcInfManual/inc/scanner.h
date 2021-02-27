#define MAX_NAME_LENGTH 20

#ifndef SCANNER_H
#define SCANNER_H

// Declaración de flag para habilitar/deshabilitar consumo de TOKENS
extern int keepLastToken;

// Definición tipoDeToken
typedef enum
{
    NAT,
    INICIO,
    FIN,
    IDENTIFICADOR,
    CONSTANTE,
    IGUAL,
    PARENIZQUIERDO,
    PARENDERECHO,
    SUMA,
    PRODUCTO,
    DEFINICION,
    FDS,
    FDT
} tipoDeToken;

// Definición de la estructura TOKEN
typedef struct TOKEN
{
    tipoDeToken type;   //Tipo
    union               //string o int
    {
        char name[MAX_NAME_LENGTH]; 
        int value;     
    } data;
} TOKEN;

#endif

// Prototipo de funciones públicas
// Función que se encarga de devolver los TOKENs según lo que el scanner analiza.
TOKEN GetNextToken(void);