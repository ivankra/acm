#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;
typedef long long int64;

// Общий вид решения:
//   a b c d
//   b e f g
//   c f h i
//   d g i j
// (будем считать, что переменные a,b,...,j, принимают значения от 0 ('A') до 25 ('Z'))
//
// Пусть x[k][a][b][c] = число слов, таких что, удалив (k-1)-ю букву, получится
// слово из букв a b c.
// Число решений в которых переменные b, c, d, f, g, i фиксированны таким образом
// равно:
//    x[0][b][c][d] * x[1][b][f][g] * x[2][c][f][i] * x[3][d][g][i]
//
// А общее число решений:
//  \sum_{0<=b,c,d,f,g,i<26} x[0][b][c][d] * x[1][b][f][g] * x[2][c][f][i] * x[3][d][g][i] =
// = \sum_{0<=b,c,d,f,g<26} (x[0][b][c][d] * x[1][b][f][g] *
//                              \sum_{0<=i<26} (x[2][c][f][i] * x[3][d][g][i])).
//
// Если y[c][d][f][g] = \sum_{0<=i<26} (x[2][c][f][i] * x[3][d][g][i]),
// то общее число решений можно вычислить как:
//   \sum_{0<=b,c,d,f,g<26} (x[0][b][c][d] * x[1][b][f][g] * y[c][d][f][g])
//

int64 x[4][26][26][26];
int64 y[26][26][26][26];

struct WordSquares {
	int64 getSquaresCount(vector<string> words) {
		memset(x, 0, sizeof(x));
		for (int i = 0; i < (int)words.size(); i++) {
			string &s = words[i];
			x[0][s[1]-'A'][s[2]-'A'][s[3]-'A']++;
			x[1][s[0]-'A'][s[2]-'A'][s[3]-'A']++;
			x[2][s[0]-'A'][s[1]-'A'][s[3]-'A']++;
			x[3][s[0]-'A'][s[1]-'A'][s[2]-'A']++;
		}

		memset(y, 0, sizeof(y));
#define F(var) for (int var = 0; var < 26; var++)
		F(c) F(d) F(f) F(g) {
			int64 &res = y[c][d][f][g];
			F(i) res += x[2][c][f][i] * x[3][d][g][i];
		}

		int64 res = 0;
		F(b) F(c) F(d) F(f) F(g)
			res += x[0][b][c][d] * x[1][b][f][g] * y[c][d][f][g];
		return res;
	}
};

