# SL midterm 2

## Task 1

:::warning
Compare irrepresentability and identifiability conditions for LASSO. Which properties are
guaranteed by these conditions ?
:::

Least Absolute Shrinkage and Selection Operator

https://arxiv.org/pdf/1812.05723.pdf

Irrepresentability $\Longrightarrow$ Identifiability

**Irrepresentability condition:**

$$\Vert X_{\bar I}^TX_I  (X_I^TX_I)^{-1}S_I \Vert_{\infty} \leq 1$$

- stronger
- can recover the sign with high probability
- is affected by the structure of correlations

**Identifiability condition:**

$$X\gamma = X\beta \text{ and } \gamma \neq \beta \text{ then } \Vert\gamma\Vert_1 > \Vert\beta\Vert_1$$

- is **not** affected by the structure of correlations
- can recover sign when the signals are strong enough using a thresholded procedure



## Task 2

:::warning
Adaptive LASSO and Ridge: In the orthogonal case (X’X=I) calculate the value of the
adaptive ridge or LASSO estimator for the specific coordinate of the beta vector. For the
ridge regression: given the true value of this parameter calculate the bias, variance and the
mean squared error of this adaptive estimator.
:::
```
ponieżej przeklejka z notatek z zeszłego roku,
jeszcze do sprawdzenia czy nie ma bugów
```

### Adaptive Ridge

Rozważ adaptacyjne wersje procedury z $\gamma_i = w_i \gamma$.

a) W sytuacji ortogonalnej wyznacz estymator dla konkretnego $\beta_i$ za pomocą adaptacyjnego ‘’ridge’’, wyznacz obciążenie, wariancję i błąd średniokwadratowy tego estymatora.

