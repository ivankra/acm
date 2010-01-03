/*
ID: infnty1
TASK: trt
LANG: C++
*/
#include <stdio.h>
#include <assert.h>

int main()
{
	unsigned n, v[2048], b1[2048], b2[2048], *f;

	freopen("trt.in", "r", stdin);
	freopen("trt.out", "w", stdout);

	scanf("%u", &n);
	assert(1 <= n && n <= 2000);

	for (int i = 0; i < n; i++) {
		scanf("%u", &v[i]);
		assert(1 <= v[i] && v[i] <= 1000);
	}

	f = b1;
	for (int i = 0; i < n; i++)
		f[i] = v[i] * n;

	for (int m = 2; m <= n; m++) {
		unsigned g = n - m + 1, *F = (f == b1) ? b2 : b1;
		for (int s = 0; s + m <= n; s++)
			F[s] = (v[s]*g+f[s+1]) >? (v[s+m-1]*g+f[s]);
		f = F;
	}

	printf("%u\n", f[0]);

	return 0;
}
