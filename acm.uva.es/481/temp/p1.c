#include <stdio.h>

/*
   x[i]: the input
   y[i]: the length of LIS, ending at x[i]
   z[i]: the smallest integer with which an LIS of length i may ends

*/

int x[131072], y[131072], z[131072], n, k;

int main()
{
	int i, j, t;

	for (n = 0; scanf("%d", &x[n]) == 1; n++);

	k = 1;
	z[0] = -0x7FFFFFFF;
	z[1] = x[0];
	y[0] = 1;

	for (i = 1; i < n; i++) {
		for (j = 1; j <= k && z[j] < x[i]; j++);

		y[i] = j;
		if (j > k) {
			z[j] = x[i];
			k = j;
		} else {
			if (x[i] < z[j]) z[j] = x[i];
		}
	}

	printf("%d\n", k);

printf("# ");for(i=0;i<n;i++)printf("%3d",i);printf("\n");
printf("x=");for(i=0;i<n;i++)printf("%3d",x[i]);printf("\n");
printf("y=");for(i=0;i<n;i++)printf("%3d",y[i]);printf("\n");
printf("z=");for(i=0;i<=k;i++)printf("%3d",z[i]);printf("\n");

	for (i = n - 1, t = k, j = 0x7FFFFFFF; i >= 0; i--)
		if (y[i] == t && x[i] < j)
			z[--t] = j = x[i];

	for (i = 0; i < k; i++)
		printf("%d\n", z[i]);

	return 0;
}
