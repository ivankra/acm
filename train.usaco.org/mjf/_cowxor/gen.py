from random import *

n = 100000
print "%d" % n

for i in range(0,n):
	print "%d" % randint(0, 2**21 - 1)
