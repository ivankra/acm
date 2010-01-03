#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;
typedef long long int64;

int len[131072], st[131072], N;
int mx[20][131072];

int solve(int a, int b)
{
	if (st[b] <= a) return b-a+1;

	int best = max(len[a], b-st[b]+1);
	b = st[b]-1;

	int k;
	for (k = 0; (1 << (k+1)) <= b-a+1; k++);

	best >?= mx[k][a];
	best >?= mx[k][b+1 - (1<<k)];

	return best;
}

struct MatchesOnTheTable {
	string getMaximumLength(string matches, string queries) {
		N = matches.size();

		memset(len, 0, sizeof(len));
		len[N-1] = 1;
		for (int i = N-2; i >= 0; i--) 
			len[i] = (matches[i] == matches[i+1]) ? 1+len[i+1] : 1;

		for (int i = 0; i < N; i++)
			mx[0][i] = len[i];

		for (int k = 1; (1 << k) <= N; k++) {
			int m = 1 << k;
			for (int i = 0; i+m <= N; i++)
				mx[k][i] = max(mx[k-1][i], mx[k-1][i+(1<<(k-1))]);
		}

		for (int i = 0; i < N; i += len[i])
			for (int j = 0; j < len[i]; j++)
				st[i+j] = i;

		string res = "";
		const char *q = queries.c_str();

		for (int i = 0; q[i] != 0; i++) {
			if (q[i] != '(') continue;

			char buf[100];
			strncpy(buf, q+i, 50);

			int a, b;
			sscanf(buf, " ( %d , %d ", &a, &b);
			sprintf(buf, "%d", solve(a, b));

			if (res.size() > 0) res += ' ';
			res += string(buf);
		}

		return res;
	}
};



/* Start of the testing code */
class MatchesOnTheTableChecker {
public:
	void doCheck (string output, vector<string> answer) {
		if (output == answer[0])
			cout << "Correct answer!" << endl;
		else
			cout << "Wrong answer: expected \""
			     << answer[0] << "\", got \"" << output << "\"" << endl;
	}
};

/* End of the testing code */

/* Start of the testing code */
int main() {
	/* Test 1 */ {
		cout << "Test 1" << endl;

		MatchesOnTheTableChecker __checker;
		MatchesOnTheTable __obj;

		string in_param_1 = "111111111";
		string in_param_2 = "(0, 3) (0, 8) (1, 1) (1, 4)";

		string answer_data_arr[] = {"4 9 1 4"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getMaximumLength(in_param_1, in_param_2), answer_data);
	}

	/* Test 2 */ {
		cout << "Test 2" << endl;

		MatchesOnTheTableChecker __checker;
		MatchesOnTheTable __obj;

		string in_param_1 = "123456789";
		string in_param_2 = "(0, 8) (0, 2) (2, 3) (4, 4)";

		string answer_data_arr[] = {"1 1 1 1"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getMaximumLength(in_param_1, in_param_2), answer_data);
	}

	/* Test 3 */ {
		cout << "Test 3" << endl;

		MatchesOnTheTableChecker __checker;
		MatchesOnTheTable __obj;

		string in_param_1 = "12333422223432";
		string in_param_2 = "(1, 5) (0, 13) (2, 7)";

		string answer_data_arr[] = {"3 4 3"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getMaximumLength(in_param_1, in_param_2), answer_data);
	}
}
/* End of the testing code */
