#include <cstdio>

int main()
{
	int x[256], y[256], n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &x[i], &y[i]);

	int best = (n <? 2);
	for (int a = 0; a < n; a++)
	for (int b = a+1; b < n; b++) {
		int r = 0;
		for (int c = 0; c < n; c++) {
			int det = (x[b]-x[a])*(y[c]-y[a])-
				  (x[c]-x[a])*(y[b]-y[a]);
			if (det == 0) r++;
		}
		best >?= r;
	}
	printf("%d\n", best);
}
