#include <cstdio>
#include <cassert>
#include <complex>
#include <vector>
#include <algorithm>
using namespace std;

typedef complex<long double> Complex;
long double PI = 2*acosl(0.0L);

long long rdtsc() {
    long long res;
    asm volatile("rdtsc" : "=A"(res));
    return res;
}

vector<Complex> FFT(const vector<Complex> &input) {
    int N = input.size(), lgN;
    for (lgN = 0; (1 << lgN) != N; lgN++);

    vector<Complex> a(N);
    for (int i = 0; i < N; i++) {
        int j = 0;
        for (int k = 0; k < lgN; k++)
            j |= ((i >> k) & 1) << (lgN - 1 - k);
        a[j] = input[i];
    }

    vector<Complex> r(N);
    r[0] = 1;
    r[1] = exp(Complex(0, 2*PI/N));
    for (int i = 1; i < N/2; i++) {
        r[2*i] = r[i] * r[i];
        r[2*i+1] = r[2*i] * r[1];
    }

    for (int s = 0; s < lgN; s++) {
        int m = 1 << s, n = 2*m, d = N/n;
        for (int k = 0; k < N; k += n) {
            for (int j = 0; j < m; j++) {
                Complex t = r[j*d] * a[k+j+m]; // r[j*(N/n)]=exp(Complex(0, 2*PI*j/n));
                a[k+j+m] = a[k+j] - t;
                a[k+j] += t;
            }
        }
    }

    return a;
}

int main()
{
    int N = 1024;

    vector<Complex> a(N);
    for (int i = 0; i < N; i++) {
        double t = i / (double)N;
        a[i] = 0;
        a[i] += sinl(2*PI*5*t);
        a[i] += 3*sinl(2*PI*7*t + 0.123);
        a[i] += 2*sinl(2*PI*20*t + 0.72346124);
        a[i] += 3.14*sinl(2*PI*510*t + 0.72346124);
        a[i] += 2.78*sinl(2*PI*511*t + 0.346124);
        a[i] += 10*sinl(2*PI*505.5*t + 0.346124);
    }

    vector<Complex> b = FFT(a);
    for (int i = 0; i < N/2; i++) printf("%d %.9g\n", i, (double)abs(b[i])/N*2);

    //for (int i = 0; i < N; i++) printf("%.9f %.9f\n", i/(double)N, (double)a[i].real());
}
