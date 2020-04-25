# Trabajo #5 - Niveles del Lenguaje: Hello.cpp v Hello.c

### Objetivo: 
- Analizar e identificar las diferencias entre hello.cpp y hello.c, en los tres niveles: léxico, sintáctico, y semántico.
---
### Hello.c
	#include <stdio.h>
	int main(){
		printf("Hello, World!\n");
		}

### Hello.cpp
	#include <iostream>
	int main(){
	    std::cout << "Hello, World!";
		}
---

### Comparación
|                |Hello.c                        |Hello.cpp                    		|
|----------------|-------------------------------|----------------------------------|
|**Léxico**          |`( )`                          |`<< ::`                          |
|**Sintaxis**        |`printf("Hello, World!\n");"` |`std::cout << "Hello, World!";`|
|**Semántica**       |`printf()`                    |`cout << " ";`                 |
---

> **Léxico:** En este caso particular la diferencia se encuentra en los símbolos señalados en el cuadro. Pero si se lo observa buscando comparar los léxicos de ambos lenguajes, son prácticamente los mismos.

> **Sintaxis:** Acá se denota una diferencia en las funciones `cout` y `printf` que requieren de un distinto orden para funcionar correctamente. Esto a nivel lenguaje, dependería particularmente de cada función.

> **Semántica:** Pragmáticamente su función es la misma, pero para conocer si semánticamente mantienen una relación, sería necesario ver como es el funcionamiento interno de cada una.