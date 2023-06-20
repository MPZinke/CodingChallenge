import math
A,C,F,R=" ABCDEFGHIJKLMNOPQRSTUVWXYZ",[a+b for b in"CDHS"for a in"A23456789TJQK"],math.factorial,range
def encode(_):
 a,b,c=0,[],list(R(52))
 for x in _:a=a*27+A.find(x)
 for x in R(52):d=F(51-x);b+=[C[c.pop(a//d)]];a%=d
 return b
def decode(_):
 b,c=0,""
 for x,d in enumerate(a:=[C.index(a)for a in _]):b+=sum(1 for y in R(x+1,52)if a[y]<d)*F(51-x)
 while b:c=A[b%27]+c;b//=27
 return c