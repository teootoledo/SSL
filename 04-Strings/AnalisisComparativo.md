# Análisis Comparativo 📊
------

![cvspy](/04-Strings/img/cvspy.jpg)
=======

1. **¿El tipo es parte del lenguaje en algún nivel?**
   1. En **C**, las cadenas al nivel sintáctico son reconocidas como los caracteres que se encierran entre "". *Ejemplo: "cadena"*. A nivel semántico se maneja como un arreglo o secuencia de caracteres independientes. *Ejemplo: ['c', 'a', 'd', 'e', 'n', 'a']*
   2. En **Python**, sintácticamente y semánticamente son muy similares respecto a cómo se maneja **C**. La gran diferencia viene en que el tipo de dato pertenece al lenguaje, por lo tanto, no se operan como si fueran arreglos. Por lo tanto, la manipulación puede considerarse, "más simple".
2. **¿El tipo es parte de la biblioteca?**
   1. En **C**, el tipo de dato *"string"* no pertenece al lenguaje. Cuando se necesita manipular *strings*, se utilizan "arrays" de tipo *char*, con una longitud determinada. También se puede realizar el uso de "vector" para que sea posible la modificación del tamaño dinámicamente. Puede incluirse a *<string.h>* para utilizar funciones de cadenas.
   2. En **Python**, los *"strings"*, son un tipo de dato particular, que ya viene definido con sus propias operaciones dentro del mismo LP. Aún así, el comportamiento interno es casi el mismo, ya que funciona con un array de tipo char.
3. **¿Qué alfabeto usa?**
   1. **C** utiliza las letras de la 'a' a la 'z' y de la 'A' a la 'Z', los números del '0' al '9', el espacio en blanco ' ', símbolos diversos '!', '@', '%', etcétera.
   2. En **Python** se incluye también a los caracteres Unicode.
4. **¿Cómo se resuelve la alocación de memoria?**
   1. En **C**, cuando se declara una variable se reserva la memoria automáticamente para el tipo de dato, incluso si ésta tiene vacío su contenido. En el caso de manejar una cadena, se almacena en la variable el puntero a primer elemento del arreglo de caracteres.
   2. En **Python**, la declaración de la variable no reserva memoria, sino el objeto al que apunta es el cual le da el tamaño. Entonces, las variables no guardan más que la dirección de memoria del objeto. No existe el tipo *puntero* en python. Por lo tanto, al declarar un string, lo que se almacena es su dirección de memoria al comienzo del arreglo, pero esta nunca se puede saber u obtener.
5. **¿El tipo tiene mutabilidad o es inmutable?**
   1. En **C** los *strings* al ser un array de caracteres permiten la mutabilidad de sus componentes.
   2. En **Python** al ser un tipo de dato perteneciente al lenguaje, adquieren la propiedad de inmutabilidad. Esto significa que una vez han sido creadas no pueden modificarse como si fueran un arreglo. En efecto, si intentamos modificar una cadena el intérprete nos indica que a ésta no se pueden asignar elementos.
6. **¿El tipo es un *first class citizen*?**
   1. En **C**, las cadenas no son consideradas *FCC*.
   2. En **Python**, los *strings* si lo son.
7. **¿Cuál es la mecánica para ese tipo cuando se los pasa como argumentos?**
   1. En **C**, se pasa como puntero a un array de *chars*.
   2. En **Python**, se pasa directamente la variable.
8. **¿Y cuando son retornados por una función?**
   1. En **C**, se retorna un puntero a un char.
   2. En **Python**, se retorna una variable de tipo *string*.

------

