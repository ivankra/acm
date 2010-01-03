#include <stdio.h>

static void quad(int x, int y, int w, int *q)
{
	int i, j;
	char c;

	for (;;) {
		c = getchar();
		if (c == 'e' || c == 'f' || c == 'p') break;
		if (c == EOF) return;
	}
	if (c >= 'A' && c <= 'Z') c = c + 'a' - 'A';

	if (c == 'e' || c == 'f') {
		for (i = 0; i < w; i++)
			for (j = 0; j < w; j++)
				q[(y+j)*32 + (x+i)] = (c == 'e') ? 0 : 1;
	} else {
		w >>= 1;
		quad(x+w, y, w, q);
		quad(x, y, w, q);
		quad(x, y+w, w, q);
		quad(x+w, y+w, w, q);
	}
}

int main()
{
	static int q1[1024], q2[1024];
	int n, i, k;

	scanf("%d", &n);
	while (n-- > 0) {
		quad(0, 0, 32, q1);
		quad(0, 0, 32, q2);
		for (i = 0, k = 0; i < 1024; i++)
			if (q1[i] || q2[i]) k++;

		printf("There are %d black pixels.\n", k);
	}

	return 0;
}
