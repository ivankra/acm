#include <stdio.h>
#include <string.h>
#include <ctype.h>

int a[32][32], id[256], n;
char name[32];

void solve()
{
	int i, j, k;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (id[a[i][j]] >= 0) {
				a[i][j] = id[a[i][j]];
				continue;
			}

			printf("NOT A SEMIGROUP: %c#%c = %c WHICH IS NOT AN ELEMENT OF THE SET\n",
				name[i], name[j], a[i][j]);
			return;
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++) {
				if (a[a[i][j]][k] == a[i][a[j][k]])
					continue;

				printf("NOT A SEMIGROUP: (%c#%c)#%c IS NOT EQUAL TO %c#(%c#%c)\n",
					name[i], name[j], name[k],
					name[i], name[j], name[k]);
				return;
			}
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (a[i][j] == a[j][i])
				continue;

			printf("SEMIGROUP BUT NOT COMMUTATIVE (%c#%c IS NOT EQUAL TO %c#%c)\n",
				name[i], name[j], name[j], name[i]);
			return;
		}
	}

	printf("COMMUTATIVE SEMIGROUP\n");
}

int main()
{
	int i, j, k;

	while (scanf("%d", &n) == 1 && n > 0) {

		for (i = 0; i < n && (k = getchar()) != EOF;)
			if (isalpha(k)) name[i++] = k;
		name[n] = '\0';

		for (i = 0; i < 256; i++)
			id[i] = -1;

		for (i = 0; i < n; i++)
			id[(int)name[i]] = i;

		for (i = 0; i < n; i++)
			for (j = 0, a[i][n] = '\0'; j < n && (k = getchar()) != EOF;)
				if (isalpha(k)) a[i][j++] = k;

		printf("S = {%c", name[0]);
		for (i = 1; i < n; i++)
			printf(",%c", name[i]);
		printf("}\n #|%s\n -+", name);

		for (i = 0; i < n; i++)
			putchar('-');
		printf("\n");

		for (i = 0; i < n; i++) {
			printf(" %c|", name[i]);
			for (j = 0; j < n; j++) putchar(a[i][j]);
			putchar('\n');
		}
		printf("\n");

		solve();

		printf("------------------------------\n\n");
	}

	return 0;
}
