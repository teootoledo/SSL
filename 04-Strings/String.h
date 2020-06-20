/*
Teo Martin Toledo
171-891-5
20062020
*/

//String.h
#include <stdbool.h>
//--------------------------------


//GetLength: Σ* → |N
//La cadena de caracteres debe ser válida y terminar con '\0'.
unsigned GetLength(const char[]);

//IsEmpty: Σ* → |B
//Sin precondiciones.
bool IsEmpty(const char[]);

//Power: Σ* x |N → Σ*
//Se asume el último argumento tiene la capacidad para almacenar la totalidad de la operación.
void Power(const char[], const unsigned, char[]);

//Contains Σ* x Σ → |B
//Se debe pasar 0 como tercer argumento. Esto debido a que no existen argumentos por defecto en C.
bool Contains(const char[], const char, unsigned pos);