library("data.table")
require("car")

# Zad 3
n = 100
X = matrix(rnorm(200), 2, 100)
Sigma = matrix(c(1, 0.9, 0.9, 1), 2, 2)/100
A = t(chol(Sigma))
X = A %*% X
X = t(X)

#### a)
Y = 3*X[,1]+rnorm(n,0,1)

#### b)
# reduced
reg1 = lm(Y~X[, 1])
# full
reg2 = lm(Y~X[, 1]+X[, 2])

confint(reg1)[2,]
tc1 = qt(0.975, n-2)
t1 = reg1$coefficients[2]
t1 > tc1
# odrzucamy H0

confint(reg2)[2,]
tc2 = qt(0.975, n-3)
t2 = reg2$coefficients[3]
t2 > tc2
# nie odrzucamy H0

#### c)
reg1 <- lm(Y~X[, 1], x = TRUE)
reg2 <- lm(Y~X[, 1]+X[, 2], x = TRUE)

s2 = 1/(n-2) * sum(reg1$residuals ** 2)
s_red_beta1 = sqrt(s2*(solve(t(reg1$x) %*% reg1$x))[2, 2])
s_red_beta1
s2 = 1/(n-3) * sum(reg2$residuals ** 2)
s_full_beta1 = sqrt(s2*(solve(t(reg2$x) %*% reg2$x))[2, 2])
s_full_beta1

power = function(n, p, alpha, s_beta, beta1){
  df = n - p
  tc = qt(1-alpha/2, df)
  delta = beta1 / s_beta
  prob1 = function(delta){pt(tc, df, delta)}
  prob2 = function(delta){pt(-tc, df, delta)}
  powerOfBeta = 1 - prob1(delta) + prob2(delta)
  powerOfBeta
}
power_red = power(n, 2, 0.05, s_red_beta1, 3.0)
power_red
power_full = power(n, 3, 0.05, s_full_beta1, 3.0)
power_full


#### d)
k = 1000
x1 = 0
x2 = 0
red_betas = rep(0, k)
full_betas = rep(0, k)
for(i in 1:k){
  e = rnorm(n, 0, 1)
  Y = 3*X[, 1] + e
  reg1 = lm(Y~X[, 1])
  reg2 = lm(Y~X[, 1]+X[, 2])
  interval1 = confint(reg1)[2,]
  interval2 = confint(reg2)[2,]
  if(0>=interval1[1] && 0<=interval1[2])
    x1 = x1+1
  if(0>=interval2[1] && 0<=interval2[2])
    x2 = x2+1
  red_betas[i] = reg1$coefficients[2]
  full_betas[i] = reg2$coefficients[2]
}
sd(red_betas)
sd(full_betas)
power_red_exp = 1-x1/k
power_red_exp
power_full_exp = 1-x2/k
power_full_exp


# Zad 5
data = read.table("/home/kuba/Documents/UWr/Modele-Liniowe/List4/CH06PR15.txt", col.names=c("age", "severity", "anxiety", "satisfaction"))
reg1<-lm(satisfaction~age+severity+anxiety, data)
summary(reg1)

# Zad 6
confint(reg1, level = 0.95)
summary(reg1)

# Zad 7
res <- reg1$residuals
pred <- predict(reg1)

plot(pred, res)
abline(h=0, col="blue")
plot(data$age, res)
abline(h=0, col="blue")
plot(data$severity, res)
abline(h=0, col="blue")
plot(data$anxiety, res)
abline(h=0, col="blue")

# Zad 8
shapiro.test(res)
qqnorm(res)

# Zad 9
dt<-read.table('/home/kuba/Documents/UWr/Modele-Liniowe/List4/csdata.txt', col.names=c("id", "GPA", "HSM", "HSS", "HSE", "SATM", "SATV", "SEX"))
reg1 <- lm(GPA~HSM+HSS+HSE, dt)
reg2 <- lm(GPA~SATM+SATV+HSM+HSS+HSE, dt)

# H_0: b5=b6=0 (SATM and SATV)
#### a)
an1 = anova(reg1)
an2 = anova(reg2)
# sse1 = sum(an1$`Sum Sq`[1:3])
# sse2 = sum(an2$`Sum Sq`[1:5])
ss1 = an1$`Sum Sq`[4]
ss2 = an2$`Sum Sq`[6]
difference = ss1 - ss2
dfEdiff = an1$`Df`[4] - an2$`Df`[6]
dfE2 = an2$`Df`[6]
F_test = (difference / dfEdiff) / (ss2 / dfE2)
F_test
ft = qf(0.95, dfEdiff, dfE2)
ft
F_test > ft
pval = 1 - pf(F_test, dfEdiff, dfE2)
pval
pval < 0.05
# Nie odrzucamy hipotezy zerowej - uznajemy, że model zredukowany jest poprawny

#### b)
anova(reg1, reg2)
# p-wartość wynosi 0.3882 czyli tyle samo co w poprzednim podpunkcie

# Zad 10
reg1 <- lm(GPA~SATM+SATV+HSM+HSE+HSS, dt)
# I sums of squares (second column)
anova(reg1)
# II sums of squares (second column)
Anova(reg1)

# a)
reg1_test <- lm(GPA~SATM+SATV+HSM, dt2)
reg2_test <- lm(GPA~SATM+SATV, dt2)
an1 <- anova(reg1_test)
an2 <- anova(reg2_test)
sse1 <- sum(an1$`Sum Sq`[1:3])
sse2 <- sum(an2$`Sum Sq`[1:2])
type_1_SSE_HSM <- sse1 - sse2
type_1_SSE_HSM
# and it is actually the sum of 1 type for HSM 
# (we can read it from the function anova() )

# b)

# Yes, in this case it is the HSM and in general it is always the last in
# order of the predictors. This is due to the equality between
# sums of 1 and 2 type.
