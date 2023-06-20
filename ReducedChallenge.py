import math
A,B,C,D=" ABCDEFGHIJKLMNOPQRSTUVWXYZ",[a+b for b in"CDHS"for a in"A23456789TJQK"],math.factorial,range
def encode(_):
 a,b,c=0,[],list(D(52))
 for x in _:a=a*27+A.find(x)
 for x in D(52):d=C(51-x);b+=[B[c.pop(a//d)]];a%=d
 return b
def decode(_):
 a,b,c=[B.index(a)for a in _],0,""
 for x,d in enumerate(a):b+=sum(1 for y in D(x+1,52)if a[y]<d)*C(51-x)
 while b:c=A[b%27]+c;b//=27
 return c