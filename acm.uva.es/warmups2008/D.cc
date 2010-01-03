#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
typedef long long LL;

#define MOD 100000007
#define MAXN 10000100

int ans[MAXN];
char isprime[MAXN];

int main()
{
    memset(isprime, 1, sizeof(isprime));
    isprime[0] = isprime[1] = 0;
    for (int i = 2; i <= 10000; i++) {
        if (isprime[i]) {
            for (int j = i*i; j < MAXN; j += i) isprime[j] = 0;
        }
    }

    ans[0] = 1;
    for (int n = 1; n < MAXN; n++) {
        if (isprime[n])
			ans[n] = (ans[n-1] * (LL)(n-1)) % MOD;
		else
			ans[n] = (ans[n-1] * (LL)n) % MOD;
    }

    int N, M;
    while (scanf("%d %d", &N, &M) == 2 && N > 0) {
        int res = ans[M];
        for (int n = M+1; n <= N; n++)
			res = (res * (LL)n) % MOD;
		res = ((res + MOD - 1) % MOD + MOD) % MOD;
        printf("%d\n", res);
    }
}
