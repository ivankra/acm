#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cctype>

struct FD {
	int A, B;
};

int N, path[200], used[200], curFD;
FD fds[200];

int rec(int curLen, int known)
{
	int i, s;

	path[curLen] = -1;
	if ((known & fds[curFD].B) == fds[curFD].B) return 1;

	s = known;
	while (true) {
		bool changed = false;
		for (i = 0; i < N; i++) {
			if (used[i]) continue;
			if ((s & fds[i].A) != fds[i].A) continue;
			if ((s | fds[i].B) == s) continue;
			s |= fds[i].B;
		   	changed = true;
		}
		if (!changed || (s & fds[curFD].B) == fds[curFD].B) break;
	}
	if ((s & fds[curFD].B) != fds[curFD].B) return 0;

	s = known;
	for (i = 0; i < N; i++) {
		if (used[i]) continue;
		if ((s & fds[i].A) != fds[i].A) continue;
		if ((s | fds[i].B) == s) continue;

		used[i] = 1;
		if (rec(curLen, s)) return 1;

		path[curLen] = i;
		s |= fds[i].B;
		if (rec(curLen+1, s)) return 1;

		break;
	}

	assert(0==1);
	return 0;
}

void parseFD(char *line, FD &fd)
{
	fd.A = fd.B = 0;
	for (int i = 0, j = 0; line[i] != 0; i++) {
		if (line[i] == '>') j = 1;
		if (isupper(line[i])) {
			if (j == 0) fd.A |= 1 << (line[i] - 'A');
			fd.B |= 1 << (line[i] - 'A');
		}
	}
}

int main()
{
	char line[1000];

	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		for (int i = 0; i < N; i++) {
			scanf(" %s", line);
			parseFD(line, fds[i]);
		}

		printf("Set number %d\n", cs);

		int nr = 0;
		for (curFD = 0; curFD < N; curFD++) {
			memset(used, 0, sizeof(used));
			used[curFD] = 1;
			if (rec(0, fds[curFD].A)) {
				printf("     FD %d is redundant using FDs:", curFD+1);
				for (int j = 0; path[j] != -1; j++) printf(" %d", path[j]+1);
				printf("\n");
				nr++;
			}
		}

		if (nr == 0) {
			printf("     No redundant FDs.\n");
		}

		printf("\n");
	}
}
