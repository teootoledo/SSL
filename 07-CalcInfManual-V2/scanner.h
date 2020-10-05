typedef enum
{
    IDENTIFICADOR,
    CONSTANTE,
    ASIGNACION,
    IGUAL,
    PARENIZQUIERDO,
    PARENDERECHO,
    SUMA,
    MULTIPLICACION,
    FDS,
    FDT,
    NAT
} TOKEN;

TOKEN Scanner(void);

void mostrar(TOKEN);
