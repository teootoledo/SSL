// HEADER DEL ANALIZADOR LÉXICO

typedef enum
{
    constante,
    identificador,
    adicion,
    producto,
    fdt,
    err
} token;

token GetNextToken(void);