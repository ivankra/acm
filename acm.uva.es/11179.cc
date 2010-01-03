#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
#include <set>
using namespace std;

int chunkLen, A[250000], N;
unsigned long long checkMul, checkMod, claimedChecksum;

int currentPos;             // [0, chunkLen)
unsigned long long currentChecksum, currentNum, totalLen;

void emit(int n, int bit) {
	for (int i = 0; i < n; i++) {
		currentNum = (currentNum << 1) + (unsigned)bit;
		if (++currentPos == chunkLen) {
			currentChecksum = (currentChecksum * checkMul + currentNum) % checkMod;
			currentNum = 0;
			currentPos = 0;
		}
	}
}

unsigned long long modpow(unsigned long long b, int n) {
	unsigned long long res = 1;
	for (; n != 0; n >>= 1) {
		if (n & 1)
			res = (res * b) % checkMod;
		b = (b * b) % checkMod;
	}
	return res;
}

// computes x^n and x+x^2+...+x^n.
void modpowsum(unsigned long long x, int n, unsigned long long &out_pow, unsigned long long &out_sum) {
	if (n == 0) {
		out_pow = 1;
		out_sum = 0;
	} else if (n == 1) {
		out_pow = x;
		out_sum = x;
	} else {
		modpowsum(x, n>>1, out_pow, out_sum);
		// x+...+x^{2n} = (x+...+x^n) + x^n (x+...+x^n) = (x+...+x^n)*(1+x^n).
		out_sum = (out_sum * (1ULL + out_pow)) % checkMod;
		out_pow = (out_pow * out_pow) % checkMod;

		if ((n & 1) == 1) {
			out_pow = (out_pow * x) % checkMod;
			out_sum = (out_sum + out_pow) % checkMod;
		}
	}
}

void emitLong(int n, int bit) {
	if (n <= 0) return;
	assert(currentPos == 0); assert(n % chunkLen == 0);
//	emit(n, bit); return;

	n /= chunkLen;
	if (bit == 0) {
		currentChecksum = (currentChecksum * modpow(checkMul, n)) % checkMod;
	} else {
		unsigned long long x = (1ULL << chunkLen) - 1ULL, m_pow, m_sum;
		modpowsum(checkMul, n-1, m_pow, m_sum);
		m_pow = (m_pow * checkMul) % checkMod;
		m_sum = (m_sum + 1) % checkMod;
		currentChecksum = (currentChecksum * m_pow) % checkMod;
		currentChecksum = ((currentChecksum + (x * m_sum)) % checkMod) % checkMod;
	}
}

unsigned long long computeChecksum() {
	if (checkMod <= 1) return 0;

	checkMul %= checkMod;
	currentPos = 0;
	currentChecksum = 0;
	currentNum = 0;

	for (int i = 0; i < N; i++) {
		if (A[i] == 0) continue;

		int prefix = (chunkLen - currentPos % chunkLen) % chunkLen;
		int postfix = (currentPos + A[i]) % chunkLen;

		if (prefix + postfix >= A[i]) {
			emit(A[i], i&1);
		} else {
			emit(prefix, i&1);
			emitLong(A[i]-prefix-postfix, i&1);
			emit(postfix, i&1);
		}
	}

	if (currentPos != 0)
		emit(chunkLen - currentPos, 0);
//printf("%lld ",currentChecksum);

	currentChecksum %= checkMod;
	return currentChecksum;
}

int main() {
	for (int cs = 1; scanf("%llu %d %llu %llu %llu", &totalLen, &chunkLen, &checkMul, &checkMod, &claimedChecksum) == 5; cs++) {
		if (totalLen <= 0) break;

		N = 0;
		while (scanf("%d", &A[N]) == 1) {
			if (A[N] == 0 && N > 0) break;
			N++;
		}

		printf("Bitstream %d: ", cs);

		unsigned long long len = 0;
		for (int i = 0; i < N; i++)
			len += A[i];

		if (len != totalLen) {
			printf("Invalid Length\n");
			continue;
		}

		if (computeChecksum() != claimedChecksum)
			printf("Invalid Checksum\n");
		else
			printf("Compression OK\n");
	}
}
