/*
1 3 4 4

n1 n2 n3 n4 n5 n6
a b c d e f

a + 2b + 3c + 4d + 5e + 6f = n1 -a + 2(n2-b) + 3(n3-c) + 4(n4-d) +5(n5-e)+6(n6-f)

2a + 4b + 6c + 8d + 10e + 12f = n1 + 2n2 + 3n3 + 4n4 + 5n5 + 6n6

a + 2b + 3c + 4d + 5e + 6f = 1/2 (n1 + 2n2 + 3n3 + 4n4 + 5n5 + 6n6)

0 <= a <= n1
0 <= b <= n2
...
0 <= f <= n6
*/
#include <stdio.h>


/*
a + 2b + 3c
0 <= a <= n1
0 <= b <= n2
0 <= c <= n3

n1=0
n2=1
n3=2
      0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
a     +
b     +     +
c     +        +     +  +     +

f[x,n1,n2,n3] = f[x,n1,n2] + f[x-3,n1,n2] + ... + f[x-3n3,n1,n2]
f[x+3,n1,n2,n3] = f[x,n1,n2,n3] + f[x+3,n1,n2] - f[x-3n3,n1,n2]

f[x,n1,n2,n3] = f[x-3,n1,n2,n3] + f[x,n1,n2] - f[x-3n3-3,n1,n2]

*/

int solve(int n[])
{
	static int tab[8][16384];
	int i, j, k, s;

	for (s = 0, i = 1; i <= 6; i++)
		s += i * n[i];

	if ((s % 2) != 0)
		return 0;

	s /= 2;

	memset(tab, 0, sizeof(tab));
	for (i = 0; i <= n[1]; i++)
		tab[1][i] = 1;

	for (k = 2; k <= 6; k++) {
		for (i = 0; i < k; i++)
			tab[k][i] = tab[k - 1][i];

		for (i = k; i <= s; i++) {
			tab[k][i] = tab[k][i - k] + tab[k - 1][i];
			if ((i - k * (n[k] + 1)) >= 0)
				tab[k][i] -= tab[k - 1][i - k * (n[k] + 1)];
		}
	}

for (i = 1; i <= 6; i++) {
	printf("%d:",i);
	for (j = 1; j <= s; j++)
		printf(" %d", tab[i][j]);
	printf("\n");
} 

printf("tab[6][s]=%d\n",tab[6][s]);
	return tab[6][s] ? 1 : 0;
}

int main()
{
	int n[8], s, t, i;

	for (t = 1;; t++) {
		for (i = 1, s = 0; i <= 6 && scanf("%d", &n[i]) == 1; i++)
			s += n[i];

		if (i <= 6 || s == 0)
			break;

		printf("Collection #%d:\n%s be divided.\n\n",
			t, solve(n) ? "Can" : "Can't");
	}

	return 0;
}
