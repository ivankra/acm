#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
typedef long long LL;

int MOD = 1000000007LL;

char grid[32][32];
int nbrows, nbcols;

int memo[13][13][256][256];

int f(int rmask, int cmask, int rwhite, int cwhite) {
	int &res = memo[rwhite][cwhite][rmask][cmask];
	if (res != -1) return res;

	int one = 0;
	res = 0;

	for (int r = 0; r < nbrows + rwhite; r++) if (((rmask >> r) & 1) == 0)
	for (int c = 0; c < nbcols + cwhite; c++) if (((cmask >> c) & 1) == 0) {
		if (grid[r][c] != 0) continue;

		res += f(
			(rmask | (1 << r)) & ((1 << nbrows) - 1),
			(cmask | (1 << c)) & ((1 << nbcols) - 1),
			rwhite - (r >= nbrows ? 1 : 0),
			cwhite - (c >= nbcols ? 1 : 0)
		);
		if (res >= MOD) res -= MOD;

		one = 1;
	}

	if (one == 0)
		res++;

	//printf("rmask=%.4X cmask=%.4X rwhite=%d cwhite=%d nbrows=%d nbcols=%d  res=%d\n",
	//		rmask, cmask, rwhite, cwhite, nbrows, nbcols, res);


	return res;
}

struct DrawingBlackCrosses {
	int count(vector<string> field) {
		int nrows = field.size();
		int ncols = field[0].size();

		vector<int> bcols, brows;
		for (int i = 0; i < nrows; i++) {
			for (int j = 0; j < ncols; j++) {
				if (field[i][j] == 'B') {
					brows.push_back(i);
					bcols.push_back(j);
				}
			}
		}
		sort(bcols.begin(), bcols.end()); bcols.erase(unique(bcols.begin(), bcols.end()), bcols.end());
		sort(brows.begin(), brows.end()); brows.erase(unique(brows.begin(), brows.end()), brows.end());

		nbrows = brows.size();
		nbcols = bcols.size();
		assert(nbrows <= 8 && nbcols <= 8);

		memset(grid, 0, sizeof(grid));
		for (int i = 0; i < nbrows; i++)
			for (int j = 0; j < nbcols; j++)
				grid[i][j] = field[brows[i]][bcols[j]] == 'B';

		int rwhite = nrows - nbrows;
		int cwhite = ncols - nbcols;

		//while (rwhite > 0 && nbrows < 8) { rwhite--; nbrows++; assert(nbrows <= 8); }
		//while (cwhite > 0 && nbcols < 8) { cwhite--; nbcols++; assert(nbcols <= 8); }
		
		while (rwhite > 12) { rwhite--; nbrows++; assert(nbrows <= 8); }
		while (cwhite > 12) { cwhite--; nbcols++; assert(nbcols <= 8); }

		memset(memo, 0xff, sizeof(memo));
		return f(0, 0, rwhite, cwhite);		
	}
};

// BEGIN CUT HERE
// {{{
#if 1
#define FOREACH(i,v) for(typeof((v).begin())i=(v).begin();i!=(v).end();++i)
#define REP(i,n) for(int i=0;i<(int)(n);++i)
vector<string> split(const string &s, char sep = ' ') {
    vector<string> v;
    for (int i = 0, j; i < (int)s.size(); i = j + 1) {
        j = s.find(sep, i);
        if (j == -1) j = s.size();
        if (j > i) v.push_back(s.substr(i, j - i));
    }
    return v;
}

#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <ctime>

#if (defined(WIN32) || defined(_WIN32)) && !defined(__CYGWIN__)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#define CYGWIN_OR_UNIX
#endif

namespace TesterNS {
void SetColor(char c = ' ') {
#ifndef CYGWIN_OR_UNIX
    WORD a = 7;
    if (c == 'R') a = 12;
    else if (c == 'G') a = 10;
    else if (c == 'Y') a = 14;
    else if (c == 'W') a = 15;
    ::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), a);
