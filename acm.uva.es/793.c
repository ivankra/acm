#include <stdio.h>
#include <stdlib.h>

int main()
{
	static int a, b, n, t, m, n1, n2;
	static char s[16];
	register int i, k, *net;

	net = (int *)malloc((m = 1024) * sizeof(int));

	(void)scanf("%d", &t);

	while (t-- > 0 && scanf("%d", &n) == 1) {
		if (n >= m)
			net = (int *)realloc(net, (m = n + 1) * sizeof(int));

		for (i = 1; i <= n; i++)
			net[i] = i;

		for (n1=0, n2=0; scanf(" %8[cqCQ] %d %d", s, &a, &b) == 3;) {
			if (s[0] == 'q' || s[0] == 'Q') {
				if (net[a] == net[b])
					n1++;
				else
					n2++;
			} else if (net[a] < net[b]) {
				for (k = net[b], i = 1; i <= n; i++)
					if (net[i] == k) net[i] = net[a];
			} else if (net[b] < net[a]) {
				for (k = net[a], i = 1; i <= n; i++)
					if (net[i] == k) net[i] = net[b];
			}
		}

		printf("%d,%d\n", n1, n2);

		if (t > 0)
			printf("\n");
	}

	return 0;
}
