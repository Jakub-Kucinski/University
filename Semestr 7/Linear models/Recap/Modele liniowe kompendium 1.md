# Modele liniowe kompendium 1

###### tags: `ml21` `ćwiczenia` `Zaitseva`

## Regresja liniowa

$\beta_0$ - wyraz wolny
$\beta_1$ - współczynnik kierunkowy
$\epsilon$ - błąd losowy

$E(Y_i) = E(X_1 \cdot \beta_1 + \beta_0) + E(\epsilon) = X_i \cdot \beta_1 + \beta_0$ 

$Var(Y_i) = Var(X_1 \cdot \beta_1 + \beta_0 + \epsilon) = Var(\epsilon) = \sigma^2$

![](https://i.imgur.com/0PR7uL6.png)

## Metody estymacji

### OLS - Ordinary Least Squares/ Metoda najmniejszych kwadratów
$(\hat\beta_0,\hat\beta_0) = argmin_{(b_0,b_1) \in \mathbb{R^2}}\sum^n_{i=1}e^2_i(b_0, b_1)= argmin_{(b_0,b_1) \in \mathbb{R^2}}\sum^n_{i=1}(Y_i -(b_0 + b_1X_i))^2$

### MLE - Maximum Likelihood Estimator
$(\hat\beta_0,\hat\beta_0,\sigma^2) = argmin_{b_0, b_1, z}\prod^n_{i=1}\frac{1}{\sqrt{2\pi z^2}}exp(-\frac{1}{2z^2}(Y_i-b_0-b_1X_i)^2)= argmin_{b_0, b_1, z} -\frac{n}{2}log2\pi - \frac{n}{2}log z^2 - \frac{1}{2z^2}\sum^n_{i=1}(Y_i-b_o-b_1X_i)^2$
$(\hat\beta_0,\hat\beta_0) = argmin_{b_0, b_1}\sum^n_{i=1}(Y_i-b_o-b_1X_i)^2$

### Estymatory beta1 i beta0
$\hat\beta_1 = \frac{\sum^n_{i=1}(X_i-\overline{X})(Y_i-\overline{Y})}{\sum^n_{i=1}(X_i-\overline{X})^2} = \frac{cov_p(X,Y)}{var_p(X)}$

$\hat\beta_0 = \overline{Y} -\hat\beta_1 \cdot \overline{X}$

```{r}
X
Y
estbeta1 <- sum((X-mean(X)) *(Y - mean(Y)))/ sum((X-mean(X))^2))
estbeta0 <- mean(Y) - estbeta1 * mean(X)

reg <- lm(Y~X, data)
summary(reg)
```

### Teoretyczne własności $\hat\beta_1$

$\beta_1 \sim N(\beta_1, \sigma^2(\hat\beta_1))$

$\sigma^2(\hat\beta_1) = \frac{\sigma^2}{\sum^n_{i=1}(X_i - \overline{X})^2}$
$\sigma^2=\frac{1}{n}\sum_{i=1}^n(Y_i - \hat\beta_0 - \hat\beta_1X_i)^2$

```{r}
X
Y
estbeta1
estbeta2
dim(X) # z tego wyciągnąć n

sigma2 <- 1/length(n) * sum(Y-estbeta0 -estbeta1*X)**2
sigma2estbeta1 <- sigma2/sum(X-mean(X)**2)
```

#### Przedział ufności $\beta_1$

##### Statystyka T
Statystyka T pochodzi z rozkładu studenta z n-2 stopniami swobody $T \sim t(n-2)$

$T = \frac{\hat\beta_1 - \beta_1}{s(\hat\beta_1)}$
$s^2(\hat\beta_1) = \frac{s^2}{\sum^n_{i=1}(X_i-\overline{X})^2}$
$s^2=\frac{1}{n-2}\sum_{i=1}^n(Y_i - \hat\beta_0 - \hat\beta_1X_i)^2$

```{r}
Y
X
estbeta1
beta1

s2 <- 1/(n-2) * sum((Y-estbeta0 -estbeta1*X)**2)
s2estbeta1 <- s2/sum((X-mean(X))**2)

T <- (estbeta1 - beta1)/sqrt(s2estbeta1)
```

##### Przedział ufności $\beta_1$
Przedział ufności o współczynniku ufności $1-\alpha$ dla parametru $\beta_1$:

$\hat\beta_1 \pm t_cs(\hat\beta_1)$

gdzie $t_c = t^*(1-\frac{\alpha}{2},n-2)$ jest kwantylem rzędu $1-\frac{\alpha}{2}$ z n-2 stopniami swobody.

```{r}
n
alfa
estbeta1
s2estbeta1

tc <- qt(1-alfa/2, df=n-2, lower.tail = T)

lower <- estbeta1 - tc * sqrt(s2estbeta1)
upper <- estbeta1 + tc * sqrt(s2estbeta1)

reg1 = lm(Y~X, data)
confint(reg1, level=0.95)
```

#### Test istotności dla $\beta_1$

Dwie hipotezy: $H_0: \beta_1=0$ i $H_1: \beta_1\neq0$

Statystyka testowa:
$T = \frac{\hat\beta_1 - 0}{s(\hat\beta_1)}$

Odrzucamy hipotezę zerową gdy $|T| > t_c$, gdzie $t_c = t^*(1-\frac{\alpha}{2},n-2)$

p-wartość:
$p = P(|z| > |T|)$ gdzie $z \sim t(n-2)$

```{r}
alfa <- 0.05
estbeta1
s2estbeta1

T <- (estbeta1 - beta1)/sqrt(s2estbeta1) 
tc <- qt(1-alfa/2, df=n-2, lower.tail = T)
# Czy odrzucamy hipotezę zerową
abs(T) > tc
```

```{r}
# pwartość
X
T

pval <- 2*pt(-abs(T), df=length(X)-2)

reg1 = lm(Y~X, data)
summary(reg1)
```

### Teoretyczne własności $\hat\beta_0$

$\beta_0 \sim N(\beta_0, \sigma^2(\hat\beta_0))$

$\sigma^2(\hat\beta_0) = \sigma^2(\frac{1}{n}+\frac{\overline{X}^2}{\sum^n_{i=1}(X_i - \overline{X})^2})$

```{r}
X
Y
estbeta0
estbeta1
n <- length(X)

sigma2 <- 1/length(n) * sum(Y-estbeta0 -estbeta1*X)**2
sigma2estbeta0 <- sigma2 * (1/n + mean(X)**2/sum((X-mean(X))**2))
```

#### Przedział ufności $\beta_0$

##### Statystyka T
Statystyka T pochodzi z rozkładu studenta z n-2 stopniami swobody $T \sim t(n-2)$

$T = \frac{\hat\beta_0 - \beta_0}{s(\hat\beta_0)}$
$s^2(\hat\beta_0) = s^2(\frac{1}{n} + \frac{\overline{X}^2}{\sum^n_{i=1}(X_i-\overline{X})^2})$

```{r}
Y
X
estbeta0
estbeta0
n <- length(X)

s2 <- 1/(length(n)-2) * sum(Y-estbeta0 -estbeta1*X)**2
s2estbeta0 <- s2 * (1/n + (mean(X)**2)/(sum((X-mean(X))**2)))

T <- (estbeta1 - beta1)/s2estbeta1
```

##### Przedział ufności $\beta_0$
Przedział ufności o współczynniku ufności $1-\alpha$ dla parametru $\beta_1$:

$\hat\beta_0 \pm t_cs(\hat\beta_0)$

gdzie $t_c = t^*(1-\frac{\alpha}{2},n-2)$ jest kwantylem rzędu $1-\frac{\alpha}{2}$ z n-2 stopniami swobody.

```{r}
n
alfa
estbeta0
s2estbeta0

tc <- qt(1-alfa/2, df=n-2, lower.tail = T)

lower <- estbeta0 - tc * sqrt(s2estbeta0)
upper <- estbeta0 + tc * sqrt(s2estbeta0)

reg1 = lm(Y~X, data)
confint(reg1, level=0.95)
```

#### Test istotności dla $\beta_0$

Dwie hipotezy: $H_0: \beta_0=\beta_{00}$ i $H_1: \beta_0\neq\beta_{00}$

Statystyka testowa:
$T = \frac{\hat\beta_0 - \beta_{00}}{s(\hat\beta_0)}$

Odrzucamy hipotezę zerową gdy $|T| > t_c$, gdzie $t_c = t^*(1-\frac{\alpha}{2},n-2)$

p-wartość:
$p = P(|z| > |T|)$ gdzie $z \sim t(n-2)$

```{r}
alfa <- 0.05
estbeta0
s2estbeta0

T <- (estbeta0 - beta0)/sqrt(s2estbeta0) 
tc <- qt(1-alfa/2, df=n-2, lower.tail = T)
# Czy odrzucamy hipotezę zerową
abs(T) > tc
```

```{r}
# p wartość
X
T

pval <- 2*pt(-abs(T), df=length(X)-2)

reg1 = lm(Y~X, data)
summary(reg1)
```


```{r}
reg1 <- lm(Y~X,dane) - funkcja konstruująca model
reg1 - model i estymatory
summary(reg1) - podsumowanie modelu
reg1$residuals - wektor wartości resztowych
confint(reg1) - funkcja zwracająca 95% przedział ufności dla naszego modelu
```


### Moc testu

Moc testu o dwóch hipotezach to prawdopodobieństwo odrzucenia $H_0$, gdy prawdziwa jest hipoteza $H_1$ (pstwo uniknięcia błędu II rodzaju).

Hipotezy: $H_0: \beta_1=0$ i $H_0: \beta_1=a$

Statystyka testowa:
$T=\frac{\hat\beta_1}{s(\hat\beta_1)}$
Wartość krytyczna:
$t_c = t^*(1-\frac{\alpha}{2}, n-2)$

wtedy moc test wynosi $\pi(a) = P_{\beta_1=a}$(test S odrzucił hipotezę $H_0$)$=P_{\beta_1=a}(|T|>t_c))$ 

