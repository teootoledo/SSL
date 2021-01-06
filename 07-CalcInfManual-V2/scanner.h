#define MAX_NAME_LENGTH 10

#ifndef SCANNER_H
#define SCANNER_H

// DEFINICION DE TIPO DE TOKEN
typedef enum
{
    NAT,
    IDENTIFICADOR,
    CONSTANTE,
    ASIGNACION,
    IGUAL,
    PARENIZQUIERDO,
    PARENDERECHO,
    SUMA,
    MULTIPLICACION,
    EXP,
    FDS,
    FDT
} tipoDeToken;

struct TOKEN //resolver en scanner
{
    tipoDeToken type;
    union
    {
        char name[10]; //string
        int value;     //int o double
    } data;
};

typedef struct TOKEN TOKEN;

#endif

TOKEN Scanner(void);
