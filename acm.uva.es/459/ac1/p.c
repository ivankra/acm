#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAXN 26
#define L2N(c) ((c | 0x20) - 'a')

int adj[MAXN][MAXN], seg[MAXN], case_no, num_nodes, r;
char buf[32];

int main(void)
{
	int i;

	scanf("%d\n\n", &case_no);
	while (case_no-- > 0) {
		fgets(buf, sizeof(buf), stdin);
		num_nodes = L2N(buf[0]) + 1;
		if (num_nodes < 0 || num_nodes > MAXN) break;

		memset(adj, 0, sizeof(adj));
		memset(seg, 0, sizeof(seg));
		for (;;) {
			if (fgets(buf, sizeof(buf), stdin) == NULL) break;
			if (buf[0] < 'A' || buf[0] > 'Z' || buf[1] < 'A' || buf[1] > 'Z')
				break;
			adj[L2N(buf[0])][L2N(buf[1])] = 1;
			adj[L2N(buf[1])][L2N(buf[0])] = 1;
		}

		for (r = 0, i = 0; i < num_nodes; i++) {
			register int j, k, f;

			if (seg[i] != 0)
				continue;
			seg[i] = ++r;

			for (j=0, f=MAXN;;) {
				for (; j < num_nodes; j++) {
					if (seg[j] != r) continue;
					for (k = 0; k < num_nodes; k++) {
						if (adj[j][k] && seg[k] != r) {
							seg[k] = r;
							if (f > k) f = k;
						}
					}
				}
				if (f >= MAXN) break;
				j = f;
				f = MAXN;
			}
		}

		printf("%d\n", r);
	}

	return 0;
}
