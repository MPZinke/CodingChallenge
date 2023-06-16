import math
A,B,C,D,E=" ABCDEFGHIJKLMNOPQRSTUVWXYZ","A23456789TJQK","CDHS",math.factorial,range
def encode(_):
 a,b,c=0,[],[x for x in E(52)]
 for x in _:a=a*27+A.index(x)
 for x in E(52):
  d=D(51-x)
  b+=[B[(e:=c.pop(a//d))%13]+C[e//13]]
  a%=d
 return b
def decode(_):
 a,b,c=[B.index(a[0])+13*C.index(a[1])for a in _],0,""
 for x,d in enumerate(a):
  b+=sum(1 for y in E(x+1,52)if a[y]<d)*D(51-x)
 while b:
  c+=A[b%27]
  b//=27
 return c[::-1]