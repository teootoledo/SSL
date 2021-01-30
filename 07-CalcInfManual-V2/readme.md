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

Este trabajo práctico es un programa de consola desarrollado en lenguaje C, que permite realizar tanto el análisis léxico, y sintáctico de las distintas sentencias ingresadas por el usuario. Cuenta con un lenguaje propio, definido para poder realizar estas evaluaciones, y arroja un resultado preciso de la operación.

Otra funcionalidad con la que cuenta este programa es la de almacenar variables con sus relativos nombres en una “memoria”, pudiendo acceder a los valores asociados para realizar posteriormente la evaluación de la sentencia.

Cabe destacar que las variables deben tener un máximo de 10 `char` para su nombre. Característica que podría modificarse según la conveniencia del usuario. Al igual que la cantidad máxima de variables almacenadas, que ahora mismo se encuentra fijada en 200.

La interfaz utilizada en la consola enseña al inicio del programa una guía del diccionario utilizado, junto a unos ejemplos de sentencias correctas.



<img src="/07-CalcInfManual-V2/imgs/Interfaz.png"  />

[^]: Ejemplo de la interfaz al momento de ejecutar el programa.



-------



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
- El final de texto (FDT) será dado por dos "ENTER" consecutivos ( “/n/n” ).



------

![](/07-CalcInfManual-V2/imgs/Banner1.png)



## Scanner

El **Scanner** es la sección del programa encargada de realizar el análisis léxico de las cadenas de caracteres que son ingresadas por el usuario.

Este desarrolla su análisis mediante un `while` que va pidiendo uno a uno los distintos `char` ingresados por el usuario, y va desplazándose por los estados posibles. Esto lo hace mediante un `switch` que modifica una variable `actualState` de tipo `State` que hace referencia un `enum` con los estados posibles.

Estos son:

```c
typedef enum
{
    Q0_inicial,
    Q1_identificador,
    Q2_constante,
    Q3_adicion,
    Q4_producto,
    Q5_parizquierdo,
    Q6_parderecho,
    Q7_igual,
    Q9_definicion,
    Q10_fds,
    Q11_fdt,
    Q12_error
} State;
```



A medida que el `while` itera el `switch` y se va desplazando por los estados, hasta llegar a un estado final, se retorna un `tipoDeToken` el cual podrá ser como los siguientes:

```c
typedef enum
{
    NAT,					//Not a Token
    IDENTIFICADOR,			//Variable
    CONSTANTE,				//Valor
    IGUAL,					//=
    PARENIZQUIERDO,			//(
    PARENDERECHO,			//)
    SUMA,					//+
    MULTIPLICACION,			//*
    DEF,					//$
    FDS,					//;
    FDT						//\n
} tipoDeToken;
```

Una vez retornado el tipo de token, el Parser es el encargado de analizar si es correcta la sintaxis de la sentencia. En caso de ser una definición o una evaluación, lo irá resolviendo a medida que va avanzando en su lógica.



### Gramática Léxica

```c
<token> -> uno de <identificador> <constante> <suma> <multiplicación> <igual> <def> <fds> <fdt>
<identificador> -> <letra> {<letra o dígito>}*
<constante> -> <dígito> {<dígito>}*
<letra o dígito> -> uno de <letra> <dígito>
<letra> -> una de a-Z
<dígito> -> uno de 0-9
<suma> -> +
<multiplicación> -> *
<igual> -> =
<def> -> $
<parenizquierdo> -> (
<parenderecho> -> )
<fds> -> ;
<fdt> -> \n\n
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



