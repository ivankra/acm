#include <stdio.h>

#define INF 0x1FFFFFFF
#define MAX 100001

int x[MAX], y[MAX], xmy[MAX], xpy[MAX], n;

int cmpm(const void *p, const void *q)
{
	int i = *(int *)p, j = *(int *)q, k;
	k = ((x[i] - y[i]) - (x[j] - y[j]));
	return (k != 0) ? k : (x[i] - x[j]);
}

int cmpp(const void *p, const void *q)
{
	int i = *(int *)p, j = *(int *)q, k;
	k = ((x[i] + y[i]) - (x[j] + y[j]));
	return (k != 0) ? k : 0;
}

int check(int t)
{
	int i, j, k, a, b;

printf("check(t=%d):\n",t);

for(i=0;i<n;i++)
  printf("(%d,%d): R=%d\n", x[xpy[i]], y[xpy[i]], x[xpy[i]] + y[xpy[i]] - t);
for(i=0;i<n;i++)
  printf("(%d,%d): L=%d\n", x[xmy[i]], y[xmy[i]], x[xmy[i]] - y[xmy[i]] + t);

	i = xpy[0];
printf("first:(%d,%d) R=%d\n", x[i],y[i], x[i]+y[i]-t);

	i = x[i] + y[i] - t;
printf("L'>%5d\n",i);

	for (i = k = 0; i < n;) {
/* L < b
*/
		k++;
		printf("left wing: i=%d  (%d,%d)  R=%d\n",
			i, x[xpy[i]], y[xpy[i]],
			x[xpy[i]] + y[xpy[i]] - t);

		a = x[xpy[i]] + y[xpy[i]] - t;
		while (i < n && (

		k++;
	}

printf("Need: %d\n",k);


}

/*                                                         (x',y')
projection of (x,y) onto y=t:                (x,y)       /
R = x - (t - y) = x + y - t                /       \   /
L = x + (t - y) = x - y + t       --y=t--L-----------R-------
                                                     L'
t fixed;

R = (x+y) - t
R = (x'-y') + t

2R - (x+y) = (x'-y')

*/


int main()
{
	int i, c, t, m;

	for (scanf("%d", &t), c = 1; c <= t && scanf("%d %d", &n, &m); c++) {
		for (i = 0; i < n; i++)
			scanf("%d %d", &y[i], &x[i]);

		for (i = 0; i < n; i++)
			xmy[i] = xpy[i] = i;
		qsort(xmy, n, sizeof(xmy[0]), &cmpm);
		qsort(xpy, n, sizeof(xpy[0]), &cmpp);

		check(-2);
break;


	}

	return 0;
}
