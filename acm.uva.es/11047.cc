#include <cstdio>
#include <map>
#include <string>
using namespace std;

int a[128][128], next[128][128];
string city[128];

map<string, int> name2id_map;
int name2id(string s) {
	if (name2id_map.count(s) == 0)
		return -1;
	return name2id_map[s];
}

int main() {
	int T, N;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		name2id_map.clear();
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			char s[1024];
			scanf(" %[^\t\r\n]", s);
			city[i] = s;
			name2id_map[city[i]] = i;
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &a[i][j]);
				next[i][j] = j;
			}
		}

		for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (a[i][k] < 0 || a[k][j] < 0) continue;
			if (a[i][j]>=0 && a[i][j] <= a[i][k]+a[k][j]) continue;

			a[i][j] = a[i][k] + a[k][j];
			next[i][j] = next[i][k];
		}

		int nq;
		for (scanf("%d", &nq); nq-- > 0;) {
			char emp[256], st[256], en[256];
			scanf(" %[^\t\r\n] %[^\t\r\n] %[^\t\r\n]", emp, st, en);

			int x = name2id(st);
			int y = name2id(en);
			if (x < 0 || y < 0 || a[x][y] < 0) {
				printf("Sorry Mr %s you can not go from %s to %s\n",
					emp, st, en);
				continue;
			}

			printf("Mr %s to go from %s to %s, you will receive %d euros\n",
					emp, st, en, a[x][y]);
			printf("Path:%s ", st);
			for (x = next[x][y]; x != y; x = next[x][y])
				printf("%s ", city[x].c_str());
			printf("%s\n", en);
		}		
	}
}	
