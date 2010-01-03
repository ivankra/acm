#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <iostream>
#include <complex>
using namespace std;

typedef complex<long double> Complex;
long double PI = 2 * acos(0.0L);

unsigned revtab[65536];

void FFT_init() {
    for (int x = 0; x < 65536; x++) {
        int y = 0;
        for (int i = 0; i < 16; i++)
            y |= ((x >> i) & 1) << (15 - i);
        revtab[x] = y;
    }
}

// Decimation-in-time radix-2 FFT.
//
// Computes in-place the following transform:
//   y[i] = A(w^(dir*i)),
// where
//   w = exp(2pi/N) is N-th complex principal root of unity,
//   A(x) = a[0] + a[1] x + ... + a[n-1] x^{n-1},
//   dir \in {-1, 1} is FFT's direction (+1=forward, -1=inverse).
//
// Notes:
//   * N must be a power of 2
//   * Inverse FFT generally needs to be followed by scaling by 1/N
void FFT(Complex *a, int N, int dir)
{
    int lgN;
    for (lgN = 1; (1 << lgN) < N; lgN++);
    assert((1 << lgN) == N);

    for (unsigned i = 0; i < N; i++) {
        unsigned j = ((revtab[i & 65535] << 16) | revtab[i >> 16]) >> (32 - lgN);
        if (i < j) swap(a[i], a[j]);
    }

    for (int s = 1; s <= lgN; s++) {
        int h = 1 << (s - 1);
        Complex t, w, w_m = exp(Complex(0, dir*PI/h));
        for (int k = 0; k < N; k += h+h) {
            w = 1;
            for (int j = 0; j < h; j++) {
                t = w * a[k+j+h];
                a[k+j+h] = a[k+j] - t;
                a[k+j] += t;
                w *= w_m;
            }
        }
    }
}


// Solution for http://www.spoj.pl/problems/VFMUL/

#define GRP   5       // number of decimal digits in each group
#define RADIX 100000  // 10^GRP

void parse(vector<Complex> &v, const char *s)
{
    int n = strlen(s);
    int m = (n + GRP-1) / GRP;
    v.resize(m);
    for (int i = 0; i < m; i++) {
        int b = n - GRP * i, x = 0;
        for (int a = max(0, b - GRP); a < b; a++)
            x = x * 10 + s[a] - '0';
        v[i] = x;
    }
}

void print(const vector<Complex> &v)
{
    int i, N = v.size();
    vector<long long> digits(N + 1, 0);
    long double err = 0;

    for (i = 0; i < N; i++) {
        long long x = (long long)(v[i].real() + 0.5);
        err = max(err, (long double)abs(x - v[i].real()));
        err = max(err, (long double)abs(v[i].imag()));
        digits[i] = x;
    }

    fprintf(stderr, "[error=%.3Lg]\n", err);

    long long c = 0;
    for (i = 0; i < N; i++) {
        c += digits[i];
        digits[i] = c % RADIX;
        c /= RADIX;
    }
    assert(c == 0);

    for (i = N-1; i > 0 && digits[i] == 0; i--);
    printf("%lld", digits[i]);
    for (i--; i >= 0; i--)
        printf("%.*lld", GRP, digits[i]);
    printf("\n");
}

long long rdtsc() {
    long long res;
    asm volatile("rdtsc" : "=A"(res));
    return res;
}

int main()
{
    static char a_str[310000], b_str[310000];
    int T;

    FFT_init();

    scanf("%d", &T);
    while (T--) {
        assert(scanf(" %s %s", a_str, b_str) == 2);

        vector<Complex> A, B;
        parse(A, a_str);
        parse(B, b_str);

        int N = 1;
        while (N < max(A.size(), B.size())) N *= 2;
        N *= 2;
        A.resize(N);
        B.resize(N);

        fprintf(stderr, "[N=%d] ", N);

        long long t = rdtsc();

        FFT(&A[0], N, +1);
        FFT(&B[0], N, +1);
        for (int i = 0; i < N; i++) A[i] *= B[i];
        FFT(&A[0], N, -1);
        for (int i = 0; i < N; i++) A[i] /= N;

        t = rdtsc() - t;

        fprintf(stderr, "[%.0fK] ", t / 1000.0);

        print(A);
    }
}
