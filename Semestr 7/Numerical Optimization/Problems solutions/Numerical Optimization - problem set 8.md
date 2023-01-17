# Numerical Optimization - problem set 8
###### tags: `no2021/2022` `ćwiczenia`
## Task 1
![](https://i.imgur.com/Zpi9f49.png)
![](https://i.imgur.com/7Lz3WRa.png)
<!-- ![](https://i.imgur.com/qP8TtWF.png) -->
![](https://i.imgur.com/3XUnct2.png)

![](https://i.imgur.com/MuCyxfq.png)


$$1 − x_1 ≤ 0, −x_2 ≤ 0, x_2 − (x_1 − 1)^2 ≤ 0$$
All equalities holds for $y=(1,0)$.
Equalities:

$$\nabla g_0 = [-1, 0]^T$$

$$\nabla g_1 = [0, -1]^T$$

$$\nabla g_2 = [-2(x_1 - 1), 1]^T$$

Now let's check those values in $y=(1,0)$:
$$\nabla g_0(y) = [-1,0]^T, \nabla g_1(y) = [0,-1]^T, \nabla g_2(y) = [0, 1]^T$$

Gradients of $g_i$ are linearlly dependent, so assumpitons of lemma giving KKT are violated.

Let's take any $v = [v_1, v_2]^T$

$$\langle \nabla g_0(y), v\rangle = -v_1 \leq 0$$

$$\langle \nabla g_1(y), v\rangle = -v_2 \leq 0$$

$$\langle \nabla g_2(y), v\rangle = v_2 \leq 0$$

so $v = [v_1, 0]$ for $v_1\geq 0$. For such $v$ obviously $v \in TS_y$ as $y+tv \in S$ for $t \geq 0$, therefore $d(y+tv, S) = 0$.

Let $f(x) = x_1 + 2x_2$. We know, that $x_1 \geq 1$ and $x_2 \geq 0$ and as $y=(1, 0)\in S$ then $y$ minimizes $f$.

$$\nabla f = [1, 2]^T$$

$$\nabla g_0 = [-1, 0]^T$$

$$\nabla g_1 = [0, -1]^T$$

$$\nabla g_2 = [-2(x_1 - 1), 1]^T$$

So we get equations:

$$1 - \mu_0 - \mu_2 2(x_1 - 1) = 0$$

$$2 - \mu_1 + \mu_2 = 0$$

$$1-x_1 = 0 \Leftrightarrow x_1 = 1$$

$$ -x_2 = 0 \Leftrightarrow x_2 = 0$$

$$ x_2 − (x_1 − 1)^2 = 0 \Leftrightarrow x_2 = (x_1−1)^2$$

From last 3 equations we have $x_1 = 1, \; x_2 = 0$ which align with $y=(1,0)$. Also $\mu_i$ can be set to be $\geq 0$.



## Task 3
![](https://i.imgur.com/NumdvjP.png)


## Task 4
![](https://i.imgur.com/g44QYNQ.png)

$$f(x) = \frac{1}{2} (x_1^2 + x_2^2),\; -x_1\leq 0, \; h(x) = -\log(x_1)$$

$$\nabla (f + \lambda h) = [x_1 - \frac{\lambda}{x_1}, x_2]^T$$

Eigenvalues: $1+\frac{\lambda}{x_1^2}$ and $1$.

$$\frac{\lVert J \rVert}{\lVert f(x) \rVert / \lVert x \rVert} = \frac{\sqrt{1+\frac{\lambda}{x_1^2}} \sqrt{x_1^2 + x_2^2}}{\frac{1}{2}(x_1^2 + x_2^2) - \lambda \log(x_1)} = \frac{\sqrt{(x_1^2 + x_2^2)+\lambda\frac{x_1^2 + x_2^2}{x_1^2}}}{\frac{1}{2}(x_1^2 + x_2^2) - \lambda \log(x_1)}$$

<!-- As $x_1$ and $x_2$ get close to optimal point (which is )
When $x_2 = 0$
$$\frac{\sqrt{1+\frac{\lambda}{x_1^2}} \sqrt{x_1^2}}{\frac{1}{2}x_1^2 - \lambda \log(x_1)} = \frac{\sqrt{x_1^2 + \lambda}}{\frac{1}{2}x_1^2 - \lambda \log(x_1)} \rightarrow_{x_1\rightarrow 0^+} = \frac{\sqrt{\lambda}}{0 - \lambda \cdot (-\infty)} = 0$$ -->=


$$\nabla (f + \lambda h) = [x_1 - \frac{\lambda}{x_1}, x_2] = 0$$

$$x_1 = \sqrt{\lambda}, \;\; x_2 = 0$$

Limit for $x_1 \rightarrow \sqrt{\lambda}$, $x_2 \rightarrow 0$:
$$\frac{\sqrt{(x_1^2 + x_2^2)+\lambda\frac{x_1^2 + x_2^2}{x_1^2}}}{\frac{1}{2}(x_1^2 + x_2^2) - \lambda \log(x_1)} \rightarrow 
\frac{\sqrt{\lambda+\lambda}}{\frac{1}{2}\lambda - \lambda \log(\lambda)} = \frac{\sqrt{2}}{\frac{1}{2}\sqrt{\lambda} -  \lambda\log(\sqrt{\lambda})}$$


Self-concordant:

$$x_1 = a + tv, \; x_2 = b + tw$$

$$f + \lambda h = \frac{1}{2}((a+tv)^2 + (b+tw)^2) - \lambda \log(a+tv)$$

$$|(\frac{1}{2}((a+tv)^2 + (b+tw)^2) - \lambda \log(a+tv))'''| = | \frac{2\lambda v^3}{(a+tv)^3} |
= \\ = 
2(\frac{\lambda v^2}{(a+tv)^2})^{3/2} \leq
2(v^2 + w^2 + \frac{\lambda v^2}{(a+tv)^2})^{3/2} 
= \\ =
2(\frac{1}{2}((a+tv)^2 + (b+tw)^2) - \lambda \log(a+tv))''^{3/2}$$

Now with another function:
$$f(x) =  x_1 + \frac{1}{2}x_2^2$$

$$\nabla (f+\lambda h) = [1 - \frac{\lambda}{x_1}, x_2]^T$$

Eigenvalues: $\frac{\lambda}{x_1^2}$ and $1$.

$$\frac{\lVert J \rVert}{\lVert f(x) \rVert / \lVert x \rVert} = \frac{\sqrt{\frac{\lambda}{x_1^2}} \sqrt{x_1^2 + x_2^2}}{\frac{1}{2}(x_1^2 + x_2^2) - \lambda \log(x_1)} = \frac{\sqrt{\lambda\frac{x_1^2 + x_2^2}{x_1^2}}}{\frac{1}{2}(x_1^2 + x_2^2) - \lambda \log(x_1)}$$

$$\nabla (f+\lambda h) = [1 - \frac{\lambda}{x_1}, x_2]^T = 0$$

$$x_1 = \lambda, \; x_2 = 0$$

$$\frac{\sqrt{\lambda\frac{x_1^2 + x_2^2}{x_1^2}}}{\frac{1}{2}(x_1^2 + x_2^2) - \lambda \log(x_1)} = \frac{\sqrt{\lambda}}{\frac{1}{2}\lambda^2 - \lambda \log(\lambda)}$$

Self-concordant:

$$x_1 = a + tv, \; x_2 = b + tw$$

$$f + \lambda h = (a+tv) + \frac{1}{2}(b+tw)^2 - \lambda \log(a+tv)$$

$$|((a+tv) + \frac{1}{2}(b+tw)^2- \lambda \log(a+tv))'''| = | \frac{2\lambda v^3}{(a+tv)^3} |
= \\ = 
2(\frac{\lambda v^2}{(a+tv)^2})^{3/2} \leq
2(w^2 + \frac{\lambda v^2}{(a+tv)^2})^{3/2} 
= \\ =
2((a+tv) + \frac{1}{2}(b+tw)^2 - \lambda \log(a+tv))''^{3/2}$$



<!-- ## Pytania: 
Task 1: Lemma 1.2: Czy ten lemat jest dla dowolnego x czy tylko optymalnego?
Task 1: Czy powinna wyjść półprosta $v = [v_1, 0]$ for $v_1\geq 0$?
Task 1: Lemma 1.2, 1.4: Czy full rank oznacza wszystkie gradienty niezależne czy rząd macierzy $= \min{(n_{col}, n_{rows})}$?
Task 1: Czy mamy w tym zadaniu 3 aktywne constrainy? Bo wtedy oczywiście gradienty $g_i$ są zależne (3 constrainy vs 2 zmienne).
Task 1: Wyszło, że assumptions of lemma giving KKT conditions are violated (jeśli rząd to niezależność gradientów), ale KKT conditions hold, jeśli uznajemy wszystkie 3 constrainy za aktywne (jeśli $g_0$ albo $g_1$ uznajemy za nieaktywny, to not holds). W ogólności jak jest z tymi aktywnymi constrainami, bo w teorii możemy dodawać dowolne constrainy, które nie wpływają na nasz feasible set, a równość (zamiast nierówności) zachodzi w rozważanym punkcie i rośnie nam liczba stopni swobody układu równań KKT, więc w pewnym momencie zawsze warunki KKT hold.
Task 4: Czy mówimy o optimal point $f$ czy $f + \lambda h$?
Task 4: Co to znaczy well conditioned i jak to sprawdzać? -->

<!-- ## Task 4 v2
![](https://i.imgur.com/g44QYNQ.png)

$$f(x) = \frac{1}{2} (x_1^2 + x_2^2),\; -x_1\leq 0, \; h(x) = -\log(x_1)$$

$$\nabla (f + \lambda h) = [x_1 - \frac{\lambda}{x_1}, x_2, -\log(x_1)]^T$$

$$H = \begin{pmatrix}
1 + \frac{\lambda}{x_1^2} & 0 & -\frac{1}{x_1}\\
0 & 1 & 0\\
-\frac{1}{x_1} & 0 & 0
\end{pmatrix}$$

$$det(H - \gamma I) = det\begin{pmatrix}
1 + \frac{\lambda}{x_1^2} - \gamma & 0 & -\frac{1}{x_1}\\
0 & 1 - \gamma & 0\\
-\frac{1}{x_1} & 0 & -\gamma
\end{pmatrix} 
=\\= 
(1 + \frac{\lambda}{x_1^2} - \gamma)(1 - \gamma)(-\gamma) - (-\frac{1}{x_1})(1 - \gamma)(-\frac{1}{x_1}) 
=\\=
(1-\gamma)(\gamma^2 - \frac{\lambda \gamma}{x_1^2} - \gamma - \frac{1}{x_1^2})$$


$$\gamma \in (1, \frac{x^2 + λ - \sqrt{x^4 + 4 x^2 + 2 x^2 λ + λ^2}}{2 x^2}, \frac{x^2 + λ + \sqrt{x^4 + 4 x^2 + 2 x^2 λ + λ^2}}{2 x^2})$$

$$\sqrt{x^4 + 4 x^2 + 2 x^2 λ + λ^2} = \sqrt{(x^2 + \lambda)^2 + 4 x^2} \geq x^2 + \lambda$$
![](https://i.imgur.com/0tglSOl.png)

$$\frac{\lVert J \rVert}{\lVert f+\lambda h \rVert / \lVert x \rVert} = \frac{\sqrt{\frac{x_1^2 + λ + \sqrt{x_1^4 + 4 x_1^2 + 2 x_1^2 λ + λ^2}}{2 x_1^2}} \sqrt{x_1^2 + x_2^2 + \lambda^2} }{\frac{1}{2}(x_1^2 + x_2^2) - \lambda \log(x_1)} $$

For fixed $\lambda$ the $x$ minimizing $f+\lambda h$ is $(\sqrt{\lambda}, 0)$. Limit for $x_1 \rightarrow \sqrt{\lambda}$, $x_2  \rightarrow 0$


Now with another function:
$$f(x) =  x_1 + \frac{1}{2}x_2^2$$

$$\nabla (f+\lambda h) = [1 - \frac{\lambda}{x_1}, x_2, -\log(x_1)]^T $$

![](https://i.imgur.com/Z1MSd6z.png)
 -->

## Task 4 v3
![](https://i.imgur.com/g44QYNQ.png)

$$f(x) = \frac{1}{2} (x_1^2 + x_2^2),\; -x_1\leq 0, \; h(x) = -\log(x_1)$$

$$\nabla (f + \lambda h) = [x_1 - \frac{\lambda}{x_1}, x_2]^T$$


$$H = \begin{pmatrix}
1 + \frac{\lambda}{x_1^2} & 0\\
0 & 1 
\end{pmatrix}$$

Maximal eigenvalue: $1+\frac{\lambda}{x_1^2}$.
Minimal eigenvalue: $1$.

Optimum of $f+\lambda h$ is where $\nabla (f+\lambda h) = 0$ as $f+\lambda h$ is convex (as sum of convex functions). We get that optimum is in $y=(\sqrt{\lambda}, 0)$.

We want to check that problem is well conditioned in the neighbourhood of $y$. In Newton method we need to compute the inverse of Hessian, we need to check how conditioned it is. We can use for this the conditional number:

$$k(H) = \frac{|\lambda_{max}(H)|}{|\lambda_{min}(H)|}$$

The further $k(H)$ is from $1$ the worse conditioned the problem is (ideal is $1$).

$$k(H) = \frac{1+\frac{\lambda}{x_1^2}}{1} = 1+\frac{\lambda}{x_1^2}$$

As $x$ is close to $y=(\sqrt{\lambda}, 0)$ we get:

$$k(H(x)) \approx 1+\frac{\lambda}{\lambda} = 2$$

So the problem is well conditioned.

Also function $f$ is self-concordant and due to that the Newton method converge faster:

$$x_1 = a + tv, \; x_2 = b + tw$$

$$f + \lambda h = \frac{1}{2}((a+tv)^2 + (b+tw)^2) - \lambda \log(a+tv)$$

$$ |(f + \lambda h)'''|= |(\frac{1}{2}((a+tv)^2 + (b+tw)^2) - \lambda \log(a+tv))'''| = | \frac{2\lambda v^3}{(a+tv)^3} |
= \\ = 
2(\frac{\lambda v^2}{(a+tv)^2})^{3/2} \leq
2(v^2 + w^2 + \frac{\lambda v^2}{(a+tv)^2})^{3/2} 
= \\ =
2(\frac{1}{2}((a+tv)^2 + (b+tw)^2) - \lambda \log(a+tv))''^{3/2} = 2(f + \lambda h)''^{3/2}$$


Now with another function:
$$f(x) =  x_1 + \frac{1}{2}x_2^2$$

$$\nabla (f+\lambda h) = [1 - \frac{\lambda}{x_1}, x_2]^T$$

$$H = \begin{pmatrix}
\frac{\lambda}{x_1^2} & 0\\
0 & 1 
\end{pmatrix}$$

Optimum of $f+\lambda h$ is where $\nabla (f+\lambda h) = 0$ as $f+\lambda h$ is convex (as sum of convex functions). We get that optimum is in $y=(\lambda, 0)$. We want to go with $\lambda$ to $0$, so let's already assume that $\lambda < 1$. For $x$ in neighbourhood of $y$:

Maximal eigenvalue: $\frac{\lambda}{x_1^2}$.
Minimal eigenvalue: $1$.

$$k(H) = \frac{|\lambda_{max}(H)|}{|\lambda_{min}(H)|}$$

$$k(H) = \frac{\frac{\lambda}{x_1^2}}{1} = \frac{\lambda}{x_1^2} \approx_{N(y)} \approx \frac{\lambda}{\lambda^2} = \frac{1}{\lambda} \rightarrow_{\lambda \rightarrow 0^+} = +\infty$$

Self-concordant:

$$x_1 = a + tv, \; x_2 = b + tw$$

$$f + \lambda h = (a+tv) + \frac{1}{2}(b+tw)^2 - \lambda \log(a+tv)$$

$$|(f + \lambda h)'''|= |((a+tv) + \frac{1}{2}(b+tw)^2- \lambda \log(a+tv))'''| = | \frac{2\lambda v^3}{(a+tv)^3} |
= \\ = 
2(\frac{\lambda v^2}{(a+tv)^2})^{3/2} \leq
2(w^2 + \frac{\lambda v^2}{(a+tv)^2})^{3/2} 
= \\ =
2((a+tv) + \frac{1}{2}(b+tw)^2 - \lambda \log(a+tv))''^{3/2}
= \\ =
2(\frac{1}{2}((a+tv)^2 + (b+tw)^2) - \lambda \log(a+tv))''^{3/2} = 2(f + \lambda h)''^{3/2}$$


## Task 5
![](https://i.imgur.com/6nOe2jj.png)
$$L(x, \lambda) = \langle c, x \rangle + \langle \lambda, f(x) \rangle$$

$$h(\lambda) = \inf_x \langle c, x \rangle + \langle \lambda, f(x) \rangle $$