Przy założeniu, że $\beta_1=a$ statystka T ma niecentralny rozkład studenta $T \sim t(n-2,\delta)$, gdzie $\delta = \frac{\beta_1}{\sigma(\hat\beta_1)}$


Dane potrzebne do wyznaczenia mocy testu:
n, $\sum^n_{i=1}(X_i-\overline{X})^2$, $\sigma^2$
```{r}
alfa <- 0.05
beta1
n
ssx
sigma2

tc <- qt(1-alfa/2, df=n-2, lower.tail = T)
sigma2hatbeta1 <- sigma2/ssx
delta <- beta1/sqrt(sigma2hatbeta1)

test <- 1 - pt(tc, n-2, delta) + pt(-tc, n-2, delta)
test
```

```{r}
power = function(n, sig2, ssx, alpha, beta1){
  sig2b1 = sig2 / ssx
  dOfF = n - 2
  tc = qt(1-alpha/2, dOfF)
  delta = beta1 / sqrt(sig2b1)
  prob1 = function(delta){pt(tc, dOfF, delta)}
  prob2 = function(delta){pt(-tc, dOfF, delta)}
  powerOfBeta = 1 - prob1(delta) + prob2(delta)
  powerOfBeta
}
ssx = sum((X - mean(X))^2)
power(n, sig2, ssx, alpha, beta1)
```

