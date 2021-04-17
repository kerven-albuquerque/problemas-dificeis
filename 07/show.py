#!/usr/bin/env python3

import matplotlib.pyplot as plt

def file2list( filename ):
	X=[]
	Y=[]
	with open(filename) as A:
		for line in A.readlines():
			x,y = map( int, line.split())
			X.append( x )
			Y.append( y )

	return X, Y

ax, ay = file2list('a.txt')
bx, by = file2list('b.txt')
cx, cy = file2list('c.txt')


plt.scatter( ax, ay, s=50, c='red', label ='Cluster 1')
plt.scatter( bx, by, s=50, c='blue', label ='Cluster 2')
plt.scatter( cx, cy, s=50, c='green', label ='Cluster 3')

plt.show()