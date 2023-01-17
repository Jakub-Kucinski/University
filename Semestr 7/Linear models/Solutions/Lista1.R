################ 1)
X = matrix(rnorm(200), 2, 100)
plot(X[1, ], X[2, ])

################ 2)
mu = matrix(c(4,2), 2, 1)
Sigma1 = matrix(c(1, 0.9, 0.9, 1), 2, 2)
Sigma2 = matrix(c(1, -0.9, -0.9, 1), 2, 2)
Sigma3 = matrix(c(9, 0, 0, 1), 2, 2)

CholeskyDecompositionTwoOnTwo <- function(A) 
{
  x = sqrt(A[1,1])
  y = A[2,1]/x
  z = sqrt(A[2,2] - y*y)
  matrix(c(x, y, 0, z), 2, 2)
}

MakeSubtaskOfSecondExercise <- function(X, mu, Sigma)
{
  A = CholeskyDecompositionTwoOnTwo(Sigma)
  X = A %*% X + c(mu[1,1], mu[2,1])
  print(X)
  plot(X[1,], X[2,])
}

MakeSubtaskOfSecondExercise(X, mu, Sigma1)
MakeSubtaskOfSecondExercise(X, mu, Sigma2)
MakeSubtaskOfSecondExercise(X, mu, Sigma3)


################ 3)
CholeskyDecomposition <- function(A) 
{
  dimensionality = dim(A)[1]
  L = matrix(0, dimensionality, dimensionality)
  for (i in 1:dimensionality){
    for (j in 1:i){
      sum = sum(L[i, 1:j] * L[j, 1:j])
      if (i == j){
        L[i,j] = sqrt(A[i,i] - sum)
      }
      else{
        L[i,j] = (1.0 / L[j,j] * (A[i,j] - sum))
      }
    }
  }
  L
}

GetVariances <- function(M)
{
  n = dim(M)[1]
  variances = matrix(0, 1, n)
  for(i in 1:n){
    variances[1, i] = M[i, i]
  }
  variances
}

GetCovariances <- function(M)
{
  n = dim(M)[1]
  covariances = matrix(0, 1, n*n - n)
  k = 1
  for(i in 1:n){
    for(j in 1:n){
      if (i != j){
        covariances[1, k] = M[i, j]
        k = k + 1
      }
    }
  }
  covariances
}

ThirdTask  <- function(num_of_vectors, d)
{
  X = matrix(rnorm(num_of_vectors*d), num_of_vectors, d)
  Sigma = matrix(0.9, d, d)
  for(i in 1:d)
  {
    Sigma[i, i] = 1
  }
  
  A = CholeskyDecomposition(Sigma)
  XDashed = X %*% t(A)
  C = cov(XDashed)
  
  var = GetVariances(C)
  covar = GetCovariances(C)
  print(mean(var))
  print(mean(covar))
  hist(var)
  hist(covar)
}
ThirdTask(200, 100)


