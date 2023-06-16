import math
A,B,C,D,E=" ABCDEFGHIJKLMNOPQRSTUVWXYZ","A23456789TJQK","CDHS",math.factorial,range
def F(_):
 a,b,c=0,[],[x for x in E(52)]
 for x in _:a=a*27+A.index(x)
 for x in E(52):
  d=D(52-x-1)
  b+=[c.pop(a//d)]
  a%=d
 return b
def G(_):
 a,b=0,""
 for x,c in enumerate(_):
  d=sum(1 for y in E(x+1,52)if _[y]<c)
  a+=d*D(52-x-1)
 for x in E(99):
  if a==0:break
  b+=A[a%27]
  a//=27
 return b[::-1]
decode=lambda _:G([B.index(a[0])+13*C.index(a[1])for a in _])
encode=lambda _:[B[a%13]+C[a//13]for a in F(_)]