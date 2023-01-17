# Algorithmic Game Theory

## Nash Equilibrium

### Heuristics

**Definition**

Assignment of strategies to players that are stable - no player wants to unilaterally deviate from the assignment.
Every player has **best response** to the other's strategies.

### Formal definition

2 players, n pure strategies, $R, \, C \in \mathbb{R}^{n\times n}$ (row and column players). It they play $i$-th and $j$-th strategy, they get $R_{i,j}$ and $C_{i,j}$ as outcome.

**Mixed strategy** is a vector $x\in \mathbb{R}^n$, s.t. $\sum_i x_i = 1$, $x_i \geq 0$ for all $1\leq i \leq n$.
If row player plays $x$ and column player plays $y$, then they play $(i,j)$ with probability $x_i \cdot y_j$.

**Expected payoff** for row player equals $$ \sum_{i,j} x_i y_j R_{i,j} = (x, Ry) = x^TRy .$$

**Nash equilibirum** $(x^\star, y^\star)$:
- $\forall_{\bar{x}} \: (\bar{x}, Ry^\star) \leq (x^\star, Ry^\star)$
- $\forall_{\bar{y}} \: (x^\star, C\bar{y}) \leq (x^\star, Cy^\star)$

**$\epsilon$-Nash equilibirum** $(x^\star, y^\star)$: ($R,\, C \in [0,1]^{n\times n}$)
- $\forall_{\bar{x}} \: (\bar{x}, Ry^\star) \leq (x^\star, Ry^\star) + \epsilon$
- $\forall_{\bar{y}} \: (x^\star, C\bar{y}) \leq (x^\star, Cy^\star)+ \epsilon$

**Theroem**
For every 2-player game described above exist Nash equilibium.

**Proof**
Follows from Brouwer fixed-point theorem (continuous function defined on convex and compact subset of $\mathbb{R}^n$ has fixed point).


Mixed strategy is **$k$-uniform** iff $\forall_i \: x_i$ is a multiple of $\frac{1}{k}$.

**Theorem**
For $(x^\star,\, y^\star)$, $\epsilon>0$ and $k \geq \frac{12 \log n}{\epsilon^2}$ exist $k$-uniform $(x', y')$ that
1. $(x', y')$ is $\epsilon$-Nash equilibirum
2. $|(x',Ry') - (x^\star,Ry^\star)| < \epsilon$
3. $|(x',Cy') - (x^\star,Cy^\star)| < \epsilon$

**Claim**
Mixed strategy is a "best response" iff it is a combination of "best response" pure strategies.

### Algorithm for finding Nash equilibrium

#### Reduction to symmetric games

