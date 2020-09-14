#include <stdio.h>
#include <stdbool.h> //?
#include "parser.h"

int main(void)
{
    if (parser())
        printf("\n--- Syntax OK ---\n");
    else
        printf("\n--- Syntax ERROR ---\n");
}