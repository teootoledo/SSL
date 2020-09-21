# Calculadora Infija: Construcción Manual 🧮

---

### Gramática léxica 🔤

```c
<token> -> uno de <identificador> <constante> <operador> <lpar> <rpar>
    <identificador> -> <letra>
    <constante> -> <dígito>
    	<letra> -> una de a-z A-Z (a-z|A-Z)*
    	<dígito> -> uno de 0-9
    	<operador> -> uno de <adición> <producto>
    		<adición> -> +
    		<producto> -> *
    	<lpar> -> (
    	<rpar> -> )
```

---

### Gramática sintáctica 🔗

```c

```

---

### AFD Scanner ◾

<img src="/07-CalcInfManual-V2/imgs/afd.png" alt="Autómata finito determinístico" style="zoom:30%;" />

### AP Parser ◾

<img src="/07-CalcInfManual-V2/imgs/ap.png" alt="Autómata de pila para parser" style="zoom:30%;" />

### 