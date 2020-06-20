#include <assert.h>
#include "String.h"
#include <stdbool.h>
#include <string.h>

int main(void){

    //Tests para GetLength
    assert(GetLength("hola")==4);

    //Tests para IsEmpty
    assert(IsEmpty("")==true);
    assert(IsEmpty("hola")==false);

    //Tests para Power
    char test[7];
    Power("ab",3,test);
    assert(strcmp(test, "ababab") == 0);
    assert(strcmp(test, "abbbbb") != 0);

    //Tests para Contains
    assert(Contains("hola", 'a', 0));
    assert(Contains("Hello World", ' ', 0));
    assert(false == Contains("Test", '3', 0));

    return 0;
}