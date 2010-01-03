#include <cstdio>

int a[1024][1024], n;

int main() {
	while (scanf("%d", &n) == 1 && n > 0) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf("%d", &a[i][j]);

		for (int i = 0; i < n-1; i++)
			for (int j = 0; j < n-1; j++)
				if ((a[i][j] - a[n-1][j] - a[i][n-1] + a[n-1][n-1]) != 0) goto no;
		printf("homogeneous\n");
		continue;
no:		printf("not homogeneous\n");
	}
}
