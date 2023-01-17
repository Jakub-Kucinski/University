# Statistical Learning mideterm 1

# Notes
## Multiple testing
### Bonferroni

Bonferroni procedure rejects all hypotheses $H_{0i}$ with $p_i$ that satisfy

$$
p_i < \frac{\alpha}{n}.
$$

Controls $FWER$, $FDR$.
### Benjamini-Hochberg

We denote $i_0 := \max\{i : p_{(i)} \leq \frac{i}{n} \alpha\}$.

We reject $H_{(i)}: i \leq i_0$.

Controls $FDR$

![](https://i.imgur.com/QovrSwT.png)


## Error measures
![](https://i.imgur.com/hdgllSc.png)



### FWER

Family-wise error rate

$$
FWER = P(V \geq 1)
$$

### FDP

False discovery proportion

$$
FDP = \frac{V}{R}1_{\{R \geq 1\}} = 
\begin{cases}
\frac{V}{R} & R\geq 1\\
0 & \text{otherwise}
\end{cases}
$$

### FDR

False discovery rate

$$
FDR = \mathbb{E}[FDP]
$$

Properties of FDR:
FDR $\leq$ FWER (FWER controll => FDR controll) 

**Expected number of false discoveries**
Let $V_i$ be 1 if $H_{0,i}$ is rejected 0 otherwise
$$
\mathbb{E}[V] = \sum_{i \not\in true\ nulls}\mathbb{E}[V_i] = \sum_{i \not\in true\ nulls}\mathbb{P}[V_i = 1] = \sum_{i \not\in true\ nulls}\alpha = (n-n_0)\alpha
$$



# Questions

1.   Given the inverse of the matrix $X’X$ and the standard deviation of the error term $\sigma$

<hr>

> Distribution of coefficients: 
> $b \sim \mathcal N\big(\beta, \sigma^2(X^TX)^{-1}\big)$

- calculate the standard deviation of the least square estimator of a given coordinate of the beta vector
    
$$
\sigma_{\beta_i} = \sigma \cdot \sqrt{(X'X)^{-1}_{[i, i]}}
$$
    
- given the value of this estimator

$$
s_{\beta_i} = s \cdot \sqrt{(X'X)^{-1}_{[i, i]}}
$$

- construct a confidence interval for the respective coordinate of beta, perform a z-test for the significance of this coordinate - given the true value of beta, calculate the power of the respective z-test.



> **Students test:**
> test statistics (distribution under $H_0$):
> $$
> t = \frac {b_i}{s_{b_i}} \sim t_{n-p}
> $$
> confidence interval:
> $$
> \beta_i \in b_i \pm s_{b_i} \cdot t_{q}\Big((1 - \frac \alpha 2), n-p\Big)
> $$


> **Z-test**
Test of significance of $\hat{\beta_i}$: $Z = \frac{\hat{\beta_i} - 0}{\sigma_{\beta_i}}$
We reject $\mathcal{H}_0$ when $|Z| > \Phi^{-1}\left( 1 - \frac{\alpha}{2} \right)$ or equivalently p-value is smaller than $\alpha$.
Two tailed p-value: $2\cdot\Phi(-|Z|) = 2\cdot(1-\Phi(|Z|))$
Confidence interval: $\hat{\beta_i} \in \beta_i \pm \sigma_{\beta_i} \cdot \Phi^{-1}\left(1-\frac{\alpha}{2}\right)$

**power**:
>$$
>\mathbb{P}\left[\text{rejection of i-th} \; | \; \mathcal{H}_{0_i}^c\right] = 1 - \Phi\left(c - \frac{\beta_i}{\sigma_{\beta_i}} \right) + \Phi\left(- c - \frac{\beta_i}{\sigma_{\beta_i}} \right),
>$$
where $c$ is critical value, i.e.
$$
c=\Phi^{-1}\left( 1 - \frac{\alpha}{2} \right)
$$

<hr>

2. Consider the situation where p<n and the elements of X are iid random variables from N(0,1).Find the expected value of the variance of the least squares estimates of individual components of beta.

<hr>

$$
\mathbb{E}[\sigma^2(\hat{\beta}_i)] = \sigma^2\frac{1}{n-p-1}
$$

> $X_{i,\cdot} \sim \mathcal N (0, \Sigma)$
Wishart Distribution:
$$
X^TX \sim W_p(\Sigma, n)
$$
$$
\mathbb E \big[(X^TX) \big] = n\Sigma
$$
Inverse Wishart distribution:
$$
(X^TX)^{-1} \sim W_p^{-1} (\Sigma^{-1}, n)
$$
$$
\mathbb E \big[(X^TX)^{-1} \big] = \frac {\Sigma^{-1}} {n - p - 1}
$$

$X_{i,\cdot} \sim \mathcal N (0, \mathbb I)$

$\mathbb E[\sigma_{\beta_i}] = \mathbb E[\sigma (X'X)^{-1}_{[i, i]}] = \sigma \mathbb E[ (X'X)^{-1}_{[i, i]}] = \sigma \cdot \frac {\mathbb I^{-1}_{[i, i]}} {n - p - 1}  = = \sigma \cdot \frac 1 {n - p - 1} = \frac { \sigma} {n - p - 1}$

<hr>

3.    Given a set of p-values perform the multiple testing procedure using Bonferroni or Benjamini-Hochberg multiple testing procedure.

<hr>

-   **Bonferroni**: reject all p-values such that $p_i < \frac{\alpha}{n}$
-   **Benjamini-Hochberg**: $i_0 := \max\{i : p_{(i)} \leq \frac{i}{n} \alpha\}$. We reject $H_{(i)}: i \leq i_0$.
> where $n$ is the number of p-values (variables)
<hr>

4. Find the expected value of the number of false discoveries when individual tests are performed at the significance level alpha.

<hr>

-  $(p - k)\alpha$  where $p$ - number of hypothese tested (so number of betas), and $k$ - number of relevant betas

<hr>

5. Given the result of the multiple testing and the indicators of true hypothesis, calculate the False Discovery proportion.

<hr>

-    Check which discoveries are true (rejected and null hypothesis was false) and which discoveries were false (rejected but null hypothesis was true) 
$FDP = \frac{\text{#false discoveries}}{\text{#false discoveries + #true discoveries}}$

<hr>

6. Given RSS and the standard estimation of the error term, use SURE to estimate the prediction error.

<hr>

$$
PE=E||Y^*-\hat{Y}||^2=E||\mu-\hat{\mu}||^2+n\sigma^2
$$

Then using Stein's identity for $g(Y)=\hat{Y}-Y=MY-Y$ we obtain

$$
PE = E||\mu-\hat{\mu}||^2+n\sigma^2 = n\sigma^2+E(||g(Y)||^2+2\sigma^2\textrm{div}g(Y))=n\sigma^2+E(RSS)+2\sigma^2(\textrm{Tr}M-\frac{n}{2})
$$

We know that $M=X(X'X)^{-1}X'$ so  $\textrm{Tr}M=\textrm{rank}(X)=p$. To estimate $PE$ we swap $E(RSS)$ with $RSS$ and obtain:

- Sigma known
$$
\widehat{PE} = RSS + 2\sigma^2p,
$$
- Sigma unknown
$$
\widehat{PE} = RSS + 2p\frac{RSS}{n-p}.
$$


> Stein's Unbiased Risk Estimator
> - $\mu \in \mathbb R ^n$
> - $x \sim \mathcal N(\mu, \sigma^2 \mathbb I)$
> - $h(x)$ - estimator of $\mu$ from $x$
> - $h(x) = x + g(x)$, where g is weakly differentiable
$$
SURE(h) = n\sigma^2 + \Vert  g(x)\Vert^2 + 2\sigma^2\sum\frac {\partial}{\partial x_i} g_i(x)
$$
$$
\mathbb E_\mu\{SURE(h)\} = MSE(h) = \mathbb E\Vert h(x) - \mu\Vert^2
$$
$$
\mathbb E_{\mu}\Vert h(x) - \mu \Vert^2 = \mathbb E_{\mu}\Bigg( n\sigma^2 + \Vert  g(x)\Vert^2 + 2\sigma^2\sum\frac {\partial}{\partial x_i} g_i(x)  \Bigg)
$$
<hr>

7. Given RSS for different regression models use AIC, BIC, RIC etc to identify the ‘best’ model.

<hr>

Finding the best model for different criteria coresponds to minimizing:
- **AIC**
$$
RSS+2\sigma^2k
$$
- **BIC**
$$
RSS+\sigma^2k\log n
$$
- **RIC**
$$
RSS+\sigma^22k\log p
$$

Next two can be wrong

- **mBIC**
$$
\log(RSS)+k\log n + 2k\log\left(\frac{p}{4}\right)
$$
- **mBIC2**
$$
\log(RSS)+k\log n + 2k\log\left(\frac{p}{4}\right) - 2\log(k!)
$$


 > When do several information criteria reject $H_{0, i}: \beta_i = 0$ for $XX' = I$:
 > - AIC: $|b_i| \geq \sqrt{2} \cdot \sigma$
 > - BIC: $|b_i| \geq \sqrt{log(n)} \cdot \sigma$
 > - RIC: $|b_i| \geq \sqrt{2log(p)} \cdot \sigma$
 > - mBIC: $\frac {n b^2_i}{\sigma} > log(n)$ (?)
 > - mBIC2: (?)
 > - EBIC2: (?)

<hr>

8. Given residuals and the elements on the diagonal of the projection matrix H calculate RSS and the cross-validation estimator of the prediction error.

<hr>

$$
RSS = \sum_{i=1}^n(y_i - \hat{y}_i)^2 = \sum_{i=1}^n e_i^2
$$

$$
CV=\sum_{i=1}^n \left(\frac{Y_i-\hat{Y}_i}{1-H_{ii}} \right)^2 = \sum_{i=1}^n \frac{RSS}{\left(1-H_{ii}\right)^2}
$$
<hr>

9. Assuming the X’X=I calculate the expected number of false discoveries for any of the considered model selection criteria.

<hr>

TODO

 - When do several information criteria reject $H_{0, i}: \beta_i = 0$ for $XX' = I$:
      - AIC: $|b_i| \geq \sqrt{2} \cdot \sigma$
      - BIC: $|b_i| \geq \sqrt{log(n)} \cdot \sigma$
      - RIC: $|b_i| \geq \sqrt{2log(p)} \cdot \sigma$
      - mBIC: $\frac {n b^2_i}{\sigma} > log(n)$ (?)
      - mBIC2: (?)
      - EBIC2: (?)
 - So the probabilities of type one error are:
      - AIC: $\mathbb{P}[|b_i| \geq \sqrt{2} \cdot \sigma] = \mathbb{P}[|b_i|/\sigma \geq \sqrt{2}] = 2 (1 - \phi(\sqrt{2}))$
      - BIC: $\mathbb{P}[|b_i| \geq \sqrt{log(n)} \cdot \sigma] = \mathbb{P}[|b_i|/\sigma \geq \sqrt{log(n)}] = 2 (1 - \phi(\sqrt{log(n)}))$
      - RIC: $\mathbb{P}[|b_i| \geq 2\sqrt{log(p)} \cdot \sigma] = \mathbb{P}[|b_i|/\sigma \geq 2\sqrt{log(p)}] = 2 (1 - \phi(2\sqrt{log(p)}))$
      - mBIC: $\frac {n b^2_i}{\sigma} > log(n)$ (?)
      - mBIC2: (?)
      - EBIC2: (?)
 - Expected number of false discoveries = $\mathbb{P}[\text{type I error}] \cdot (p-k)$
 
<hr>
 

TODO

10. When would you use AIC ? BIC ? RIC ? mBIC ? mBIC2 ?

<hr>

 - AIC - good prediction properties
 - BIC - consistent
 ![](https://i.imgur.com/JyZPpEx.png)
![](https://i.imgur.com/jqpI3C1.png)

 - RIC - controls number of false discoveries (depends on p, doesn't depend on n)
 - mBIC - controls FWER (~Bonferroni)
 - mBIC2 - controls FDR (~BH)
 ![](https://i.imgur.com/6niDD2O.png)

 https://books.google.pl/books?id=uIqRCwAAQBAJ&pg=PA61&lpg=PA61&dq=mbic2&source=bl&ots=k_5X7kcSqm&sig=ACfU3U2HWoLEXD7Cnq887aGOyQoD2k-fnw&hl=en&sa=X&ved=2ahUKEwjUkv7N9rb3AhVLtIsKHU5sCgwQ6AF6BAgWEAM#v=onepage&q=mbic2&f=false

<hr>

11. Given RSS and the eigenvalues of the inverse of X’X use SURE to estimate the prediction error of ridge regression.

<hr>

In Ridge regression $\hat{\beta}=(X'X+\gamma I)^{-1}X'Y$ so $\hat{Y}=X\hat{\beta}=MY$, with $M=X(X'X+\gamma I)^{-1}X'$
So using SURE to estimate $PE$ we get

$$
\widehat{PE}=RSS+2\sigma^2\textrm{Tr}M=RSS+2\sigma^2\sum_{i=1}^n\frac{\lambda_i(X'X)}{\lambda_i(X'X)+\gamma},
$$
where $\lambda_i(X'X)$ are eigenvalues of $X'X$.

We are given $\lambda_i((X'X^{-1}))$, but we know that $\lambda_i(X'X) = \frac{1}{\lambda_i((X'X^{-1}))}$.

<hr>

12. Assuming the X’X=I and given values of the least squares estimator provide values of ridge and LASSO estimators.
<hr>

In **Ridge** regression:
$\hat{\beta}_{RIDGE}=(X'X+\gamma I)^{-1}X'Y$ and the OLS estimator is $\hat{\beta}_{OLS}=(X'X)^{-1}X'Y$ 
so given that $XX' = I$ we have $\hat{\beta}_{OLS}=X'Y$ 
and so $\hat{\beta}_{RIDGE} = \frac{1}{1 + \gamma}X'Y = \frac{1}{1+\gamma}\hat{\beta}_{OLS}$

In **LASSO** for $XX'$ we have
$$
\hat{\beta}_i = 
\begin{cases} \hat{\beta}^{LS}_i - \lambda & \hat{\beta}^{LS}_i \ge \lambda \\
0 &  |\hat{\beta}^{LS}_i| < \lambda \\
\hat{\beta}^{LS}_i + \lambda & \hat{\beta}^{LS}_i \le -\lambda \\
\end{cases}.
$$

<hr>

13. Given X’X = I calculate MSE of the ridge estimator.
<hr>

$$
MSE = \mathbb{E} \|\hat{\beta} - \beta\|^2 = \sum_{i=1}^p \mathbb{E} (\hat{\beta_i} - \beta_i)^2 =\sum_{i=1}^p \left( Var(\hat\beta_i) + (b(\hat\beta_i)^2\right) = \\
\sum_{i=1}^p \left(\frac{\sigma^2}{(1+\gamma)^2}+
\beta_i^2 \left(\frac{\gamma}{1+\gamma} \right)^2\right) = 
\frac{p\sigma^2}{(1+\gamma)^2} + \frac{\gamma^2}{(1+\gamma)^2}  \sum_{i=1}^p \beta_i^2.
$$


<hr>

14. Given X’X=I calculate the expected value of false discoveries and the power of LASSO estimator.
<hr>

> - Selects $|\beta^{LS}| > \lambda$ 

$$
\mathbb P(Type I Error) = 
\mathbb P(reject H_{0,i}|H_{0,i}) = 
\mathbb P(\beta^{LS} > \lambda|H_{0,i}) = 
\mathbb P\Big(|\frac {\beta^{LS}} {\sigma}| > \frac \lambda \sigma|H_{0,i}\Big) = 
2\big(1 - \Phi^{-1}( \frac \lambda \sigma)\big) \\
\mathbb E FP_{LASSO} = p_0 2\big(1 - \Phi^{-1}( \frac \lambda \sigma)\big),
$$

where $p_0$ is the number of true null hypotheses.

**Power**: (?)
> Calculations for type I error look like performing Z-test on $\beta^{LS}$ at signifcance level $\frac{\lambda}{\sigma}$. Then, we compute power as in *Problem 1*, changing only the ctrical value
$$
c = \Phi^{-1} \left( 1- \frac{\lambda}{2\sigma}\right).
$$
<hr>

15. Be able to verify the irrepresentability condition for LASSO and understand what it implies.
<hr>

Calculate $C$ value and add appropriate comment?
> Irrepresentability condition
$$
S(\beta) = \text{signs of }\beta \\
I = \{ i \in \{1, \ldots ,p \} \,|\, \beta_i \neq 0\}
$$
$$
C = \lVert X_{\bar{I}}'X_I(X_I'X_I)^{-1}S(\beta_I) \rVert_\infty
$$
If $C>1$, then probability of the support recovery by LASSO is smaller than $0.5$. 
<hr>

16. Given RSS,the number of variables selected by elastic net (LASSO) [and eigenvalues of the inverse of $X_A’X_A$], estimate the prediction error of elastic net (LASSO).
<hr>

**Propozycja:**

> **ENet (ElasticNet)**
> Active set: $\mathcal A$
> *Projection* matrix:
> $$H_{\lambda_2}(\mathcal A) = X_{\mathcal A} (X_{\mathcal A}^TX_{\mathcal A} + \lambda_2 \mathbb I)^{-1}X_{\mathcal A}^T$$
> Trace of *projection* matrix:
> $$Tr(H_{\lambda_2}(\mathcal A)) = \widehat {df}$$


**SURE for PE:**

$$\widehat {PE} = \mathbb E \Vert\hat\mu - \mu\Vert^2 = \mathbb E_\mu \Vert h(Y) -Y  \Vert^2 =  \mathbb E_\mu\{SURE(h)\} = RSS + 2\sigma^2Tr(M)$$

**LASSO**

$\lambda_2 = 0$, 
$\widehat {df}_{LASSO} = \#\mathcal A$

- Sigma known
$$\widehat{PE} = RSS + 2\sigma^2 Tr(M) = RSS + 2\sigma^2 \#\mathcal A$$
- Sigma unknown
$$\widehat{PE} = RSS + 2Tr(M)\frac{RSS}{n-p} = RSS + 2\frac{RSS}{n-p} \#\mathcal A$$

where $p = \textrm{rank}(X)$ and $n$ is number of rows in $X$. 

**ElasticNet**

**SURE for PE:**

$\widehat {PE} = n \sigma^2 + \mathbb E [SURE(\hat\mu - \mu)] = n \sigma^2 + RSS + 2\sigma^2Tr(M) - n \sigma^2  = RSS + 2\sigma^2Tr(M)$

- Sigma known
$$\widehat{PE} = RSS + 2\sigma^2 Tr(M) = RSS + 2\sigma^2 \sum \frac {\lambda_i(X'X)}{\lambda_i(X'X) + \lambda_2},$$
- Sigma unknown
$$\widehat{PE} = RSS + 2Tr(M)\frac{RSS}{n-p} = RSS + 2\frac{RSS}{n-p}\sum \frac {\lambda_i(X'X)}{\lambda_i(X'X) + \lambda_2},$$

where $p = \textrm{rank}(X)$ and $n$ is number of rows in $X$. Note! $\lambda_2$ is the l_2 regularization parameter

<hr>

17. When would you prefer elastic net over LASSO? What are the main differences between these methods?
<hr>

- when we want to choose more than n variables (LASSO chooses at most n)
- when we suspect there may be strongly correlated important variables (LASSO tends to choose only one from the group)

> **Limitations of LASSO:**
> - selects at most $n$ variables
> - fails with groupped variables

> **ElasticNet advatages**:
> - removes the limitation of the number of selected variables
> - encourages groupping effect
> - stabilizes the $\mathcal l_1$ regularization path

<hr>

18. Why do LASSO and elastic net perform variable selection and ridge regression does not ?

<hr>

The $\ell_1$ penalty creates sigularities at the vertexes which gives us sparsity

![](https://i.imgur.com/C5SwZO4.png)


Regularization with $\ell_1$ norm shrinks to 0, $\ell_2$ regularization shrinks to small values.
<hr>



# Multiple Regression

Multiple Linear Regression is a statistical approach for modeling a linear relationship between a scalar response variable and many explanatory variables. 
Let's consider $n$ observations (values of response variable and vectors of explanatory variables). The number of explanatory variables is denoted by $p-1$. The model is of the form:

$$
Y_i = \beta_0 + X_i\beta_{[1, \ldots,p-1]} + \epsilon_i
$$
or equivalently the model in a matrix form:

$$
Y = X\beta + \epsilon
$$
where:

- $Y_i$ is the value of the response variable for $i$th observation, $Y$ is the (horizontal) vector of response variable ($n \times 1$);

- $X_i$ is the (vertical) vector of explanatory variables for $i$th observation, $X$ is a design matrix (first column filled with ones, $X_{i, j+1}$ is the value of the $j$th explanatory variable in the $i$th observation ($n \times p$);

- $\beta_0$ is the intercept, 

- $\beta$ is the (horizontal) vector of coefficients ($n \times 1$),

- $\epsilon_i$ is the error for $i$th observation, let's consider normally distributed errors: $\epsilon_i \sim \mathcal N (0, \sigma^2)$, $\epsilon$ is the vector of errors ($n \times 1$),

- $i$ is the index of the observation.

There are two standard formulas for estimating $\beta$: least squares and maximum likelihood. When the error is normally distributed (as we have previously assumed) those method are equivalent. 

The estimator of $\beta$ is denoted by $b$, the estimator of $\sigma$ (standard deviation of the errors) will be denoted as $s$.

The fitted values of the response variables will be denoted as $\hat{Y}$. We can calculate it by replacing $\beta$ with its estimator and $\epsilon$ by its mean value ($b$ and $0$).

$$
\hat Y = Xb
$$ 
The difference between real and fitted (predicted) values of the response variable is called residual and it is marked with $e$:

$$
e = Y - \hat Y
$$
Let's get into more details.

## Estimating Regression Coefficients

We will show the least squares estimation of $\beta$. The method is based on minimalizing the values of the error $\epsilon$.

$$
b = arg\min_{b \in \mathbb R ^n}  \quad (Y - Xb)^T(Y - Xb)
$$

Let's expand the minimised formula: 

$$
(Y - Xb)^T(Y - Xb) = Y^TY - b^TX^TY - Y^TXb + b^TX^TXb
$$

Let's derive by $b$: 

$$
-X^TY - Y^TX + 2X^TXb = 0
$$

$$X^TXb = X^TY$$
The sationar point:

$$b = (X^TX)^{-1}X^TY$$
The second derivative is $2X^TX$. Let's have $v \in \mathbb R ^p$.

$$v^T X^TXv = (Xv)^TXv = Xv \circ Xv = \Vert Xv \Vert^2 \geq 0$$

Thus, $X^TX$ is a positive-definite matrix, so we have found the local minimum.

Let take a look on the distribution of the estimator:

$$b \sim \mathcal N\big(\beta, \sigma^2(X^TX)^{-1}\big)$$

## Fitted Values

After providing the formula for $b$ we are able to derive the formula for $\hat Y$ in terms of $X$ and $Y$:

$$\hat Y = Xb = X(X^TX)^{-1}X^TY$$

As we can see in the above equation, there is a linear dependence between $Y$ and $\hat Y$. The matrix transforming $Y$ into $\hat Y$ is called hat matrix and it is denoted by $H$:

$$\hat Y = H Y$$
The formual for the hat matrix is: 

$$H = X(X^TX)^{-1}X^T$$

THe matrix $H$ *projects* $Y$ into $\hat Y$.

## Estimator of $\sigma$

The estimator of $\sigma^2$ uses the values of the residuals has the form:

$$s^2 = \frac {e^Te} {n-p} = \frac {(Y - Xb)^T(Y - Xb)} {n-p}$$

## Wishart and Inverse-Wishart Distribution

In the upcoming simulations, we will consider the design matrix of i.i.d. normally distributed random variables. X is a $n \times p$ matrix, each row is independently drawn from p-variate normal distribution with mean zero and covariance matrix $\Sigma = \frac 1 {1000}I$. Thus, $X^TX$ ($p \times p$ random matrix) has the Wishart probability distribution with parameters $\Sigma$ and $n$:

$$X^TX \sim W_p(\Sigma, n)$$

Thus, the inverse of $X^TX$ comes from the Inverse-Wishart distribution:

$$(X^TX)^{-1} \sim W_p^{-1} (\Sigma^{-1}, n)$$

The mean value of a random variable from Inverse-Wishart distribution has the mean:

$$\mathbb E \big[(X^TX)^{-1} \big] = \frac {\Sigma^{-1}} {n - p - 1}$$

# Multiple Testing

---
*NOTE*

Usually the number of tested hypotheses is denoted as $n$. As we will test the relevance of the regression coefficients we will stay  unified with the notation from the previous section and denote the number of hypotheses as $p$. Thus $p$ and $p_0$ will state the number of hypotheses, $p_1, \ldots, p_p$ will tate for p-values.

---


Let's consider p testing problems:

$$H_{0, i}: \mu_i = 0 \quad vs \quad H_{1, i}: \mu_i \neq 0$$

Multiple testing means testing many individual hypotheses ($H_{0, i}$ vs. $H_{1, i}$) at the same time. To  simply statistically test each hypothesis separately doesn't lead to satisfying results. We use **multiple comparison procedures** (MCPs) instead. MCPs are used to improve the quality of the tests. 

The outcome of an MCP can be presented in the following form:

|     | accepted | rejected | total   |
|-----|----------|----------|---------|
|true | TN (U)   | FP (S)   | $p_0$   |
|false| FN  (V)  | TP (T)   |$p - p_0$|
|total| p - R    | R        | p       |

The symbols used:

- TN - True Negatives - the null hypothesis is true, and it was accepted (U in *Candes*),

- FP - False Positives - the null hypothesis is true, but it was rejected (V in *Candes*),

- FN - False Negatives - the null hypothesis is false, and it was accepted (T in *Candes*),

- TP - True Positives - the null hypothesis is false, and it was rejected (S in *Candes*), 

- $p_0$ - the number of true null hypotheses,

- R - the number of rejected hypotheses,

- $p$ - the number of hypotheses.

---
*NOTE*

$p$ and $p_0$ are the numbers. $p$ is a known number; $p_0$ is an unknown number. TN, FP, FN, TP, R are random variables. R is an observed random variable; TN, FP, FN, TP are unobserved random variables.

---

## Test Quality Measures

The definition of the Type I Error does not simply propagate to multiple testing problem. On the one hand, allowing a single false discovery with the probability $\alpha$  is a very strict condition. On the other hand, allowing the probability of false discovery in each test to be $\alpha$, leads to many false discoveries. Hence we need to introduce new quality measures: FWER and FDR.

### FWER

FWER stands for **F**amili**w**ise **E**rror **R**ate. 

In **strong** sense: it is the probability of making any false discoveries: 

$$FWER = \mathbb{P}(V \geq 1)$$

In **weak** sense: it is the probability of making any false discoveries if all the global null hypothesis is true: 

$$FWER = \mathbb{P}(V \geq 1 |  \forall_i H_{0, i})$$

### FDR

FDR stands for **F**alse **D**iscovery **R**ate id the expected value of FDP (**F**alse **D**iscovery **P**roportion) - the ratio between the numbers of false discoveries and all rejections:

$$FDR = \mathbb{E}\Bigg[ \frac{FP}{ max(R, 1)}\Bigg]$$
Under the global null hypothesis, FDR and FWEAR are equivalent.

### mFDR

$$mFDR = \frac {\mathbb E V } {\mathbb E R} = \frac {\mathbb E V} {\mathbb E [V + T]} $$

### Power

Power is the probability of rejecting the null hypothesis when it is false. In the above terms, we can express it as the expected value of the ratio of TP and the number of false hypotheses:

$$power = \mathbb{E}\Bigg[ \frac{TP}{p - p_0} \Bigg]$$

## Multiple Testing Procedures

For all below procedures, first we calculate the p-values of single tests:

- p-values: $p_1, p_2, \ldots, p_p$,

- ordered p-values: $p_{(1)}, p_{(2)}, \ldots, p_{(p)}$.

### Bonferroni's procedure

Reject $H_{0, i}$ if: $$p_i <  \frac \alpha n$$

This method is very conservative. We know from the lecture that Bonferroni's method controls FWER in a strong sense. In fact, 

$$FWER = \mathbb{P}(FP \geq 1) \leq \sum_{i=1}^{p_0}\mathbb P(FP = i) = \sum_{i=1}^{n_0} {{p_0}\choose{i}} \alpha^i(1 - \alpha)^{p_0 - i}$$

$$FWER \leq \frac{p_0}{p} \alpha$$

### Benjamini-Hochberg's procedure

Reject $H_{0, (i)}$ if: 

$$\exists _{(j \geq i)}  \quad p_{(j)} <  \frac {j} {n} \alpha$$
Benjamini-Hochberg's method is a step-down procedure. This procedure controls FDR under independence. Thus, it controls FWER weakly. It does not control FWER in a strong sense. It is much more liberal than Hochberg's procedure (more powerful and leads to more false discoveries). 


## Regression

### Ridge


#### Ortogonal design ($XX' = I$)


We have $\hat{\beta} = \frac{1}{1+\gamma}X'Y = \frac{1}{1+\gamma}X'(X\beta + \epsilon) = \frac{1}{1+\gamma}(\beta + X'\epsilon)$
We know that $\hat\beta^{LS} = X'Y = X'(X\beta + \epsilon) = \beta + X'\epsilon$
Let $X'\epsilon = Z \sim N_p(X' \cdot 0, X'\sigma^2X) = N_p(0,\sigma^2 I)$
then $Z_i \sim N(0, \sigma^2)$, and $Z_i$ are iid.
We then have $\hat\beta_i =  \frac{1}{1+\gamma}\hat\beta^{LS}_i =\frac{1}{1+\gamma}(\beta_i + Z_i)$

**Expected value**:
$$\mathbb{E}[\hat\beta_i] = \frac{1}{1+\gamma}\beta_i + \frac{1}{1+\gamma}\mathbb{E}[Z_i] = \frac{1}{1+\gamma}\beta_i$$

**Bias**:
$$b(\hat\beta_i) = \mathbb{E}[\hat\beta_i] - \beta_i  = \frac{1}{1+\gamma}\beta_i - \beta_i = \frac{-\gamma}{1+\gamma}\beta_i$$

**Variance**:
$$Var{\hat\beta_i} = Var(\frac{1}{1+\gamma}(\beta_i + Z_i)) = (\frac{1}{1+\gamma})^2\cdot Var(\beta_i + Z_i) =\\
=(\frac{1}{1+\gamma})^2\cdot Var(Z_i) = (\frac{\sigma}{1+\gamma})^2$$

**MSE**:
$$MSE = \mathbb{E} \|\hat{\beta} - \beta\|^2 = \sum_{i=1}^p \mathbb{E} (\hat{\beta_i} - \beta_i)^2 =\sum_{i=1}^p \left( Var(\hat\beta_i) + (b(\hat\beta_i)^2\right) = \\
\sum_{i=1}^p \left(\frac{\sigma^2}{(1+\gamma)^2}+
\beta_i^2 \left(\frac{\gamma}{1+\gamma} \right)^2\right) = 
\frac{p\sigma^2}{(1+\gamma)^2} + \frac{\gamma^2}{(1+\gamma)^2}  \sum_{i=1}^p \beta_i^2.
$$

To calculate optimal $\gamma$ we have to optimize:
$$
f(x) = \frac{x^2}{(1+x)^2} A + \frac{B}{(1+x)^2}.
$$
$$
f'(x) = \frac{2Ax - 2B}{(1+x)^3} = 0 \Leftrightarrow x = \frac{B}{A}
$$
$$
f''(x) =\frac{2A - 4Ax + 6B}{(1+x)^4} \quad 
f''\left(\frac{B}{A}\right) = \frac{2A + 2B}{(1+\frac{B}{A})^4} >0,
$$
because $A = \sum_{i=1}^p \beta_i^2 > 0$ i $B = \sigma^2 p >0$.
So optimal $\gamma$ is $\frac{\sigma^2 p }{\|\beta\|^2}$, and smallest $MSE$ is
$$
f\left(\frac{B}{A}\right) = \frac{AB}{A+B} = 
\frac{\|\beta\|^2 \sigma^2p}{\|\beta\|^2 + \sigma^2 p}.
$$

### LASSO

In ortogonal case
$$\hat{\beta}_i = 
\begin{cases} \hat{\beta}^{LS}_i - \lambda & \hat{\beta}^{LS}_i \ge \lambda \\
0 &  |\hat{\beta}^{LS}_i| < \lambda \\
\hat{\beta}^{LS}_i + \lambda & \hat{\beta}^{LS}_i \le -\lambda \\
\end{cases}.$$

Error of I type:
$$
\begin{aligned}
\mathbb{P}(\hat\beta_i^{LS} \ge \lambda \text{  or  } \hat\beta_i^{LS} \le -\lambda  | \beta_i = 0) &= 
 \mathbb{P} (\hat\beta_i^{LS} \ge \lambda | \beta_i = 0) +  \mathbb{P} (\hat\beta_i^{LS} \le -\lambda | \beta_i = 0) \\
 &=
 2F_{N(0, \sigma^2)}(-\lambda).
\end{aligned}
$$



