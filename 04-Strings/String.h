//String.h
#include <stdbool.h>
//--------------------------------

//GetLength: Σ* → |N
unsigned GetLength(const char[]);

//IsEmpty: Σ* → |B
bool IsEmpty(const char[]);

//Power: Σ* x |N → Σ*
void Power(const char[], const unsigned, char[]);

//Contains Σ* x Σ → |B
bool Contains(const char[], const char, unsigned pos);