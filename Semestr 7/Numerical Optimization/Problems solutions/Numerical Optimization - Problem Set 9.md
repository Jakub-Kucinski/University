# Numerical Optimization - Problem Set 9
###### tags: `no2021/2022` `ćwiczenia`
## Task 1
![](https://i.imgur.com/FnWArDR.png)
Lipschitz continuous with constant M:
$$ \vert f(x) - f(y) \vert \leq M \Vert x - y \Vert$$

It is enough to show: 
$$\forall_{x\notin S} \exists_{y\in S} f(x) + \lambda d(x,S) > f(y) + \lambda d(y, S) = f(y)$$

Let's take any $x \notin S$. For such $x$ let's take $y \in S$ such that $d(x, S) = d(x, y)$. We know that such $y$ exists as $S$ is closed. We get:

$$f(x)+\lambda d(x, S) - f(y) = f(x) + \lambda d(x, y) - f(y) 
=\\= 
f(x) - f(y) + \lambda \Vert x-y \Vert  > f(x) - f(y) + M \Vert x - y \Vert \geq M \Vert x - y \Vert - \vert f(x) - f(y) \vert \geq 0$$

So we got:
$$f(x)+\lambda d(x, S) > f(y)$$

Therefore:
$$\min_{x\in D(f)}f(x)+\lambda d(x, S) = \min_{x\in S}f(x)+\lambda d(x, S) = \min_{x\in S}f(x)$$


## Task 2
![](https://i.imgur.com/3iGnPmz.png)
$$L(x, \mu, \theta) = \langle c, x \rangle + \langle \mu, Ax+b \rangle + \langle \theta, Ax+d \rangle 
=\\= 
\langle c, x \rangle + \langle \mu, b \rangle + \langle \theta, d \rangle + \langle A^T(\mu + \theta), x \rangle
=\\=
\langle \mu, b \rangle + \langle \theta, d \rangle + \langle A^T(\mu + \theta) + c, x \rangle
$$

So dual $h$ is:
$$h(\mu, \theta) = \inf_x \langle \mu, b \rangle + \langle \theta, d \rangle + \langle A^T(\mu + \theta) + c, x \rangle$$

Linear function is bounded from below only when it is identically 0. So we get:

$$h(\mu, \theta) = \langle \mu, b \rangle + \langle \theta, d \rangle$$

with domain of pairs $(\mu, \theta)$ such that

$$A^T(\mu + \theta) + c = 0$$


## Task 3
![](https://i.imgur.com/j4eEYUa.png)
![](https://i.imgur.com/DYMAMom.png)
![](https://i.imgur.com/3XGvNKd.png)
![](https://i.imgur.com/uVB54CX.png)


## Task 4
![](https://i.imgur.com/4XpIWrR.png)


## Task 5
![](https://i.imgur.com/xGlpzcv.png)

