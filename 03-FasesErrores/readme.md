# Trabajo #6 - Fases de la traducción y errores

### Objetivo: 
- Identificar las fases de traducción y errores.
---
### Tareas:
1. Investigar las funcionalidades y opciones que su compilador presenta para limitar el inicio y fin de las fases de traducción.
2. Para la siguiente secuencia de pasos: 
	2a. Transicribir en readme.md cada comando ejecutado.
	2b. Describir en readme.md el resultado u error obtenidos para cada paso.
---
## 1. Investigación

> #### Comandos

| Comando     						| Resultado												|
|-----------------------------------|-------------------------------------------------------|
| gcc -E source.c > source.i		| Devuelve el preprocesamiento.							|
| gcc -S source.c					| Devuelve el programa en assembler. 					|
| gcc -c source.c					| Devuelve código objeto, para fabricar un ejecutable 	|

> #### Etapas de compilación.
El proceso de compilación involucra cuatro etapas sucesivas: **preprocesamiento**, **compilación**, **ensamblado** y **enlazado**. Para pasar de un programa fuente escrito por un humano a un archivo ejecutable es necesario realizar estas cuatro etapas en forma sucesiva. Los comandos gcc y g++ son capaces de realizar todo el proceso de una sola vez.



## 2- Etapas

#### 1 - Creación de *"hello2.c"*

#### 2 - *hello2.c* preprocesado y volcado en *hello2.i*

Comando utilizado: 

	gcc -E hello2.c > hello2.i