## Estymacja $E(Y_h)=\mu_h$ i predykcja $Y_h$

$\hat\mu_h = \hat\beta_0 + \hat\beta_1X_h$
$\mu_h \sim N(\mu_h, \sigma^2(\hat\mu_h))$
$\sigma^2(\hat\mu_h)= \sigma^2(\frac{1}{n}+\frac{(X_h-\overline{X})^2}{\sum^n_{i=1}(X_i-\overline{X})^2)})$

```{r}
estbeta0
estbeta1
sigma2
X
Xh

estmih <- estbeta0 + estbeta1 * Xh
sigma2estmih = sigma2 * (1/n + ((Xh - mean(X))**2/sum((X - mean(X))**2)))
```

### Przedział ufności dla E($Y_h$)

Statystyka $T \sim t(n-2)$:
$T = \frac{\hat\mu- E(\hat\mu_h)}{s(\hat\mu_h)}$
$s^2(\mu_h)=s^2(\frac{1}{n} + \frac{(X_h-\overline{X})^2}{\sum^n_{i=1}(X_i-\overline{X})^2})$

$\hat\mu_h \pm t_cs(\hat\mu_h)$
``


```{r}
newdata = data.frame(copiers=c(11))
predict.lm(reg1, newdata, interval = "confidence", level=0.95)
```

