/*
Teo Martin Toledo
171-891-5
22062020
*/

#include <assert.h>
#include "String.h"
#include <stdbool.h>
#include <string.h>

    //Prototipos ---------------
void GetLengthTests(void);
void IsEmptyTests(void);
void PowerTests(void);
void ContainsTests(void);


    //Main ---------------
int main(void){
    GetLengthTests();
    IsEmptyTests();
    PowerTests();
    ContainsTests();
    return 0;
}


    //Definiciones de funciones ---------------
    //Tests para GetLength
void GetLengthTests(){
    assert(GetLength("hola")==4);
    }

    //Tests para IsEmpty
void IsEmptyTests(){
    assert(IsEmpty("")==true);
    assert(IsEmpty("hola")==false);
    }

    //Tests para Power
void PowerTests(){
    char test[7];
    Power("ab",3,test);
    assert(strcmp(test, "ababab") == 0);
    assert(strcmp(test, "abbbbb") != 0);
    }

    //Tests para Contains
void ContainsTests(){
    assert(Contains("hola", 'a', 0));
    assert(Contains("Hello World", ' ', 0));
    assert(false == Contains("Test", '3', 0));
    }