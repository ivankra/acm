#include <cstdio>

int main()
{
	char as[4096], bs[4096];
	int al[26], bl[26];
	int i, k;

	while (gets(as) && gets(bs)) {
		for (i = 0; i < 26; i++)
			al[i] = bl[i] = 0;

		for (i = 0; as[i]; i++)
			if (as[i] >= 'a' && as[i] <= 'z') al[as[i] - 'a']++;

		for (i = 0; bs[i]; i++)
			if (bs[i] >= 'a' && bs[i] <= 'z') bl[bs[i] - 'a']++;

		for (i = 0; i < 26; i++) {
			k = (al[i] < bl[i]) ? al[i] : bl[i];
			while (k-- > 0)
				putchar('a' + i);
		}

		putchar('\n');
	}

	return 0;
}
