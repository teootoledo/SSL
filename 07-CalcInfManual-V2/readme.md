# Calculadora 2

### Descripción del lenguaje utilizado

- El único tipo de dato es natural incluyendo el 0.
- Todos los identificadores son declarados explicitamente y con una longitud máxima de 8 caracteres.
- Los identificadores deben comenzar con una letra y están compuestos de letras y dígitos.
- Las constantes son secuencias de dígitos.
- Hay dos tipos de sentencias:
    - **Asignación** Identificador := Constante
    - **Consulta** Expresion =
- Cada sentencia termina con un "enter" (/n).
- El final de texto (fdt) será dado por dos "enter" consecuitivos (/n/n) 


### Gramática Léxica

~~~
<token> -> uno de <identificador> <constante> <operadorAditivo> <operadorMultiplicador> <asignación> <igual> <carácterPuntuación>
<identificador> -> <letra> {<letra o dígito>}
<constante> -> <dígito> {<dígito>}
<letra o dígito> -> uno de <letra> <dígito>
<letra> -> una de a-z A-Z
<dígito> -> uno de 0-9
<palabraReservada> -> una de leer escribir
<operadorAditivo> -> + 
<operadorMultiplicador> -> *
<asignación> -> :=
<igual> -> =
<carácterPuntuación> -> uno de ( ) 
~~~

### Gramática Sintáctica

~~~
<parser> -> <sentencias> 
<sentencias> -> <asignación> FDS | <expresion> FDS | <sentencias>
<asignacion> -> ID ASIGNACION CONSTANTE
<expresión> -> $ <primaria> { +|*  <primaria>}
<primaria> -> IDENTIFICADOR | CONSTANTE | ( <expresion> )


<expresión> -> <primaria> {<operadorAditivo> <primaria>}
<primaria> -> <identificador> | <constante> |
 ( <expresión> )



| En la entrada | Nombre del Token |
|---------------|------------------|
| := | ASIGNACION |
| = | IGUAL |
| ( | PARENIZQUIERDO |
| ) | PARENDERECHO |
| + | SUMA |
| * | MULTIPLICACION |
| . | FDS |
| $ | EXP|
| /n/n | FDT |

