#include <stdio.h>
#include <string.h>

char text[20*1048576];
int map[256], ord1[32], ord2[32], freq[32], isalp[256], n;

int main()
{
	register int i, j;

	for (i = 0; i < 256; i++)
		isalp[i] = ('a' <= i && i <= 'z') || ('A' <= i && i <= 'Z');

	memset(freq, 0, sizeof(freq));
	while (gets(text) && text[0] != '\0')
		for (i = 0; text[i]; i++)
			if (isalp[text[i]]) freq[(text[i] | 0x20) - 'a']++;

	for (ord1[0] = 0, i = 1; i < 26; i++) {
		for (j = i - 1; j >= 0 && freq[ord1[j]] < freq[i]; j--)
			ord1[j + 1] = ord1[j];
		ord1[j + 1] = i;
	}

	for (n = 0; (i = fread(text + n, 1, sizeof(text) - n - 1, stdin)) > 0;)
		n += i;

	memset(freq, 0, sizeof(freq));

	j = n;
	for (i = 0; i < j; i++)
		if (isalp[text[i]]) freq[(text[i] | 0x20) - 'a']++;

	for (ord2[0] = 0, i = 1; i < 26; i++) {
		for (j = i - 1; j >= 0 && freq[ord2[j]] < freq[i]; j--)
			ord2[j + 1] = ord2[j];
		ord2[j + 1] = i;
	}

	for (i = 0; i < 256; i++)
		map[i] = i;

	for (i = 0; i < 32; i++)
		map[ord2[i] + 'a'] = ord1[i] + 'a';

	for (i = 0; i < 32; i++)
		map[ord2[i] + 'A'] = ord1[i] + 'A';

	j = n;
	for (i = 0; i < j; i++)
		text[i] = map[text[i]];

	write(1, text, n);
	return 0;
}
