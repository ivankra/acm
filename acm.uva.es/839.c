#include <stdio.h>

static int tree(int *w)
{
	int wl, dl, wr, dr, e;

	scanf("%d %d %d %d", &wl, &dl, &wr, &dr);

	e = 1;

	if (wl == 0)
		e = tree(&wl) && e;

	if (wr == 0)
		e = tree(&wr) && e;

	if (w)
		*w = wl + wr;

	return (e && ((wl * dl) == (wr * dr)));
}

int main()
{
	int t;

	for (scanf("%d", &t); t-- > 0;) {
		if (tree(NULL))
			printf((t > 0) ? "YES\n\n" : "YES\n");
		else
			printf((t > 0) ? "NO\n\n" : "NO\n");
	}

	return 0;
}
