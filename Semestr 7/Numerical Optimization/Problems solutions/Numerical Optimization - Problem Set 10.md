# Numerical Optimization - Problem Set 10
###### tags: `no2021/2022` `ćwiczenia`
## Task 1
![](https://i.imgur.com/RrIzSuc.png)

$$\textrm{proj}_h(x) = \textrm{argmin}_y\left(\frac{1}{2}\|y-x\|^2+h(y)\right)$$

### $f(x) = - \log (x)$
$$\textrm{proj}_f(x) = \textrm{argmin}_y\left(\frac{1}{2}\|y-x\|^2-\log(y)\right) = \textrm{argmin}_y g(y)$$

$$\textrm{Dom}_g = (0, \infty)$$

$$\frac{\partial g}{\partial y} = y - x - \frac{1}{y} = 0$$

$$y^2 - xy - 1 = 0$$

$$\Delta = x^2 + 4$$

$$y_1 = \frac{x + \sqrt{x^2 + 4}}{2} > 0$$

$$y_1 = \frac{x - \sqrt{x^2 + 4}}{2} < 0$$

$$\textrm{proj}_f(x) =\frac{x + \sqrt{x^2 + 4}}{2}$$


### $f(x) = \max (x^3, 0)$

### $f(x) = - \log (x)$
$$\textrm{proj}_f(x) = \textrm{argmin}_y\left(\frac{1}{2}\|y-x\|^2+ \max (y^3, 0)\right) = \textrm{argmin}_y g(y)$$


$$g(y) = 
\begin{cases}
\frac{1}{2}(y^2 - 2xy + x^2) + y^3, & y\geq 0 \\
\frac{1}{2}(y^2 - 2xy + x^2), & y < 0
\end{cases}$$

$g(y)$ is strictly convex.


$y < 0$

$$\frac{\partial g}{\partial y} = y - x = 0$$

$$y = x \Rightarrow x < 0$$


$y\geq 0, x \geq 0$

$$\frac{\partial g}{\partial y} = y - x + 3y^2 = 0$$

$$\frac{\partial g}{\partial y} = y - x + 3y^2 = 0$$

$$ 3y^2 + y - x = 0 $$



$$\Delta = 1 + 12x$$

$$y_1 = \frac{-1 + \sqrt{1 + 12x}}{6} > 0$$

$$y_1 = \frac{-1 - \sqrt{1 + 12x}}{6} < 0$$


## Task 2
![](https://i.imgur.com/dDSmCKX.png)
![](https://i.imgur.com/kLjBeAo.png)
![](https://i.imgur.com/F9lI6qA.png)
![](https://i.imgur.com/0O7KLfL.png)



## Task 3
![](https://i.imgur.com/vUqcJeZ.png)

### $f(x) = \max (1, \exp(x^2))$

$$f(x) = \max (1, \exp(x^2)) =  \exp(x^2)$$

$f$ is differentiable at x, then clearly $\partial f (x) =
\{∇f (x)\}$.

$$\partial f(x) = \{2x \exp(x^2) \}$$

### $g(x) = \max (e, \exp(x^2))$

$$g(x) = \max (e, \exp(x^2)) = 
\begin{cases}
e, & |x| \leq 1 \\
\exp(x^2), & |x|>1 
\end{cases}$$

$$\partial g(x) = 
\begin{cases}
\{0\}, & |x| < 1 \\
\{2x\exp(x^2)\}, & |x|>1 \\
\{?\}, & |x|=1.
\end{cases}$$


Case: $|x| = 1$.
![](https://i.imgur.com/5NJxpr2.png)
![](https://i.imgur.com/Oy1eDQk.png)
Note that $(x, f(x)) \in \phi(y)$.

The slope (that is $v$) will be between leftside and rightside derivatives.

Subcase: $x = 1$. Then $(1, e) \in \phi(y)$.

$$g'(1^-) = 0$$

$$g'(1^+) = 2e$$

Therefore

$$v \in [0, 2e]$$

Subcase: $x = -1$. Then $(-1, e) \in \phi(y)$.

$$g'(-1^-) = -2e$$

$$g'(1^+) = 0$$

Therefore

$$v \in [-2e, 0]$$

