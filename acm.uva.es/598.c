#include <stdio.h>
#include <string.h>

char name[32][32];
int n;

void show(int k)
{
	int a[16], i, j;

	for (a[0] = -1, i = 0; i >= 0;) {
		if (i == k) {
			for (j = 0; j < k; j++)
				printf((j+1)>=k ? "%s\n" : "%s, ", name[a[j]]);
			i--;
		} else if (++a[i] >= n) {
			i--;
		} else {
			a[i + 1] = a[i];
			i++;
		}
	}
}

int main()
{
	static char s[256];
	int t, a, b;

	for (scanf("%d", &t); t-- > 0 && scanf(" %[^\n]\n", s) == 1;) {
		if (s[0] == '*') {
			a = 1;
			b = 100;
		} else if (sscanf(s, "%d %d", &a, &b) == 1) {
			b = a;
		}

		for (n = 0; gets(name[n]) && name[n][0] != '\0'; n++);

		if (a < 1)
			a = 1;

		if (b > n)
			b = n;

		for (; a <= b; a++) {
			printf("Size %d\n", a);
			show(a);
			printf("\n");
		}

		if (t != 0)
			printf("\n");
	}

	return 0;
}
