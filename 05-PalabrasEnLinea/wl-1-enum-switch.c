#include <stdio.h>

enum state{IN, OUT};

typedef enum state State;

int main(void){
    State estado = OUT;

    char c; //utilizo este caracter para la seleccion del switch
    while((c=getchar())!= EOF){

        switch (c)
        {
        case '\n':
        case '\t':
        case ' ':
            if (estado == IN) putchar('\n');
            estado = OUT;
            break;
        default:            
            putchar(c);
            estado = IN;
            break;
        }
    }
}