### Przedział predykcyjny dla E($Y_h$)

$T = \frac{\hat\mu- E(\hat\mu_h)}{s(pred)}$
$s^2(pred) = s^2(1+\frac{1}{n} + \frac{(X_h-\overline{X})^2}{\sum^n_{i=1}(X_i-\overline{X})^2})$

$\hat\mu_h \pm t_cs(pred)$

```{r}
alfa <- 0.05
estbeta0
estbeta1
s2
X
Xh
n <- length(X)

estmih <- estbeta0 + estbeta1 * Xh
s2estmih = s2 * (1+1/n + ((Xh - mean(X))**2/sum((X - mean(X))**2)))
tc <- qt(1-alfa/2, df=n-2, lower.tail = T)

lower <- estmih - sqrt(s2estmih) * tc
upper <- estmih + sqrt(s2estmih) * tc

```

```{r}
newdata = data.frame(copiers=c(11))
predict.lm(reg1, newdata, interval = "prediction", level=0.95)
```

### Przedział ufności vs przedział predykcyjny
$s_{pred}^2 = s_{conf}^2 + s^2$

### Pasmo ufności E($Y_h$)

$\hat\mu_h \pm Ws(\hat\mu_h)$
fdzie $W^2 = 2F(1-\alpha, 2, n-2)$ jest podwojonym kwantylem rzędu $1-\alpha$ z rozkładu Fishera-Snedecora z 2 i n − 2 stopniami swobody.

```{r}
alfa <- 0.05
n <- length(X)
s2estmih
estmih

W2 <- 2 * qf(1-alfa, 2, n-2)

lower <- estmih - sqrt(s2estmih * W2)
right <- estmih + sqrt(s2estmih * W2)
```

## ANOVA

SST = $\sum^n_{i=1}(Y_i-\overline{Y})^2$ 
dfT = n-1

SSE = $\sum^n_{i=1}(Y_i-\hat Y_i)^2$ 
dfE = n-2

SSM = $\sum^n_{i=1}(\hat Y_i-\overline{Y})^2$ 
dfM = 1


SST = SSM + SSE
dfT = dfM + dfE

E(MSM) = $\sigma^2 + \beta_1^2\sum^n_{i=1}(X_i-\overline{X})^2$
E(MSE) = $\sigma^2$

```{r}
SST <- sum((Y - mean(Y))**2)
dfT <- n-1
SSE <- sum((Y - estY)**2)
dfE <- n-2
SSM <- sum((estY - mean(Y))**2)
dfM <- 1
```

### Test F

Hipotezy $H_0: \beta_1=0$ i $H_1: \beta_1 \neq 0$

Mamy statystyke F = MSM/MSE, która pochodzi z rozkładu Fishera–Snedecora z dfM i dfE stopniami swobody.

