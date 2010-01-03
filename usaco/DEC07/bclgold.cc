/*
TASK: bclgold
LANG: C++
ID: infnty1
*/
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;

char in[100000], out[100000];
int rank[100000], sa[100000], L;
long long key[100000];

bool cmp(int i, int j) { return key[i] < key[j]; }

void buildRanks()
{
	for (int i = 0; i <= L; i++) {
		sa[i] = i;
		key[i] = in[i];
	}

	sort(sa, sa+L+1, cmp);

	for (int K = 1; ; K *= 2) {
		for (int i = 0; i <= L; i++)
			rank[sa[i]] = (i > 0 && key[sa[i-1]] == key[sa[i]] ? rank[sa[i-1]] : i);
		if (K > L) break;
		for (int i = 0; i <= L; i++)
			key[sa[i]] = rank[sa[i]] * 1000000LL + (sa[i]+K <= L ? rank[sa[i]+K] : 0);
		sort(sa, sa+L+1, cmp);
	}
}

int main()
{
	assert(freopen("bclgold.in", "r", stdin) != NULL);
	assert(freopen("bclgold.out", "w", stdout) != NULL);

	int N;
	scanf("%d", &N);
	memset(in, 0, sizeof(in));
	for (int i = 0; i < N; i++) {
		scanf(" %c", &in[i]);
		in[N+N-i] = in[i];
	}
	in[N] = ' ';
	L = N+1+N;
	buildRanks();

	int a = 0, b = N-1, outPos = 0;
	while (outPos < N) {
		if (in[a] < in[b] || a == b) {
			out[outPos++] = in[a++];
		} else if (in[b] < in[a]) {
			out[outPos++] = in[b--];
		} else {
			// in[a] == in[b]
			char c = in[a];
			int i = 1;
			while (a+i < b-i && in[a+i] == c && in[b-i] == c)
				i++;

			for (int k = 0; k < i; k++)
				out[outPos++] = c;

			if (rank[a+i] < rank[N+1+(N-1-(b-i))])
			//if (strcmp(in+(a+i), in+(N+1+(N-1-(b-i)))) < 0)
				a += i;
			else
				b -= i;
		}
	}

	for (int i = 0; i < outPos; i += 80) {
		for (int j = 0; j < 80 && i+j < outPos; j++)
			putchar(out[i+j]);
		putchar('\n');
	}
}
