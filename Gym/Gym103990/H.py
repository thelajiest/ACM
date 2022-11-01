import math

a= int(input())

def power(a,b):
	res = 1
	while(b):
		if(b%2 == 1):
			res=res*a
		a=a*a
		b = b//2
	return res
if a == 0:
	print(1)
else:
	l =1
	r= 20000
	while(l<r):
		print(l,r)
		mid = (l+r+1)//2
		if(power(6,mid)> a):
			r=mid-1
		else:
			l=mid
	print(l+1)
