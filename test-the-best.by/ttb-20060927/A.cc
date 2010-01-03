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

struct Matchmaking {
	double count(int N, vector<int> dice) {
		double f[50][6];

		double sum = 0.0;
		for (int i = 0; i < 6; i++)
			sum += dice[i];

		for (int i = 0; i < 6; i++)
			f[1][i] = sum / 6.0;

		for (int k = 2; k <= N; k++) {
			for (int s = 0; s < 6; s++) {
				f[k][s] = 0;
				for (int i = 0; i < 6; i++)
					f[k][s] += (i == s ? 0 : dice[i]) + f[k-1][i];
				f[k][s] /= 6.0;
			}
		}

		double res = 0;
		for (int s = 0; s < 6; s++)
			res += f[N][s] / 6.0;
		return res;
	}
};


/* Start of the testing code */
class MatchmakingChecker {
public:
	void doCheck (double output, vector<string> answer) {
		double answerAsDouble;
		istringstream iss(answer[0]);
		iss >> answerAsDouble;

		int precision = cout.precision();
		cout.precision(15);
		cout << fixed;	

		if (fabs(output-answerAsDouble) <= 1e-6)
			cout << "Correct answer!" << endl;
		else
			cout << "Wrong answer: expected "
			     << answerAsDouble << ", got " << output << endl;

		cout.precision(precision);
	}
};

/* End of the testing code */

/* Start of the testing code */
int main() {
	/* Test 1 */ {
		cout << "Test 1" << endl;

		MatchmakingChecker __checker;
		Matchmaking __obj;

		int in_param_1 = 1;
		int in_param_2_arr[] = {1, 1, 1, 1, 1, 1};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 6);

		string answer_data_arr[] = {"1.0000000000000000"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.count(in_param_1, in_param_2), answer_data);
	}

	/* Test 2 */ {
		cout << "Test 2" << endl;

		MatchmakingChecker __checker;
		Matchmaking __obj;

		int in_param_1 = 2;
		int in_param_2_arr[] = {1, 1, 1, 1, 1, 1};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 6);

		string answer_data_arr[] = {"1.8333333333333333"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.count(in_param_1, in_param_2), answer_data);
	}

	/* Test 3 */ {
		cout << "Test 3" << endl;

		MatchmakingChecker __checker;
		Matchmaking __obj;

		int in_param_1 = 2;
		int in_param_2_arr[] = {1, 2, 3, 4, 5, 6};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 6);

		string answer_data_arr[] = {"6.4166666666666667"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.count(in_param_1, in_param_2), answer_data);
	}

	/* Test 4 */ {
		cout << "Test 4" << endl;

		MatchmakingChecker __checker;
		Matchmaking __obj;

		int in_param_1 = 5;
		int in_param_2_arr[] = {10, 5, 3, 11, 4, 100};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 6);

		string answer_data_arr[] = {"96.055555555555556"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.count(in_param_1, in_param_2), answer_data);
	}

	/* Test 5 */ {
		cout << "Test 5" << endl;

		MatchmakingChecker __checker;
		Matchmaking __obj;

		int in_param_1 = 20;
		int in_param_2_arr[] = {1, 1, 1, 1, 1, 1};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 6);

		string answer_data_arr[] = {"16.833333333333333"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.count(in_param_1, in_param_2), answer_data);
	}

	/* Test 6 */ {
		cout << "Test 6" << endl;

		MatchmakingChecker __checker;
		Matchmaking __obj;

		int in_param_1 = 20;
		int in_param_2_arr[] = {10, 5, 3, 11, 4, 100};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 6);

		string answer_data_arr[] = {"373.13888888888889"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.count(in_param_1, in_param_2), answer_data);
	}
}
/* End of the testing code */
