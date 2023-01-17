library(lpSolve)

library(Rcpp)
library(glmnet)


gen_beta <- function(k, val = 20, p = 200){
  beta <- rep(0, p)
  beta[1:k] <- val
  return(beta)
}



check_id_con <- function(X, max_k, p = 200, val = 20){
  success <- rep(0,100)
  beta <- rep(0, p)
  
  obj<-rep(1,2*p);
  constmat1 <- cbind(X,-X);
  constmat2 <- cbind(diag(p),matrix(rep(0,p*p),nrow=p));
  constmat3 <- cbind(matrix(rep(0,p*p),nrow=p),diag(p));
  constmat <- rbind(constmat1,constmat2,constmat3);
  consteq <- c(rep('=',n),rep('>=',2*p));
  
  for (k in 1:max_k){
    beta <- gen_beta(k, val = 20, p = p)
    Yn <- X%*%beta
    constright <- c(Yn,rep(0,2*p));
    wyn1 <- lp('min',obj,constmat,consteq,constright);
    wyn <- wyn1$solution[1:p]-wyn1$solution[(p+1):(2*p)];
    success[k] <- (max(abs(wyn-beta))<1E-7)
  }
  return(max(which(success==1)))
}



n <- 100
p <- 200
set.seed(2022)
X <- matrix(rnorm(n * p, 0, 0.1), n, p)
(max_k_id <- check_id_con(X, 100, val = 20, p = p))

beta <- gen_beta(max_k_id, val = 100, p = p)
sb <- abs(sign(beta))
Y <- X%*%beta + rnorm(n)
lambda_vec <- seq(from = 0.01, to = 1, by = 0.001)
res <- matrix(0, length(lambda_vec), 2)
res[,1] <- lambda_vec
for(i in 1:length(lambda_vec)){
  obj <- glmnet(X, Y, alpha = 1, lambda = lambda_vec[i])
  coef <- coefficients(obj)[-1, 1]
  scoef <- abs(sign(coef))
  res[i,2] <- sum(sb != scoef) == 0
}
(min_lambda_zero <- res[min(which(res[,2] == 1)),1])


obj<-cv.glmnet(X,Y);
betacv<-coefficients(obj, s='lambda.min')[2:(p+1),1];
plot(betacv~beta);
sum((betacv-beta)^2)

lambda<-0.5*obj$lambda.min;
obj2<-glmnet(X,Y,lambda=lambda);
betahat<-coefficients(obj2)[2:(p+1)];
plot(betahat~beta)
sum((betahat-beta)^2)

########Adaptive LASSO 1 #######

  W2<-abs(betahat)+0.000001;
  Xtemp<-sweep(X,2,W2,'*');

  obj3=cv.glmnet(Xtemp,Y,intercept=FALSE,standardize=FALSE);

  betaadcv<-coefficients(obj3, s='lambda.min')[2:(p+1),1];
  betahatad=betaadcv * W2;

  plot(betahatad~beta);
  sum((betahatad-beta)^2)

  lambda<-0.08*obj3$lambda.min;
obj4<-glmnet(Xtemp,Y,lambda=lambda, intercept=FALSE, standardize=FALSE);
betahat<-coefficients(obj4)[2:(p+1)]*W2;
plot(betahat~beta)
sum((betahat-beta)^2)


#########skorelowane:LASSO-SLOPE#######
library(mvtnorm)
library(SLOPE)
n=100;
p=150;
k=40;

rho=0.8;
sigma <- matrix(rho,p,p) 
diag(sigma) <- 1
sigma<-sigma;
X <- (rmvnorm(n,numeric(p),sigma))

beta<-rep(0,p);
beta[1:k]<-100;

Y=X%*%beta+rnorm(n);


obj<-cv.glmnet(X,Y);
betacv<-coefficients(obj, s='lambda.min')[2:(p+1),1];
plot(betacv~beta);
sum((betacv-beta)^2)

lambda<-0.09*obj$lambda.min;
obj2<-glmnet(X,Y,lambda=lambda);
betahat<-coefficients(obj2)[2:(p+1)];
plot(betahat~beta)
sum((betahat-beta)^2)

#####adaptive LASSO####
W2<-abs(betahat)+0.000001;
  Xtemp<-sweep(X,2,W2,'*');

  obj3=cv.glmnet(Xtemp,Y,intercept=FALSE,standardize=FALSE);

  betaadcv<-coefficients(obj3, s='lambda.min')[2:(p+1),1];
  betahatad=betaadcv * W2;

  plot(betahatad~beta);
  sum((betahatad-beta)^2)

lambda<-0.04*obj3$lambda.min;
obj4<-glmnet(Xtemp,Y,lambda=lambda, intercept=FALSE, standardize=FALSE);
betahat<-coefficients(obj4)[2:(p+1)]*W2;
plot(betahat~beta)
sum((betahat-beta)^2)


library('SLOPE')
obj3<-SLOPE(X,Y,intercept=FALSE, lambda='bh', q=0.2, scale='none', center=FALSE, alpha=1.4/n);
betaslope<-obj3$coefficients;
sum((betaslope-beta)^2);
plot(betaslope~beta)

W2<-abs(betaslope)+0.000001;
  Xtemp<-sweep(X,2,W2,'*');

obj4<-SLOPE(Xtemp,Y,intercept=FALSE, lambda='bh', q=0.2, scale='none', center=FALSE, alpha=4, solver='admm');
betaslope<-obj4$coefficients*W2;
sum((betaslope-beta)^2);
plot(betaslope~beta)

#######precision matrix##############
rho=0.8;
sigma <- matrix(rho,10,10) 
diag(sigma) <- 1

zeros<-matrix(rep(0,10*10),nrow=10);
Sigma1<-cbind(sigma,zeros,zeros);
Sigma2<-cbind(zeros,sigma,zeros);
Sigma3<-cbind(zeros,zeros,sigma);
Sigma<-rbind(Sigma1,Sigma2,Sigma3);

Omega<-solve(Sigma);

n<-50;

X <- (rmvnorm(n,numeric(30),Sigma))
S=t(X)%*%X/n;
P<-solve(S);
MSE<-sum((Omega-P)^2);

Omega1<-Omega;
P1<-P;
diag(Omega1)=rep(0,30);
diag(P1)<-rep(0,30);
sum((Omega1-P1)^2)


library('glasso');
wyn<-glasso(S,rho=0.3);
MSElasso<-sum((Omega-wyn$wi)^2)
MSElasso

wyn<-glasso(S,rho=0.03);
MSElasso<-sum((Omega-wyn$wi)^2)
MSElasso




