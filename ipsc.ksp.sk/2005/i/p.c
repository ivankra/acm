#include <stdio.h>
#include <String.h>
#include <gmp.h>

int main()
{
	static char s[1048576];
	mpz_t a;
	int i, k;

	mpz_init(a);

	while (gmp_scanf("%Zd", &a) == 1) {
		memset(s, 0, sizeof(s));
		mpz_get_str(s, 7, a);
		for (i = strlen(s) - 1; i >= 0; i--)
			putchar("0125986"[s[i] - '0']);

//			putchar("0125689"[s[i] - '0']);

		putchar('\n');
	}

	return 0;
}
