#include <stdio.h>
#include <ctype.h>

int a[128][128], n, t;

int count(int w)
{
	int r1, c1, r2, c2, r3, c3, r4, c4, k;

	for (r1 = 0, k = 0; r1 < n; r1++) {
		for (c1 = 0; c1 < n; c1++) {
			if (a[r1][c1] != w)
				continue;

			for (r2 = r1; r2 < n; r2++) {
				for (c2 = c1 + 1; c2 < n; c2++) {
					if (a[r2][c2] != w)
						continue;

					r3 = r1 + (c2 - c1);
					c3 = c1 - (r2 - r1);
					if (r3 < 0 || r3 >= n || c3 < 0 || c3 >= n ||
					    a[r3][c3] != w)
						continue;

					r4 = r2 + (c2 - c1);
					c4 = c2 - (r2 - r1);
					if (r4 < 0 || r4 >= n || c4 < 0 || c4 >= n ||
					    a[r4][c4] != w)
						continue;

					if (r3 <= r1 || r4 <= r1 || c3 > c2 || c4 > c2)
						continue;

/*{int i,j;for(i=0;i<n;i++){for(j=0;j<n;j++)if(i==r1&&j==c1)printf("A");else if
(i==r2&&j==c2)printf("B");else if(i==r3&&j==c3)printf("C");else if(i==r4&&j==c4)
printf("D");else printf(".");printf("\n");}printf("(%d,%d; %d,%d; %d,%d; %d,"
"%d %c)\n\n",r1,c1,r2,c2,r3,c3,r4,c4,w);}*/

					k++;
				}
			}
		}
	}

	return k;
}

int main()
{
	int i, j, m;

	for (t = 0; scanf("%d %d", &n, &m) == 2 && n > 0;) {
		if (t++)
			printf("\n");

		for (i = 0; i < n; i++)
			for (j = 0; j < n && (a[i][j] = getchar()) != EOF;)
				if (isalpha(a[i][j])) j++;

		while (m-- > 0) {
			while ((i = getchar()) != EOF && !isalpha(i));
			printf("%c %d\n", i, count(i));
		}
	}
printf("\n");
	return 0;
}
