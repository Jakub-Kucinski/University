def zad1a(n):
	if n%2==0:
		return n
	else:
		return -1*n

def zad1b(n):
	suma=0
	for i in range(1,n+1):
		if i%2==0:
			suma=suma+1/i
		else:
			suma=suma+(-1)/i
	return suma

def pot(a,b):
	wyn=1
	while b>0:
		wyn=wyn*a
		b=b-1
	return wyn
	
def zad1c(n, x):
	suma=0
	for i in range(1,n+1):
		suma=suma+i*pot(x,i)
	return suma

def zad2a(a,b):			  #NWW
	if a==b:
		return a
	if a>b:
		maxi=a
		mini=b
	else:
		maxi=b
		mini=a
	for i in range(1,mini+1):
		if maxi*i%mini==0:
			return maxi*i
		
def zad2b(a,b):
	if a==b:
		return(1,1)
	if a>b:
		maxi=a
		mini=b
	else:
		maxi=b
		mini=a
	for i in range(2,mini+1):
		while a%i==0 and b%i==0:
			a=a//i
			b=b//i
	return a,b

def euklides(m,n):
	while n!=m:
		if n>m:
			n=n-m
		else:
			m=m-n
	return n

def zad3(n,L):
	nwd=0
	for i in range(n):					#szukanie maksymalnej wartości w L
		if L[i]>nwd:
			nwd=L[i]
	for i in range(n-1):				#bieganie po n-1 elementach M 
		for j in range(i+1,n):
			pom=euklides(L[i],L[j])
			if pom<nwd:
				nwd=pom
	return nwd

def binarna(a):
	L1=[] 
	L2=[]
	L1.append(a%2)
	a=a//2
	while a>0:
		L1.append(a%2)
		a=a//2
	for i in range(len(L1)):			#odwracanie kolejności L1, return L1[::-1]
		L2.append(L1[len(L1)-i-1])
	return L2
	
def zad4_pajtonowe(n):
	return n==n[::-1]

def zad4(M):
	for i in range(len(M)//2):
		if M[i]!=M[len(M)-i-1]:
			return 0
	return 1

def zad5_pajtonowe(n):			
	return len(set(str(n)))

def zad5(n):
	L=[]
	M=[]
	dl=0
	while n>0:					#wypelnia L kolejnymi cyframi
		L.append(n%10)
		dl+=1
		n=n//10
	for i in range(10):			#wypelnia M zerami
		M.append(0)
	for i in range(dl):			#dodaje 1 do M[n-1] dla liczb n w L
		M[L[i]]+=1
	licz=0
	for i in range(10):			#liczy ile wystapien n>0 jest w M
		if M[i]>0:
			licz+=1
	return licz
	
print(zad5(345161))
