![](/07-CalcInfManual-V2/imgs/Banner.png)



----------------------

**¿De qué trata este trabajo?** [Link al documento.](https://josemariasola.github.io/ssl/assignments/2020/Ssl%20Assignments.pdf#page=53)

---------



# Tabla de Contenidos

<!--ts-->
- [Tabla de contenidos](#tabla-de-contenidos)
- [Síntesis](#síntesis)
- [Calculadora](#calculadora)
    - [Descripción del lenguaje utilizado](#descripción-del-lenguaje-utilizado)
    - [Scanner](#scanner)
        - [Gramática Léxica](#gramática-léxica)
        - [Lista de tokens](#lista-de-tokens)
    - [Parser](#parser)
        - [Gramática Sintáctica](#gramática-sintáctica)
    - [Memoria](#memoria)
        - [GetPosition()](#getposition)
        - [Assign()](#assign)
        - [GetValue()](#getvalue)
<!--te-->


# Síntesis

Este trabajo práctico es un programa de consola desarrollado en lenguaje C, con herramientas como **Flex** y **Bison**, que permite realizar tanto el análisis léxico, y sintáctico de las distintas sentencias ingresadas por el usuario. Cuenta con un lenguaje propio, definido para poder realizar estas evaluaciones, y arroja un resultado preciso de la operación.

Otra funcionalidad con la que cuenta este programa es la de almacenar variables con sus relativos nombres en una “memoria”, pudiendo acceder a los valores asociados para realizar posteriormente la evaluación de la sentencia.

Cabe destacar que las variables deben tener un máximo de 20 `char` para su nombre. Característica que podría modificarse según la conveniencia del usuario. Al igual que la cantidad máxima de variables almacenadas, que ahora mismo se encuentra fijada en 200.



-------

![](/07-CalcInfManual-V2/imgs/Banner.png)

# Calculadora



## Descripción del lenguaje utilizado

- Operaciones en el dominio de los números Naturales incluyendo al 0.
- Todos los identificadores son declarados explícitamente y con una longitud máxima de 10 caracteres.
- Los identificadores deben comenzar con una letra y están compuestos de letras y dígitos.
- Las constantes son secuencias de dígitos.
- Hay dos tipos de sentencias:
  - **Definición** > Este tipo de sentencia almacena el valor pasado en una variable.
  - **Expresión** > Esta sentencia realiza la evaluación de una expresión simple o compuesta.
- Las variables ya existentes pueden modificar su valor. El procedimiento es el mismo que al definir una nueva variable.
- Cada sentencia termina con un ‘’ ; ‘’, el cual hace referencia a un token llamado “FDS” que refiere al final de la sentencia. Para confirmar el ingreso de la sentencia se presiona “ENTER” ( “\n” ).
- El final de texto (FDT) será dado por el char ' ! ' consecutivos.



------

![](/07-CalcInfManual-V2/imgs/Banner1.png)



## Scanner

El **Scanner** es la sección del programa encargada de realizar el análisis léxico de las cadenas de caracteres que son ingresadas por el usuario.

La función del analizador léxico, `yylex`, reconoce tokens desde el flujo de entrada y se los devuelve al analizador. Bison no crea esta función automáticamente; usted debe escribirla de manera que `yyparse` pueda llamarla.

En programas simples, `yylex` se define a menudo al final del archivo de la gramática de
Bison. En programas un poco más complejos, lo habitual es crear un programa en Flex
que genere automáticamente esta función y enlazar Flex y Bison.

### Gramática Léxica

La gramática léxica, junto a los `TOKEN` que corresponden, se especifican en el archivo `scanner.l` ubicado en la carpeta `rules\`.

```c
[0-9]+                  {
                        yylval.value = atoi(yytext);
                        return CONSTANTE;
                        }

[a-zA-Z][a-zA-Z | 0-9]* {
                        strcpy(yylval.name, yytext);
                        return IDENTIFICADOR;
                        }

\+                      return SUMA;
        
\*                      return MULTIPLICACION;

\$                      return DEF;

\=                      return IGUAL;
                        
\;                      return FDS;

\(                      return PARENIZQUIERDO;

\)                      return PARENDERECHO;

\!                      return FDT;

[\n]                    ;

.                       return NAT;
```



### Lista de tokens

| En la entrada  | Nombre del Token |
| :------------- | ---------------- |
| =              | IGUAL            |
| (              | PARENIZQUIERDO   |
| )              | PARENDERECHO     |
| +              | SUMA             |
| *              | MULTIPLICACION   |
| ;              | FDS              |
| $              | DEF              |
| /n/n           | FDT              |
| val1 (ejemplo) | IDENTIFICADOR    |
| 123 (ejemplo)  | CONSTANTE        |



-----

![](/07-CalcInfManual-V2/imgs/Banner2.png)



## Parser

El **Parser** es la sección del programa encargada de realizar el análisis sintáctico de las sentencias ingresadas. Trabaja abstrayéndose de los caracteres ingresados. Para esto utiliza **TOKENS**.

A medida que necesita analizar un nuevo token, el Parser consume uno solicitándolo al Scanner mediante la función `GetNextToken()` la cual devuelve el próximo a analizar.

Un `TOKEN` está compuesto de la siguiente manera:

```c
struct TOKEN
{
    tipoDeToken type;
    union
    {
        char name[10]; //string
        int value;     //int o double
    } data;
};

typedef struct TOKEN TOKEN;
```

Su propiedad `type`, como su nombre lo dice, hace referencia al tipo de token que ha sido detectado.

Por otro lado, su estructura `data` proporciona la información necesaria para operar posteriormente con este token. Ya que un token no puede tener un `name` y un `value` al mismo tiempo, utilizamos `union` para cumplir con esta característica. Solo dispondrá de un nombre cuando estemos hablando de un `IDENTIFICADOR` y de un valor cuando se trate de una `CONSTANTE`.



### Gramática Sintáctica

```c
<Parser>     -> <Sentencias> FDT
<Sentencias> -> unaSentencia { <unaSentencia> }*
<unaSentencia> -> <Definición> FDS
                | <Expresión> FDS
<Definición> -> DEF ID IGUAL CONSTANTE
<Expresión>  -> <Término> { SUMA <Término> }*
<Término>    -> Factor { MULTIPLICACION <Factor> }*
<Factor>     -> CONSTANTE
              | IDENTIFICADOR
              | PARENIZQUIERDO <Expresión> PARENDERECHO

```

El Parser va “descendiendo” por sus funciones “No terminales”



---

![](/07-CalcInfManual-V2/imgs/Banner3.png)



## Memoria

Esta calculadora cuenta con la funcionalidad de almacenar en memoria variables con su nombre y valor correspondiente. Esto lo realiza gracias al código desarrollado en `memory.h` y `memory.c`. Donde están definidas las siguientes funciones:

- `unsigned GetPosition(char[]);` 
- `void Assign(unsigned, int);`
- `int GetValue(char[]);`

----

### `GetPosition()`

Se encarga de obtener la posición del array en la que debe guardarse el nombre de la variable. Si existe ya esa variable en el array devuelve su índice. De lo contrario guarda su nombre en donde corresponda según la variable global `memoryLastPosition` , posteriormente la incrementa y retorna su valor decrementado en uno (sin efecto de lado). 

### `Assign()`

Es la responsable de asignar a cierta posición un valor natural.

### `GetValue()`

Obtiene el valor de un nombre de memoria. Lo hace iterando el array y retorna su valor para ser operado en una evaluación. En caso de no existir el nombre buscado en memoria, muestra una leyenda “El identificador deseado no existe.” y corta la ejecución del programa con `exit(1);`.



---

![](/07-CalcInfManual-V2/imgs/Banner4.png)



## Inconvenientes encontrados

A la hora de encontrarnos con algunos problemas ya sean lógicos, conceptuales, o de cualquier otro tipo, recurrimos a la discusión de los mismos y el uso de herramientas gráficas para buscar una posible solución de una manera más fácil.

Para ello utilizamos tanto *OneNote* como *Miró*.

Pueden acceder a la pizarra de *Miró* a través del siguiente link: [Link al documento.](https://miro.com/app/board/o9J_lZ_aUhE=/)



![](/07-CalcInfManual-V2/imgs/Miro.jpg)



