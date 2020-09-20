// HEADER DEL ANALIZADOR LÉXICO

typedef enum
{
    constante,
    identificador,
    adicion,
    producto,
    lpar,
    rpar,
    fdt,
    err
} token;

token GetNextToken(void);