#else
    if (!isatty(1)) return;
    if (c == 'R') printf("\033[01;31m");
    else if (c == 'G') printf("\033[01;32m");
    else if (c == 'Y') printf("\033[01;33m");
    else if (c == 'W') printf("\033[01m");
    else printf("\033[0m");
#endif
}

void color_printf(char code, const char *fmt, ...) {
    SetColor(code);
    va_list va; va_start(va, fmt); vprintf(fmt, va); va_end(va);
    SetColor();
    fflush(stdout);
}

struct Stopwatch {
    double a, b;
    void start() { a = clock(); }
    void stop() { b = clock(); }
    double elapsed() const { return (b - a) / (double)CLOCKS_PER_SEC; }
};

class ReadError { };
void Must(bool a) { if (!a) throw ReadError(); }

int Next(istream &s) {
    Must(!s.fail() && !s.eof());
    int c = s.get();
    Must(!s.fail() && c != EOF);
    return c;
}

int NextNW(istream &s) {
    int c;
    do { c = Next(s); } while (isspace(c));
    return c;
}

bool Skip(istream &s, int what) {
    int c = NextNW(s);
    if (c == what) return true;
    s.unget();
    return false;
}

template<typename T> void Read(T &out, istream &s) {
    s >> out;
    Must(!s.fail());
}

template<> void Read(string &out, istream &s) {
    Must(Skip(s, '\"'));
    out = "";
    for (;;) {
        int c = Next(s);
        if (c == '\"') break;

        if (c == '\\') {
            c = Next(s);
            if (c == '\\' || c == '\"') {
                out += c;
            } else {
                out += '\\';
                s.unget();
            }
        } else {
            out += c;
        }
    }
}

template<typename T> void Read(vector<T> &out, istream &s) {
    Must(Skip(s, '{'));
    out.clear();
    for (;;) {
        int c = NextNW(s);
        if (c == '}') break;
        s.unget();

        T var;
        Read(var, s);
        out.push_back(var);

        c = NextNW(s);
        Must(c == ',' || c == '}');
        if (c == '}') break;
    }
}

template<typename T> void Write(ostream &s, const T &in) { s << in; }

template<> void Write(ostream &s, const string &in) {
    s << "\"";
    for (int i = 0; i < (int)in.size(); i++) {
        if (in[i] == '\\' || in[i] == '\"') s << "\\";
        s << in[i];
    }
    s << "\"";
}

template<typename T> void Write(ostream &s, const vector<T> &in) {
    s << "{";
    for (int i = 0; i < (int)in.size(); i++) {
        s << (i == 0 ? " " : ", ");
        Write<T>(s, in[i]);
    }
    if (in.size() != 0) s << " ";
    s << "}";
}

template<typename T> string ToString(const T &in) {
    ostringstream os;
    Write(os, in);
    return os.str();
}

template<typename T> bool Equal(const T &x, const T &y) { return x == y; }

template<> bool Equal(const double &x, const double &y) {
    if (x == y) return true;

    if (fabs(x - y) < 1e-9) return true;

    double a = y * (1.0 - 1e-9);
    double b = y * (1.0 + 1e-9);
    if (a > b) swap(a, b);
    if (!(a < x && x < b)) return false;

    a = x * (1.0 - 1e-9);
    b = x * (1.0 + 1e-9);
    if (a > b) swap(a, b);
    if (!(a < y && y < b)) return false;

    return true;
}

template<typename T> bool Equal(const vector<T> &x, const vector<T> &y) {
    if (x.size() != y.size()) return false;
    for (int i = 0; i < (int)x.size(); i++)
        if (!Equal<T>(x[i], y[i])) return false;
    return true;
}

struct InputTuple {
	vector<string> arg1;
};

template<> void Read(InputTuple &out, istream &s) {
	Read(out.arg1, s);
}

template<> void Write(ostream &s, const InputTuple &in) {
	Write(s, in.arg1);
}

typedef int OutputType;

OutputType Execute(InputTuple input) {
	DrawingBlackCrosses instance;
	return instance.count(input.arg1);
}



