#include <stdio.h>
#include <string.h>
#include <assert.h>

int code[100], found;
int S[1024], f[1024], len;

char R[1024], prev[1024];

typedef struct { int x, l; } rec;

void go(int p, int q)
{
	rec a[3], w;
	int i;

	if (found >= 100 || p > len || f[p] == 0) return;

	if (p == len) {
		R[q] = '\0';
		if (strcmp(prev, R) == 0) return;
		printf("%s\n", R);
		strcpy(prev, R);
		found++;
		return;
	}

	if ((p + 1) >= len) {
		if (code[S[p]]) {
			R[q] = code[S[p]];
			go(p+1,q+1);
		}
		return;
	}

	a[0].x = code[S[p]];
	a[0].l = 1;

	a[1].x = code[S[p]*10 + S[p+1]];
	a[1].l = 2;

	a[2].x = 0;
	a[2].l = 3;
	if ((p+2) < len && S[p] == 0) a[2].x = code[S[p+1]*10 + S[p+2]];

	if (a[0].x > a[1].x) { w = a[0]; a[0] = a[1]; a[1] = w; }
	if (a[0].x > a[2].x) { w = a[0]; a[0] = a[2]; a[2] = w; }
	if (a[1].x > a[2].x) { w = a[1]; a[1] = a[2]; a[2] = w; }

	for (i = 0; i < 3; i++)
		if (a[i].x > 0) {
			R[q] = a[i].x;
			go(p+a[i].l, q+1);
		}
}

int main()
{
	int i, j, n, x, t;
	char buf[1024], c;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		printf("Case #%d\n", t);

		memset(code, 0, sizeof(code));
		for (i = 0; i < n; i++) {
			scanf(" %c %d", &c, &x);
			assert(code[x] == 0 || code[x] == c);
			code[x] = c;
		}

		while ((i = getchar()) != EOF && i != '\n');

		memset(S, 0, sizeof(S));
		gets(buf);
		for (len = 0, i = 0; buf[i]; i++)
			if ('0' <= buf[i] && buf[i] <= '9') S[len++] = buf[i] - '0';

		memset(f, 0, sizeof(f));
		f[len] = 1;

		for (i = len - 1; i >= 0; i--) {
			f[i] = 0;
			if (code[S[i]] != 0) f[i] += f[i+1];
			if (i < (len - 1) && code[S[i]*10+S[i+1]] != 0) f[i] += f[i+2];
			if (i < (len - 2) && S[i] == 0 && code[S[i+1]*10+S[i+2]] != 0) f[i] += f[i+3];
		}

/*printf("S= ");for(i=0;i<len;i++) printf("%d ",S[i]);printf("\n");
printf("f= ");for(i=0;i<=len;i++) printf("%d ",f[i]);printf("\n");
for(i=0;i<=99;i++) if (code[i]) printf("%d=>%c ",i,code[i]);printf("\n");*/

		found = 0;
		strcpy(prev, "***");
		go(0, 0);

		printf("\n");
	}

	return 0;
}
