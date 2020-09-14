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

token scanner(void);

token GetNextToken(void);