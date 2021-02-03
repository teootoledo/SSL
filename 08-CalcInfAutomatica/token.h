
typedef enum
{
    NAT,
    IDENTIFICADOR,
    CONSTANTE,
    IGUAL,
    PARENIZQUIERDO,
    PARENDERECHO,
    SUMA,
    MULTIPLICACION,
    DEF,
    FDS,
    FDT
} tipoDeToken;

struct TOKEN
{
    tipoDeToken type;
    union
    {
        char name[10]; //string
        int value;     //int o double
    } data;
};

typedef struct TOKEN TOKEN;}

TOKEN CreateToken(tipoDeToken, char);