struct Tester {
    InputTuple input;
    OutputType output, answer;
    bool haveAnswer, passed;

    bool ReadTest(istream &inp, const string &ans = "") {
        haveAnswer = false;

#ifndef CYGWIN_OR_UNIX
        bool keyboard = (&inp == &cin);
#else
        bool keyboard = (&inp == &cin && isatty(0));
#endif
        if (keyboard) fprintf(stderr, "(reading test case from stdin)\n");

        try {
            bool bracket = Skip(inp, '[');
            Read(input, inp);
            Must(!inp.fail());
            if (ans != "") {
                istringstream s(ans);
                Read(answer, s);
                haveAnswer = true;
            } else if (!keyboard) {
                string s;
                inp >> s;
                if (!inp.fail()) {
                    if (s.size() > 3)
                        s = s.substr(0, 3);
                    for (int i = 0; i < (int)s.size(); i++)
                        s[i] = tolower(s[i]);

                    if (s == "exp" || s == "ret") {
                        Skip(inp, ':');
                        Read(answer, inp);
                        haveAnswer = true;
                    }
                }
            }
            if (bracket) Must(Skip(inp, ']'));
        } catch (ReadError) {
            return false;
        }

        return true;
    }

    void Run(const string &name, istream &inp, const string &ans = "") {
        color_printf('W', "%s) ", name.c_str());

        passed = false;
        if (!ReadTest(inp, ans)) {
            color_printf('R', "Failed to parse test data.\n");
            return;
        }

        Stopwatch stopwatch;
        stopwatch.start();
        try {
            output = Execute(input);
        } catch (...) {
            color_printf('R', "Exception was thrown.\n");
            return;
        }
        stopwatch.stop();

        if (haveAnswer && Equal(answer, output)) {
            passed = true;
        }

        if (passed) {
            color_printf('G', "OK");
            printf(" [%.3fs]\n", stopwatch.elapsed());
        } else if (!haveAnswer) {
            color_printf('Y', "Returns");
            printf(" %s", ToString(output).c_str());
            printf(" [%.3fs]\n", stopwatch.elapsed());
        } else {
            color_printf('R', "WRONG");
            printf(" [%.3fs]\n", stopwatch.elapsed());
            printf("Received: %s\n", ToString(output).c_str());
            printf("Expected: %s\n\n", ToString(answer).c_str());
        }
        fflush(stdout);
    }

    void Run(const string &name, const string &inp, const string &ans = "") {
        istringstream s(inp);
        Run(name, s, ans);
    }

    void Run(const string &s) { Run("test", s, ""); }
};
}

int main(int argc, char *argv[]) {
const char *e[] = {
"{\".\"} Returns: 1",
"{\"BBB\",  \"BBB\"} Returns: 1",
"{\"...\",   \"BB.\"} Returns: 5",
"{\"....................\",   \"....................\",   \"....................\",   \"....................\",   \"....................\",   \"....................\",   \"....................\",   \"....................\",   \"....................\",   \"....................\",   \"....................\",   \"....................\",   \"....................\",   \"....................\",   \"....................\",   \"....................\",   \"....................\",   \"....................\",   \"....................\",   \"....................\"} Returns: 563200757",
"{\"B..B\",  \"B.B.\",  \"...B\",  \"BB.B\",  \"....\"} Returns: 324"

};
    int i, j, n = sizeof(e) / sizeof(e[0]);
    TesterNS::Tester tester;
    if (argc <= 1) {
        for (i = 0; i < n; i++) tester.Run(TesterNS::ToString(i), e[i]);
    } else {
        for (i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-") == 0) {
                tester.Run("stdin", cin);
            } else {
                j = atoi(argv[i]);
                if (0 <= j && j < n)
                    tester.Run(argv[i], e[j]);
                else
                    fprintf(stderr, "Test \"%s\" is undefined\n", argv[i]);
            }
        }
    }
}
#endif
// vim: ts=4 sts=4 sw=4 noet fdm=marker
// }}}
// END CUT HERE
