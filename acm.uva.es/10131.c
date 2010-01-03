#include <stdio.h>
#include <stdlib.h>

struct rec {
	int serial, w, r;
} data[1024];

int n, pred[1024], len[1024], seq[1024];

int compare(const void *p, const void *q)
{
	return (((struct rec *)p)->w < ((struct rec *)q)->w) ? -1 : 1;
}

int main()
{
	register int i, j, k;

	for (n = 0; scanf("%d %d", &data[n].w, &data[n].r) == 2; n++)
		data[n].serial = n + 1;

	qsort(data, n, sizeof(struct rec), &compare);

	for (i = 0; i < n; i++) {
		for (j = 0, k = -1; j < i && data[j].w < data[i].w; j++)
			if (data[j].r > data[i].r) {
				k = j;
				break;
			}

		if (k < 0) {
			pred[i] = -1;
			len[i] = 1;
			continue;
		}

		for (; j < i && data[j].w < data[i].w; j++)
			if (data[j].r > data[i].r && len[j] > len[k])
				k = j;

		pred[i] = k;
		len[i] = len[k] + 1;
	}

	for (i = 0, j = 1; j < n; j++)
		if (len[j] > len[i]) i = j;

	for (j = 0; i >= 0; i = pred[i])
		seq[j++] = i;

	printf("%d\n", j);
	while (j-- > 0)
		printf("%d\n", data[seq[j]].serial);

	return 0;
}
