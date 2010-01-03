#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
	static char s[1048576], b, c;
	int count[256], share[256], i, p, q, r, t, tn, ts;

	while (gets(s) && sscanf(s, "%d", &t) != 1);
	gets(s);

	while (t-- > 0 && gets(s)) {
		memset(count, 0, sizeof(count));
		memset(share, 0, sizeof(share));

		for (i = 0; s[i]; i++)
			count[s[i]]++;

		tn = ts = 0;
		while (gets(s) && sscanf(s, " %c%n", &c, &p) >= 1) {
			ts -= share[c];
			for (; sscanf(s + p, "%*[ ,] %c : %d%n", &b, &r, &q) >= 2; p += q) {
				if (count[b] == r)
					share[c] += 2;
				else if (abs(count[b] - r) == 1)
					share[c]++;
				tn++;
			}
			ts += share[c];
		}

		for (i = 'A'; i <= 'Z'; i++)
			if (share[i] > 0)
				printf("%c %.2f\n", i, tn * 2. * share[i] / (double)ts);
		if (t) printf("\n");
	}

	return 0;
}
