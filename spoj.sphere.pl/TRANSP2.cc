#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cassert>
#include <map>
using namespace std;
typedef long long LL;

int prime[] = {
// {{{
2,
3,
5,
7,
11,
13,
17,
19,
23,
29,
31,
37,
41,
43,
47,
53,
59,
61,
67,
71,
73,
79,
83,
89,
97,
101,
103,
107,
109,
113,
127,
131,
137,
139,
149,
151,
157,
163,
167,
173,
179,
181,
191,
193,
197,
199,
211,
223,
227,
229,
233,
239,
241,
251,
257,
263,
269,
271,
277,
281,
283,
293,
307,
311,
313,
317,
331,
337,
347,
349,
353,
359,
367,
373,
379,
383,
389,
397,
401,
409,
419,
421,
431,
433,
439,
443,
449,
457,
461,
463,
467,
479,
487,
491,
499,
503,
509,
521,
523,
541,
547,
557,
563,
569,
571,
577,
587,
593,
599,
601,
607,
613,
617,
619,
631,
641,
643,
647,
653,
659,
661,
673,
677,
683,
691,
701,
709,
719,
727,
733,
739,
743,
751,
757,
761,
769,
773,
787,
797,
809,
811,
821,
823,
827,
829,
839,
853,
857,
859,
863,
877,
881,
883,
887,
907,
911,
919,
929,
937,
941,
947,
953,
967,
971,
977,
983,
991,
997,
1009,
1013,
1019,
1021,
1031,
1033,
1039,
1049,
1051,
1061,
1063,
1069,
1087,
1091,
1093,
1097,
1103,
1109,
1117,
1123,
1129,
1151,
1153,
1163,
1171,
1181,
1187,
1193,
1201,
1213,
1217,
1223,
1229,
1231,
1237,
1249,
1259,
1277,
1279,
1283,
1289,
1291,
1297,
1301,
1303,
1307,
1319,
1321,
1327,
1361,
1367,
1373,
1381,
1399,
1409,
1423,
1427,
1429,
1433,
1439,
1447,
1451,
1453,
1459,
1471,
1481,
1483,
1487,
1489,
1493,
1499,
1511,
1523,
1531,
1543,
1549,
1553,
1559,
1567,
1571,
1579,
1583,
1597,
1601,
1607,
1609,
1613,
1619,
1621,
1627,
1637,
1657,
1663,
1667,
1669,
1693,
1697,
1699,
1709,
1721,
1723,
1733,
1741,
1747,
1753,
1759,
1777,
1783,
1787,
1789,
1801,
1811,
1823,
1831,
1847,
1861,
1867,
1871,
1873,
1877,
1879,
1889,
1901,
1907,
1913,
1931,
1933,
1949,
1951,
1973,
1979,
1987,
1993,
1997,
1999
// }}}
};

#define MAXF 20
int MOD = 1000003;
int A, B, N, pow2[1000010], invtab[1000010];
int FP[MAXF], FE[MAXF], FX[MAXF], FN;
int answer;

// ax + by = g
static void egcd(int a, int b, int &x, int &y, int &g)
{
    if (b == 0) {
        x = 1;
        y = 0;
        g = a;
    } else {
        // a = qb + r
        // (qb + r)x + by = g
        // (qx+y)b + rx = g
        //   y'  b + rx' = g
        egcd(b, a%b, y, x, g);
        y -= (a/b) * x;
    }
}

int inverse(int a)
{
	if (invtab[a] != 0) {
		return invtab[a];
	} else {
        int x, y, g;
        egcd(a, MOD, x, y, g);
        // ax + my = 1
        x %= MOD;
        if (x < 0) x += MOD;
        invtab[a] = x;
        return x;
    }

/*	int res = 1, b = x, e = MOD - 2;
	for (; e > 0; e >>= 1) {
		if (e & 1)
			res = (res * (LL)b) % MOD;
		b = (b * (LL)b) % MOD;
	}
	invtab[x] = res;
	assert((res * (LL)x) % MOD == 1);
	return res;*/
}

int encode(int e[]) {
	int res = 0;
	for (int i = 0; i < FN; i++)
		res += FX[i] * e[i];
	assert(res <= 10000);
	return res;
}

void factorize()
{
	int temp = N;
	FN = 0;
	for (int i = 0; prime[i] * prime[i] <= temp; i++) {
		if (temp % prime[i] == 0) {
			FP[FN] = prime[i];
			FE[FN] = 0;
			while (temp % prime[i] == 0) {
				temp /= prime[i];
				FE[FN]++;
			}
			FN++;
		}
	}
	if (temp > 1) { FP[FN] = temp; FE[FN] = 1; FN++; }
    assert(FN < MAXF);

	FX[0] = 1;
	for (int i = 1; i < FN; i++)
		FX[i] = FX[i-1] * (FE[i-1]+1);

}

int table[10000], seen[10000], seenId=1;

void dosub(int e[], int i, int enc, int maxe[], int target)
{
	if (i < FN) {
		for (e[i] = 0; e[i] <= maxe[i]; ++e[i])
			dosub(e, i+1, enc + e[i] * FX[i], maxe, target);
	} else if (enc != target) {
		table[target] += MOD - table[enc];
		if (table[target] >= MOD)
			table[target] -= MOD;
	}
}

void doit(int e[], int i, int enc, int prod)
{
	if (i < FN) {
		for (e[i] = 0; e[i] <= FE[i]; ++e[i]) {
			doit(e, i+1, enc + e[i] * FX[i], prod);
			prod *= FP[i];
		}
	} else {
		assert(seen[enc] < seenId);
		seen[enc] = seenId;
		table[enc] = pow2[__gcd(N/prod, A) * prod];
		int ee[MAXF];
		memset(ee, 0, sizeof(ee));
		dosub(ee, 0, 0, e, enc);

//printf("%d => %d   gcd(N/prod=%d,A=%d)*prod=%d   (enc=%d)\n\n",
//        prod, table[enc], N/prod,A, __gcd(N/prod, A)*prod, enc);

		answer = (answer + table[enc] * (LL)inverse(prod)) % MOD;
	}
}

/*
for k in divisors(n):
    counts[k] = 1 << gcd(n, a*k)
    for m in divisors(k):
        if m < k: counts[k] -= counts[m]
answer = (1<<N) - sum(counts[i]/i for i in counts.keys())
*/

int main()
{
	int T, e[MAXF];
	scanf("%d", &T);

	pow2[0] = 1;
	for (int i = 0; i <= 1000000; i++) {
		pow2[i+1] = pow2[i] + pow2[i];
		if (pow2[i+1] >= MOD) pow2[i+1] -= MOD;
	}

	for (int cs = 1; cs <= T; cs++) {
		if (scanf("%d %d", &A, &B) != 2) break;
		N = A + B;
		factorize();
		answer = 0;
		memset(e, 0, sizeof(e));
		doit(e, 0, 0, 1);
		answer = (pow2[N] + MOD - answer) % MOD;
		printf("%d\n", answer);
		seenId++;
	}
}
