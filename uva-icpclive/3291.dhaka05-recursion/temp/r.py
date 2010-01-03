from random import *
for T in range(0, 100):
	N, S = randint(1,500), ""
	for i in range(0, N):
		S += "%d " % randint(-10, 10)
	print "%d\n%s" % (N, S)
