# Máquinas de Estado -  Palabras en Líneas

------

### 1.b - Árbol de expresión - Inicialización de variables.

<img src="C:\Users\teoot\Documents\GitHub\SSL\05-ContadorDePalabras\img\arbolInicializacion.png" alt="arbolInicializacion" style="zoom:50%;" />

> c == " || c == '\n' || c == '\t'

### 1.c Árbol de expresión - Condición del if.

<img src="C:\Users\teoot\Documents\GitHub\SSL\05-ContadorDePalabras\img\arbolCondicionIf.png" alt="arbolCondicionIf" style="zoom: 50%;" />

> nl = nw = nc = 0

------

### 2. Máquina de estado - Palabras en línea.

<img src="C:\Users\teoot\Documents\GitHub\SSL\05-ContadorDePalabras\img\wl.png" alt="wc" style="zoom:50%;" />

- **Q**  = {IN, OUT}

* **∑**  = ASCII
* **q0** = OUT
* **F**  = {IN, OUT} = **Q**
* **T**  =  { 
  * (OUT, '\n' || '\t' || ' ', OUT), 
  * (OUT,  otro, IN, putchar(‘c’) ),
  * (IN, '\n' || '\t' || ' ', OUT, putchar(‘\n’)),
  * (IN, '\n', otro, IN, putchar(‘c’))
* }

------

### 3.a.ii Indicar ventajas y desventajas entre K&R y enum-switch.

|               | Ventajas                                                     | Desventajas                                                  |
| ------------- | :----------------------------------------------------------- | ------------------------------------------------------------ |
| K&R           | Menor cantidad de código, utilizando variables de un mismo tipo. El define es más simple de implementar al menos en la forma de entender su uso y la lectura del programa. | El gráfico de la máquina de estado para este algoritmo dista bastante del código del programa. El uso de las variables de un solo tipo simplifica el código pero complica su lectura. Es más difícil entender lo que realiza el programa. |
| `enum-switch` | La semántica es más clara separando por casos y asimilándose aún más a la máquina de estados. Esto permite relacionar más fácilmente ambos productos. | La sentencia que establece el estado como OUT se repite en todos los casos. Implementa el uso de una variable tipo `char` además de las `int`. |

### 3.b.iv ¿Tiene alguna aplicación `go to` hoy en día? ¿Algún lenguaje moderno lo utiliza?

Por lo investigado, no muchos lenguajes modernos implementan esta función de control de flujo. La aplicación va a depender siempre del contexto y de lo que estemos haciendo.

------

### 3.c.ii ¿Es necesario que las funciones accedan a contadores?

No es necesario que las funciones accedan a contadores.

