# Calculadora Infija: Construcción Manual

---

### Gramática léxica

```c
<token> -> uno de <identificador> <constante> <operador>
    <identificador> -> <letra>
    <constante> -> <dígito>
    	<letra> -> una de a-z A-Z (a-z|A-Z)*
    	<dígito> -> uno de 0-9
    	<operador> -> uno de <operadorSuma> <operadorMultiplicación>
    		<Suma> +
    		<Multiplicación> *
```

---

### Gramática sintáctica

```c
<expresión> -> <operando> <operador> <operando> (<operador> <operando>)*
    <operando> -> <dígito> <letra>
    <operador> -> <+> <*>
```

---

### AFD

<img src="/06-CalcInfManual/imgs/afd.png" alt="Autómata finito determinístico" style="zoom:30%;" />

---

