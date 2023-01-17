# # SVG graphics device
# svg("my_plot.svg")

# # Code of the plot
# plot(rnorm(20))

# # Close the graphics device
# dev.off() 

require("car")
require("ggplot2")
library(svglite)
library(broom)
library(MASS)

# Zad 3
#### a)
n = 100
X = matrix(rnorm(200), 2, 100)
Sigma = matrix(c(1, 0.9, 0.9, 1), 2, 2)/100
A = t(chol(Sigma))
X = A %*% X
X = t(X)
Y = 3*X[,1]+rnorm(n,0,1)
plot(X[,1], X[,2])
plot(X[,1], Y)

# svglite("myplot.svg", width = 4, height = 4)
svglite("normal1.svg")
plot(X[,1], X[,2])
dev.off()
svglite("normal2.svg")
plot(X[,1], Y)
dev.off()
# With ggsave()
# ggsave("myplot.svg", width = 8, height = 8, units = "cm")

#### b)
# reduced
reg1 = lm(Y~X[, 1])
# full
reg2 = lm(Y~X)

confint(reg1)
# odrzucamy H0

confint(reg2)
# nie odrzucamy H0

#### c)
reg1 = lm(Y~X[, 1], x = TRUE)
reg2 = lm(Y~X[, 1]+X[, 2], x = TRUE)

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

# Zad 4
#### a)
n = 1000
X = matrix(rnorm(950000, 0, 0.1), n, 950)
e = rnorm(n)
beta = c(3, 3, 3, 3, 3, rep(0, 945))
Y = X %*% beta + e

nvars = c(1, 2, 5, 10, 50, 100, 500, 950)
sse = rep(0, 8)
mse = rep(0, 8)
mse2 = rep(0, 8)
aic = rep(0, 8)
pval1 = rep(0, 8)
pval2 = rep(0, 8)
false_discoveries = rep(0, 8)

for (i in 1:8){
    k = nvars[i]
    Xi = X[, 1:k]
    reg = lm(Y~Xi)
    sse[i] = sum(reg$residuals^2)
    aic[i] = AIC(reg)
    beta_diff = matrix(reg$coefficients[-1]-beta[1:k], k, 1)
    mse[i] = sum((Xi%*%beta_diff)^2)/(n-k+1)
    mse2[i] = mean((Xi%*%beta_diff)^2)
    pval1[i] = summary(reg)$coefficients[2, 4]
    if(i != 1)
        pval2[i] = summary(reg)$coefficients[3, 4]
    if(i != 1)
        false_discoveries[i] = sum(summary(reg)$coefficients[2:min(k, 6), 4]>0.05)
    if(i >= 4)
        false_discoveries[i] = sum(summary(reg)$coefficients[7:(k+1), 4]<0.05) + false_discoveries[i]
}

# Wpisać do macierzy/dataframe'u
nvars
sse
mse
mse2
aic
pval1
pval2
false_discoveries



# Zad 5
data = read.table("./CH06PR15.txt", col.names=c("age", "severity", "anxiety", "satisfaction"))
reg1 = lm(satisfaction~age+severity+anxiety, data)
summary(reg1)

# Zad 6
confint(reg1, level = 0.95)
summary(reg1)

# Zad 7
res = reg1$residuals
pred = predict(reg1)

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
qqline(res)

# Zad 9
dt = read.table('./csdata.txt', col.names=c("id", "GPA", "HSM", "HSS", "HSE", "SATM", "SATV", "SEX"))
reg1 = lm(GPA~HSM+HSS+HSE, dt)
reg2 = lm(GPA~SATM+SATV+HSM+HSS+HSE, dt)

# H_0: b5=b6=0 (SATM and SATV)
#### a)

sse1 = sum(reg1$residuals^2)
sse2 = sum(reg2$residuals^2)
difference = sse1 - sse2
dfEdiff = (224 - 4) - (224 - 6)
dfE2 = 224 - 6
# dfEdiff = an1$`Df`[4] - an2$`Df`[6]
# dfE2 = an2$`Df`[6]
F_test = (difference / dfEdiff) / (sse2 / dfE2)
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
dt = read.table('./csdata.txt', col.names=c("id", "GPA", "HSM", "HSS", "HSE", "SATM", "SATV", "SEX"))
reg1 = lm(GPA~SATM+SATV+HSM+HSE+HSS, dt)
# sumy typu I
anova(reg1)
# sumy typu II
Anova(reg1)

#### a)
reg1 = lm(GPA~SATM+SATV+HSM, dt)
reg2 = lm(GPA~SATM+SATV, dt)
sse1 = sum(reg1$residuals^2)
sse2 = sum(reg2$residuals^2)
sse1; sse2
type_1_SSE_HSM = sse2 - sse1
type_1_SSE_HSM
anova(reg1)$`Sum Sq`[3]

#### b)
# Ostatnie sumy typów I i II są zawsze równe, opisują je dokładnie te same wzory 
# (w obu przypadkach porównujemy model bez ostatniej zmiennej z modelem ze wszystkimi zmiennymi)

# Zad 11
dt = read.table('./csdata.txt', col.names=c("id", "GPA", "HSM", "HSS", "HSE", "SATM", "SATV", "SEX"))
dt$SAT = dt$SATM + dt$SATV
reg1 = lm(GPA~SATM+SATV+SAT, dt)
summary(reg1)

