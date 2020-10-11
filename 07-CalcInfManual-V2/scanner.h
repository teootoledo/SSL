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
    EXP,
    FDS,
    FDT
} TOKEN;

#endif

TOKEN Scanner(void);
void MostrarToken(TOKEN);