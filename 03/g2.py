#!/usr/bin/env python3

import sys
from random import randint as ri
from random import sample as ss

np = len(sys.argv)

if np not in (2,3,4):
	print( '   *** Usage:', sys.argv[0], '<N> [s_min] [s_max]' )
	exit(0)


N=int(sys.argv[1])
s_min = 30 if np <= 2 else int(sys.argv[2])
s_max = 60 if np <= 3 else int(sys.argv[3])

s_min = (s_min * N) // 100
s_max = (s_max * N) // 100

print(N)
for n in range(N):
	s = ri( s_min, s_max )
	K = ss( range(N), s )
	print( ' '.join( map( str, K ) ) )