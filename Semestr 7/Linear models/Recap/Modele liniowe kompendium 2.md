# Modele liniowe kompendium 2

###### tags: `ml21` `ćwiczenia` `Zaitseva`


## Estymator metody najmniejeszych kwadratów

$\hat\beta = (X'X)^{-1}X'Y$

```r
X
Y
estbeta = solve(t(X) %*% X) %*% t(X) %*% Y
```

## Predykcja Y


$\hat Y = X\hat\beta$

## Nieobciążony estymator

$s^2 = \frac{1}{n-p} \sum_i (Y_i - \hat Y_i)^2 = \frac{1}{n-p} \sum_i e_i^2$

```r
n
p
reg2 = lm(Y~X, x = TRUE)
s2 = 1/(n-p) * sum(reg2$residuals ** 2)
covariance = s2*(solve(t(reg2$x) %*% reg2$x))
s_beta1 = sqrt(covariance[2, 2])
s_beta1
```


## Własności teoretyczne $\hat \beta$

$\hat \beta \sim N(\beta, \sigma^2 (X' X)^{-1})$
$cov(\hat \beta) = \sigma^2 (X' X)^{-1}$


## Macierz H
Macierz H jest macierzą rzutu ortogonalnego na przestrzeń Lin(X) rozpiętą na kolumnach macierzy eksperymentu.
$H = X (X^TX)^{-1}X^T$
$\hat Y = HY$
$e = Y − \hat Y = (I − H)Y$


## Własności teoretyczne $\hat Y$ i e

$\hat Y \sim N(X \beta, \sigma^2 H)$
$\hat Y = HY$

$e \sim N(0, \sigma^2 (I - H))$
$e = (I - H) Y$

## Testowanie za pomocą testu T
![](https://i.imgur.com/BxiJtfh.png)
![](https://i.imgur.com/VN6xAZN.png)
![](https://i.imgur.com/Lbc29WL.png)

## Przedział ufności
![](https://i.imgur.com/jCwczQr.png)


## Przedział predykcyjny
![](https://i.imgur.com/V7Y0TKk.png)


## Moc testu
```r
n
p
s_betai
true_betai
power = function(n, p, alpha, s_beta, beta1){
  df = n - p
  tc = qt(1-alpha/2, df)
  delta = beta1 / s_beta
  prob1 = function(delta){pt(tc, df, delta)}
  prob2 = function(delta){pt(-tc, df, delta)}
  powerOfBeta = 1 - prob1(delta) + prob2(delta)
  powerOfBeta
}

power_full = power(n, p, 0.05, s_betai, true_betai)
power_full
```

## Analiza wariancji
![](https://i.imgur.com/wDlWaJC.png)

```r
SST <- sum((Y - mean(Y))**2)
dfT <- n-1
SSE <- sum((Y - estY)**2)
dfE <- n-p
SSM <- sum((estY - mean(Y))**2)
dfM <- p-1
```

## Ogólny test F

![](https://i.imgur.com/sARVG15.png)

### Własność 1
![](https://i.imgur.com/saPHadj.png)

### Własność 2
![](https://i.imgur.com/Kyjhm8L.png)

### Własność 3
![](https://i.imgur.com/zY5ggyC.png)

```r
r
p
n

dfEr = n - r
dfEf = n - p
dfM = p - 1

SSEr = sum((fitted(fitr) - Y) * (fitted(fitr) - Y))
SSEf = sum((fitted(fitf) - Y) * (fitted(fitf) - Y))

MSEf = SSEf / dfef

f = ((SSEr - SSEf)/(dfer - dfef))/(MSEf)
f
dfef
fc = qf(1-alpha, dfer-dfef, dfef)
f > fc

pval <- pf(-f, dfEr-dfEf, dfEf) + 1 - pf(f, dfEr-dfEf, dfEf)
pval
```

## Sumy pierwszego i drugiego rodzaju
![](https://i.imgur.com/HoROMcu.png)


## Współczynnik determinacji $R^2$
$R^2 = SSM/SST = 1 − SSE/SST$
![](https://i.imgur.com/Mu8VcDH.png)

![](https://i.imgur.com/yV6bxs0.png)
$\tilde R = 1 − MSE/MST$

## Standaryzacja danych
$\tilde X_i = s(Y) X_i / s(X_i)$
Wtedy:
$\tilde{ \hat \beta_i} = s(X_i) \hat\beta_i / s(Y)$

## Multikolinearność
![](https://i.imgur.com/0jKFQuf.png)

## Model z interakcją
![](https://i.imgur.com/qlYcJST.png)

## Problem wyboru modelu

![](https://i.imgur.com/ebgyMGb.png)

## AIC i BIC

![](https://i.imgur.com/lXE8nFt.png)

## $C_p$ Mallows'a
![](https://i.imgur.com/O120CL9.png)

## Partial regression plots
![](https://i.imgur.com/MT4HSNh.png)
![](https://i.imgur.com/RwGiMMd.png)


## Wenętrzna i zewnętrzna studentyzacja residuów
![](https://i.imgur.com/FMm3WHU.png)
![](https://i.imgur.com/1bYO88E.png)



```r
reg1 = lm(Y~X, dt)
r = residuals(reg1)
r1 = rstandard(reg1) # studentyzacja wewnętrzna
r2 = rstudent(reg1)  # studentyzacja zewnętrzna
plot(1:dim(dt)[1], r1)
plot(1:dim(dt)[1], r2)
```

## Macierz H

![](https://i.imgur.com/o1aRTCC.png)

![](https://i.imgur.com/Tl9gSVi.png)


## Miara DFFITS
![](https://i.imgur.com/fpJDm4v.png)
```r 
reg1 = lm(Y~X, dt)
y = dffits(reg1)
h_value = 2*sqrt(p/n)
```

## Odległość Cook'a
![](https://i.imgur.com/9oJLKxJ.png)
```r 
reg1 = lm(Y~X, dt)
cookd(reg1)
```

## Miara DFBETAS
![](https://i.imgur.com/xanXShW.png)
```r 
dfbetas <- as.data.frame(dfbetas(model))
n <- nrow(mtcars)
#calculate DFBETAS threshold value
thresh <- 2/sqrt(n)
```

## Miary Variance inflation factor oraz Tolerance
![](https://i.imgur.com/HZYkUwV.png)
![](https://i.imgur.com/WmYP5D7.png)
```r 
reg1 = lm(Y~X, dt)
v = vif(reg1)
tolerance = 1/v
tolerance
```