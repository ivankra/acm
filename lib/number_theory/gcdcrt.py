# Implements binary GCD
def gcd(a, b):
	a, b, s = abs(a), abs(b), 0

	if a == 0 and b == 0:
		raise "gcd(0,0) is undefined"

	while ((a | b) & 1) == 0:
		a, b, s = a >> 1, b >> 1, s + 1

	while True:
		if a == 0 or b == 0: return max(a, b) << s

		while (a & 1) == 0: a >>= 1
		while (b & 1) == 0: b >>= 1

		if a > b:
			a -= b
		else:
			b -= a

def lcm(a, b):
	return (a / gcd(a, b)) * b

# gcdext(a, b) -> (d, x, y)
# ax + by = d = (a,b)
def gcdext(a, b):
	if a < 0:
		s = gcdext(-a, b)
		return (s[0], -s[1], s[2])
	elif b < 0:
		s = gcdext(a, -b)
		return (s[0], s[1], -s[2])
	elif b == 0:
		if a == 0: raise "gcdext(0,0) is undefined"
		return (a, 1, 0)
	else:
		s = gcdext(b, a % b)
		return (s[0], s[2], s[1] - (a / b) * s[2])

# Returns modular inverse of a mod m, or None if it doesn't exist
def modinv(a, m):
	s = gcdext(a, m)
	if s[0] == 1: return s[1] % m

# Solves x = a1 (mod m1), x = a2 (mod m2)
def crt_old(a1, m1, a2, m2):
	b = gcdext(m1, m2)

	if (abs(a2 - a1) % b[0]) != 0:
		return None

	m = (m1 / b[0]) * m2
	return ((a1 + (m1 / b[0]) * b[1] * (a2 - a1)) % m, m)

# Solves the system: x = a_i (mod m_i).
# Input: e = [(a_1, m_1), (a_2, m_2), ..., (a_n, m_n)]
# Output: None, or pair (a, m), indicating that x = a (mod m)
def crt(e):
	s = (0, 1)

	for t in e:
		b = gcdext(s[1], t[1])
		if (abs(t[0] - s[0]) % b[0]) != 0: return None

		m = (s[1] / b[0]) * t[1]
		s = ((s[0] + (s[1] / b[0]) * b[1] * (t[0] - s[0])) % m, m)

	return s

### Examples

# An old woman goes to market and a horse steps on her basket and crashes
# the eggs. The rider offers to pay for the damages and asks her how many eggs
# she had brought. She does not remember the exact number, but when she had
# taken them out two at a time, there was one egg left. The same happened when
# she picked them out three, four, five, and six at a time, but when she took
# them seven at a time they came out even. What is the smallest number of eggs
# she could have had?
print crt([(1, 2), (1, 3), (1, 4), (1, 5), (1, 6), (0, 7)])[0]

# There are certain things whose number is unknown. Repeatedly divided by 3,
# the remainder is 2; by 5 the remainder is 3; and by 7 the remainder is 2.
# What will be the number?
print "%d + %dt" % crt([(2, 3), (3, 5), (2, 7)])
