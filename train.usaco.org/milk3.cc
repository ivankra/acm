/*
ID: infnty1
PROB: milk3
LANG: C++
*/
#include <stdio.h>
#include <string.h>

int A, B, C, seen[32][32], can[32];

void go(int a, int b, int c)
{
	if (seen[a][b]) return;
	seen[a][b] = 1;
	if (a == 0) can[c] = 1;

	int t;
	t = B-b <? a; go(a-t, b+t, c);
	t = A-a <? b; go(a+t, b-t, c);
	t = A-a <? c; go(a+t, b, c-t);
	t = C-c <? a; go(a-t, b, c+t);
	t = C-c <? b; go(a, b-t, c+t);
	t = B-b <? c; go(a, b+t, c-t);
}

int main()
{
	freopen("milk3.in", "r", stdin);
	freopen("milk3.out", "w", stdout);

        scanf("%d %d %d", &A, &B, &C);

	memset(seen, 0, sizeof(seen));
	memset(can, 0, sizeof(can));
	go(0,0,C);

	for (int i = 0, k = 0; i < 32; i++)
		if (can[i]) printf(k++ ? " %d" : "%d", i);
	printf("\n");

	return 0;
}
