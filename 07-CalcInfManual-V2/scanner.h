#if !defined TOKEN_H
#define TOKEN_H
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
    FDS,
    FDT
} TOKEN;

#endif

TOKEN scanner(void);