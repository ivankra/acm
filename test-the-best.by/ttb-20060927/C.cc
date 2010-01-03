#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;
typedef long long int64;

struct FriendlyGame {
	int64 G(int64 a, int64 b) {
		if (a < b) swap(a, b);
		return (b*b-a*a)/(a*b);
	}

	string whoWins(vector<int> A, vector<int> B) {
		int N = A.size();

		int64 x = 0;
		for (int i = 0; i < N; i++)
			x ^= G(A[i], B[i]);

		if (x == 0)
			return "You lose.";

		for (int i = 0; i < (int)A.size(); i++) {
			int64 a = A[i], b = B[i];
			if (a > b) swap(a, b);

			int64 t = x ^ G(a, b);

			for (int s = -1; s <= 1; s++) {
				long double w;
				w = sqrt(4.0L+t*1.0L*t);
				w = (s*1.0L*a*a*w + a*2.0L*b - a*1.0L*t*a) / (a*2.0L*a);
printf("w=%.5f\n",(double)w);

				int64 m = (int64)w;
				for (int64 diff = -1; diff <= 1; diff++) {
					int64 c = m + diff;
					if (c < 1 || b-a*c < 1) continue;

					if (G(a,b-a*c) == t) {
						char msg[100];
						sprintf(msg,
							"You can win. Cut %lld squares from %d rectangle.",
							c, i);
						return string(msg);
					}
				}
			}
		}

		return "bug";
	}
};


/* Start of the testing code */
class FriendlyGameChecker {
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

		FriendlyGameChecker __checker;
		FriendlyGame __obj;

		int in_param_1_arr[] = {6};
		vector<int> in_param_1(in_param_1_arr, in_param_1_arr + 1);
		int in_param_2_arr[] = {3};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 1);

		string answer_data_arr[] = {"You can win. Cut 1 squares from 0 rectangle."};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.whoWins(in_param_1, in_param_2), answer_data);
	}

	/* Test 2 */ {
		cout << "Test 2" << endl;

		FriendlyGameChecker __checker;
		FriendlyGame __obj;

		int in_param_1_arr[] = {2};
		vector<int> in_param_1(in_param_1_arr, in_param_1_arr + 1);
		int in_param_2_arr[] = {2};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 1);

		string answer_data_arr[] = {"You lose."};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.whoWins(in_param_1, in_param_2), answer_data);
	}

	/* Test 3 */ {
		cout << "Test 3" << endl;

		FriendlyGameChecker __checker;
		FriendlyGame __obj;

		int in_param_1_arr[] = {6, 3, 2, 7};
		vector<int> in_param_1(in_param_1_arr, in_param_1_arr + 4);
		int in_param_2_arr[] = {2, 13, 6, 3};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 4);

		string answer_data_arr[] = {"You can win. Cut 2 squares from 1 rectangle."};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.whoWins(in_param_1, in_param_2), answer_data);
	}

	/* Test 4 */ {
		cout << "Test 4" << endl;

		FriendlyGameChecker __checker;
		FriendlyGame __obj;

		int in_param_1_arr[] = {2, 7, 12, 20, 18};
		vector<int> in_param_1(in_param_1_arr, in_param_1_arr + 5);
		int in_param_2_arr[] = {4, 22, 15, 10, 3};
		vector<int> in_param_2(in_param_2_arr, in_param_2_arr + 5);

		string answer_data_arr[] = {"You can win. Cut 3 squares from 4 rectangle."};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.whoWins(in_param_1, in_param_2), answer_data);
	}
}
/* End of the testing code */
