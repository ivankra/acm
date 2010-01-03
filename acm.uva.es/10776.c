#include <stdio.h>
#include <string.h>

int a[32], c[32], s[32];
char z[1024];

void print()
{
	int i, j, k;

	for (i = 0, k = 0; i < 26; i++)
		for (j = 0; j < a[i]; j++) z[k++] = 'a' + i;
	z[k] = '\0';

	printf("%s\n", z);
}

void make(int k, int r)
{
	if (0 <= r && r <= (s[26] - s[k])) {
		if (k == 26)
			print();
		else
			for (a[k] = c[k]; a[k] >= 0; a[k]--)
				make(k + 1, r - a[k]);
	}
}

int main()
{
	int i, r;

	while (scanf(" %[a-z] %d", z, &r) == 2) {
		memset(c, 0, sizeof(c));
		for (i = 0; z[i]; i++)
			c[z[i] - 'a']++;

		for (s[0] = 0, i = 0; i < 26; i++)
			s[i + 1] = s[i] + c[i];

		make(0, r);
	}

	return 0;
}
