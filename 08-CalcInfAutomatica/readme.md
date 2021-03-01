![](/08-CalcInfAutomatica/imgs/Banner.png)

---

**¿De qué trata este trabajo?** [Link al documento.](https://josemariasola.github.io/ssl/assignments/2020/Ssl%20Assignments.pdf#page=53)

---

# Tabla de Contenidos

- <!--ts-->

  - [Tabla de contenidos](#tabla-de-contenidos)
  - [Síntesis](#síntesis)
  - [Calculadora](#calculadora) - [Descripción del lenguaje utilizado](#descripción-del-lenguaje-utilizado) - [Scanner](#scanner) - [La función del analizador léxico](#la-funcion-del-analizador-lexico) - [Gramática Léxica](#gramática-léxica) - [Lista de tokens](#lista-de-tokens) - [Parser](#parser) - [Bison](#bison) - [La función del analizador sintáctico](#la-funcion-del-analizador-sintactico) - [Gramática Sintáctica](#gramática-sintáctica) - [Memoria](#memoria) - [GetPosition()](#getposition) - [Assign()](#assign) - [GetValue()](#getvalue) - [Makefile](#makefile) - [Compilación](#compilación) - [Test](#test) - [Clean](#clean) - [Códigos de errores](#errores) - [Inconvenientes encontrados](#inconvenientes-encontrados) - [Miro](#miro)
    <!--te-->

# Síntesis

Este trabajo práctico es un programa de consola desarrollado en lenguaje C, con herramientas como **Flex** y **Bison**, que permite realizar tanto el análisis léxico, y sintáctico de las distintas sentencias ingresadas por el usuario. Cuenta con un lenguaje propio, definido para poder realizar estas evaluaciones, y arroja un resultado preciso de la operación.

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

![](/08-CalcInfAutomatica/imgs/Banner1.png)

## Scanner

El **Scanner** es la sección del programa encargada de realizar el análisis léxico de las cadenas de caracteres que son ingresadas por el usuario.

### La función del Analizador Léxico `yylex()`

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

[\s\t\n]                    ;

.                       return NAT;
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

![](/08-CalcInfAutomatica/imgs/Banner2.png)

## Parser

El **Parser** es la sección del programa encargada de realizar el análisis sintáctico de las sentencias ingresadas. Trabaja abstrayéndose de los caracteres ingresados. Para esto utiliza **TOKENS**.

### Bison

El fuente de **Bison** se convierte en una función en C llamada `yyparse`. Aquí describimos las convenciones de interfaz de `yyparse` y las otras funciones que éste necesita usar.

Tenga en cuenta que el analizador utiliza muchos identificadores en C comenzando con
‘yy’ e ‘YY’ para propósito interno.

Si utiliza tales identificadores (a parte de aquellos descritos en el manual) en una acción o en código C adicional en el archivo de la gramática, es probable que se encuentre con problemas.  

### La Función del Analizador `yyparse()`
Se llama a la función yyparse para hacer que el análisis comience. Esta función lee tokens, ejecuta acciones, y por último retorna cuando se encuentre con el final del fichero o un error de sintaxis del que no puede recuperarse. Usted puede también escribir acciones que ordenen a yyparse retornar inmediatamente sin leer más allá. 

El valor devuelto por yyparse es 0 si el análisis tuvo éxito (el retorno se debe al final del fichero). El valor es 1 si el análisis falló (el retorno es debido a un error de sintaxis). 

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



---

![](/08-CalcInfAutomatica/imgs/Banner3.png)

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

![](/08-CalcInfAutomatica/imgs/Banner5.png)

## Makefile

A la hora de querer ejecutar nuestro programa en nuestro PC, debemos abrir la terminal del sistema en la carpeta con el siguiente path:

```
08-CalcInfAutomatica/src/
```

Aquí dentro se encuentra junto a los archivos con extensión `.c`, otro llamado `makefile` el cuál a través de unas rutinas ya definidas en él, nos permitirá tanto compilar, testear y limpiar el repositorio del proyecto.

### Compilación

Para proceder a la compilación de los archivos necesarios, debemos ejecutar el comando `make` desde la línea de comandos, lo que iniciará la rutina por default llamada `TARGET`, que se encarga de compilar el programa, dejando como producto el ejecutable del mismo en la siguiente ubicación:

```
08-CalcInfAutomatica/bin/
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

![](/08-CalcInfAutomatica/imgs/Banner4.png)

## Inconvenientes encontrados

A la hora de encontrarnos con algunos problemas ya sean lógicos, conceptuales, o de cualquier otro tipo, recurrimos a la discusión de los mismos y el uso de herramientas gráficas para buscar una posible solución de una manera más fácil.

Para ello utilizamos tanto _OneNote_ como _Miró_.

Pueden acceder a la pizarra de _Miró_ a través del siguiente link: [Link al documento.](https://miro.com/app/board/o9J_lZ_aUhE=/)

![](/08-CalcInfAutomatica/imgs/Miro.jpg)
