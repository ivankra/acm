#include <cstdio>
#include <cstring>
#include <cstdlib>

extern "C" { int read(int, char *, int); }
extern "C" { int write(int, const char *, int); }

#define MAX 100100

int sib[MAX], kid[MAX], count = 0;
unsigned char alpha[MAX];

static char inbuf[16*1048576], outbuf[1048576], *inp=inbuf, *outp=outbuf;
static int isdig[256], cmap[256];

extern "C" { int main1(); }

int main1() {
	for (int i = 0; i < 256; i++) isdig[i] = cmap[i] = 0;
	for (int i = '0'; i <= '9'; i++) isdig[i] = 1;
	for (int i = 0; i < 17; i++) cmap["A234567890JQKCDHS"[i]] = i+1;

	inbuf[read(0, inbuf, sizeof(inbuf)-1)] = 0;

#define R(x)  { while (!isdig[*inp]) inp++; \
		for (x = *inp++ - '0'; isdig[*inp];) \
			x = x * 10 + *inp++ - '0'; }
	for (;;) {
		int n; R(n); if (n == 0) break;

		count = 0;
		sib[0] = kid[0] = alpha[0] = 0;

		while (n-- > 0) {
			static int path[100];
			int m; R(m);

			for (int i = 0; i < m; i++) {
				while (cmap[*inp] == 0) inp++;
				path[i] = (cmap[inp[0]] << 4) + cmap[inp[1]];
				inp += 2;
			}

			for (int x = 0, i = m-1; i >= 0; i--) {
				unsigned char a = path[i];
				int y;
				for (y = kid[x]; y != 0; y = sib[y])
					if (alpha[y] == a) break;
				if (y == 0) {
					y = ++count;
					sib[y] = kid[x];
					kid[x] = y;
					alpha[y] = a;
					kid[y] = 0;
				}
				x = y;
			}
		}

		if (count == 0) {
			*outp++ = '0';
		} else {
			char tmp[20], *s = tmp+19;
			for (*s = 0; count > 0; count /= 10)
				*--s = '0' + (count % 10);
			while (*s) *outp++ = *s++;
		}
		*outp++ = '\n';
	}

	write(1, outbuf, outp-outbuf);
	exit(0);
}
