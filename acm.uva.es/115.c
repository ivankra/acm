#include <stdio.h>
#include <string.h>

char names[1024][32], s[1024], t[1024];
int xr[1024], yr[1024], parent[1024], n;

int get(char *s)
{
	int i;

	for (i = 1; i <= n; i++)
		if (strcmp(names[i], s) == 0) return i;

	strcpy(names[++n], s);
	parent[n] = 0;
	return n;
}

int main()
{
	int k, x, y, xn, yn;

	n = 0;

	memset(parent, 0, sizeof(parent));
	while (scanf(" %s %s", s, t) == 2 && strcmp(s, "no.child") != 0)
		parent[get(s)] = get(t);

	while (scanf(" %s %s", s, t) == 2) {
		x = get(s);
		y = get(t);

		for (k = x, xn = 0; k != 0; k = parent[k])
			xr[xn++] = k;

		for (k = y, yn = 0; k != 0; k = parent[k])
			yr[yn++] = k;

		for (k = 0; k < xn && k < yn && xr[xn - k - 1] == yr[yn - k - 1]; k++);

		if (k == 0) {
			printf("no relation\n");
			continue;
		}

		xn -= k;
		yn -= k;

		if (xn == 0) {
			for (; yn > 2; yn--) printf("great ");
			for (; yn > 1; yn--) printf("grand ");
			printf("parent\n");
		} else if (yn == 0) {
			for (; xn > 2; xn--) printf("great ");
			for (; xn > 1; xn--) printf("grand ");
			printf("child\n");
		} else if (xn == 1 && yn == 1) {
			printf("sibling\n");
		} else if (xn == yn) {
			printf("%d cousin\n", xn - 1);
		} else if (xn < yn) {
			printf("%d cousin removed %d\n", xn - 1, yn - xn);
		} else {
			printf("%d cousin removed %d\n", yn - 1, xn - yn);
		}
	}

	return 0;
}
