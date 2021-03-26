#!/usr/bin/env python3

import sys
from random import randint as ri

if len(sys.argv) < 2:
	print( '   *** Usage:', sys.argv[0], 'N' )
	exit(0)

N=int(sys.argv[1])

print(N)
for x in range(N):
	print( ri(-99,99) )