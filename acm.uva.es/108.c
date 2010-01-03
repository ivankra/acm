#include <stdio.h>

#define MAXN 100

int n, subsum[MAXN], tmp;
char arr[MAXN*MAXN];

int main()
{
	int i, j, maxsum;
	int left, right;

	scanf("%d\n", &n);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &tmp);
			arr[i * MAXN + j] = tmp;
		}
	}

	maxsum = arr[0];
	for (left = 0; left < n; left++) {
		for (right = left; right < n; right++) {
			for (i = 0; i < n; i++) {
				char *p = &arr[i * MAXN + left];
				for (subsum[i] = 0, j = (right - left + 1); j > 0; j--)
					subsum[i] += *p++;
			}

			for (i = 0; i < n; i++) {
				int s;
				for (s = 0, j = i; j < n; j++) {
					s += subsum[j];
					if (s > maxsum) maxsum = s;
				}
			}
		}
	}

	printf("%d\n", maxsum);
	return 0;
}
