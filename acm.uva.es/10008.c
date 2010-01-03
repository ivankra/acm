#include <stdio.h>

int main()
{
	static char buf[16384];
	static int t, f[26], s[26];
	int i, j, c;

	for (i = 0; i < 26; i++)
		f[i] = 0;

	scanf("%d\n", &t);
	while (t > 0 && (i = fread(buf, 1, sizeof(buf), stdin)) > 0)
		for (j = 0; t > 0 && j < i; j++)
			if ((c = buf[j]) == '\n')
				t--;
			else if (c >= 'a' && c <= 'z')
				f[c - 'a']++;
			else if (c >= 'A' && c <= 'Z')
				f[c - 'A']++;

	for (i = 1, s[0] = 0; i < 26; i++) {
		for (c = f[i], j = i - 1; j >= 0 && f[s[j]] < c; j--)
			s[j + 1] = s[j];
		s[j + 1] = i;
	}

	for (i = 0; i < 26 && f[s[i]] > 0; i++)
		printf("%c %d\n", (s[i] + 'A'), f[s[i]]);

	return 0;
}
