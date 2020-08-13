#include <stdio.h>

void OUT();
void IN();

int main(void){
    OUT();
    return 0;
}

void OUT(){
    char c;
    if((c = getchar()) != EOF) 
        if (c == ' ' || c == '\n' || c == '\t') OUT();
        else { 
            putchar(c);
            IN(); 
        }
}

void IN(){
    char c;
    if((c = getchar()) != EOF) 
        if (c == ' ' || c == '\n' || c == '\t'){
            putchar('\n');
            OUT();}
        else { 
            putchar(c);
            IN();
        }
}