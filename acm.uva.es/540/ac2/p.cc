#include <cstdio>
#include <cstring>
#include <cctype>
#include <cassert>
#include <queue>
using namespace std;

int N, team_of[1000010];
queue<int> Main, team[1010];

int main() {
	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		Main = queue<int>();
		for (int i = 0; i < N; i++) team[i] = queue<int>();

		for (int i = 0; i < N; i++) {
			int m, x;
			scanf("%d", &m);
			for (int j = 0; j < m && scanf("%d", &x)==1; j++)
				team_of[x] = i;
		}

		printf("Scenario #%d\n", cs);
		char cmd[100];
		while (scanf(" %s", cmd) == 1) {
			cmd[0] = toupper(cmd[0]);
			if (cmd[0]=='E') {
				int x;
				scanf("%d", &x);

				int t = team_of[x];
				if (team[t].size() == 0)
					Main.push(t);
				team[t].push(x);
			} else if (cmd[0]=='D') {
				assert(Main.size() != 0);
				int t = Main.front();
				printf("%d\n", team[t].front(), t);
				team[t].pop();
				if (team[t].size() == 0) Main.pop();
			} else if (cmd[0] == 'S') {
				break;
			}
		}
		printf("\n");
	}
}
