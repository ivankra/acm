// hanoi towers
// (given N disks on the first peg, what's the minimum number of moves
// to separate odd and even numbered disks on different pegs)
#include <cstdio>

int main()
{
	int T, N;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d", &N) == 1; cs++) {
		long double res = 0;
		for (int i = 0; i < N-1; i++) {
			res = res * 2 + (i % 3 == 2 ? 0 : 1);
		}
		printf("%.0Lf\n", res);
	}
}
