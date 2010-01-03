#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int read(int, char *, int);

char inbuf[16*1048576];
int isdig[256], not_isdigzn[256], not_isdigz[256];
int p[1048576];

int main()
{
	char *inp;
	int i, n, t, x, y, r;

	for (i = 0; i < 256; i++) {
		isdig[i] = ('0' <= i && i <= '9');
		not_isdigzn[i] = not_isdigz[i] = !isdig[i];
	}
	not_isdigzn[0] = not_isdigz[0] = 0;
	not_isdigzn['\n'] = 0;

	inbuf[i = read(0, inp = inbuf, sizeof(inbuf) - 1)] = '\0';
	assert(i < (sizeof(inbuf) - 1024));

#define READ(x, end_code, eof_code) { \
	for (;;) { \
		while (not_isdigzn[*inp]) inp++; \
		if (*inp == '\0') { eof_code } \
		if (*inp == '\n') { \
			if (*++inp == '\n') { inp++; end_code } \
			continue; \
		} \
		break; \
	} \
	for (x = *inp++ - '0'; isdig[*inp];) x = x * 10 + *inp++ - '0'; \
}

#define READW(x, eof_code) { \
	while(not_isdigz[*inp]) inp++; \
	READ(x, { return 0; }, eof_code) \
}

	READW(t, { return 0; });

	while (t-- > 0) {
		READW(n, { return 0; });

		for (r = n, i = 0; i <= n; i++) p[i] = i;

		for (;;) {
			READ(x, { goto end_case; }, { goto end_case; });
			READ(y, { goto end_case; }, { goto end_case; });

			for (i = x; p[i] != i; i = p[i]);
			p[x] = i; x = i;

			for (i = y; p[i] != i; i = p[i]);
			p[y] = i; y = i;

			if (x == y) continue;

			p[y] = x;
			r--;
		}
end_case:
		printf(t ? "%d\n\n" : "%d\n", r);
	}

	return 0;
}
