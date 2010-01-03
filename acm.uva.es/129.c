#include <stdio.h>
#include <string.h>

char listbuf[1048576], *listfree, *list[32][256], make_s[1024];
int count[32];

int make(int k, int m)
{
	int i, j;

	if (k > 0 && count[m] < 250) {
		for (list[m][++count[m]] = listfree, i = 0; i < k;)
			*listfree++ = make_s[i++];
		*listfree++ = '\0';
	}

	if (k > 120)
		return 1;

	for (make_s[k] = 'A'; make_s[k] < ('A' + m); make_s[k]++) {
		for (i = 1, j = 0; (k + 1) >= (2 * i); i++) {
			if (memcmp(&make_s[k - i + 1], &make_s[k - 2 * i + 1], i) == 0) {
				j = 1;
				break;
			}
		}

		if (j == 0 && make(k + 1, m))
			return 1;
	}

	return 0;
}

void print(char *s)
{
	int i;

	if (s == NULL) {
		printf("0\n");
		return;
	}

	for (i = 0; s[i]; i++) {
		if (i > 0 && (i % 64) == 0)
			putchar('\n');
		else if (i > 0 && (i % 4) == 0)
			putchar(' ');
		putchar(s[i]);
	}

	printf("\n%d\n", strlen(s));
}

int main()
{
	int n, m;

	listfree = listbuf;
	memset(list, 0, sizeof(list));
	memset(count, 0, sizeof(count));

	for (m = 1; m <= 26; m++)
		make(0, m);

	while (scanf("%d %d", &n, &m) == 2 && n > 0)
		print(list[m][n]);

	return 0;
}
