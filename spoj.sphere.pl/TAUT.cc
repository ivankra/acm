#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

char expr[1000];
int varIndex[256], args, K, pos;

bool eval()
{
	char c = expr[pos++];

	if (islower(c)) {
		return (args & (1 << varIndex[c])) != 0;
	} else if (c == 'N') {
		return !eval();
	} else {
		bool a = eval();
		bool b = eval();
		switch (c) {
			case 'C': return a & b;
			case 'D': return a | b;
			case 'I': return (!a) | b;
			case 'E': return a == b;
		}
		return false;
	}
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf(" %s", expr);

		memset(varIndex, 0xff, sizeof(varIndex));
		K = 0;
		for (int i = 0; expr[i]; i++) {
			if (islower(expr[i]) && varIndex[expr[i]] < 0) {
				varIndex[expr[i]] = K++;
			}
		}

		bool tautology = true;

		for (args = 0; args < (1 << K); args++) {
			pos = 0;
			if (eval() == false) {
				tautology = false;
				break;
			}
		}

		printf(tautology ? "YES\n" : "NO\n");
	}
}
