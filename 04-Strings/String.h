//String.h
#include <stdbool.h>
//--------------------------------

//GetLength: Σ* → |N
unsigned GetLength(const char[]);

//IsEmpty: Σ* → |B
bool IsEmpty(const char[]);

//Power: Σ* x |N → Σ*
char* Power(char[], unsigned);