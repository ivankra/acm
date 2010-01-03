#include <stdio.h>

int main()
{
	static int a[4096], d[4096];
	int i, j, f, n;

	while (scanf("%d", &n) > 0) {
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);

		for (i = 0; i < 4096; i++)
			d[i] = 0;

		for (i = 1, f = 1; i < n; i++) {
			j = (a[i]>a[i-1]) ? (a[i] - a[i-1]) : (a[i-1] - a[i]);
			if (j >= n || d[j]++ != 0) {
				f = 0;
				break;
			}
		}

		if (f) {
			for (i = 1; i < n; i++) {
				if (d[i] == 0) {
					f = 0;
					break;
				}
			}
		}

		printf(f ? "Jolly\n" : "Not jolly\n");
	}

	return 0;
}
