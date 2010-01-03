#include <stdio.h>

int main()
{
	long long n;
	while (scanf("%lld", &n) == 1 && n > 0)
		printf("%lld\n", ((((n*n+3)*n+12)*n+8)*n*n)/24);
	return 0;
}


/*
#include <stdio.h>

void rot(int a[], char *s)
{
	int i, t;
	t = a[s[3] - 'a'];
	for (i = 2; i >= 0; i--)
		a[s[i+1] - 'a'] = a[s[i] - 'a'];
	a[s[0] - 'a'] = t;
}

int main()
{
	int i, j, k, t, x, y, z, n, p[6], a[6] = { 0, 1, 2, 3, 4, 5 };

	for (x = 0; x < 4; x++, rot(a, "bfde"))
		for (y = 0; y < 4; y++, rot(a, "aecf"))
			for (z = 0; z < 4; z++, rot(a, "abcd"))
	{
		for (i = 0; i < 6; i++) printf("%d ",a[i]);

		for (i = 0; i < 6; i++)
			p[i] = a[i];

		for (k = 0, i = 0; i < 6; i++)
			if (p[i] >= 0)
				for (k++, j = i; p[j] >= 0;)
					t = p[j], p[j] = -1, j = t;

		printf(": %d\n", k);
	}
}

*/
