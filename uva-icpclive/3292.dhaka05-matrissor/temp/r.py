from random import *

T = 20

print "%d" % T

for dummy1 in range(0, T):
	N = 6
	Q = 100

	print "%d" % N

	R = []
	for i in range(0, N+1):
		R.append(randint(1, 50))

	for i in range(0, N):
		print "%d %d" % (R[i], R[i+1])

	print "%d" % Q
	S = ""
	for i in range(0, 100):
		S += ("%d " % randint(1, 2000))
	print "%s\n" % S

