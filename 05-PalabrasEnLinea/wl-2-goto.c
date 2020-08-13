#include <stdio.h>

int main(void) {
    char c;
    OUT: if((c = getchar()) == EOF) return 0;
        if (c == ' ' || c == '\n' || c == '\t')
            goto OUT;
        else { 
            putchar(c);
            goto IN; 
        }

    IN: if((c = getchar()) == EOF) return 0;
        if (c == ' ' || c == '\n' || c == '\t') {
            putchar('\n');
            goto OUT;
        }
        else {
            putchar(c);
            goto IN;
        } 
}