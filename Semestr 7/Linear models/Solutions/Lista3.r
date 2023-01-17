# Zad 1
alpha = 0.05
deg = 10
# a) 
tc = qt(p=1-alpha/2, df=deg)
# b)
Fc = qf(p=1-alpha, df1 = 1, df2 = deg)
# c)
Fc_sqrt = sqrt(Fc)
print(Fc_sqrt == tc)

# Zad 3
data = read.table("/home/kuba/Documents/UWr/Modele-Liniowe/List3/Tabela1_6.txt", col.names=c("id", "GPA", "IQ", "gender", "pstest"))
# a)
reg1 = lm(GPA~IQ, data)
summary(reg1)
predictedGPA = predict.lm(reg1, data.frame(IQ=c(data$IQ)), interval = "confidence", level=0.95)[, 1]
SST = sum((data$GPA - mean(data$GPA))^2)
SSE = sum((data$GPA - predictedGPA)^2)
R2 = 1 - SSE/ SST
R2


# b)
predict.lm(reg1, data.frame(IQ=c(100)), interval = "prediction", level=0.90)

# c)
x = data$IQ
y = data$GPA
newx = seq(min(x),max(x),by = 0.05)
conf_interval = predict(reg1, newdata=data.frame(IQ=newx), interval="prediction",level = 0.95)
plot(x, y, ylim=c(0, 15),  ylab="GPA", xlab="IQ")
abline(reg1, col="lightblue")
matlines(newx, conf_interval[,2:3], col = "blue", lty=25)


# Zad 4
data = read.table("/home/kuba/Documents/UWr/Modele-Liniowe/List3/Tabela1_6.txt", col.names=c("id", "GPA", "IQ", "gender", "pstest"))
# a,b)
reg2 = lm(GPA~pstest, data)
summary(reg2)
predictedGPA = predict.lm(reg2, data.frame(pstest=c(data$pstest)), interval = "confidence", level=0.95)[, 1]
SST = sum((data$GPA - mean(data$GPA))^2)
SSE = sum((data$GPA - predictedGPA)^2)
R2 = 1 - SSE/ SST
R2

# c)
predict.lm(reg2, data.frame(pstest=c(60)), interval = "prediction", level=0.90)

# d)
x = data$pstest
y = data$GPA
newx = seq(min(x),max(x),by = 0.05)
conf_interval = predict(reg2, newdata=data.frame(pstest=newx), interval="prediction",level = 0.95)
plot(x, y, ylim=c(0, 15),  ylab="GPA", xlab="Piers-Harris score")
abline(reg2, col="lightblue")
matlines(newx, conf_interval[,2:3], col = "blue", lty=25)

# e)


# Zad 5
data = read.table("/home/kuba/Documents/UWr/Modele-Liniowe/List3/CH01PR20.txt", col.names=c("hours", "copiers"))
reg1 = lm(hours~copiers, data)

# a)
r<-residuals(reg1)
sum(r)

# b)
plot(r~data$copiers, ylab="residuals", xlab="number of copiers")
# abline(h = 0)

# c)
x<-seq(1:dim(data)[1])
plot(r~x)

# d)
h<-hist(r, breaks = seq(min(r)-0.1,max(r)+0.1,length.out = 12));
m<-mean(r);
s<-sd(r);
xfit<-seq(min(r),max(r),length=40);
d<-dnorm(xfit,m,s);
d <- d*diff(h$mids[1:2])*length(r) 
lines(d~xfit, col='blue')


# Zad 6
data2 = read.table("/home/kuba/Documents/UWr/Modele-Liniowe/List3/CH01PR20.txt", col.names=c("hours", "copiers"))
data2[1, 1] = 2000
reg2 = lm(hours~copiers, data2)

# a)
summary(reg1)
summary(reg2)

# b)
r<-residuals(reg2)
plot(r~data$copiers, ylab="residuals", xlab="number of copiers")

x<-seq(1:dim(data)[1])
plot(r~x)

h<-hist(r, breaks = seq(min(r)-0.1,max(r)+0.1,length.out = 12));
m<-mean(r);
s<-sd(r);
xfit<-seq(min(r),max(r),length=40);
d<-dnorm(xfit,m,s);
d <- d*diff(h$mids[1:2])*length(r) 
lines(d~xfit, col='blue')


# Zad 7
data = read.table("/home/kuba/Documents/UWr/Modele-Liniowe/List3/CH03PR15.txt", col.names=c("Y", "X"))
reg1 = lm(Y~X, data)
summary(reg1)


