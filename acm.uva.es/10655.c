#include <stdio.h>
#include <string.h>

typedef unsigned long long num;

#define HDIV	65521
#define HSIZE	65536

unsigned htab[HDIV], hgot[HDIV], next[HSIZE], arg[HSIZE], testno, count;
num val[HSIZE], s, p;

num pwr(num x, unsigned n)
{
	num y, z;

	for (z = 1, y = x; n > 0; n >>= 1) {
		if (n & 1) z *= y;
		y *= y;
	}

	return z;
}

num f(unsigned n)
{
	num t;
	unsigned h, i;

	if (n == 0) return 2;
	if (n == 1) return s;

	h = n % HDIV;
	if (hgot[h] != testno) {
		hgot[h] = testno;
		htab[h] = 0;
	} else {
		for (i = htab[h]; i != 0; i = next[i])
			if (arg[i] == n) return val[i];
	}

	if ((n & 1) == 0) {
		i = n >> 1;
		t = f(i);
		t = t * t - 2ULL * pwr(p, i);
	} else {
		i = n >> 1;
		t = f(i) * f(i + 1) - s * pwr(p, i);
	}

	if (count < (HSIZE - 2)) {
		arg[count] = n;
		val[count] = t;
		next[count] = htab[h];
		htab[h] = count++;
	}

	return t;
}

int main()
{
	static char buf[1024];
	unsigned n;
	num r;

	memset(hgot, 0, sizeof(hgot));
	testno = 0;

	while (gets(buf)) {
		if (sscanf(buf, "%llu %llu %u", &s, &p, &n) != 3) break;

		testno++;
		count = 0;

		r = f(n);
		if ((r >> 63) & 1ULL)
			printf("-%llu\n", (~r) + 1ULL);
		else
			printf("%llu\n", r);
	}

	return 0;
}
