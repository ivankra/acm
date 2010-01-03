#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

typedef unsigned long long u64;
typedef unsigned int u32;

#define ABS(x) (((x) < 0) ? -(x) : (x))

struct Big {
	u32 *d;
	int size, alloc;

	void resize(int need) {
		if (d == NULL) {
			alloc = need;
			d = (u32 *)malloc(alloc * sizeof(u32));
			size = 0;
		} else if (alloc < need) {
			alloc = max(need, ABS(size)+1) + 16;
			d = (u32 *)realloc(d, alloc * sizeof(u32));
		}
	}

	~Big() { assert(d != NULL); free(d); d = NULL; }

	Big(int x = 0, int reserve = 4) {
		d = NULL;
		resize(reserve);
		size = x < 0 ? -1 : (x > 0 ? 1 : 0);
		d[0] = ABS(x);
	}

	Big(const Big &y, int reserve = 4) {
		d = NULL;
		resize(max(ABS(y.size)+1, reserve));
		size = y.size;
		memcpy(d, y.d, ABS(size) * sizeof(u32));
	}

	Big &operator =(const Big &y) {
		size = y.size;
		resize(ABS(size)+1);
		memcpy(d, y.d, ABS(size) * sizeof(u32));
		return *this;
	}

	Big &operator =(int y) {
		if (y > 0) size = 1, d[0] = y;
		else if (y < 0) size = -1, d[0] = -y;
		else size = 0;
		return *this;
	}

	void rmz() {
		if (size >= 0) {
			while (size > 0 && d[size-1] == 0) size--;
		} else {
			size = -size;
			while (size > 0 && d[size-1] == 0) size--;
			size = -size;
		}
	}

	/* this = |x| + |y| */
	void madd(const Big &x, const Big &y) {
		int xn = ABS(x.size), yn = ABS(y.size), m = (xn < yn) ? xn : yn;
		resize(m+1);

		u64 c = 0;
		u32 *zp = d, *xp = x.d, *yp = y.d;
		for (; m--; c >>= 32) {
			c += (u64)(*xp++) + (u64)(*yp++);
			*zp++ = (u32)c;
		}

		if (xn >= yn) { m = xn - yn; } else { m = yn - xn; xp = yp; }
		if (xp != zp) {
			for (; m--; c >>= 32) { c += (u64)(*xp++); *zp++ = (u32)c; }
			if (c != 0) *zp++ = 1;
			size = zp - d;
		} else if (c != 0) {
			while (m-- && *zp == 0xFFFFFFFF) *zp++ = 0;
			if (m < 0) { *zp++ = 1; size = zp - d; } else (*zp)++;
		}
	}

	Big &operator +=(const Big &y) {
		if (y.size == 0) return *this;
		if (size == 0) return (*this = y);

		if ((size > 0 && y.size > 0) || (size < 0 && y.size < 0)) {
			int sign = (size < 0) ? -1 : 1;
			madd(*this, y);
			size *= sign;
			return *this;
		}

                /*fixme*/
		return *this;
	}

	u32 mdiv1(u32 y) {
		u64 r = 0;
		for (int i = ABS(size)-1; i >= 0; i--) {
			r = (r << 32) | d[i];
			d[i] = r / y;
			r %= y;
		}
		rmz();
		return (u32)r;
	}

	void mmul1(u32 y) {
		if (y == 0) {
			size = 0;
		} else {
			u64 c = 0;
			int n = ABS(size);
			for (int i = 0; i < n; i++) {
				c += (u64)d[i] * (u64)y;
				d[i] = (u32)c;
				c >>= 32;
			}
			if (c > 0) {
				if (n >= alloc) resize(n+1);
				d[n++] = (u32)c;
				size = (size < 0) ? -n : n;
			}
		}
	}

	Big &operator *=(int y) {
		if (y < 0) { y = -y; size = -size; }
		mmul1(y);
		return *this;
	}

	const char *c_str() const {
		static char *buf[16];
		static int pos = -1;

		if (size == 0) return "0";

		if (pos < 0) memset(buf, 0, sizeof(buf));
		pos = (pos + 1) & 15;
		if (buf[pos] != NULL) free(buf[pos]);

		int sz = ABS(size) * 12 + 10;
		buf[pos] = (char *)malloc(sz);

		char *s = buf[pos] + sz;
                *--s = '\0';

		Big t(*this);
		t.size = ABS(t.size);
		for (int i = 0; t.size != 0; i++) {
			unsigned r = t.mdiv1(1000000000U);
			for (int j = 0; j < 9; j++, r /= 10)
				*--s = '0' + (r % 10);
		}
		while (*s == '0') s++;

		if (size < 0) *--s = '-';

		return s;
	}
};

int main()
{
	int F, N, S;

	while (scanf("%d %d %d", &F, &N, &S) == 3) {
		Big denom = 1;
		for (int i = 0; i < N; i++) denom *= F;
		if (S < 1 || S > F*N) { printf("0/%s\n", denom.c_str()); continue; }

		vector<Big> A(S+1, 0), B(S+1, 0);
		A[0] = 1;
		for (int n = 1; n <= N; n++) {
			int u1 = min(n*F, S);
			for (int s = n; s <= u1; s++) {
				B[s] = 0;
				int u = min(F, s-n+1);
				for (int k = max(1, s-(n-1)*F); k <= u; k++)
					B[s] += A[s-k];
			}
			A.swap(B);
		}

		printf("%s/%s\n", A[S].c_str(), denom.c_str());
	}

	return 0;
}