# Zad 8
x = data$X
y = data$Y
newx = seq(min(x),max(x),by = 0.05)
conf_interval = predict(reg1, newdata=data.frame(X=newx), interval="prediction",level = 0.95)
plot(x, y, xlab="time", ylim=c(-1.5, 3.5), ylab="solution concentration")
matlines(newx, conf_interval[,1], col = "lightblue", lty=25)
matlines(newx, conf_interval[,2:3], col = "blue", lty=25)

real = data$Y
pred = predict.lm(reg1, data.frame(X=data$X), interval = "prediction", level=0.95)[, 1]
cor(real, pred, method ="pearson")


# Zad 9
require(MASS)
boxcox(data$Y~data$X)


# Zad 10
data = read.table("/home/kuba/Documents/UWr/Modele-Liniowe/List3/CH03PR15.txt", col.names=c("Y", "X"))
data$Y = log(data$Y)
reg1 = lm(Y~X, data)
summary(reg1)

x = data$X
y = data$Y
newx = seq(min(x),max(x),by = 0.05)
conf_interval = predict(reg1, newdata=data.frame(X=newx), interval="prediction",level = 0.95)
plot(x, y, ylim=c(-3, 1.3), xlab="time", ylab="log solution concentration")
matlines(newx, conf_interval[,1], col = "lightblue", lty=25)
matlines(newx, conf_interval[,2:3], col = "blue", lty=25)

real = data$Y
pred = predict.lm(reg1, data.frame(X=data$X), interval = "prediction", level=0.95)[, 1]
cor(real, pred, method ="pearson")


# Zad 11
data = read.table("/home/kuba/Documents/UWr/Modele-Liniowe/List3/CH03PR15.txt", col.names=c("Y", "X"))
data$Y = log(data$Y)
reg1 = lm(Y~X, data)
x = data$X
y = data$Y
newx = seq(min(x),max(x),by = 0.05)
conf_interval = predict(reg1, newdata=data.frame(X=newx), interval="prediction",level = 0.95)
pred = predict.lm(reg1, data.frame(X=data$X), interval = "prediction", level=0.95)[, 1]

data = read.table("/home/kuba/Documents/UWr/Modele-Liniowe/List3/CH03PR15.txt", col.names=c("Y", "X"))
reg1 = lm(Y~X, data)
x = data$X
y = data$Y
newx = seq(min(x),max(x),by = 0.05)
plot(x, y, ylim=c(0, 4), xlab="time", ylab="solution concentration")
matlines(newx, exp(conf_interval[,1]), col = "lightblue", lty=25)
matlines(newx, exp(conf_interval[,2:3]), col = "blue", lty=25)

cor(data$Y, exp(pred), method ="pearson")


# Zad 12
data = read.table("/home/s/2018/s309881/Dokumenty/Modele-Liniowe/Lista3/CH03PR15.txt", col.names=c("Y", "X"))
data$X = (data$X)**(-0.5)
data$Y = data$Y
reg1 = lm(Y~X, data)
summary(reg1)

x = data$X
y = data$Y
newx = seq(min(x),max(x)+0.05,by = 0.05)
conf_interval = predict(reg1, newdata=data.frame(X=newx), interval="prediction",level = 0.95)
plot(x, y, ylim=c(-0.5, 3.5), xlab="time^(-0.5)", ylab="solution concentration")
matlines(newx, conf_interval[,1], col = "lightblue", lty=25)
matlines(newx, conf_interval[,2:3], col = "blue", lty=25)

real = data$Y
pred = predict.lm(reg1, data.frame(X=data$X), interval = "prediction", level=0.95)[, 1]

cor(real, pred, method ="pearson")


# --------------------------------------------------------------------------------------------------------------
data = read.table("/home/s/2018/s309881/Dokumenty/Modele-Liniowe/Lista3/CH03PR15.txt", col.names=c("Y", "X"))
data$X = (data$X)^(-0.5)
data$Y = data$Y
reg1 = lm(Y~X, data)
x = data$X
y = data$Y
newx = seq(min(x)-0.01,max(x)+0.01,by = 0.01)
conf_interval = predict(reg1, newdata=data.frame(X=newx), interval="prediction",level = 0.95)
pred = predict.lm(reg1, data.frame(X=data$X), interval = "prediction", level=0.95)[, 1]

data = read.table("/home/s/2018/s309881/Dokumenty/Modele-Liniowe/Lista3/CH03PR15.txt", col.names=c("Y", "X"))
reg1 = lm(Y~X, data)
x = data$X
y = data$Y
newx = newx^(-2)
plot(x, y, ylim=c(-0.5, 3.5), xlab="time", ylab="solution concentration")
matlines(newx, conf_interval[,1], col = "lightblue", lty=25)
matlines(newx, conf_interval[,2:3], col = "blue", lty=25)

cor(data$Y, pred, method ="pearson")

