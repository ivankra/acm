#include <stdio.h>
#include <string.h>

int main()
{
	static char buf[1024];
	static int s[256], len[256];
	int n, i, j, t;

	for (t = 1;; t++) {
		for (n = 0; scanf(" %[019]", buf) == 1 && buf[0] != '9'; n++) {
			for (i = 0, s[n] = 0; buf[i]; i++)
				s[n] = (s[n] << 1) | (buf[i] - '0');
			len[n] = i;
		}

		if (n == 0)
			break;

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (i == j || len[j] < len[i])
					continue;

				if ((s[j] >> (len[j] - len[i])) == s[i])
					break;
			}

			if (j < n) break;
		}

		printf("Set %d %s immediately decodable\n",
			t, (i >= n) ? "is" : "is not");
	}

	return 0;
}
