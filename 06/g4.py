#!/usr/bin/env python3

import sys
from random import randint as ri

if len(sys.argv) < 2:
    print('   *** Usage: %s <N> [density]' % sys.argv[0] )
    exit(0)

N=int(sys.argv[1])
d=30 if len(sys.argv) < 3 else int(sys.argv[2])

ne = (d * (N*(N-1))//2)//100
G={}

while ne > 0:
    e = ( ri(0,N-1), ri(0,N-1) )
    if e[0] == e[1]: continue

    if G.get( e, -1 ) != -1:
        continue

    G[ e ] = 1
    G[ (e[1],e[0]) ] = 1
    ne = ne -1

W=[ str(ri(10,99)) for x in range(N) ]

print(N)
print( ' '.join(W) )
for i in range(N):
    for j in range(N):
        print( G.get( (i,j), 0 ), end='' )
        if j != N-1: print (' ', end='')
    print( '' )
