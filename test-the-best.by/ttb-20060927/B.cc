#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
using namespace std;
typedef long long int64;

int P[10000];
vector<vector<int> > adj;

int solve(int x, int parent) {
	vector<int> kids;

	for (int i = 0; i < (int)adj[x].size(); i++) {
		int y = adj[x][i];
		if (y != parent) {
			kids.push_back(solve(y, x));
		}
	}

	sort(kids.begin(), kids.end());
	reverse(kids.begin(), kids.end());

	int m = kids.size();
	int res = 0;

	for (int i = 0, t = 1; i < m; i += P[x], t++) {
		for (int j = 0; j < P[x] && i+j < m; j++) {
			res >?= t + kids[i+j];
		}
	}

	return res;
}

struct PegionMail {
	int fastDelivery(int numKingdoms, vector<int> numPegions, vector<string> neighbours, int partyPlace) {
		int N = numKingdoms;
		for (int i = 0; i < N; i++)
			P[i] = numPegions[i];

		adj.assign(N, vector<int>());
		for (int i = 0; i < (int)neighbours.size(); i++) {
			int a, b;
			sscanf(neighbours[i].c_str(), "%d %d", &a, &b);
			adj[a].push_back(b);
			adj[b].push_back(a);
		}

		return solve(partyPlace, -1);
	}
};


/* Start of the testing code */
class PegionMailChecker {
public:
	void doCheck (int output, vector<string> answer) {
		int answerAsInt;
		istringstream iss(answer[0]);
		iss >> answerAsInt;
		
		if (output == answerAsInt)
			cout << "Correct answer!" << endl;
		else
			cout << "Wrong answer: expected "
			     << answerAsInt << ", got " << output << endl;
	}
};

/* End of the testing code */

/* Start of the testing code */
int main() {
	/* Test 1 */ {
		cout << "Test 1" << endl;

		PegionMailChecker __checker;
		PegionMail __obj;

		int in_param_1 = 4;
		int in_param_2_arr[] = {1, 1, 1, 1};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 4);
		string in_param_3_arr[] = {"0 1", "3 1", "2 3"};
		vector<string> in_param_3(in_param_3_arr, in_param_3_arr + 3);
		int in_param_4 = 0;

		string answer_data_arr[] = {"3"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.fastDelivery(in_param_1, in_param_2, in_param_3, in_param_4), answer_data);
	}

	/* Test 2 */ {
		cout << "Test 2" << endl;

		PegionMailChecker __checker;
		PegionMail __obj;

		int in_param_1 = 4;
		int in_param_2_arr[] = {1, 2, 1, 1};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 4);
		string in_param_3_arr[] = {"0 1", "3 1", "2 3"};
		vector<string> in_param_3(in_param_3_arr, in_param_3_arr + 3);
		int in_param_4 = 1;

		string answer_data_arr[] = {"2"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.fastDelivery(in_param_1, in_param_2, in_param_3, in_param_4), answer_data);
	}

	/* Test 3 */ {
		cout << "Test 3" << endl;

		PegionMailChecker __checker;
		PegionMail __obj;

		int in_param_1 = 7;
		int in_param_2_arr[] = {3, 2, 2, 1, 1, 2, 2};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 7);
		string in_param_3_arr[] = {"2 0", "1 2", "4 2", "2 3", "5 6", "5 2"};
		vector<string> in_param_3(in_param_3_arr, in_param_3_arr + 6);
		int in_param_4 = 5;

		string answer_data_arr[] = {"3"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.fastDelivery(in_param_1, in_param_2, in_param_3, in_param_4), answer_data);
	}

	/* Test 4 */ {
		cout << "Test 4" << endl;

		PegionMailChecker __checker;
		PegionMail __obj;

		int in_param_1 = 7;
		int in_param_2_arr[] = {1, 1, 1, 1, 1, 1, 1};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 7);
		string in_param_3_arr[] = {"0 6", "6 4", "4 2", "3 1", "1 2", "5 2"};
		vector<string> in_param_3(in_param_3_arr, in_param_3_arr + 6);
		int in_param_4 = 2;

		string answer_data_arr[] = {"3"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.fastDelivery(in_param_1, in_param_2, in_param_3, in_param_4), answer_data);
	}
}
/* End of the testing code */
