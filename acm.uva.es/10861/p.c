#include <stdio.h>
#include <string.h>

struct {
	int m, s[64];
} shapes[1024];

struct {
	int a, cycle, shape;
	int sub[64], nsub;
} block[64];

int n, nrshapes;

int result[64];

int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71 };
int nprimes = 20;

int fact_tab[64][32];

void mkfact()
{
	int i, j, t;

	memset(fact_tab, 0, sizeof(fact_tab));

	for (i = 2; i < 64; i++) {
		for (j = 0; j < nprimes; j++)
			fact_tab[i][j] = fact_tab[i - 1][j];

		for (t = i, j = 0; t > 1; j++) {
			while ((t % primes[j]) == 0) {
				t /= primes[j];
				fact_tab[i][j]++;
			}
		}
	}

}

void divnum(int x)
{
	int i;

	for (i = 0; x > 1 && i < nprimes; i++) {
		while ((x % primes[i]) == 0) {
			x /= primes[i];
			result[i]--;
		}
	}
}

void mulfact(int f)
{
	int i;

	if (f >= 0) {
		for (i = 0; i < nprimes; i++)
			result[i] += fact_tab[f][i];
	} else {
		f = -f;
		for (i = 0; i < nprimes; i++)
			result[i] -= fact_tab[f][i];
	}
}

void sort(int a[], int m)
{
	int i, j, t;

	for (i = 1; i < m; i++) {
		for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
			a[j + 1] = a[j];
		a[j + 1] = t;
	}
}

int getshape(int x)
{
	int i;

	if (block[x].shape >= 0)
		return block[x].shape;

	for (block[x].nsub = 0, i = 0; i < n; i++) {
		if (block[i].a != x || i == x || block[i].cycle != 0)
			continue;

		block[x].sub[block[x].nsub++] = getshape(i);
	}

	sort(block[x].sub, block[x].nsub);

	for (i = 0; i < nrshapes; i++)
		if (shapes[i].m == block[x].nsub &&
		    memcmp(shapes[i].s, block[x].sub, block[x].nsub * sizeof(int)) == 0)
			return (block[x].shape = i);

	shapes[nrshapes].m = block[x].nsub;
	memcpy(shapes[nrshapes].s, block[x].sub, block[x].nsub * sizeof(int));

	return nrshapes++;
}

void print()
{
	unsigned long long r;
	int i, j;

	for (r = 1, i = 0; i < nprimes; i++)
		for (j = result[i]; j-- > 0;) r *= primes[i];

	printf("%llu\n", r);
}

void solve()
{
	static struct {
		int s[128], m;
	} cycles[128];
	static int s[1024], v[1024];
	int i, j, k, t, ncycles;

	for (i = 0; i < n; i++) {
		block[i].cycle = 0;
		block[i].shape = -1;
	}

	for (i = 0; i < n; i++) {
		if (block[i].cycle)
			continue;

		for (j = block[i].a, k = n + 5; k-- > 0 && j != i;)
			j = block[j].a;

		if (i != j)
			continue;

		for (j = block[i].a;; j = block[j].a) {
			block[j].cycle = 1;
			if (j == i) break;
		}
	}

	nrshapes = 1;
	shapes[0].m = 0;

	for (i = 0; i < n; i++)
		getshape(i);

	memset(result, 0, sizeof(result));
	mulfact(n);

	for (i = 0; i < n; i++) {
		if (block[i].nsub == 0)
			continue;

		for (j = 1, k = 1; j < block[i].nsub; j++) {
			if (block[i].sub[j - 1] == block[i].sub[j]) {
				k++;
			} else {
				mulfact(-k);
				k = 1;
			}
		}

		mulfact(-k);
	}

	memset(v, 0, sizeof(v));
	for (ncycles = 0, i = 0; i < n; i++) {
		if (v[i] || !block[i].cycle)
			continue;

		for (j = block[i].a, k = 0;; j = block[j].a) {
			v[j] = 1;
			s[k++] = getshape(j);
			if (j == i) break;
		}

		for (j = 0; j < k; j++)
			s[k + j] = s[j];

		for (t = 0, j = 0; j < k; j++)
			if (memcmp(s, s + j, k * sizeof(int)) == 0) t++;

		divnum(t);

		cycles[ncycles].m = k;
		memcpy(cycles[ncycles].s, s, 2 * k * sizeof(int));
		ncycles++;
	}

	memset(v, 0, sizeof(v));
	for (i = 0; i < ncycles; i++) {
		if (v[i]) continue;

		for (k = 0, j = 0; j < ncycles; j++) {
			if (v[j]) continue;

			if (cycles[j].m != cycles[i].m)
				continue;

			for (t = 0; t < cycles[i].m; t++)
				if (memcmp(cycles[i].s, cycles[j].s + t,
					   cycles[i].m * sizeof(int)) == 0) break;

			if (t >= cycles[i].m)
				continue;

			v[j] = 1;
			k++;
		}

		mulfact(-k);
	}

	print();
}

int main()
{
	int i;

	mkfact();

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n; i++) {
			scanf("%d", &block[i].a);
			block[i].a--;
		}

		solve();
	}

	return 0;
}
