#include <assert.h>
#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{

    TOKEN t;
    t = Scanner();
    assert(CONSTANTE == t.type);
    assert(IDENTIFICADOR == Scanner().type);
    assert(ASIGNACION == Scanner().type);
    assert(IGUAL == Scanner().type);
    assert(PARENIZQUIERDO == Scanner().type);
    assert(SUMA == Scanner().type);
    assert(MULTIPLICACION == Scanner().type);
    assert(EXP == Scanner().type);
}