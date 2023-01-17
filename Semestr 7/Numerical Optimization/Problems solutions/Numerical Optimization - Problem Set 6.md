# Numerical Optimization - Problem Set 6
###### tags: `no2021/2022` `ćwiczenia`
## Task 1
![](https://i.imgur.com/vrrGarw.png)
$$\nabla f(x) = [x_1, \frac{1}{2}x_2]^T$$

### gradient descent with exact line search started in p oint such that x2 > 0 will stay in points such that x2 > 0
Let $$g(\alpha) = f(x_i + \alpha \nabla f(x_i)) = f([x_{i_1}(1+\alpha), x_{i_2}(1+\alpha / 2)]^T)$$
Then $$g(\alpha) = 1/2(x_{i_1}^2(1+\alpha)^2 + 1/2(1+\alpha/2)^2x_{i_2}^2)$$ $$g'(\alpha) = x_{i_1}^2 + \alpha x_{i_1}^2 + \frac{1}{4} x_{i_2}^2 + \frac{\alpha}{8} x_{i_2}^2$$
We are looking for $g'(\alpha) = 0$ and we get $$\alpha = -\frac{x_{i_1}^2+\frac{1}{4} x_{i_2}^2}{x_{i_1}^2+\frac{1}{8} x_{i_2}^2}$$
It is easy to check that $-2 < \alpha < -1$.
We have $$x_{i+1} = [(1+\alpha)x_{i_1}, (1+\alpha / 2)x_{i_2}]^T$$ We know that $x_{0_2}>0$ and by induction assume $x_{i_2}>0$. As $-2 < \alpha < -1$ we have $0<(1+\alpha / 2)<1/2$ so $x_{{i+1}_2} = (1+\alpha / 2)x_{i_2}>0$.

### Justify that g has Lipschitz continuous gradient.
$$\nabla g(x) = \left[x_1, \left|\frac{1}{2}x_2\right|\right]^T$$
We need to show that $$\| f(x) - f(y) \| \leq L\| x-y \|$$
Proof:
$$\| \nabla g(x) - \nabla g(y) \| = \| \left[x_1 - y_1, \frac{1}{2}|x_2| - \frac{1}{2}|y_2|\right]^T \| \leq \| \left[x_1 - y_1, \frac{1}{2}|x_2 - y_2|\right]^T \| \leq \\ \leq \|\left[x_1 - y_1, |x_2 - y_2|\right]^T \| = 1\cdot \|\left[x_1 - y_1, x_2 - y_2\right]^T \| = 1\cdot \|x - y\|$$

### Consider gradient descent with line search which chooses local minimum online closest to starting point. Use first part of the problem to show that such gradient descent started at point such that x2> 0 will produce the same sequence of approximations for f and g.
$$x_{i+1} = x_i + \alpha \nabla g(x_i)$$
$$\phi(\alpha) = x_i + \alpha \nabla g(x_i)$$
We want to minimize $g(\phi(\alpha))$. We know that $x_{0_2}>0$ and by induction assume $x_{i_2}>0$. $$g(\phi(\alpha)) = g([x_{i_1}(1+\alpha), x_{i_2}+(\alpha / 2)|x_{i_2}|]^T) = g([x_{i_1}(1+\alpha), x_{i_2}(1+\alpha / 2)]^T)$$
There might be more than one minima as we have different $g$ definition for $x_2\geq 0$ and $x_2 < 0$ and equaly for $(1+\alpha / 2)\geq 0$ and $(1+\alpha / 2)< 0$ which is again equal to $\alpha\geq -2$ and $\alpha < -2$. We might have 2 minimas, one for $\alpha\geq -2$ case and one for $\alpha < -2$. We need to check which is closer to $x_i$. So we want to minimize: $$\| x_i - \phi(\alpha) \| = \| x_i - (x_i + \alpha \nabla g(x_i)) \| =  \| \alpha \nabla g(x_i)) \| =  |\alpha|\cdot \|\nabla g(x_i)) \|$$
We want to compare $|\alpha|\cdot \|\nabla g(x_i)) \|$ for case $\alpha\geq -2$ and $\alpha< -2$. We can skip $\|\nabla g(x_i)) \|$ as it is same and nonnegative for both cases. We also already checked in first part of task that for first case optimal $\alpha$ satisfies $-1\geq\alpha\geq -2$. So for first case $1\leq|\alpha|\leq 2$ and for second case $2\leq|\alpha|$. Therefore second case is always further than first one so we always take positive $x_{i_2}$ and obtain same sequence of approximations as for f. 
 

