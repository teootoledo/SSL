//Definición de funciones
#include <stdbool.h>
#include "String.h"

//GetLength
unsigned GetLength(const char str[]){
    unsigned counter=0;
    for(unsigned i=0; str[i]!='\0'; ++i){
        ++counter;
    }
    return counter;
}


//IsEmpty
bool IsEmpty(const char str[]){
    return GetLength(str)==0;
}


//Power
//char* Power(char str[], const unsigned exp){
//    unsigned newLength = GetLength(str)*exp;
//    char power[newLength];
//}