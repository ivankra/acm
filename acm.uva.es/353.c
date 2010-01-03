#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <ctype.h>

#define MAXPAL 65536

struct {
	int pos, len;
	unsigned long hash;
} pal[MAXPAL];

static char buffer[256];
static int palno, n;

static void add(int pos, int len)
{
	register int i, j;
	unsigned long h;

	for (i = 0, h = 0; i < len; i++)
		h = ((h << 5) | (h >> 28)) + buffer[pos + i];

	for (i = 0; i < palno; i++) {
		if (pal[i].hash != h || pal[i].len != len) continue;
		for (j = 0; j < len; j++)
			if (buffer[pos + j] != buffer[pal[i].pos + j]) break;
		if (j >= len)
			return;
	}

	pal[palno].pos = pos;
	pal[palno].len = len;
	pal[palno].hash = h;
	palno++;
}


int main()
{
	register int i, j, k;

	while (gets(buffer)) {
		n = strlen(buffer);
		palno = 0;

		for (i = 0; i < n; i++) {
			for (j = i; j < n; j++) {
				if (buffer[i] != buffer[j]) continue;
				for (k = (j - i); k > 0; k--)
					if (buffer[i + k] != buffer[j - k])
						break;
				if (k == 0)
					add(i, j - i + 1);
			}
		}

		printf("The string '%s' contains %d palindromes.\n", buffer, palno);
	}

	return 0;
}