## Task 3
### a)
$$f(x) = cosh(x)$$
$$|f'''(x)| = |sinh(x)| \leq 2[cosh(x)]^{3/2}$$
$$|\frac{e^x - e^{-x}}{2}|\leq 2 (\frac{e^x + e^{-x}}{2})^{3/2}$$
It is true as $|e^x - e^{-x}|\leq e^x + e^{-x}$ and $\frac{e^x + e^{-x}}{2} \geq 1$ so also $\frac{e^x + e^{-x}}{2} < (\frac{e^x + e^{-x}}{2})^{3/2}$


In a), b), c) we will be using
![](https://i.imgur.com/icflpWl.png)
![](https://i.imgur.com/QVprv7I.png)

### b) 
![](https://i.imgur.com/2dLzkVs.png)
$$f(x,y) = −log( y) −log(y −x^T x/y)$$
We need to show it is self-concordant on every line, so lets $x = x' + tv, y = y' + tw$.
$$f(x' + tv, y' + tw) = −log
(y' + tw − \frac{x'^T x'}{y' + tw} − \frac{2tx'^T}{vy' + tw} − \frac{t^2v^Tv}{y' + tw})−log(y' + tw)$$
If $w=0$ than we have quadratic function of $t$ that is concave. Otherwise we can change variable from $t$ to $y$ and obtain:
$$f(x' + tv, y' + tw) = −log(\alpha + \beta y −\gamma /y) −log(y)$$ for some not important constants not dependent on $y$ (but $\gamma > 0$ which is important for convexity).
Let $g(y) = -\alpha - \beta y +\gamma /y$. Of course $g(y)$ is convex. Then $f(x' + tv, y' + tw) = −log(- g(y) ) −log(y)$.
$$g''(y) = 2\gamma / y^3, g'''(y) = -6\gamma/y^4$$
so
$$|g'''(y)| = |-6\gamma/y^4|\leq 3g''(y)/y = 6\gamma / y^4$$

### c)
![](https://i.imgur.com/Acu6QAr.png)
$$f = f_1 + f_2$$ where
$$f_1(x,y) = −log( y) −log(y^{1/p} −x), f_2(x,y) = −log( y) −log(y^{1/p} + x)$$
Similarly to b) $x = x' + tv, y = y' + tw$. If $w=0$ we get linear functions which are self-concordant. Let change variable from $t$ to $y$. We want to show that $$-log(y) - log(y^{1/p} + \alpha y + \beta)$$ is self-concordant. $\alpha$ and $\beta$ are not important for us as in the example b). Let $g(y) = -\alpha y - \beta - y^{1/p}$. Of course $g(y)$ is convex.

$$g''(y) = \frac{(p-1)}{p^2}y^{\frac{1}{p} - 2}$$ $$g'''(y) = \frac{-(1-p)(1-2p)}{p^3}y^{\frac{1}{p} - 3}$$


$$|g'''(y)| = \leq 3g''(y)/y$$ $$|\frac{(1-p)(1-2p)}{p^3}| \leq 3 \frac{(p-1)}{p^2}$$ which is true for $p\geq 1$.

### d)
![](https://i.imgur.com/rK1DCVM.png)
Similarly to b) and c) $x = x' + tv, y = y' + tw$
$$f(x' + tv, y' + tw) = −log(y' + tw) −log(log(y' + tw) −x' −tv)$$
For $w=0$ it has linear functions inside logarithms so it is self-concordant. We change variable from $t$ to $y$ and get:
$$−log(y) −log(log( y) −\alpha −\beta y)$$
Let $g(y) = \alpha +\beta y - log(y)$. Of course $g(y)$ is convex.
$$g''(y) = 1/y^2$$
$$g'''(y) = -2/y^3$$
$$|g'''(y)| = 2/y^3 \leq 3g''(y)/y = 3/y^3$$


## Task 4
### a)
![](https://i.imgur.com/CWzeUN6.png)

We need to calculate second and third derivatives.
$f'(x) = -1/x^2$, $f''(x) = 2/x^3$, $f'''(x) = - 6/x^4$

Self concordance inequality:
$$6/x^4 \leq 2 (2/x^3)^{3/2} = \frac{4\sqrt{2}}{x^4\sqrt{x}}$$
Multipling by $x^4$ both sides of inequality:
$$6\leq \frac{4\sqrt{2}}{\sqrt{x}}$$ which is same as 
$$\sqrt{x} \leq \frac{2\sqrt{2}}{3}$$ because $x>0$. Taking to the power of 2 we get:
$$x\geq 8/9$$ which is consistent with our domain, therefore $f$ is self-concordant.

### b)
![](https://i.imgur.com/TppHZv9.png)
There is a typo in the sum. There should be $(b_i - \langle a_i, x\rangle)$.

First of all we see that $b_i - \langle a_i, x\rangle > 0$ from definition of $dom(f)$ (and therefore also $c>0$). We can change the last inequality to form:
$$\frac{8}{9} > \frac{\max_i{\sup_{x\in dom(f)}{(b_i - \langle a_i, x\rangle)}}}{c}$$

Let now introduce new variables: $$y_i = \left(\frac{c}{b_i - \langle a_i, x\rangle}\right)^{-1}$$

As $$\max_i{\sup_{x\in dom(f)}{(b_i - \langle a_i, x\rangle)}} \geq b_i - \langle a_i, x\rangle$$ and by using previous inequality we obtain: $$y_i < 8/9$$ So $$y_i\in (0, 8/9)$$ and $$f(x) = \sum_i \frac{1}{y_i}$$ so it is a sum of self-concordant function (from $a)$ task) so $f$ is self-concordant.

