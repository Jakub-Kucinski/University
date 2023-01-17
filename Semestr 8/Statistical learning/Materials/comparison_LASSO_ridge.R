library('glmnet')

n<-300;
p<-200;
epsilon<-0.05;
p<-delta*n;
beta_sing<-5;
X<-rnorm(n*2*p,0,1/sqrt(n))
X<-matrix(X,nrow=n,ncol=2*p);
rep1<-10;
q<-0.2;
sigma<-1;
Powertot<-rep(0,2*rep1);
Powertot<-matrix(Powertot,nrow=2);
MSE<-rep(0,2*rep1);
MSE<-matrix(MSE,nrow=2);
FDP<-rep(0,2*rep1);
FDP<-matrix(FDP,nrow=2);

for (i in 1:rep1)
{
print(i);
k<-rbinom(1,p,epsilon);
beta<-rep(0,2*p);
ind<-sample(p,k);
beta[ind]<-rep(beta_sing,k);
Y<-X%*%beta+rnorm(n,0,sigma);
obj1<-cv.glmnet(X[,1:p],Y,standardize=FALSE, intercept=FALSE);
hatb1<-coef(obj1, s='lambda.min')[2:(p+1)];
MSE[1,i]<-sum((beta[1:p]-hatb1)^2);
obj<-cv.glmnet(X,Y,standardize=FALSE, intercept=FALSE);
hatb<-coef(obj, s='lambda.min');
w<-abs(hatb[2:(p+1)])-abs(hatb[(p+2):(2*p+1)]);
Power<-function(u){
wyn<-sort(abs(u),decreasing=TRUE,index.return=TRUE);
fd<-cumsum(u[wyn$ix]<0); 
nd<-cumsum(u[wyn$ix]>0);
fdr<-(fd+1)/nd;
u1<-which(fdr<q);
fdp<-0;
tp<-0;
if (length(u1)>0)
{
indopt<-max(u1);
a1<-wyn$ix[1:indopt];
a2<-which(u>0);
a3<-intersect(a1,a2);
tp<-sum(abs(beta[a3])>0);
fd<-length(a3)-tp;
if (length(a3)>0){fdp<-fd/(fd+tp)}}
return(c(tp/k,fdp))}

Result<-Power(w)
Powertot[1,i]<-Result[1];
FDP[1,i]<-Result[2];



obj2<-cv.glmnet(X[,1:p],Y,standardize=FALSE, intercept=FALSE, alpha=0);
hatb2<-coef(obj2, s='lambda.min')[2:(p+1)];
MSE[2,i]<-sum((beta[1:p]-hatb2)^2);
obj<-cv.glmnet(X,Y,standardize=FALSE, intercept=FALSE, alpha=0);
hatb<-coef(obj, s='lambda.min');
w<-abs(hatb[2:(p+1)])-abs(hatb[(p+2):(2*p+1)]);
Power<-function(u){
wyn<-sort(abs(u),decreasing=TRUE,index.return=TRUE);
fd<-cumsum(u[wyn$ix]<0); 
nd<-cumsum(u[wyn$ix]>0);
fdr<-(fd+1)/nd;
fdp<-0;
tp<-0;
u1<-which(fdr<q);
if (length(u1)>0)
{
indopt<-max(u1);
a1<-wyn$ix[1:indopt];
a2<-which(u>0);
a3<-intersect(a1,a2);
hat2b<-rep(0,p);
hat2b[a3]<-hatb2[a3];

tp<-sum(abs(beta[a3])>0);
fd<-length(a3)-tp;
if (length(a3)>0){fdp<-fd/(fd+tp)}}
return(c(tp/k,fdp))}

Result<-Power(w)
Powertot[2,i]<-Result[1];
FDP[2,i]<-Result[2];
}



