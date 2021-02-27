#define MAX_NAME_LENGTH 20

#ifndef SCANNER_H
#define SCANNER_H

// Definición tipoDeToken
typedef enum
{
    NAT,
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

// Creamos struct TOKEN
struct TOKEN
{
    tipoDeToken type;   //Tipo
    union               //string o int
    {
        char name[MAX_NAME_LENGTH]; 
        int value;     
    } data;
};

// Redefino referencia a la estructura
typedef struct TOKEN TOKEN;

#endif

// Prototipo de funciones públicas --------

// Función que se encarga de devolver los TOKENs según lo que el scanner analiza.
TOKEN GetNextToken(void);
