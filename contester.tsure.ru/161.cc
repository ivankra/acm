#include <cstdio>
#include <cstring>
#include <string>
#include <map>
using namespace std;

int main() {
	int know[4096], x[4096], y[4096], N, M;
	char s[1024], t[1024];

	scanf("%d %d", &N, &M);

	map<string, int> Map;
	for (int i = 0; i < N; i++) {
                scanf(" %s", s);
                Map[s] = i;
	}

	for (int i = 0; i < M; i++) {
		scanf(" %s %s", s, t);
		x[i] = Map[s];
		y[i] = Map[t];
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) know[j] = 0;
		know[i] = 1;
		for (int k = 0; k < M; k++) {
			if (know[x[k]] || know[y[k]]) {
				know[x[k]] = know[y[k]] = 1;
			}
		}

		for (int j = 0; j < N; j++) {
			if (!know[j]) {
				printf("NO\n");
				return 0;
			}
		}
	}

	printf("YES\n");
	return 0;
}
