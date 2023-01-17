
n<-500;
p<-400;
k<-50;

library(glmnet);
library(bigstep);


     beta<-rep(0,p);
     beta[1:k]<-3.5; 
     
         X<-rnorm(n*p,0,1/sqrt(n));
         X<-matrix(X,nrow=n);
        
         Y=X%*%beta+rnorm(n);
         obj<-cv.glmnet(X,Y, alpha=0, intercept=FALSE, standardize=FALSE);
         betacv<-coefficients(obj, s='lambda.min');
         betacv<-betacv[2:(p+1),1];
         msecv<-sum((betacv-beta)^2)
         lambda<-obj$lambda;
         
         
         lambda<-seq(from=0.0001,by=0.0001, to=0.003)
         obj<-cv.glmnet(X,Y, alpha=0, intercept=FALSE, standardize=FALSE, lambda=lambda);
         betacv<-coefficients(obj, s='lambda.min');
         betacv<-betacv[2:(p+1),1];
         msecv2<-sum((betacv-beta)^2)
        
         
         
         lambdan<-n*lambda;
         l<-length(lambda)
         sureridge<-rep(0,l);
         betaridge<-matrix(rep(0,p*l),nrow=l);
         for (u in 1:l)
         {
          sridge<-solve(t(X)%*%X+lambdan[u]*diag(p));
          trM<-sum(diag(X%*%sridge%*%t(X)));
          betaridge[u,]<-sridge%*%t(X)%*%Y;
           hridge<-sridge%*%t(X)%*%Y;
          sureridge[u]<-sum((X%*%hridge-Y)^2)+2*trM;
         }
         ind<-which(sureridge==min(sureridge));
         mseridge<-sum((betaridge[ind,]-beta)^2);

        obj3<-lm(Y~X-1);
        betals<-obj3$coefficients;
        msels<-sum((betals-beta)^2);

        d<-prepare_data(Y,X);
        wyn<-stepwise(d,crit=mbic2);
        name<-wyn$model;
        ind<-as.numeric(name);
        XmBIC<-X[,ind];
        betamBIC<-rep(0,p);
        betamBIC[ind] = summary(lm(Y ~ XmBIC-1))$coef[,1]
        msemBIC<-sum((betamBIC-beta)^2);


       
        d<-prepare_data(Y,X);
        wyn<-stepwise(d,crit=bic);
        name<-wyn$model;
        ind<-as.numeric(name);
        XmBIC<-X[,ind];
        betamBIC<-rep(0,p);
        betamBIC[ind] = summary(lm(Y ~ XmBIC-1))$coef[,1]
        msemBIC<-sum((betamBIC-beta)^2);


        d<-prepare_data(Y,X);
        wyn<-fast_forward(d,crit=aic);
        name<-wyn$model;
        ind<-as.numeric(name);
        XmBIC<-X[,ind];
        betamBIC<-rep(0,p);
        betamBIC[ind] = summary(lm(Y ~ XmBIC-1))$coef[,1]
        msemBIC<-sum((betamBIC-beta)^2);





         
  
         
         
