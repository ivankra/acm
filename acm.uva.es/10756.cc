#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;

const double EPS = 1e-6;

int goal;
bool rule[256];

int D[50], N;
char DS[50][8];

double S[50];

int expr_op[50], expr_pos;
char *expr_num[50];

string fmt()
{
	assert(expr_pos > 0);
	expr_pos--;
	if (expr_op[expr_pos] == 'n')
		return string(expr_num[expr_pos]);

	char op = expr_op[expr_pos];
	string r = fmt();
	string l = fmt();
	return "(" + l + op + r + ")";
}

bool go(int dp, int sn, int ep)
{
	if (dp == N && sn == 1) {
		if (fabs(S[0] - goal) > EPS) return false;

		expr_pos = ep;
		printf("%s\n", fmt().c_str());
		return true;
	}

	if (dp < N) {
		expr_op[ep] = 'n';
		expr_num[ep] = DS[dp];
		S[sn] = D[dp];
		if (go(dp+1, sn+1, ep+1)) return true;
	}

	if (sn < 2) return false;

	for (int i = 0; i < 4; i++) {
		expr_op[ep] = "+-*/"[i];
		if (!rule[expr_op[ep]]) continue;

		double a = S[sn-2];
		double b = S[sn-1];

		double res;
		if (i == 0) res = a + b;
		else if (i == 1) res = a - b;
		else if (i == 2) res = a * b;
		else {
			if (fabs(b) < EPS) continue;
			res = a / b;
		}

		S[sn-2] = res;
		if (go(dp, sn-1, ep+1)) return true;

		S[sn-2] = a;
		S[sn-1] = b;
	}

	return false;
}

set<string> memo2;

bool solve3()
{
//	printf("solve3: D = { ");for (int i = 0; i < N; i++)printf("%d ", D[i]);printf("}\n");
	return go(0, 0, 0);
}

bool solve2(char *digits)
{
	if (!memo2.insert(digits).second) return false;

	if (rule['j']) {
		int n = strlen(digits);
		for (int m = 1<<(n-1); m < (1 << n); m++) {
			N = 0;
			D[0] = 0;
			for (int i = 0, k = 0; i < n; i++) {
				D[N] = D[N] * 10 + digits[i]-'0';
				DS[N][k++] = digits[i];
				if (m & (1 << i)) {
					DS[N][k] = 0;
					k = 0;
					N++;
					D[N] = 0;
				}
			}
			if (solve3()) return true;
		}
		return false;
	} else {
		N = strlen(digits);
		for (int i = 0; i < N; i++) {
			D[i] = digits[i]-'0';
			DS[i][0] = digits[i];
			DS[i][1] = 0;
		}
		return solve3();
	}
}

bool solve1(char *digits)
{
	if (rule['x']) {
		int n = strlen(digits);
		for (int m = 1; m < (1 << n); m++) {
			char s[10];
			int k = 0;
			for (int i = 0; i < n; i++)
				if (m & (1 << i)) s[k++] = digits[i];
			s[k] = 0;
			if (solve2(s)) return true;
		}
		return false;
	} else {
		return solve2(digits);
	}
}

int main()
{
	int T;
	scanf("%d", &T);

	char digits[100], rules[100];
	for (int cs = 1; cs <= T; cs++) {
		if (cs > 1) printf("\n");
		scanf(" %s %d %s", digits, &goal, rules);

		for (int i = 0; i < 256; i++)
			rule[i] = false;
		for (int i = 0; rules[i]; i++)
			rule[(int)rules[i]] = true;

		memo2.clear();

		bool can = false;
		if (rule['p']) {
			int n = strlen(digits);
			sort(digits, digits+n);
			do {
				if (solve1(digits)) { can = true; break; }
			} while (next_permutation(digits, digits+n));
		} else {
			can = solve1(digits);
		}

		if (!can) printf("Impossible\n");
	}
}
