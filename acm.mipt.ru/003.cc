#include <cstdio>
#include <vector>
using namespace std;

int G[256][256], N;

int main() {
	scanf("%d", &N);

	memset(G, 0xff, sizeof(G));
	for (int i = 0; i < N; i++) G[i][i] = 0;

	for (int i = 0; i < N; i++) {
		char s[256];
		scanf(" %s", s);
		for (int j = 0; j < i; j++) {
			G[i][j] = (s[j] == '+');
			G[j][i] = 1 - G[i][j];
		}
	}

	vector<int> v(1, 0);
	for (int m = 1; m < N; m++) {
		int i;
		for (i = 0; i < (int)v.size() && !G[m][v[i]]; i++);
		v.insert(v.begin() + i, m);
	}

	for (int i = 0; i < N; i++)
		printf(i+1 < N ? "%d " : "%d\n", v[i]+1);
}
