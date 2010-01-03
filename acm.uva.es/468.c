#include <stdio.h>
#include <string.h>

static void count(char *s, int t[])
{
	static int f[256], r[256];
	register int i, j;

	for (i = 0; i < 256; i++)
		f[i] = 0;

	for (i = 0; s[i]; i++)
		f[s[i]]++;

	for (r[0] = 0, i = 1; i < 256; i++) {
		for (j = i - 1; j >= 0 && f[r[j]] < f[i]; j--)
			r[j + 1] = r[j];
		r[j + 1] = i;
	}

	for (i = 0; i < 256; i++)
		t[i] = r[i];
}

int main()
{
	static char p[65536], q[65536];
	static int t, u[256], v[256], m[256];
	int i;

	for (scanf("%d",&t); t-- > 0 && scanf(" %[a-zA-Z] %[a-zA-Z]",p,q)==2;){
		count(p, u);
		count(q, v);

		for (i = 0; i < 256; i++)
			m[v[i]] = u[i];

		for (i = 0; q[i]; i++)
			p[i] = m[q[i]];
		p[i] = '\0';

		printf("%s\n", p);
		if (t > 0) printf("\n");
	}

	return 0;
}
