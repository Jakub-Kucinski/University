data = read.table("http://www.math.uni.wroc.pl/~mkos/Modele_liniowe/CH01PR20.txt", col.names=c("hours", "copiers"))

##### 1
plot(hours~copiers, data, ylab="Spent hours", xlab="Number of copiers")
abline(lm(hours~copiers, data))

##### 2
reg1 = lm(hours~copiers, data)
summary(reg1)
confint(reg1, level=0.95)
# plot(reg1)

##### 3
newdata = data.frame(copiers=c(11))
predict.lm(reg1, newdata, interval = "confidence", level=0.95)

##### 4
predict.lm(reg1, newdata, interval = "prediction", level=0.95)

##### 5
v1 = predict(reg1, interval = "prediction")
v1down = sort(v1[,2])
v1up = sort(v1[,3])
# v2 = predict(reg1, interval = "confidence")
# v2down = sort(v2[,2])
# v2up = sort(v2[,3])
m1 = sort(v1[,1])
copiers1 = sort(data$copiers)
hours1 = sort(data$hours)
plot(copiers1, m1, type='l', ylim=c(0,165),  ylab="Spent hours", xlab="Number of copiers")
points(data$copiers, data$hours)
points(copiers1, v1up, type='l', col='red')
points(copiers1, v1down, type='l', col='red')
dim(data)

##### 6
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
# a)
n = 40
sig2 = 120
ssx = 1000
alpha = 0.05
beta1 = 1
power(n, sig2, ssx, alpha, beta1)
# b)
beta1 = seq(from=-2.0, to=2.0, by=0.01)
plotData = power(n, sig2, ssx, alpha, beta1)
plot(beta1, plotData, type='l', ylim=c(0,1), ylab="Test power", xlab="beta1")
abline(h=0.05, col="red")

##### 7
n = 200
X = rnorm(n, 0, 1/n)
alpha = 0.05
sig2 = 1
ssx = sum((X - mean(X))^2)

# a)
beta1 = 0
rejected = 0
y_num = 1000 #1000
for (i in 1:y_num){
  Y = 5 + beta1* X + rnorm(n, 0, 1)
  reg1 = lm(Y~X)
  b0 = coef(reg1)[1]
  b1 = coef(reg1)[2]
  s2 = 1/(n-2) * sum((Y - b0 - b1 * X)^2)
  s2b = s2 / sum((X - mean(X))^2)
  t = (b1 - 0) / sqrt(s2b)
  tc = qt(1 - alpha/2, n - 2)
  if (abs(t) > tc) {
    rejected = rejected + 1
  }
}
rejected
# powinno wyjść około 5% z 1000 czylo 50 - ok

# b)
beta1 = 0
rejected = 0
y_num = 1000 #1000
for (i in 1:y_num){
  Y = 5 + beta1* X + rexp(n, 1)
  reg1 = lm(Y~X)
  b0 = coef(reg1)[1]
  b1 = coef(reg1)[2]
  s2 = 1/(n-2) * sum((Y - b0 - b1 * X)^2)
  s2b = s2 / sum((X - mean(X))^2)
  t = (b1 - 0) / sqrt(s2b)
  tc = qt(1 - alpha/2, n - 2)
  if (abs(t) > tc) {
    rejected = rejected + 1
  }
}
rejected
# powinno wyjść około 5% z 1000 czylo 50 - ok

# c)
beta1 = 1.5
rejected = 0
rejected2 = 0
rejected3 = 0
y_num = 1000 #1000
for (i in 1:y_num){
  Y = 5 + beta1* X + rnorm(n, 0, 1)
  reg1 = lm(Y~X)
  b0 = coef(reg1)[1]
  b1 = coef(reg1)[2]
  s2 = 1/(n-2) * sum((Y - b0 - b1 * X)^2)
  s2b = s2 / sum((X - mean(X))^2)
  t = (b1 - 0) / sqrt(s2b)
  tc = qt(1 - alpha/2, n - 2)
  if (abs(t) > tc) {
    rejected = rejected + 1
  }
  if (2 * pt(t, n-2) < 0.05){
    rejected2 = rejected2 + 1
  }
  if (summary(reg1)$coefficient[8] < 0.05){
    rejected3 = rejected3 + 1
  }
  # print(summary(reg1))
  # print(t)
  # print(2 * pt(t, n-2))
  # print(tc)
}
rejected
rejected2
rejected3
power(n, sig2, ssx, alpha, beta1)

# d)
beta1 = 1.5
rejected = 0
y_num = 1000 #1000
for (i in 1:y_num){
  Y = 5 + beta1* X + rexp(n, 1)
  reg1 = lm(Y~X)
  b0 = coef(reg1)[1]
  b1 = coef(reg1)[2]
  s2 = 1/(n-2) * sum((Y - b0 - b1 * X)^2)
  s2b = s2 / sum((X - mean(X))^2)
  t = (b1 - 0) / sqrt(s2b)
  tc = qt(1 - alpha/2, n - 2)
  if (abs(t) > tc) {
    rejected = rejected + 1
  }
}
rejected
power(n, sig2, ssx, alpha, beta1)