# Już przed wykonaniem eksperymentu możemy podejrzewać, że nic istotnego się nie wydarzy,
# bo w zadaniu 9 pokazaliśmy, że zmienne SATM i SATV nie mają istotnego wpływu na GPA.
# Po wywołaniu summary na naszym modelu widzimy, że nie ma podstaw do odrzucenia H_0 dla SATV,
# ale możemy odrzucić H_0 dla SATM. Zmienna SAT nie została w ogóle użyta przez model,
# bo jest kombinacją liniową SATM i SATV i nie wnosi żandej nowej informacji.
# Widzimy, że ogólnie model jest bardzo słaby, bo wyjaśnia jedynie 0.06337 zmienności
# zmiennej objaśnianej.

# Zad 12
dt = read.table('./csdata.txt', col.names=c("id", "GPA", "HSM", "HSS", "HSE", "SATM", "SATV", "SEX"))

x = lm(HSM~HSS+HSE+SATM+SATV+SEX, dt)
y = lm(GPA~HSS+HSE+SATM+SATV+SEX, dt)
# svglite("HSMvsGPA.svg")
plot(x$residuals, y$residuals, xlab="HSM", ylab="GPA", main = "HSM vs GPA")
# dev.off()

x = lm(HSS~HSM+HSE+SATM+SATV+SEX, dt)
y = lm(GPA~HSM+HSE+SATM+SATV+SEX, dt)
# svglite("HSSvsGPA.svg")
plot(x$residuals, y$residuals, xlab="HSS", ylab="GPA", main = "HSS vs GPA")
# dev.off()

x = lm(HSE~HSM+HSS+SATM+SATV+SEX, dt)
y = lm(GPA~HSM+HSS+SATM+SATV+SEX, dt)
# svglite("HSEvsGPA.svg")
plot(x$residuals, y$residuals, xlab="HSE", ylab="GPA", main = "HSE vs GPA")
# dev.off()

x = lm(SATM~HSM+HSS+HSE+SATV+SEX, dt)
y = lm(GPA~HSM+HSS+HSE+SATV+SEX, dt)
# svglite("SATMvsGPA.svg")
plot(x$residuals, y$residuals, xlab="SATM", ylab="GPA", main = "SATM vs GPA")
# dev.off()

x = lm(SATV~HSM+HSS+HSE+SATM+SEX, dt)
y = lm(GPA~HSM+HSS+HSE+SATM+SEX, dt)
# svglite("SATVvsGPA.svg")
plot(x$residuals, y$residuals, xlab="SATV", ylab="GPA", main = "SATV vs GPA")
# dev.off()

x = lm(SEX~HSM+HSS+HSE+SATM+SATV, dt)
y = lm(GPA~HSM+HSS+HSE+SATM+SATV, dt)
# svglite("SEXvsGPA.svg")
plot(x$residuals, y$residuals, xlab="SEX", ylab="GPA", main = "SEX vs GPA")
# dev.off()

# Zad 13
dt = read.table('./csdata.txt', col.names=c("id", "GPA", "HSM", "HSS", "HSE", "SATM", "SATV", "SEX"))
reg1 = lm(GPA~HSM+HSS+HSE+SATM+SATV+SEX, dt)
r = residuals(reg1)
r1 = rstandard(reg1) # studentyzacja wewntrzna
r2 = rstudent(reg1)  # studentyzacja zewntrzna
# cbind(r, r1, r2)
# svglite("studentyzacjawewnetrzna.svg")
plot(1:dim(dt)[1], r1)
# dev.off()
# svglite("studentyzacjazewnetrzna.svg")
plot(1:dim(dt)[1], r2)
# dev.off()

# Zad 14
dt = read.table('./csdata.txt', col.names=c("id", "GPA", "HSM", "HSS", "HSE", "SATM", "SATV", "SEX"))
reg1 = lm(GPA~HSM+HSS+HSE+SATM+SATV+SEX, dt)
y = dffits(reg1)
p = dim(dt)[2] - 1
n = dim(dt)[1]
h_value = sqrt(p/n)
plot(1:dim(dt)[1], y)
abline(h=2*h_value)
abline(h=-2*h_value)

# Obserwacje leżące poza przedziałem +- 2 * h_value mają znaczący wpływ na predykcję.
# Widzimy, że zdecydowana większość obserwacji leży wewnątrz przedziału,
# ale jest kilkanaście obserwacji wykraczającymi poza ten zakres i mogą być one
# obserwacjami odstającymi lub wpływowymi.

# Zad 15
# Tolerancja to odwrotność VIF i pomaga nam zidentyfikować zjawisko multikolinearności.
# Wartości poniżej 0.1 wskazują na problem z multikolinearnością.
v<-vif(reg1)
tolerance = 1/v
tolerance
# Widzimy, że wszystkie wartości wynosza ponad 0.1, więc w naszych danych
# nie występuje problem multikolinearności.

# Zad 16
dt = read.table('./csdata.txt', col.names=c("id", "GPA", "HSM", "HSS", "HSE", "SATM", "SATV", "SEX"))
reg = lm(GPA~HSM+HSS+HSE+SATM+SATV+SEX, dt)
summary(reg)
AIC(reg)
BIC(reg)
