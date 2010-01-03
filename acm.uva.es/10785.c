#include <stdio.h>
#include <stdlib.h>

static char nth_cons_data[] = "JSBKTCLDMVNWFXGPYHQZR";

#define NTH_CON(n) (nth_cons_data[n] - 'A')

static char nth_vowel_data[] = "AUEOI";
#define NTH_VOW(n) (nth_vowel_data[n] - 'A')

static int is_vowel[]={1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0};

void solve(int n)
{
	int i, c, j, use[26];

	for (i = 0; i < 26; i++) use[i]=0;

	for (i = 0; i < n; i++) {
		if ((i & 1) == 0) {
			/* vowel */
			for (j = 0; ; j++) {
				c = NTH_VOW(j);
				if (use[c] < 21) break;
			}
		} else {
			/* consonant */
			for (j = 0; ; j++) {
				c = NTH_CON(j);
				if (use[c] < 5) break;
			}
		}
		use[c]++;
	}

	for (i = 0; i < n; i++) {
		if ((i & 1) == 0) {
			for (j = 0; j < 26; j++)
				if (is_vowel[j] && use[j]) break;
		} else {
			for (j = 0; j < 26; j++)
				if (!is_vowel[j] && use[j]) break;
		}
		use[j]--;
		putchar('A'+j);
	}

	printf("\n");
}

int main(void)
{
	int i, c, n;

	scanf("%d", &c);
	for (i = 1; i <= c; i++) {
		scanf("%d", &n);
		printf("Case %d: ", i);
		solve(n);
	}

	return 0;
}
