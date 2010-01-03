#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

struct Statement {
	int op;
	int var, num;
	Statement() {}
	Statement(int op_, int var_ = -1, int num_ = -1) { op = op_; var = var_; num = num_; }
};

struct Program {
	int id, cur;
	vector<Statement> code;
};

int N, quantum, cost[256], variable[26];
Program *progs[100000];
deque<Program *> readyQ, blockQ;
Program *holder;

void simulate()
{
	memset(variable, 0, sizeof(variable));
	holder = NULL;

	readyQ.clear();
	blockQ.clear();

	for (int i = 1; i <= N; i++)
		readyQ.push_back(progs[i]);

	while (!readyQ.empty()) {
		Program *p = readyQ.front();
		readyQ.pop_front();

		int tm = quantum;
		while (true) {
			if (tm <= 0) {
				readyQ.push_back(p);
				break;
			}

			if (p->cur >= (int)p->code.size()) break;

			const Statement &s = p->code[p->cur++];
			tm -= cost[s.op];
//printf("<currently executing: id=%d line=%d (%c var=%d num=%d)>\n",p->id, p->cur, s.op, s.var, s.num);

			if (s.op == 'e') {
				break;
			} else if (s.op == 'p') {
				printf("%d: %d\n", p->id, variable[s.var]);
			} else if (s.op == '=') {
				variable[s.var] = s.num;
			} else if (s.op == 'l') {
				if (holder == NULL) {
					holder = p;
				} else {
					p->cur--;
					blockQ.push_back(p);
					tm = 0;
					break;
				}
			} else {
				assert(holder == p);
				holder = NULL;

				if (!blockQ.empty()) {
					readyQ.push_front(blockQ.front());
					blockQ.pop_front();
				}
			}
		}
	}
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		for (int i = 0; i < 5; i++)
			scanf("%d", &cost["=plue"[i]]);
		scanf("%d", &quantum);

		for (int i = 1; i <= N; i++) {
			progs[i] = new Program();
			progs[i]->id = i;
			progs[i]->cur = 0;

			vector<Statement> &code = progs[i]->code;
			code.clear();

			while (true) {
				char s[100];
				int k = scanf(" %s", s);
				assert(k == 1);
				s[0] = tolower(s[0]);

				if (strlen(s) > 1) {
					code.push_back(Statement(s[0]));
					if (s[0] == 'p') {
						scanf(" %s", s);
						code.back().var = tolower(s[0]) - 'a';
					}
				} else {
					code.push_back(Statement('=', s[0] - 'a'));
					scanf(" = %d", &code.back().num);
				}

				if (code.back().op == 'e') break;
			}
		}

		simulate();

		for (int i = 1; i <= N; i++) {
			delete progs[i];
		}

		if (cs < T) printf("\n");
	}
}
