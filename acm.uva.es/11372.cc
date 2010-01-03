#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
#define foreach(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

struct Problem {
	int id;
	char diff, type;
	int favor;

	bool operator <(const Problem &o) const {
		return id < o.id;
	}
};

int N;
Problem prob[201];

int memo[202][3][3][3][3][3][3];
vector<int> ans;

int f(int at, int haveE, int haveM, int haveH, int needD, int needG, int needM)
{
	if (haveE > 2) return -1000000;
	if (haveM > 2) return -1000000;
	if (haveH > 2) return -1000000;

	if (needD < 0) needD = 0;
	if (needG < 0) needG = 0;
	if (needM < 0) needM = 0;

	int &res = memo[at][haveE][haveM][haveH][needD][needG][needM];
	if (res != -1) return res;

	if (at == N) {
		if (haveE + haveM + haveH != 6) return res = -1000000;
		if (needD > 0 || needG > 0 || needM > 0) return res = -1000000;
		return res = 0;
	}

	res = f(at+1, haveE, haveM, haveH, needD, needG, needM);

	int with = f(
			at+1,
			haveE + (prob[at].diff == 'E' ? 1 : 0),
			haveM + (prob[at].diff == 'M' ? 1 : 0),
			haveH + (prob[at].diff == 'H' ? 1 : 0),
			needD - (prob[at].type == 'D' ? 1 : 0),
			needG - (prob[at].type == 'G' ? 1 : 0),
			needM - (prob[at].type == 'M' ? 1 : 0)) + prob[at].favor;
	res = max(res, with);

//printf("f at=%d EMH=%d/%d/%d DGM=%d/%d/%d => %d with%d\n", at,haveE,haveM,haveH, needD,needG,needM, res,with);
	return res;
}

void recover(int at, int haveE, int haveM, int haveH, int needD, int needG, int needM)
{
	assert(haveE <= 2 && haveM <= 2 && haveH <= 2);

	if (needD < 0) needD = 0;
	if (needG < 0) needG = 0;
	if (needM < 0) needM = 0;

	if (at == N) {
		assert(haveE + haveM + haveH == 6);
		return;
	}

	int res = f(at,haveE,haveM,haveH,needD,needG,needM);

	int with = f(
			at+1,
			haveE + (prob[at].diff == 'E' ? 1 : 0),
			haveM + (prob[at].diff == 'M' ? 1 : 0),
			haveH + (prob[at].diff == 'H' ? 1 : 0),
			needD - (prob[at].type == 'D' ? 1 : 0),
			needG - (prob[at].type == 'G' ? 1 : 0),
			needM - (prob[at].type == 'M' ? 1 : 0)) + prob[at].favor;

//printf("recover at=%d EMH=%d/%d/%d DGM=%d/%d/%d => %d with %d\n", at,haveE,haveM,haveH, needD,needG,needM, res,with);

	if (res == with) {
		ans.push_back(prob[at].id);
		recover(
			at+1,
			haveE + (prob[at].diff == 'E' ? 1 : 0),
			haveM + (prob[at].diff == 'M' ? 1 : 0),
			haveH + (prob[at].diff == 'H' ? 1 : 0),
			needD - (prob[at].type == 'D' ? 1 : 0),
			needG - (prob[at].type == 'G' ? 1 : 0),
			needM - (prob[at].type == 'M' ? 1 : 0));
	} else {
		recover(at+1, haveE, haveM, haveH, needD, needG, needM);
	}
}

void solve()
{
	memset(memo, 0xff, sizeof(memo));
	ans.clear();

	int fav = f(0, 0,0,0, 2,1,1);
	if (fav < 0) {
		printf("No solution.\n");
		return;
	}

	recover(0, 0,0,0, 2,1,1);
	if (ans.size() != 6) {
		printf("No solution.\n");
		return;
	}

	assert(ans.size() == 6);

	for (int i = 0; i < 6; i++)
		printf(i < 5 ? "%.3d " : "%.3d\n", ans[i]);
}

int main()
{
	char buf[10000];

	while (gets(buf)) {
		if (sscanf(buf, "%d", &N) != 1) break;
		if (N <= 0) break;

		for (int i = 0; i < N; i++) {
			char *s = gets(buf);
			assert(s != NULL);

			buf[3] = 0;
			prob[i].id = atoi(buf);

			prob[i].diff = toupper(buf[31-1]);
			prob[i].type = toupper(buf[33-1]);
			prob[i].favor = buf[35-1]-'0';
		}

		sort(prob, prob+N);
		solve();
	}
}
