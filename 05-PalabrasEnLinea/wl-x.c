#include <stdio.h>
#include <stdbool.h>

#define condicion ((c=='\n')||(c=='\t')||(c==' '))

int main(void){
    bool estado=false; /*  FALSE: OUT <-> TRUE: IN    */
    
    char c;
    while((c=getchar())!=EOF){
        
        if(estado==false)
            if(!condicion) estado=true;
                else break;
        if(estado==true)
            if(!condicion) putchar(c);
                else
                {
                    putchar('\n');
                    estado=false;
                }
    }
}