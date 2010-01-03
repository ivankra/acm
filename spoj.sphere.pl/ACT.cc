#include <cstdio>
#include <cstring>

int main()
{
	int T, N;
	char S[100000];
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %s", &N, S);
		printf("%c\n", S[strlen(S)-1]);
	}
}
