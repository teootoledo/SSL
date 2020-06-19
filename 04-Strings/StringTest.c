#include <assert.h>
#include "String.h"
#include <stdbool.h>

int main(void){

    assert(GetLength("hola")==4);

    assert(IsEmpty("")==true);
    assert(IsEmpty("hola")==false);

    return 0;
}