**Ridge**
Adaptacyjne Ridge dla konkretengo $i$ wzorki na 
obciążenie, wariancję i błąd średniokwadratowy są takie same jak dla zwykłego, tylko trzeba wziąć $\gamma_i$ zamiast $\gamma$.
Niech $D$ - macierz diagonalna, taka że $D_{ii} = \frac{1}{1 + \gamma_i}$
**Obciążenie**:
Mamy $\hat{\beta} = DX'Y = DX'(X\beta + \epsilon) = D(\beta + X'\epsilon)$
Wiemy, że $\hat\beta^{LS} = X'Y = X'(X\beta + \epsilon) = \beta + X'\epsilon$
Niech $X'\epsilon = Z \sim N(X' \cdot 0, X'\sigma^2X) = N(0,\sigma^2 I)$
wtedy $Z_i \sim N(0, \sigma^2)$ i $Z_i$ są niezależne.
Mamy wtedy $\hat\beta_i =  \frac{1}{1+\gamma_i}\hat\beta^{LS}_i =\frac{1}{1+\gamma_i}(\beta_i + Z_i)$
Wartość oczekiwana:
$$\mathbb{E}[\hat\beta_i] = \frac{1}{1+\gamma_i}\beta_i + \frac{1}{1+\gamma_i}\mathbb{E}[Z_i] = \frac{1}{1+\gamma_i}\beta_i$$
Obciążenie:
$$b(\hat\beta_i) = \mathbb{E}[\hat\beta_i] - \beta_i  = \frac{1}{1+\gamma}\beta_i - \beta_i = \frac{-\gamma_i}{1+\gamma_i}\beta_i$$
**Wariancja**:
$$Var{\hat\beta_i} = Var(\frac{1}{1+\gamma}(\beta_i + Z_i)) = (\frac{1}{1+\gamma_i})^2\cdot Var(\beta_i + Z_i) =\\
=(\frac{1}{1+\gamma_i})^2\cdot Var(Z_i) = (\frac{\sigma}{1+\gamma_i})^2$$
**Błąd średniokwadratowy**:
$$\mathbb{E}[\|\hat\beta_i - \beta_i\|^2] = Var(\hat\beta_i) + (b(\hat\beta_i))^2 = (\frac{\sigma}{1+\gamma_i})^2 +\beta_i^2 (\frac{\gamma_i}{1+\gamma_i})^2$$


b) Dysponując macierzami $X$ i $Y$ wyznacz adaptacyjny estymator dla konkretnego $\beta_i$.
$\hat\beta = (X'X + A^2)^{-1}X'Y$, gdzie $A^2$ jest macierzą diagonalną,taką że $A^2_{ii} = \gamma_i$


### Adaptive LASSO

http://users.stat.umn.edu/~zouxx019/Papers/adalasso.pdf

$$\beta_{aL} = argmin_{b} \left\{ \frac 1 2 \Vert y - Xb \Vert^2_2 + \lambda \sum_{i=1}^p w_i|b_i| \right\}$$

weights: $w_i = \frac 1 {\hat \beta_i}$ for some consistent estimator of beta.

![](https://i.imgur.com/jbbjacM.png)

With orthogonal design: $$\hat{\beta}_i^{AL} = \frac{1}{w_i}\hat{\gamma_i}$$ $$\hat{\gamma_i} = \begin{cases} w_i \hat{\beta}^{LS}_i - \lambda, & w_i \hat{\beta}^{LS}_i \geq \lambda \\ 0, & |w_i \hat{\beta}^{LS}_i| < \lambda \\ w_i \hat{\beta}^{LS}_i + \lambda, & w_i \hat{\beta}^{LS}_i \leq -\lambda \\ \end{cases}$$

należy pamiętać, że LS robimy dla $\tilde X$ i wtedy estymator $\gamma$ bez wag, estymator $\beta_{LASSO}$ z wagami (?)

## Task 3

:::warning
Bayesian interpretation of ridge and LASSO: given the tuning parameters for LASSO or
ridge provide the respective prior distribution for the related Maximum A Posteriori Bayesian
rule.
:::

https://cdn.fbsbx.com/v/t59.2708-21/289429814_717813636103225_3862325912282346063_n.pdf/Wyk%C5%82ad10.pdf?_nc_cat=105&ccb=1-7&_nc_sid=0cab14&_nc_ohc=WtOhThrrRE8AX_Aji4N&_nc_ht=cdn.fbsbx.com&oh=03_AVLGrfntCOSD3zFNDXRNbE4s53v68qWTqhCI5hTwbKLIlA&oe=62B4F976&dl=1

![](https://i.imgur.com/rdyHqT9.jpg)

Ridge: Normal

LASSO: Laplace

http://courses.ieor.berkeley.edu/ieor165/lecture_notes/ieor165_lec8.pdf

## Task 4

:::warning
Given the tuning parameters for the spike and slab LASSO and the value of the sparsity
parameter, calculate the probability that a given beta belongs to the spike (or the slab)
component.
:::

https://repository.upenn.edu/cgi/viewcontent.cgi?article=1629&context=statistics_papers

![](https://i.imgur.com/4oYZ69N.png)

Ten wzór trzeba udogólnić dla dowolnych $\lambda_i$

1 - slab

0 - spike

## Task 5

:::warning
Define SLOPE. Describe SLOPE properties. How is it different from LASSO ?
:::

$$\hat{\beta}_{SLOPE} = argmin_{b} \left\{ \frac 1 2 \Vert y - Xb \Vert^2_2 +  \sum_{i=1}^p \lambda_i|b_{(i)}| \right\}$$
$$|b|_{(1)} \geq \ldots \geq |b|_{(p)} \\ \lambda_1 \geq \ldots \geq \lambda_p$$
Penalization term:

$$J_\lambda(b) = \sum_{i=1}^p \lambda_i|b_{(i)}| $$

:::info
For orthogonal design $(XX^T=I)$ SLOPE controls FDR at level $q \frac {p_0} p$ for lambdas corresponding to BH correction:

$$\lambda_i = \sigma \Phi^{-1}\Big(1 - i \cdot \frac q {2p}\Big)$$

It also adapts to unknown sparsity and is asymptotically minimax under orthogonal and random Gaussian design. 
:::


We can use $\lambda = \sigma \sqrt{2 logp}(1+o_p)$ to make LASSO behave like Bonferroni correction. A non-increasing sequence of tunning parameters (used in SLOPE) allow the method to be less conservative and still control FDR (like Benjamini-Hochberg procedure).
LASSO has difficulties with correlated predictors, SLOPE can handle them in groups. 

## Task 6


:::warning
Knockoffs: Given vector of values of W statistics calculate the respective critical value so
that FDR is controlled at a given level, use this procedure to decide which variables are
significant predictors of Y
:::


https://arxiv.org/pdf/1404.5609.pdf
https://arxiv.org/pdf/1610.02351.pdf

<!-- $$T = min\Big\{ t \in \mathcal W: \frac {\#\{j: W_j \leq -t\}} {max(\#\{j: W_j \geq t\},  1)} \leq q \Big\}$$
 -->
<!-- or  -->
Randomised threshold:

$$T = min\Big\{ t \in \mathcal W: \frac {1 + \#\{j: W_j \leq -t\}} {\#\{j: W_j \geq t\}} \leq q \Big\} \\ \mathcal{W} = \{ |W_j| \: | \: j\in \{1, \ldots, p \} \}$$

Variable in significant when $W_j \geq T$.



## Task 7

:::warning
Given a covariance matrix for the 3-dimensional multivariate normal distribution be able to
determine which pairs of variables are independent/conditionally independent. Be able to
draw a respective graphical model.
:::

$$X|Y \sim N(\mu_{X|Y}, \Sigma_{X|Y})$$

$$\mu_{X|Y} = \mu_X + \Sigma_{XY}\Sigma_{YY}^{-1}(y - \mu_Y)$$

$$\Sigma_{X|Y} =  \Sigma_{XX} - \Sigma_{XY}\Sigma_{YY}^{-1} \Sigma_{YX}$$


Vertices: variables
Edges: when variables are conditionally dependent (so when $\Theta_{i,j} \neq 0$)


Or simplier: using covariance and precision matrix.

![](https://i.imgur.com/odPqWvT.png)


## Task 8

:::warning
Provide the definition of the precision matrix. How is it related to the gaussian graphical
model ?
:::

http://ir.hit.edu.cn/~jguo/docs/notes/report-in-princeton-research.pdf

![](https://i.imgur.com/As8Yj3N.png)

![](https://i.imgur.com/kwsH9R8.png)

![](https://i.imgur.com/jFmfKom.png)

Precision matrix is the inverse of covariance matrix. 

 $X_i$, $X_j$ are uncorelated $\Leftrightarrow$ $\Sigma_{ij}=0$ 
 and $X_i$, $X_j$ are conditionaly independent $\Leftrightarrow$ $\Theta_{ij}=0$
 


## Task 9

:::warning
Formulate the graphical LASSO and graphical SLOPE algorithms.
:::

https://bochang.me/gmrg/files/Bo_05152015.pdf

![](https://i.imgur.com/ydUbKof.png)




http://www.few.vu.nl/~wvanwie/presentations/WNvanWieringen_RidgeEstimationOfGGM.pdf

![](https://i.imgur.com/HaXw8kt.png)

![](https://i.imgur.com/bGzZpS1.png)


https://arxiv.org/pdf/2204.10403.pdf
![](https://i.imgur.com/yGWQwps.png)

