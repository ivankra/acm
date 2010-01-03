#include <stdio.h>
#include <string.h>

char s[65536];

void del(int i)
{ int j; for (j = i + 1; s[j]; j++) s[j-1] = s[j]; s[j-1] = s[j] = 0;}


int main()
{
	int i, j, k, c;

/*	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);*/

	scanf(" %s %d", s, &k);

	while (k > 0) {
/*printf("%s k=%d\n", s,k);*/

		c = 0;

		for (i = 0; k > 0 && s[i]; i++) {
			if (s[i+1] && s[i] < s[i+1]) {
				k--;
				del(i);
				c=1; break;
			}
		}

		if (c) continue;


/*		for (i = 0; k > 0 && s[i]; i++) {
 *			if (s[i+1] && s[i] <= s[i+1]) {
 *				k--; del(i);
 *				c=1; break;
 *			}
 *		}
 */

		if (c == 0) break;
	}

  /*
printf("%s k=%d\n", s,k);
printf("---\n");
*/
	i = strlen(s) - k;
	for (j = 0; j < i; j++);
	s[j] = 0;

	printf("%s\n", s);

	return 0;
}
