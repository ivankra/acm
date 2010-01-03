#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>

namespace FastIO
{
	static char *inp, *inend, *outp, IsDigit[257], outbuf[1048576], inbuf[1048576+1];

	static inline void init() {
		inp = inend = inbuf; outp = outbuf;
		for (int i = '0'; i <= '9'; i++) IsDigit[i+1] = 1;
	}

	static inline void flush() {
		fwrite(outbuf, 1, outp - outbuf, stdout);
		outp = outbuf;
	}

	static inline int nextChar() {
		if (inp >= inend) {
			inend = inbuf + fread(inbuf, 1, sizeof(inbuf)-1, stdin);
			inp = inbuf;
			if (inp == inend) return EOF;
			*inend = ' ';
		}
		return *inp++;
	}

	static inline int nextInt() {
		int c, res = 0;
		do { c = nextChar(); } while (IsDigit[c+1] == 0);
		while (IsDigit[c+1]) { res = res * 10 + c - '0'; c = nextChar(); }
		if (c != EOF) --inp;
		return res;
	}

	static inline bool nextInt(int &res) {
		int c;
		do { c = nextChar(); if (c == EOF) return false; } while (IsDigit[c+1] == 0);
		res = 0;
		while (IsDigit[c+1]) { res = res * 10 + c - '0'; c = nextChar(); }
		if (c != EOF) --inp;
		return true;
	}

	static inline void putChar(char c) {
		if (outp - outbuf == sizeof(outbuf)) flush();
		*outp++ = c;
	}

	static inline void print(const char *s) {
		while (*s) putChar(*s++);
	}

	static inline void print(int n) {
		if (n < 0) { putChar('-'); n = -n; /*beware of -2^31*/ }
		if (n == 0) { putChar('0'); return; }
		char z[16], *p = &z[15];
		*p = 0;
		while (n != 0) { *--p = '0' + n % 10; n /= 10; }
		print(p);
	}
};

int main()
{
	FastIO::init();


	FastIO::flush();
}