Odrzucamy hipotezę zerową gdy F > $F_c$, gdzie $F_c$ jest kwantylem rzędu $1-\alpha$ z rozkładu Fishera–Snedecora z dfM i dfE stopniami swobody.

p-wartość:
p=P(z>F), gdzie $z \sim F(dfM, dfE) = F(1, n-2)$

Test F i T są równoważne $F = T^2$, gdy mamy jeden regresor (jedną zmienną).

```{r}
alfa <- 0.05
MSM
MSE

F <- MSM/MSE
# fc <- qf(1-alfa, 1, n-2)
fc <- qf(1-alfa,dfM,dfE)
# Czy odrzucamy hipotezę zerową
abs(F) > fc
```

```{r}
#pwartość
dfM
dfE
F

pval <- pf(-f, dfM, dfE) + 1 - pf(f, dfM, dfE)

```
### Współczynnik determinacji $R^2$
Współczynnik determinacji $R^2$ jest miarą jakości dopasowania modelu. Mówi on o tym, jaką część całkowitej zmiennosci w wektorze Y (SST) stanowi zmienność wyjaśniona przez model (SSM).

W regresji liniowej prostej jest on tożsamy z kwadratem próbkowanej korelacji persona pomiędzy zmeinnymi zależna i niezależną

$R^2 = SSM/SST = 1 - SSE/SST$

Aby porównać modele o różnych liczbach regresorów:
$\overline{R}^2 = 1 - MSE/MST$

```{r}
R2 <- SSM/SST
```
```{r}
R2 <- 1-SSE/SST
```
```{r}
adjR2 <- 1-MSE/MST
```

## Diagnostyka modelu i środki zaradcze

### Transformacja Boxa-Coxa

Odpowiada na pytanie jaką funkcję nałożyć na Y, aby otrzymać liniową zależność.

Szuka najlepszej $\alpha$ żeby:
$Y' = \beta_0 + \beta_1X_i + \epsilon_i$
gdzie $Y' = Y^\alpha$ lub Y' = $(Y^\alpha-1)/\alpha$


Dla $\alpha = 0$ to Y' = $(Y^\alpha-1)/\alpha$ w granicy dostajemy logarytm
```{r}
optlambda <- MASS::boxcox(Y~X)
optlambda
```

## Obszar ufności dla $\beta_0$ $\beta_1$

Nierówność Bonderroniego
$P(\beta_0\in(c_0,d_0)\land \beta_1\in(c_1,d_1)) \geq 1-P(\beta_0\notin(c_0,d_0)) - P(\beta_1\notin(c_1,d_1))$

Obszar ufność Bonderroniego dla $\alpha$ wyznaczamy dla
$\alpha/2 \geq P(\beta_i\notin(c_i,d_i))$
czyli dla obszaru ufności o współczynniku ufności $1 - \alpha$ wyznaczamy przy wykorzystaniu klasycznych przedziałów ufność o  współczynniku $1-\alpha/2$

Metodę tą można wykorzystać przy większej liczbie parametrów odpowiednio zwiększając współczynnik ufności dla pojedyńczych przedziałów $1-\alpha/m$

```{r}
n
alfa
estbeta0
s2estbeta0

tc <- qt(1-alfa/4, df=n-2, lower.tail = T)

lower <- estbeta0 - tc * sqrt(s2estbeta0)
upper <- estbeta0 + tc * sqrt(s2estbeta0)

# i podobnie dla beta1
```

## Równoczesne przedziały ufności dla kilku wartości $E(Y_h) = \mu_h$
![](https://i.imgur.com/llUHDCK.png)

## Równoczesne przedziały predykcyjne dla kilku wartości $Y_h$
![](https://i.imgur.com/X2RXs47.png)


## Regresja liniowa prosta przechodząca przez początek układu odniesienia
![](https://i.imgur.com/m6HYyzS.png)

## Kalibracja
![](https://i.imgur.com/mEoEbvE.png)


## Regresja liniowa prosta - zapis macierzowy
```{r}
# TO DO
```
``