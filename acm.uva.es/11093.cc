#include <cstdio>
#include <cstring>

int a[200100], x;

int main() {
	int N, T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);

		for (int i = 1; i <= N; i++) {
			scanf("%d", &a[i]);
			a[N+i] = a[i];
		}

		for (int i = 1; i <= N; i++) {
			scanf("%d", &x);
			a[i] -= x;
			a[N+i] -= x;
		}

		a[0] = 0;
		for (int i = 1; i <= N+N; i++)
			a[i] += a[i-1];

		int s = 0, mi = 1, cn = 0;
		for (int i = 0; i <= N+N; i++) {
			if (a[i] >= mi) {
				if (++cn > N) break;
			} else {
				mi = a[i];
				s = i;
				cn = 1;
				if (i >= N) break;
			}
		}

		printf("Case %d: ", cs);
		if (cn > N) printf("Possible from station %d\n", s+1);
		else printf("Not possible\n");
	}
}
