#include "scanner.h"
struct simbolo
{
    TOKEN tipo;
    int nombre[8];
    int valor[8];
} tablaDeSimbolos[8];
typedef struct simbolo simbolo;

void MostrarTablaSimbolos(void);
void AgregarSimbolo(int[], TOKEN);
void SetNombre(int[]);
void SetValor(int[]);
void SetTipo(TOKEN);
void MostrarValor(int[]);
void MostrarNombre(int[]);