Contenido de **hello2.i**:

    # 1 "hello2.c" 
    # 1 "<built-in>" 
    # 1 "<command-line>" 
    # 1 "hello2.c" 
    int main(void){
	int i=42;
	prontf("La respuesta es %d\n");

> En el archivo "hello2.i" puede verse aún el código en lenguaje C, pero se ven modificadas ciertas líneas. Lo que se realizó, fue la **interpretación de las directivas** al preprocesador. Un ejemplo puede ser el reemplazo de los comentarios por `" "`.

#### 3 - Creación de *"hello3.c"*

#### 4 - Semántica de la línea #1

> La línea `int  printf(const  char *s, ...);` semánticamente envía un **output con formato** definido a *stdout*. El "`*s`" establece que será de tipo **string**.

#### 5 - Diferencias entre *"hello3.c"* y *"hello3.i"*

Comando utilizado: 

	gcc -E hello3.c > hello3.i

Contenido de **"hello3.i"**:


	# 1 "hello3.c"
	# 1 "<built-in>"
	# 1 "<command-line>"
	# 1 "hello3.c"
	int printf(const char *s, ...);
	int main(void){
	int i=42;
	prontf("La respuesta es %d\n");

Contenido de **"hello3.c"**:

	int printf(const char *s, ...);
	int main(void){
	int i=42;
	prontf("La respuesta es %d\n");

> La diferencia principal está en las primeras 4 líneas que comienzan con `#1 "..."`. Por lo demás, el archivo mantiene el mismo código en lenguaje C que el archivo fuente. Eso sí, con las directivas al preprocesador ya realizadas.

#### 6 - Compilar y generar *"hello3.s"* sin ensamblar

Comando utilizado:

	gcc -S hello3.c

Contenido de **"hello3.s"**:

		.file	"hello3.c"

Error mostrado por consola:

	hello3.c: In function 'main':
	hello3.c:4:2: warning: implicit declaration of function 'prontf' [-Wimplicit-function-declaration]
	  prontf("La respuesta es %d\n");
	  ^~~~~~
	hello3.c:4:2: error: expected declaration or statement at end of input

#### 7 - Corregir en *"hello4.c"*. Compilar sin ensamblar

Contenido de **"hello4.c"**:

	int  printf(const  char *s, ...);
	int  main(void){
	int i=42;
	printf("La respuesta es %d\n");}

Comando utilizado:

	gcc -S hello4.c

Contenido de **"hello4.s"**:

		.file	"hello4.c"
		.def	___main;	.scl	2;	.type	32;	.endef
		.section .rdata,"dr"
	LC0:
		.ascii "La respuesta es %d\12\0"
		.text
		.globl	_main
		.def	_main;	.scl	2;	.type	32;	.endef
	_main:
	LFB0:
		.cfi_startproc
		pushl	%ebp
		.cfi_def_cfa_offset 8
		.cfi_offset 5, -8
		movl	%esp, %ebp
		.cfi_def_cfa_register 5
		andl	$-16, %esp
		subl	$32, %esp
		call	___main
		movl	$42, 28(%esp)
		movl	$LC0, (%esp)
		call	_printf
		movl	$0, %eax
		leave
		.cfi_restore 5
		.cfi_def_cfa 4, 4
		ret
		.cfi_endproc
	LFE0:
		.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
		.def	_printf;	.scl	2;	.type	32;	.endef

#### 8 - Investigar *"hello4.s"*

> La compilación resulta en un archivo que contiene el programa en código Assembler. Este es utilizado posteriormente para ser ensamblado y concluir en el archivo objeto.

#### 9 - Ensamblar *"hello4.s"* en *"hello4.o"*. No vincular

Comando utilizado:

	as -o hello4.o hello4.s

Contenido de **"hello4.o"**:

	4c01 0600 0000 0000 c801 0000 1200 0000
	0000 0401 2e74 6578 7400 0000 0000 0000
	0000 0000 2c00 0000 0401 0000 a001 0000
	0000 0000 0300 0000 2000 3060 2e64 6174
	6100 0000 0000 0000 0000 0000 0000 0000
	0000 0000 0000 0000 0000 0000 0000 0000
	4000 30c0 2e62 7373 0000 0000 0000 0000
	0000 0000 0000 0000 0000 0000 0000 0000
	0000 0000 0000 0000 8000 30c0 2e72 6461
	7461 0000 0000 0000 0000 0000 1400 0000
	3001 0000 0000 0000 0000 0000 0000 0000
	4000 3040 2f34 0000 0000 0000 0000 0000
	0000 0000 2400 0000 4401 0000 0000 0000
	0000 0000 0000 0000 4000 3040 2f31 3500
	0000 0000 0000 0000 0000 0000 3800 0000
	6801 0000 be01 0000 0000 0000 0100 0000
	4000 3040 5589 e583 e4f0 83ec 20e8 0000
	0000 c744 241c 2a00 0000 c704 2400 0000
	00e8 0000 0000 b800 0000 00c9 c390 9090
	4c61 2072 6573 7075 6573 7461 2065 7320
	2564 0a00 4743 433a 2028 4d69 6e47 572e
	6f72 6720 4743 432d 362e 332e 302d 3129
	2036 2e33 2e30 0000 1400 0000 0000 0000
	017a 5200 017c 0801 1b0c 0404 8801 0000
	1c00 0000 1c00 0000 0400 0000 2900 0000
	0041 0e08 8502 420d 0565 c50c 0404 0000
	0a00 0000 1000 0000 1400 1900 0000 0a00
	0000 0600 1e00 0000 1100 0000 1400 2000
	0000 0400 0000 1400 2e66 696c 6500 0000
	0000 0000 feff 0000 6701 6865 6c6c 6f34
	2e63 0000 0000 0000 0000 0000 5f6d 6169
	6e00 0000 0000 0000 0100 2000 0201 0000
	0000 0000 0000 0000 0000 0000 0000 0000
	2e74 6578 7400 0000 0000 0000 0100 0000
	0301 2900 0000 0300 0000 0000 0000 0000
	0000 0000 2e64 6174 6100 0000 0000 0000
	0200 0000 0301 0000 0000 0000 0000 0000
	0000 0000 0000 0000 2e62 7373 0000 0000
	0000 0000 0300 0000 0301 0000 0000 0000
	0000 0000 0000 0000 0000 0000 2e72 6461
	7461 0000 0000 0000 0400 0000 0301 1400
	0000 0000 0000 0000 0000 0000 0000 0000
	0000 0000 1900 0000 0000 0000 0500 0000
	0301 2300 0000 0000 0000 0000 0000 0000
	0000 0000 0000 0000 2400 0000 0000 0000
	0600 0000 0301 3800 0000 0100 0000 0000
	0000 0000 0000 0000 5f5f 5f6d 6169 6e00
	0000 0000 0000 2000 0200 5f70 7269 6e74
	6600 0000 0000 0000 2000 0200 2e00 0000
	2e72 6461 7461 247a 7a7a 002e 6568 5f66
	7261 6d65 002e 7264 6174 6124 7a7a 7a00
	2e65 685f 6672 616d 6500 

#### 10 - Vincular *"hello4.o"* con la biblioteca estándar. Generar el ejecutable

Comando utilizado:

	gcc -o hello4 hello4.o

Error resultante:

	hello4.o:hello4.c:(.text+0x1e): undefined reference to `prontf'
	collect2.exe: error: ld returned 1 exit status

#### 11 - Corregir en *"hello5.c"*. Generar el ejecutable

Contenido de **"hello5.c"**:

	int  printf(const  char *s, ...);
	int  main(void){
	int i=42;
	printf("La respuesta es %d\n");}

Comando utilizado:

	gcc hello5.c

#### 12 - Ejecutar y analizar el resultado

Resultado obtenido:

	"La respuesta es 4200768"

> El resultado es erróneo debido a que no se especifica la variable a ser mostrada en el printf.

#### 13 - Corregir en *"hello6.c"*

Contenido de **"hello6.c"**:

	int  printf(const  char *s, ...);
	int  main(void){
	int i=42;
	printf("La respuesta es %d\n",i);}

Comando utilizado:

	gcc hello6.c

Resultado obtenido:

	"La respuesta es 42" ✅

#### 14 - Escribir la variante *"hello7.c"*

Contenido de **"hello7.c"**:

	int main(void){
		int i=42;
		printf("La respuesta es %d\n", i);
		}

#### 15 - ¿Por qué funciona?
> *EN TIEMPO DE LINKEO BUSCA SIEMPRE LA LIBRERÍA ESTÁNDAR*
> La variante anterior compila porque printf está declarada implícitamente. Arroja el siguiente warning:

	hello7.c: In function 'main':
	hello7.c:3:5: warning: implicit declaration of function 'printf' [-Wimplicit-function-declaration]
	     printf("La respuesta es %d\n", i);
	     ^~~~~~
	hello7.c:3:5: warning: incompatible implicit declaration of built-in function 'printf'
	hello7.c:3:5: note: include '<stdio.h>' or provide a declaration of 'printf'

> El programa en mi caso no es ejecutable.
> Arroja una alerta "Acceso denegado"

![Error](/03-FasesErrores/Error.jpg)
