/*
ID: infnty1
PROB: prime3
LANG: C++
*/
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

//#define NO_SYMMETRY		// Symmetry from transposition

int primesum, upleft, t_next[100000][16], t_sum[100000], t_count, t_val[100000];
int t_out[100000], t_first[100000], first_bit[1024], okay_n[100001];
int row1;
char isprime[100010], *t_num[50000], okay[10][10][10][10][10];
vector<string> sol;

#define for_each_bit(K, X) \
	for(int K,ZZ##K=(X);(ZZ##K)!=0;(ZZ##K)&=(ZZ##K)-1){K=first_bit[ZZ##K];

int digsum(int n) { return n > 9 ? digsum(n/10) + n%10 : n; }

static void doit3(int v[]) {
    static int w[8], tmp;

    for_each_bit(a, t_out[v[0]] & t_out[0])
        w[0] = t_next[v[0]][a];

#ifndef NO_SYMMETRY
        if (t_val[w[0]] > row1) continue;
#endif

        int b = t_sum[w[0]] - v[6];
        if (b < 0 || b > 9) continue;

        if ((w[1] = t_next[v[1]][b]) == 0) continue;
        if (t_next[t_next[0][a]][b] == 0) continue;

        w[6] = v[6] + b;

        int a1 = t_first[w[0]];
        if (a1 != primesum - w[6]) continue;
        if ((tmp = t_next[0][a1]) == 0) continue;
        int b1 = t_first[w[1]];
        if (t_next[tmp][b1] == 0) continue;

        for_each_bit(d, t_out[v[3]] & t_out[v[5]])
            w[5] = t_next[v[5]][d];
            w[3] = t_next[v[3]][d];

            int d1 = t_first[w[3]];
            int e1 = t_first[w[5]];
            int c1 = primesum - a1 - b1 - d1 - e1;

            if (!okay[a1][b1][c1][d1][e1]) continue;

            int c = primesum - c1 - t_sum[v[2]];
            if ((w[2] = t_next[v[2]][c]) == 0) continue;

            int e = primesum - e1 - t_sum[v[4]];
            if (!okay[a][b][c][d][e]) continue;
            if ((w[4] = t_next[v[4]][e]) == 0) continue;
            if (t_first[w[4]] != e1) continue;

            for (int tr = 0; tr < 2; tr++) {
                string s = "";
                int p = 0;
                for (int Row = 0; Row < 5; Row++) {
                    for (int Col = 0; Col < 5; Col++) {
                        int dig = (tr==0 ? t_num[w[Col]][Row] : t_num[w[Row]][Col]) - '0';
                        s += (char)(dig + '0');
                        if (Col == 4-Row) p = p * 10 + dig;
                    }
                    s += '\n';
                }
                int q = 0;
                for (int i = 0; i < 5; i++, p /= 10) q = q * 10 + (p % 10);
                if (okay_n[q]) sol.push_back(s);
            }

        }
    }
}

static void doit(int row, int v[]) {
    int w[8], col[4], dig[5];

    for_each_bit(a, t_out[v[0]] & t_out[0])
        if (row == 0 && a != upleft) continue;
        col[0] = t_next[0][a];
        w[0] = t_next[v[0]][a];
        dig[0] = a;

#ifndef NO_SYMMETRY
        if (row > 0 && t_val[w[0]] > row1) continue;
#endif

        for_each_bit(b, t_out[v[1]] & t_out[col[0]])
            col[1] = t_next[col[0]][b];
            w[1] = t_next[v[1]][b];
            dig[1] = b;

            for_each_bit(c, t_out[v[2]] & t_out[col[1]])
                col[2] = t_next[col[1]][c];
                w[2] = t_next[v[2]][c];
                dig[2] = c;

                for_each_bit(d, t_out[v[3]] & t_out[col[2]])
                    int e = primesum - t_sum[t_next[col[2]][d]];
                    if ((w[4] = t_next[v[4]][e]) == 0) continue;
                    dig[3] = d;
                    dig[4] = e;

                    if ((w[5] = t_next[v[5]][dig[row]]) == 0) continue;
                    w[6] = v[6] + dig[4-row];

                    w[3] = t_next[v[3]][d];

                    if (row == 0) {
                        row1 = (((a*10+b)*10+c)*10+d)*10+e;
                        doit(1, w);
                    } else if (row == 2) {
                        doit3(w);
                    } else {
                        doit(row+1, w);
                    }
                }
            }
        }
    }
}

int main() {
	freopen("prime3.in", "r", stdin);
	freopen("prime3.out", "w", stdout);

	scanf("%d %d", &primesum, &upleft);

int tmr=clock();

	memset(isprime, 1, sizeof(isprime));
	isprime[0] = isprime[1] = 0;
	for (int k = 2; k < 1000; k++) {
		if (!isprime[k]) continue;
		for (int i = k*k; i <= 100000; i += k)
			isprime[i] = 0;
	}

	for (int x = 0, i; x < 1024; x++) {
		for (i = 0; i < 11 && ((x >> i) & 1) == 0; i++);
		first_bit[x] = i;
	}

	t_count = 1;
	memset(t_next, 0, sizeof(t_next));
	memset(t_sum, 0, sizeof(t_sum));
	memset(t_num, 0, sizeof(t_num));
	memset(t_val, 0, sizeof(t_val));
	memset(okay, 0, sizeof(okay));
	memset(okay_n, 0, sizeof(okay_n));
	t_num[0] = "00000";

	for (int k = 10000; k <= 99999; k++) {
		if (!isprime[k] || digsum(k) != primesum) continue;

		char *s = (char *)malloc(6);
		sprintf(s, "%.5d", k);

		char tmp[10] = "00000";

		for (int i = 0, x = 0, y = 0; i < 5; i++) {
			y += s[i] - '0';
			tmp[i] = s[i];

			if (t_next[x][s[i]-'0'] == 0) {
				t_next[x][s[i]-'0'] = ++t_count;
				t_sum[t_count] = y;
				t_num[t_count] = s;
				t_val[t_count] = atoi(tmp);
			}
			x = t_next[x][s[i]-'0'];
		}

		okay[s[0]-'0'][s[1]-'0'][s[2]-'0'][s[3]-'0'][s[4]-'0'] = 1;
		okay_n[k] = 1;
	}

	memset(t_out, 0, sizeof(t_out));
	for (int x = 0; x <= t_count; x++) {
		t_out[x] = 0;
		for (int i = 0; i < 10; i++)
			if (t_next[x][i] != 0) t_out[x] |= 1 << i;
		t_first[x] = first_bit[t_out[x]];
	}

	int u[]={0,0,0,0,0,0,0};
	sol.clear();
	doit(0,u);

	sort(sol.begin(), sol.end());
	sol.erase(unique(sol.begin(), sol.end()), sol.end());

	for (int i = 0; i < (int)sol.size(); i++)
		printf(i ? "\n%s" : "%s", sol[i].c_str());
	if (sol.size() == 0) printf("NONE\n");

fprintf(stderr, "[%d]  t_count=%d\n", (int)(clock()-tmr), t_count);

}
