#include "scanner.h"
struct simbolo
{
    TOKEN tipo;
    int nombre[8];
    int valor[8];
} tablaDeSimbolos[8];
typedef struct simbolo simbolo;

void mostrarTablaSimbolos(void);
void agregarSimbolo(int[], TOKEN);
void SetNombre(int[]);
void SetValor(int[]);
void SetTipo(TOKEN);
void mostrarValor(int[]);
void mostrarNombre(int[]);
