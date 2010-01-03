/*
let a[0], a[1], ..., a[n-1] be the sequence of cows' assigned numbers
let b[k] = a[0] xor a[1] xor ... xor a[k-1], for k=0..n
then a[i] xor a[i+1] xor ... xor a[j-1] = b[i] xor b[j]

the problem reduces to finding a pair of integers (i,j), s.t.:
  a) 0 <= i <= j <= n
  b) b[i] xor b[j] is maximized
  c) j is minimized
  d) i is maximized
the answer to the original problem is the segment a[i]...a[j-1]
*/
#include <stdio.h>
#include <assert.h>

#define M	21	 	/* number of bits in cows' assigned numbers */
#define MAXN	100005

int main()
{
	static int a[MAXN], b[MAXN];
	int i, j, n, ri, rj, rx;;

	freopen("cowxor.in", "r", stdin);
	/*freopen("cowxor.out", "w", stdout);*/

	scanf("%d", &n);
	assert(1 <= n && n < MAXN);
	for (i = 0, b[0] = 0; i < n; i++) {
		scanf("%d", &a[i]);
		assert(0 <= a[i] && a[i] < (1 << M));
		b[i+1] = b[i] ^ a[i];
	}

	rx = ri = rj = 0;
	for (i = 0; i <= n; i++) {
		for (j = i; j <= n; j++) {
			if ((b[i] ^ b[j]) < rx) continue;
			if ((b[i] ^ b[j]) == rx) {
				if (j > rj) continue;
				if (j == rj && i < ri) continue;
			}
			rx = b[i] ^ b[j]; ri = i; rj = j;
		}
	}

	printf("%d %d %d\n", rx, ri+1, rj);
	return 0;
}