![](https://i.imgur.com/F24QFfv.png)

#### Lemke-Howson algorithm

Idea: search state space of vertices (graph).

#### Class PPAD

## Transferable Utility Games

![](https://i.imgur.com/HwTUpLN.png)

**Example**

![](https://i.imgur.com/mhGybOM.png)

### Idea

We want to divide the prize $v(N)$ between players. $i$-th player gets $x_i$. $x(S) = \sum_{i \in S} x_i$. Ideas below are ideas how to fairly divide the prize. Different ideas of fairness

### Core

![](https://i.imgur.com/gSKLJ7Q.png)

Can be large, small or empty set.

### Shapley Value

![](https://i.imgur.com/iaQKEmr.png)

Unique payoff distribution for the grand coalition. Assigns to player his "average marginal contribution".

#### Derived terms

**Efficiency** $$\sum_{i \in N} \phi_i(N, v) = v(N)$$

**Symmetry** $$\left(\forall_{S\subseteq N, \, i,j \notin S} \: v(S \cup \{i\}) = v(S \cup \{j\})\right) \: \: \Rightarrow \: \: (\phi_i(N) = \phi_j(N))$$

**Linearity** $$\phi_i(v + w) = \phi_i(v) + \phi_i(w)$$ $$\forall_{a \in \mathbb{R}} \: \phi_i(av) = a\phi_i(v)$$

**Null player** $$\left( \forall_{S \subseteq N} \: v(S \cup \{ i \}) = v(S) \right) \: \: \Rightarrow \: \: \phi_i (v) = 0 $$

### Nucleolus

Game is **essential** if $$v(N) \geq \sum_{i\in N} v(\{i\})$$.

**Imputations** $$I(N,v) = \{x \in \mathbb{R}^N \:|\: x(N) = v(N), \forall_{i\in N} \, x_i \geq v(\{i\}) \}$$

**Excess** (the measure of dissatisfaction of the coalition $S$) $$e(S,x) = v(S) - x(S)$$

**Nucleolus**
For every element of $I(N,v)$ we store list of excesses sorted from highest to lowest one. Then we introduce lexicographical order. Nucleouls is the minimal element of this order.

## Fisher's market

## Definition
$|A| = n$, goods, $b_j$ - amount of good $j$
$|B| = m$, buyers, $e_i$ - budget of $i$

**utility** of $i\in B$ for an unit of $j\in A$ is $u_{ij}$

If $i$ gets $x_{ij}$ of good $j$, then his **utility** is $$\sum_{j=1}^n u_{ij}x_{ij} = u_i(x) $$

**prices** $p = (p_1, \ldots, p_n)$

**allocation** $x^i\in [0,1]^n$, $i=1, \ldots, m$.

### Market equilibrium

**affordable** $p \circ x^i \leq e_i$

**demand** $$x^i \in \text{Demand}_i(p) = \text{argmax}_{px \leq e_i} u_i(x)$$

**market clearing** $\forall_{j\in A} \sum_{i\in B} x^i(j) = b_j$

## Flows

## Mechanism Design

![](https://i.imgur.com/iO6vMpt.png)

$A$ alternatives

$I$ voters $|I|=n$
$L$ total orders on $A$ (permutations)
$\succ \in L$ antisymmetric and transitive

$a\succ_i b$: i perfers a to b

$F: L^n \rightarrow L$ social welfare function
$f: L^n \rightarrow A$ social choice function

### Terms

$F$ is **unanimous** iff $\forall_{\succ \in L} F(\succ, \ldots, \succ) = \, \succ$

Voter $i$ is **dictator** in $F$ iff $\forall_{\succ_1,\ldots, \succ_n \in L} F(\succ_1, \ldots, \succ_n) = \succ_i$
$F$ is a **dictatorship** iff there exists a dictator.

**independence of irrelevant alternatives**
![](https://i.imgur.com/RJxqRks.png)

### Arrow theorem

If $|A| \geq 3$ and a social welfare function satisifes both unanimity and independence of irrelevant alternatives, then $F$ is a dictatorship.

### Manipulation

Social welfare function $f$ can be **strategically manipulated** by voter $i$ iff $\exists_{\succ_1, \ldots, \succ_n \in L}$ and exists $\succ_i'\in L$ such that we have $a \prec_i a'$ and $a = f(\succ_1, \ldots, \succ_n)$ and $a'=f(\succ_1, \ldots,\succ_i',\ldots, \succ_n)$.

$f$ is **incentive compatible** if it cannot be manipulated.

$i$ is a **dictator** in $f$ iff $\left(\forall_{\succ_1, \ldots , \succ_n \in L} \forall_{a\neq b} \; a\succ_i b\right) \Rightarrow f(\succ_1, \ldots , \succ_n) = a$

#### Gibbard theorem

Let $f$ be an incentive compatible social choice function onto $A$, where $|A| \geq 3$, then $f$ is a dictatorship.

## Mechanisms with money

### Single item auction

Second price auction is truthful.

$v_i$ - true value of item for player $i$ $$u_i = \begin{cases}v_i - \textrm{payment}, & \textrm{ if } i \textrm{ wins} \\ 0 & \textrm{otherwise} \end{cases}$$

### DR mechanism

![](https://i.imgur.com/fIyi8XH.png)


### Incentive compatibility

![](https://i.imgur.com/5riLxC2.png)

### VCG Mechanism

![](https://i.imgur.com/Y5fb9Xs.png)

![](https://i.imgur.com/rvtrd4G.png)

![](https://i.imgur.com/7yzDfio.png)

![](https://i.imgur.com/K5Lf1Gt.png)

![](https://i.imgur.com/2k4JFK6.png)

### Profit Maximization in Mechanism Design

![](https://i.imgur.com/hGTwkcn.png)

![](https://i.imgur.com/f5Lmwku.png)

#### Bayesian Optimal Mechanism Design

![](https://i.imgur.com/U7qSCfI.png)

##### Virtualn Valuations, Virtual Surplus and Expected Profit

![](https://i.imgur.com/jWmrAwE.png)

![](https://i.imgur.com/jO4f07o.png)

![](https://i.imgur.com/ss37DHV.png)

![](https://i.imgur.com/00e9rWA.png)

The hazard rate of a distribution is defined as $f(z)/(1 − F(z))$. If the hazard rate is monotone nondecreasing, then the virtual valuations are monotone nondecreasing as well.

![](https://i.imgur.com/kJourDY.png)

## Mechanisms without money

![](https://i.imgur.com/Onf2IMT.png)

![](https://i.imgur.com/WWa5dgS.png)

**strategy-proof** dominant strategy is to tell the truth

**unanimous** $(\forall_{i,j} p_i=p_j) \:\: \Rightarrow \:\: f(\preccurlyeq_1, \ldots, \preccurlyeq_n)=p_i$

**Pareto-optimal** 
![](https://i.imgur.com/l5lcx83.png)

![](https://i.imgur.com/wzZsxoj.png)

Choosing k-th smallest peak is strategy-proof.

### House allocation (kidney exchange)
$|N|=n$ agents, each has a house (kidney)
$x\succ_i y$ : i prefers x over y


![](https://i.imgur.com/loY24Cf.png)

![](https://i.imgur.com/a6cyUk3.png)

### Stable matchings

![](https://i.imgur.com/228u7Rd.png)

![](https://i.imgur.com/qe8WKcR.png)

Mechanism is strategy proof for men and not for women.

## Combinatorial Auctions

![](https://i.imgur.com/BWj1uGJ.jpg)

![](https://i.imgur.com/29zs0RH.png)

![](https://i.imgur.com/EQMNfcr.jpg)



### Walrasian Equilibrium

![](https://i.imgur.com/Ly9obhX.png)

![](https://i.imgur.com/TqUm8ez.png)

## Nonatomic Selfish Routing

![](https://i.imgur.com/hrZWq5z.png)

![](https://i.imgur.com/ePCavcc.png)
![](https://i.imgur.com/wWv4JCT.png)

![](https://i.imgur.com/9g3WbZK.png)


![](https://i.imgur.com/BDF9wfW.png)


![](https://i.imgur.com/nPkPp6I.png)
![](https://i.imgur.com/5Y7IQCO.png)

**Price of anarchy (POA)**
![](https://i.imgur.com/OZgjHJN.png)

Examples:
![](https://i.imgur.com/2JdXcP6.png)
![](https://i.imgur.com/oREG2rv.png)


**Potential of flow f**
![](https://i.imgur.com/OiTxUdn.png)
![](https://i.imgur.com/viLRMKC.png)

![](https://i.imgur.com/6SkUYPz.png)

![](https://i.imgur.com/M1AyVfz.png)

## Cost sharing

![](https://i.imgur.com/VajYB74.png)

![](https://i.imgur.com/rinxpBI.png)

![](https://i.imgur.com/63SQHso.png)

![](https://i.imgur.com/c8v327v.png)

### Cost sharing scheme

**cost-sharing scheme**
![](https://i.imgur.com/ZAFgqhF.png)

**cross-monotone**
![](https://i.imgur.com/vtHPN04.png)
*Cross-monotonicity* property captures the notion that agents should not be penalized as the serviced set grows.

![](https://i.imgur.com/acd8S7t.png)

![](https://i.imgur.com/l1z9YSJ.png)



