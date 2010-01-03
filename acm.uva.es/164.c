#include <stdio.h>
#include <string.h>

char buf[256], s1[256], s2[256];
int dist[32][32], n1, n2;

int main()
{
	int i, j, k, m;

	while (gets(buf) && strchr(buf, '#') == NULL) {
		memset(s1, 0, sizeof(s1));
		memset(s2, 0, sizeof(s2));

		for (k = 0, n1 = 1; buf[k] && buf[k] != ' ';)
			s1[n1++] = buf[k++];

		while (buf[k] == ' ') k++;

		for (n2 = 1; buf[k] && buf[k] != ' ';)
			s2[n2++] = buf[k++];

		memset(dist, 0, sizeof(dist));

		for (i = 0; i <= n2; i++)
			dist[n1 + 1][i] = n2 - i + 1;

		for (i = 0; i <= n1; i++)
			dist[i][n2 + 1] = n1 - i + 1;

		for (i = n1; i >= 1; i--) {
			for (j = n2; j >= 1; j--) {
				if (s1[i] == s2[j])
					dist[i][j] = dist[i + 1][j + 1];
				else if (dist[i + 1][j + 1] < dist[i][j + 1] &&
					   dist[i + 1][j + 1] < dist[i + 1][j])
					dist[i][j] = dist[i + 1][j + 1] + 1;
				else if (dist[i + 1][j] < dist[i][j + 1])
					dist[i][j] = dist[i + 1][j] + 1;
				else
					dist[i][j] = dist[i][j + 1] + 1;
			}
		}

		for (i = 1, j = 1, k = 0; i <= n1 && j <= n2;) {
			if (s1[i] == s2[j]) {
				i++;
				j++;
			} else if (dist[i + 1][j + 1] <= dist[i][j + 1] &&
				   dist[i + 1][j + 1] <= dist[i + 1][j]) {
				printf("C%c%.2d", s2[j], i - k);
				i++;
				j++;
			} else if (dist[i + 1][j] <= dist[i][j + 1]) {
				printf("D%c%.2d", s1[i], i - k);
				i++;
				k++;
			} else {
				printf("I%c%.2d", s2[j], i - k);
				k--;
				j++;
			}
		}

		for (; i <= n1; i++, k++)
			printf("D%c%.2d", s1[i], i - k);

		for (; j <= n2; j++, i++)
			printf("I%c%.2d", s2[j], i - k);

		printf("E\n");
	}

	return 0;
}
