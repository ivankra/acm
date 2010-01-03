#include <stdio.h>
#include <string.h>

int a[1024], n;
int s[65536];

int f()
{
	int i, j;

	if (a[0] < 1) return 0;

	for (i = 1; i < n; i++)
		if (a[i] < 1 || a[i-1] >= a[i]) return 0;

	memset(s, 0, sizeof(s));
	s[0] = 1;

	for (i = 0; i < n; i++) {
		if (s[a[i]]) return 0;
		for (j = 32768; j >= 0; j--)
			s[j + a[i]] |= s[j];
	}

	return 1;
}

int main()
{
	int i, t;

	for (t = 1; scanf("%d", &n) == 1; t++) {
		for (i = 0; i < n; i++) scanf("%d", &a[i]);
		printf("Case #%d:", t);
		for (i = 0; i < n; i++) printf(" %d", a[i]);
		printf("\nThis is %s A-sequence.\n", f() ? "an" : "not an");
	}

	return 0;
}
