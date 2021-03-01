![](/07-CalcInfManual/imgs/Banner.png)

---

**¿De qué trata este trabajo?** [Link al documento.](https://josemariasola.github.io/ssl/assignments/2020/Ssl%20Assignments.pdf#page=53)

---

# Tabla de Contenidos

<!--ts-->

- [Tabla de contenidos](#tabla-de-contenidos)
- [Síntesis](#síntesis)
- [Calculadora](#calculadora) - [Descripción del lenguaje utilizado](#descripción-del-lenguaje-utilizado) - [Scanner](#scanner) - [Gramática Léxica](#gramática-léxica) - [Lista de tokens](#lista-de-tokens) - [Parser](#parser) - [Gramática Sintáctica](#gramática-sintáctica) - [Memoria](#memoria) - [GetPosition()](#getposition) - [Assign()](#assign) - [GetValue()](#getvalue) - [Makefile](#makefile) - [Compilación](#compilación) - [Test](#test) - [Clean](#clean) - [Códigos de errores](#errores) - [Inconvenientes encontrados](#inconvenientes-encontrados) - [Miro](#miro)
<!--te-->

# Síntesis

Este trabajo práctico es un programa de consola desarrollado en lenguaje C, que permite realizar tanto el análisis léxico, y sintáctico de las distintas sentencias ingresadas por el usuario. Cuenta con un lenguaje propio, definido para poder realizar estas evaluaciones, y arroja un resultado preciso de la operación.

Otra funcionalidad con la que cuenta este programa es la de almacenar variables con sus relativos nombres en una “memoria”, pudiendo acceder a los valores asociados para realizar posteriormente la evaluación de la sentencia.

Cabe destacar que las variables deben tener un máximo de 20 `char` para su nombre. Característica que podría modificarse según la conveniencia del usuario. Al igual que la cantidad máxima de variables almacenadas, que ahora mismo se encuentra fijada en 200.

---

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

---

![](/07-CalcInfManual/imgs/Banner1.png)

## Scanner

El **Scanner** es la sección del programa encargada de realizar el análisis léxico de las cadenas de caracteres que son ingresadas por el usuario.

Su implementación consta de dos funciones principales, una **pública** y otra **privada**. La función de carácter público es la llamada `GetNextToken()`. Esta es la que el **Parser** llama cada vez que necesita el siguiente `TOKEN` para continuar con la derivación. Su declaración se encuentra en `inc\scanner.h` y su definición en `src\scanner.c`. Por otro lado, la función privada es la definida como `Scanner()` la cual es invocada por la anterior ( `GetNextToken()`) y es la encargada del análisis de la entrada mediante un `while` que va pidiendo uno a uno los distintos `char` ingresados por el usuario, y va desplazándose por los estados posibles. Esto lo hace mediante un `switch` que modifica una variable `actualState` de tipo `State` que hace referencia un `enum` con los estados posibles. En distintos estados empleamos la utilización de la función privada `ActionState_Qx` ya que ahorra código y aumenta la legibilidad a la hora de resetear el estado actual, devolver el último `char` analizado al flujo de entrada, y retornar el `TOKEN` identificado. Esto lo hace con `CreateToken()`.

La función `GetNextToken()` cuenta con un "flag" al cual decidimos llamar `keepLastToken`. Esto lo explicamos en la sección del [Parser](#parser).

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
    Q8_definicion,
    Q9_fds,
    Q10_fdt,
    Q11_lexError
} State;
```

A medida que el `while` itera el `switch` y se va desplazando por los estados, hasta llegar a un estado final, se retorna un `TOKEN` con su correspondiente `tipoDeToken` el cual podrá ser como los siguientes:

```c
typedef enum
{
    NAT,
    IDENTIFICADOR,
    CONSTANTE,
    IGUAL,
    PARENIZQUIERDO,
    PARENDERECHO,
    SUMA,
    MULTIPLICACION,
    DEF,
    FDS,
    FDT
} tipoDeToken;
```

Una vez retornado el `TOKEN`, el Parser es el encargado de analizar si es correcta la sintaxis de la sentencia. En caso de ser una definición o una evaluación, lo irá resolviendo a medida que va avanzando en su lógica.

### Gramática Léxica

```c
<token> -> uno de <identificador> <constante> <suma> <multiplicación> <igual> <definición> <fds> <fdt>
<identificador> -> <letra> {<letra o dígito>}*
<constante> -> <dígito> {<dígito>}*
<letra o dígito> -> uno de <letra> <dígito>
<letra> -> una de a-Z
<dígito> -> uno de 0-9
<suma> -> +
<multiplicación> -> *
<igual> -> =
<definición> -> $
<parenizquierdo> -> (
<parenderecho> -> )
<fds> -> ;
<fdt> -> !
```

### Lista de tokens

| En la entrada  | Nombre del Token |
| :------------- | ---------------- |
| =              | IGUAL            |
| (              | PARENIZQUIERDO   |
| )              | PARENDERECHO     |
| +              | SUMA             |
| \*             | MULTIPLICACION   |
| ;              | FDS              |
| $              | DEF              |
| !              | FDT              |
| val1 (ejemplo) | IDENTIFICADOR    |
| 123 (ejemplo)  | CONSTANTE        |

---

![](/07-CalcInfManual/imgs/Banner2.png)

## Parser

El **Parser** es la sección del programa encargada de realizar el análisis sintáctico de las sentencias ingresadas. Trabaja abstrayéndose de los caracteres ingresados. Para esto utiliza **TOKENS**.

A medida que necesita analizar un nuevo token, el Parser consume uno solicitándolo al Scanner mediante la función `GetNextToken()` la cual devuelve el próximo a analizar.

Un `TOKEN` está compuesto de la siguiente manera:

```c
typedef struct TOKEN
{
    tipoDeToken type;
    union
    {
        char name[10]; //string
        int value;     //int o double
    } data;
} TOKEN;
```

Su propiedad `type`, como su nombre lo dice, hace referencia al tipo de token que ha sido detectado.

Por otro lado, su estructura `data` proporciona la información necesaria para operar posteriormente con este token. Ya que un token no puede tener un `name` y un `value` al mismo tiempo, utilizamos `union` para cumplir con esta característica. Solo dispondrá de un nombre cuando estemos hablando de un `IDENTIFICADOR` y de un valor cuando se trate de una `CONSTANTE`.

### Gramática Sintáctica

```c
<Parser>     -> <listaSentencias> FDT
<listaSentencias> -> Sentencia FDS { <Sentencia> FDS }*
<Sentencia> -> DEF <Definición>
               IGUAL <Expresión>
<Definición> -> ID IGUAL CONSTANTE
<Expresión>  -> <Término> { SUMA <Término> }*
<Término>    -> Factor { MULTIPLICACION <Factor> }*
<Factor>     -> CONSTANTE
              | IDENTIFICADOR
              | PARENIZQUIERDO <Expresión> PARENDERECHO

```

El Parser va analizando la sintaxis con una **derivación vertical a izquierda**.

Este se va desplazando a través de las distintas subrutinas semánticas. `Definicion()` es la que se encarga de asociar el valor de una constante al nombre de una variable. `Expresion()` devuelve el resultado de la sentencia ingresada por el usuario.

`Match()` es la encargada de confirmar que la sintaxis se va desarrollando de forma correcta. Tiene la capacidad de "consumir" realmente un token, cambiando el estado del flag global `keepLastToken`, el cual modifica la lógica de `GetNextToken()`, permitiéndole acceder o no, a la función `Scanner()` para actualizar el token actual.

---

![](/07-CalcInfManual/imgs/Banner3.png)

## Memoria

Esta calculadora cuenta con la funcionalidad de almacenar en memoria variables con su nombre y valor correspondiente. Esto lo realiza gracias al código desarrollado en `memory.h` y `memory.c`. Donde están definidas las siguientes funciones:

- `unsigned GetPosition(char[]);`
- `void Assign(unsigned, int);`
- `int GetValue(char[]);`

---

### `GetPosition()`

Se encarga de obtener la posición del array en la que debe guardarse el nombre de la variable. Si existe ya esa variable en el array devuelve su índice. De lo contrario guarda su nombre en donde corresponda según la variable global `memoryLastPosition` , posteriormente la incrementa y retorna su valor decrementado en uno (sin efecto de lado).

### `Assign()`

Es la responsable de asignar a cierta posición un valor natural.

### `GetValue()`

Obtiene el valor de un nombre de memoria. Lo hace iterando el array y retorna su valor para ser operado en una evaluación. En caso de no existir el nombre buscado en memoria, muestra una leyenda “El identificador deseado no existe.” y corta la ejecución del programa con `exit(5);`.

---

![](/07-CalcInfManual/imgs/Banner5.png)

## Makefile

A la hora de querer ejecutar nuestro programa en nuestro PC, debemos abrir la terminal del sistema en la carpeta con el siguiente path:

```
07-CalcInfManual/src/
```

Aquí dentro se encuentra junto a los archivos con extensión `.c`, otro llamado `makefile` el cuál a través de unas rutinas ya definidas en él, nos permitirá tanto compilar, testear y limpiar el repositorio del proyecto.

### Compilación

Para proceder a la compilación de los archivos necesarios, debemos ejecutar el comando `make` desde la línea de comandos, lo que iniciará la rutina por default llamada `TARGET`, que se encarga de compilar el programa, dejando como producto el ejecutable del mismo en la siguiente ubicación:

```
07-CalcInfManual/bin/
```

Como _ventaja_ de realizar la compilación a través de este método, obtenemos un mejor tiempo de compilación a la hora de estar realizando cambios en algunos de los archivos del proyecto. Gracias a la comparación que realiza `make` de los archivos `.o`, es posible compilar únicamente los archivos que fueron modificados y no recompilar el proyecto desde 0.

### Test

La rutina que se ejecuta con el comando `make test`, nos permite con un input preestablecido en el archivo `entrada.txt` ubicado en la carpeta `/test`, obtener una salida que será escrita en `obtenido.txt` la cual posteriormente será comparada automáticamente utilizando el comando `comp`. Este nos advierte si encuentra una diferencia entre `obtenido.txt` y `esperado.txt`. Dándonos la posibilidad de identificar en caso de que falle, dónde lo está haciendo.

### Clean

Utilizaremos el comando `make clean` para limpiar de nuestro repositorio los archivos `.o`, `.d` y `.exe`.

### Run

Por último, utilizaremos el comando `make run` para ejecutar directamente el archivo `Calculadora.exe` y realizar la entrada manual sentencias..

### Errores

| Código de error | Descripción                                                  |
| --------------- | ------------------------------------------------------------ |
| 1               | Error léxico. Sucede en la etapa de análisis realizada por el *Scanner*. |
| 2               | Error sintáctico. Sucede en la subrutina semántica de `Sentencia`. |
| 3               | Error sintáctico. Sucede en la subrutina semántica de `Factor`. |
| 4               | Error sintáctico. Sucede en la función `Match`.              |
| 5               | Error de memoria. El identificador solicitado no existe en memoria. |



---

![](/07-CalcInfManual/imgs/Banner4.png)

## Inconvenientes encontrados

A la hora de encontrarnos con algunos problemas ya sean lógicos, conceptuales, o de cualquier otro tipo, recurrimos a la discusión de los mismos y el uso de herramientas gráficas para buscar una posible solución de una manera más fácil.

Para ello utilizamos tanto _OneNote_ como _Miró_.

Pueden acceder a la pizarra de _Miró_ a través del siguiente link: [Link al documento.](https://miro.com/app/board/o9J_lZ_aUhE=/)

![](/07-CalcInfManual/imgs/Miro.jpg)
