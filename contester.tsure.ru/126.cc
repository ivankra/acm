#include <cstdio>

int main()
{
	int c[32], st[32], n, m, cap, d, i, r, rm;

	scanf("%d %d %d",&n,&m,&cap);
	for (i = 1; i <= n; i++) scanf("%d", &c[i]);
	for (i = 1; i <= n; i++) st[i] = 0;

	for (r = rm = 0; m-- > 0;) {
		scanf("%d", &d);
		if (st[d]) {
			st[d] = 0;
			r -= c[d];
		} else {
			st[d] = 1;
			r += c[d];
			if (r > rm) rm = r;
		}
	}

	if (rm > cap)
		printf("Fuse was blown\n");
	else
		printf("%d\n", rm);
}
