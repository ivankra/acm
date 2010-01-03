#include <stdio.h>
#include <string.h>

#define GOAL 46234

int succ[362881], move[362881], fact[16];

int encode(int a[])
{
	static int c[16];
	int i, k, r;

	for (i = 0; i < 9; i++)
		c[i] = i;

	for (r = 0, k = 0; k < 9; k++) {
		r += c[a[k]] * fact[8 - k];

		for (i = a[k]; i < 9; i++)
			c[i]--;
	}

	return (r + 1);
}

void decode(int a[], int r)
{
	static int c[16];
	int i, k;

	for (i = 0; i < 9; i++)
		c[i] = i;

	for (r--, k = 0; k < 9; k++) {
		i = r / fact[8 - k];
		r %= fact[8 - k];

		a[k] = c[i];

		for (; i < 9; i++)
			c[i] = c[i + 1];
	}
}

void mktab()
{
	static int queue[362882], a[16];
	int p, x, y, *qh, *qt;

	memset(succ, '\0', sizeof(succ));

	qh = qt = queue;
	*qt++ = GOAL;
	succ[GOAL] = GOAL;

	while (qh < qt) {
		decode(a, x = *qh++);

		for (p = 0; a[p] != 0; p++);

		/* right */
		if ((p % 3) != 2) {
			a[p] = a[p + 1];
			a[p + 1] = 0;

			y = encode(a);
			if (succ[y] == 0) {
				succ[y] = x;
				move[y] = 'l';
				*qt++ = y;
			}

			a[p + 1] = a[p];
			a[p] = 0;
		}

		/* left */
		if ((p % 3) != 0) {
			a[p] = a[p - 1];
			a[p - 1] = 0;

			y = encode(a);
			if (succ[y] == 0) {
				succ[y] = x;
				move[y] = 'r';
				*qt++ = y;
			}

			a[p - 1] = a[p];
			a[p] = 0;
		}


		/* up */
		if (p >= 3) {
			a[p] = a[p - 3];
			a[p - 3] = 0;

			y = encode(a);
			if (succ[y] == 0) {
				succ[y] = x;
				move[y] = 'd';
				*qt++ = y;
			}

			a[p - 3] = a[p];
			a[p] = 0;
		}

		/* down */
		if (p <= 5) {
			a[p] = a[p + 3];
			a[p + 3] = 0;

			y = encode(a);
			if (succ[y] == 0) {
				succ[y] = x;
				move[y] = 'u';
				*qt++ = y;
			}

			a[p + 3] = a[p];
			a[p] = 0;
		}



	}
}

int main()
{
	int a[16], i, c, t;

	for (fact[0] = 1, i = 1; i < 16; i++)
		fact[i] = i * fact[i - 1];

	mktab();

	scanf("%d", &t);

	while (t-- > 0) {
		for (i = 0; i < 9 && (c = getchar()) != EOF;)
			if (c >= '1' && c <= '9')
				a[i++] = c - '0';
			else if (c == 'x' || c == 'X')
				a[i++] = 0;

		if (i < 9)
			break;

		for (c = 0; c < 9; c++) {
			for (i = 0; i < 9; i++)
				if (a[i] == c) break;

			if (i == 9) break;

			for (i++; i < 9; i++)
				if (a[i] == c) break;

			if (i < 9) break;
		}

		if (c < 9) {
			printf("unsolvable\n");
			continue;
		}

		c = encode(a);
		if (succ[c] == 0) {
			printf("unsolvable\n");
		} else {
			for (; c != GOAL; c = succ[c])
				putchar(move[c]);
			putchar('\n');
		}

		if (t != 0)
			printf("\n");
	}

	return 0;
}
