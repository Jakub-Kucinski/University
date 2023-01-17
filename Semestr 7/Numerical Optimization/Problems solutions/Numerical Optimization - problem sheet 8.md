# Numerical Optimization - problem sheet 8
###### tags: `no2021/2022` `ćwiczenia`
Jakub Kuciński 309881
## Task 1
![](https://i.imgur.com/Zpi9f49.png)
Definition of tangent set:
![](https://i.imgur.com/ZzhIkoL.png)

![](https://i.imgur.com/7Lz3WRa.png)

Plot of constraints. Feasible set lies in the top right corner (the most bright color).
![](https://i.imgur.com/3XUnct2.png)

Definitions from "Linear and Non-linear Programming":
![](https://i.imgur.com/MuCyxfq.png)

Constraints from task:
$$1 − x_1 ≤ 0, −x_2 ≤ 0, x_2 − (x_1 − 1)^2 ≤ 0$$
All equalities holds for $y=(1,0)$ (all inequalities are active).

Gradients:

$$\nabla g_0 = [-1, 0]^T$$

$$\nabla g_1 = [0, -1]^T$$

$$\nabla g_2 = [-2(x_1 - 1), 1]^T$$

Now let's calculate those gradients in $y=(1,0)$:
$$\nabla g_0(y) = [-1,0]^T, \nabla g_1(y) = [0,-1]^T, \nabla g_2(y) = [0, 1]^T$$

Gradients of $g_i$ are linearlly dependent, so assumpitons of lemma giving KKT are violated.

From Lemma 1.2 we know that $TS_y \subset \{v: \forall_{i\in E} \langle \nabla g_i, v \rangle = 0, \forall_{i\in J} \langle \nabla g_i, v \rangle \leq 0\} = V$. So we can determine the $V$ set and check which of vectors in $V$ are actually in $TS_y$.
Let's take any $v = [v_1, v_2]^T \in V$. Then

$$\langle \nabla g_0(y), v\rangle = -v_1 \leq 0$$

$$\langle \nabla g_1(y), v\rangle = -v_2 \leq 0$$

$$\langle \nabla g_2(y), v\rangle = v_2 \leq 0$$

so $v = [v_1, 0]$ for $v_1\geq 0$. For such $v$ obviously $v \in TS_y$ as $y+tv \in S$ for $t \geq 0$, therefore $d(y+tv, S) = 0$.

Let $f(x) = x_1 + 2x_2$. We know, that $x_1 \geq 1$ and $x_2 \geq 0$ and as $y=(1, 0)\in S$ then $y$ minimizes $f$.

Our gradients are:

$$\nabla f = [1, 2]^T$$

$$\nabla g_0 = [-1, 0]^T$$

$$\nabla g_1 = [0, -1]^T$$

$$\nabla g_2 = [-2(x_1 - 1), 1]^T$$

So from KKT we get the equations:

$$1 - \mu_0 - \mu_2 2(x_1 - 1) = 0$$

$$2 - \mu_1 + \mu_2 = 0$$

$$1-x_1 = 0 \Leftrightarrow x_1 = 1$$

$$ -x_2 = 0 \Leftrightarrow x_2 = 0$$

$$ x_2 − (x_1 − 1)^2 = 0 \Leftrightarrow x_2 = (x_1−1)^2$$

From last 3 equations we have $x_1 = 1, \; x_2 = 0$ which align with $y=(1,0)$. Also $\mu_i$ can be set to be $\geq 0$ (e.g. $\mu_0 = 1, \; \mu_1 = 2,\; \mu_2 = 0)$, so the sentence in exercise is wrong and KKT conditions are actually satisfied (however assumptions of the lemma are not - gradients $\nabla g_i$ are not independent).

## Task 2
![](https://i.imgur.com/P5YIZfv.png)

We multiply $f$ by $-1$ to get the minimization problem.
$$f(x) = - (x_1+1)^2 - (x_2+1)^2$$

$$\nabla f = [-2x_1 - 2, -2x_1 - 2]^T$$

$$g(x) = x_1^2 + x_2^2 - 2$$

$$\nabla g = [2x_1, 2x_2]^T$$

$$h(x) = 1 - x_2$$

$$\nabla h = [0,-1]^T$$

We need to check 2 cases, first with inequality constraint active and second with inactive.

#### Inequality constraint active
From KKT we get the conditions:

$$-2 x_1 - 2 + \mu_1 \cdot 2 x_1 = 0$$

$$-2 x_2 - 2 - \lambda_2 + \mu_2 \cdot 2 x_2 = 0$$

$$x_1^2 + x_2^2 - 2 = 0$$

$$1 - x_2 = 0$$

$$\mu_i \geq 0$$

We can substitute $x_2 = 1$ to the remaining equalities:

$$-2 x_1 - 2 + \mu_1 \cdot 2 x_1 = 0$$

$$-2 - 2 - \lambda_2 + 2\mu_2 = 0$$

$$x_1^2 + 1 - 2 = 0 \Leftrightarrow x_1 = \pm -1$$

Now we need to check another two cases:

First case: $x_1 = 1,\; x_2 = 1$. Then $\mu_1 = 2$, $\lambda_2$ and $\mu_2$ can be chosen to be $4$ and $4$. All conditions are satisfied and $f(x) = -8$.

Second case: $x_1 = -1,\; x_2 = 1$. Then $\mu_1 = 0$, $\lambda_2$ and $\mu_2$ can be chosen to be $4$ and $4$. All conditions are satisfied and $f(x) = -4$.

So for the case with inequality constrain active it is better to chose $x_1 = 1,\; x_2 = 1$ which gives the $f(x) = -8$.

#### Inequality constraint inactive

$$-2 x_1 - 2 = 0$$

$$-2 x_2 - 2 - \lambda_2 = 0$$

$$1 - x_2 = 0$$

So we get $x_1 = 1$ and $x_2 = 1$. But then $x_1^2 + x_2^2 = 1^2 + 1^2 = 2$ which breaks the assumption that inequality constrain is inactive so in this case there are no solutions.

In the end our best solution is $x_1 = 1, \; x_2 = 1$ which gives the $f(x) = -8$ (in maximization task that is $8$).

## Task 3
![](https://i.imgur.com/dCxMzXr.png)
![](https://i.imgur.com/TUEfQZt.png)

We know that the norm we want to minimize looks like:

$$\Vert z - x \Vert = \sqrt{\sum_i (x_i - z_i)^2}$$

So it is minimal when $(x_i-z_i)^2$ are the smallest possible. In our case of $S = [0, \infty)^n$ the choices for $z_i$ are independent from each other, so we can minimize it per $i$. If $x_i\in [0, \infty)$ then of course the best $z_i$ is $x_i$. On the other hand if $x_i \in (-\infty, 0)$ it is the best to take the closest $z_i$ and that is $0$. Therefore we can easily derive the formula for projection:

$$\left(Proj_{[0, \infty)^n}(x)\right)_i = \max(x_i, 0)$$


# Task 4
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

If $k(H)$ is far from $1$ then the problem is badly confitioned (ideally $k(H)=1$).

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