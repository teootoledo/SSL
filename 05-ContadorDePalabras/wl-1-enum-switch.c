#include <stdio.h>

enum state{IN, OUT};

typedef enum state State;

int main(){
    State estado = OUT;
    int nc, nl, nw;
    nc=nl=nw=0;

    char c; //utilizo este caracter para la seleccion del switch
    while((c=getchar())!= EOF){
        
        ++nc; //nuevo caracter

        switch (c)
        {
        case '\n':          //NUEVA LINEA
            ++nl;
            estado=OUT;
            break;
        case '\t':   //ESPACIOS
            estado=OUT;
            break;
        case ' ':   //ESPACIOS
            estado=OUT;
            break;
        default:            //DENTRO DE UNA PALABRA
            if(estado==OUT){
                estado==IN;
                ++nw; //nueva palabra
                }
            break;
        }
    }

    printf("%d %d %d\n", nl, nw, nc);

}