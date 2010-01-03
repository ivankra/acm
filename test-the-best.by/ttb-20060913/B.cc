#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

int N, M, cell[32][32], memo[22][22][22][22][4];

int f(int row1, int row2, int col1, int col2, int cor) {
	int &res = memo[row1][row2][col1][col2][cor];
	if (res != -1) return res;
	if (row1 > row2 || col1 > col2) return res = -(1<<20);

	int r = (cor <= 1) ? row1 : row2;
	int c = (cor == 0 || cor == 3) ? col1 : col2;
	int sum = 0;

	res = -(1<<20);

	while (row1 <= r && r <= row2 && col1 <= c && c <= col2) {
		sum += cell[r][c];

		res >?= sum;
		switch (cor) {
			case 0: res >?= sum + f(row1+1, row2, col1, c, 1); break;
			case 1: res >?= sum + f(row1, r, col1, col2-1, 2); break;
			case 2: res >?= sum + f(row1, row2-1, c, col2, 3); break;
			case 3: res >?= sum + f(r, row2, col1+1, col2, 0); break;
		}

		static int dr[] = { 0, 1, 0, -1 }, dc[] = { 1, 0, -1, 0 };
		r += dr[cor];
		c += dc[cor];
	}
	return res;
}

struct DonkeyRunning {
	int getPoints(vector<string> ground) {
		N = ground.size();
		memset(cell, 0, sizeof(cell));
		for (int i = 0; i < N; i++) {
			istringstream is(ground[i]);
			for (M = 0; is >> cell[i][M]; M++);
		}
		memset(memo, 0xff, sizeof(memo));
		return f(0,N-1, 0,M-1, 0);
	}
};


/* Start of the testing code */
class DonkeyRunningChecker {
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
#if 1
	/* Test 1 */ {
		cout << "Test 1" << endl;

		DonkeyRunningChecker __checker;
		DonkeyRunning __obj;

		string in_param_1_arr[] = {"-33 37", "15 -5"};
		vector<string> in_param_1(in_param_1_arr, in_param_1_arr + 2);

		string answer_data_arr[] = {"14"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getPoints(in_param_1), answer_data);
	}

	/* Test 2 */ {
		cout << "Test 2" << endl;

		DonkeyRunningChecker __checker;
		DonkeyRunning __obj;

		string in_param_1_arr[] = {"26 -100 1", "3 6 4"};
		vector<string> in_param_1(in_param_1_arr, in_param_1_arr + 2);

		string answer_data_arr[] = {"29"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getPoints(in_param_1), answer_data);
	}

	/* Test 3 */ {
		cout << "Test 3" << endl;

		DonkeyRunningChecker __checker;
		DonkeyRunning __obj;

		string in_param_1_arr[] = {"-34"};
		vector<string> in_param_1(in_param_1_arr, in_param_1_arr + 1);

		string answer_data_arr[] = {"-34"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getPoints(in_param_1), answer_data);
	}

	/* Test 4 */ {
		cout << "Test 4" << endl;

		DonkeyRunningChecker __checker;
		DonkeyRunning __obj;

		string in_param_1_arr[] = {"-10 25 11 -59 23 74", "-27 33 -85 12 78 11", "14 -44 33 60 27 -47", "-67 -17 -86 -95 -89 -14", "95 35 -97 52 55 64"};
		vector<string> in_param_1(in_param_1_arr, in_param_1_arr + 5);

		string answer_data_arr[] = {"296"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getPoints(in_param_1), answer_data);
	}
#endif
	/* Test 5 */ {
		cout << "Test 5" << endl;

		DonkeyRunningChecker __checker;
		DonkeyRunning __obj;

		string in_param_1_arr[] = {
			"33 -85 12 78",
			"-44 33 60 27"
		};
		vector<string> in_param_1(in_param_1_arr, in_param_1_arr + 2);

		string answer_data_arr[] = {"158"};
		vector<string> answer_data(answer_data_arr, answer_data_arr + 1);

		__checker.doCheck(__obj.getPoints(in_param_1), answer_data);
	}

}
/* End of the testing code */

