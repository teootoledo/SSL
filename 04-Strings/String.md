# Especificaciones matemáticas 📝🔢

------



### GetLength

GetLength: Σ* → |N
$$
GetLength: Σ* → N / GetLength(str)=\left\{\begin{matrix}
0, &si\ str = \epsilon \\
1+GetLength(s),& si\ str= s*w \wedge  w\in \sum ^{1}
\end{matrix}\right.
$$


### IsEmpty

IsEmpty: Σ* → |B
$$
IsEmpty: Σ* → B / IsEmpty(str)=\left\{\begin{matrix}
F, &si\ str \neq  \epsilon \\
V,& si\ str= \epsilon
\end{matrix}\right.
$$


### Power

Power: Σ* x |N → Σ*
$$
Power: Σ* \cdot N → Σ*/Power(str,e)=\left\{\begin{matrix}
\epsilon, &si\ e = 0 \vee str=\epsilon \\
str\cdot Power(str,(e-1)),& si\ e>0
\end{matrix}\right.
$$


### Contains

Contains: Σ* x Σ → |B
$$
\left ( \sum * \cdot \sum  \cdot \ \mathbb{N}\right )Contains \left\{\begin{matrix}
1, &si\ c  \subseteq str \\
0, & eoc
\end{matrix}\right.
$$
