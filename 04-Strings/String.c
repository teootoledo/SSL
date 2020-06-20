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
void Power(const char str[], const unsigned exp, char resultado[]){
    unsigned lengthResultado = GetLength(str)*exp;
    for(unsigned i=0; i<lengthResultado; ++i){
        resultado[i]=str[i%GetLength(str)];
    }
    resultado[lengthResultado]='\0'; //fin de la cadena
}


//Contains NO RECURSIVA
/*
bool Contains(const char str[], const char c){
    for(unsigned i=0; i < GetLength(str); ++i){
        if(c==str[i]) return true;
        else continue;
    }
    return false;
}
*/

//Constains RECURSIVA

bool Contains(const char str[], const char c, unsigned pos){
    while(str[pos] != '\0'){
        if(str[pos]==c) return true;
        return Contains(str, c, ++pos);
    }
    return false;
}