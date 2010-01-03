#include <algorithm>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;

struct CodeRed {
	int count(string text) {
		int res = 0;
		for (int i = 0; i+3 <= text.size(); i++) {
			if (tolower(text[i]) == 'r' &&
			    tolower(text[i+1]) == 'e' &&
			    tolower(text[i+2]) == 'd') res++;

		}
		return res;		
	}
};

// BEGIN CUT HERE
// Powered by KiaEdit v.20070119
#if 1
// Powered by KiaEdit v.20070119

// TODO:
//   - fix bug: when taking data from _redirected_ stdin, tester fails to
//     parse input without a "Returns:" or "Expected:"
//   - catch exceptions (and, possibly, runtime errors? thru debug API?),
//     throwed in tested method
//   - report memory usage

//#include <algorithm>
//#include <vector>
//#include <sstream>
//#include <cmath>
//#include <cctype>
#include <iostream>
//using namespace std;

#if (defined(_MSC_VER) || defined(_WIN32)) && !defined(WIN32)
#define WIN32
#endif
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <unistd.h>
#include <sys/time.h>
#endif
#include <stdarg.h>

namespace TesterNS {
#ifdef _MSC_VER
	typedef unsigned __int64 uint64;
#else
	typedef unsigned long long uint64;
#endif

	uint64 GetMicroTime() {
#ifdef WIN32
		FILETIME ft;
		GetSystemTimeAsFileTime(&ft);
		uint64 r = ft.dwHighDateTime;
		r = (r << 32) | (uint64)ft.dwLowDateTime;
		return r / 10;
#else
		struct timeval tv;
		gettimeofday(&tv, NULL);
		uint64 m = 1000000;
		return m * (uint64)tv.tv_sec + (uint64)tv.tv_usec;
#endif
	}

	void SetColor(char c = ' ') {
#ifdef WIN32
		WORD rgb = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

		WORD a;
		if (c == 'R') a = FOREGROUND_RED | FOREGROUND_INTENSITY;
		else if (c == 'G') a = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		else if (c == 'Y') a = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		else if (c == 'W') a = rgb | FOREGROUND_INTENSITY;
		else if (c == 'r') a = rgb | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_INTENSITY;
		else if (c == 'g') a = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		else if (c == 'y') a = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		else a = rgb;

		HANDLE h = ::GetStdHandle(STD_OUTPUT_HANDLE);
		::SetConsoleTextAttribute(h, a);
#else
		if (!isatty(1)) return;
		if (c == 'R') printf("\033[01;31m");
		else if (c == 'G') printf("\033[01;32m");
		else if (c == 'Y') printf("\033[01;33m");
		else if (c == 'W') printf("\033[01m");
		else if (c == 'r') printf("\033[01;41m");
		else if (c == 'g') printf("\033[30;42;05m");
		else if (c == 'y') printf("\033[30;43;05m");
		else printf("\033[0m");
#endif
	}

	void color_printf(char code, char *fmt, ...)
	{
		SetColor(code);
		va_list va;
		va_start(va, fmt);
		vprintf(fmt, va);
		va_end(va);
		fflush(stdout);
		SetColor();
	}

	class ReadError { };
	void Must(bool a) { if (!a) throw ReadError(); }

	int Next(istream &s) {
		Must(s.good() && !s.eof());
		int c = s.get();
		Must(!s.bad() && c != EOF);
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
		Must(!s.bad());
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
			T var;
			Read(var, s);
			out.push_back(var);
			int c = NextNW(s);
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
	string arg1;
};

template<> void Read(InputTuple &out, istream &s) {
	Read(out.arg1, s);
}

template<> void Write(ostream &s, const InputTuple &in) {
	Write(s, in.arg1);
}

typedef int OutputType;

OutputType Execute(InputTuple input) {
	CodeRed instance;
	return instance.count(input.arg1);
}



	struct Tester {
		InputTuple input;
		OutputType output, answer;

		bool haveAnswer, passed;
		long long runtime;

		bool ReadTest(istream &inp, const string &ans = "") {
			haveAnswer = false;

#ifdef WIN32
			bool keyboard = (&inp == &cin);
#else
			bool keyboard = (&inp == &cin && isatty(0));
#endif
			if (keyboard) {
				fprintf(stderr, "(reading test case from stdin)\n");
				fflush(stderr);
			}

			try {
				bool bracket = Skip(inp, '[');

				Read(input, inp);
				Must(!inp.bad());

				if (ans != "") {
					istringstream s(ans);
					Read(answer, s);
					haveAnswer = true;
				} else if (!keyboard) {
					string s;
					inp >> s;
					if (!inp.bad()) {
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
			fflush(stdout);

			passed = false;
			if (!ReadTest(inp, ans)) {
				color_printf('R', "FAILED TO PARSE TEST DATA");
				printf("\n");
				return;
			}

			long long st = GetMicroTime();
			output = Execute(input);
			runtime = GetMicroTime() - st;

			if (haveAnswer && Equal(answer, output))
				passed = true;

			if (passed) {
				color_printf('G', "OK");
				printf(" [%.3fs]\n", runtime/1000000.0);
			} else if (!haveAnswer) {
				color_printf('Y', "GOT");
				printf(" %s", ToString(output).c_str());
				printf(" [%.3fs]\n", runtime/1000000.0);
			} else {
				color_printf('R', "WRONG");
				printf(" [%.3fs]\n", runtime/1000000.0);
				printf("Got: %s\n", ToString(output).c_str());
				printf("Exp: %s\n\n", ToString(answer).c_str());
			}
			fflush(stdout);
		}

		void Run(const string &name, const string &inp, const string &ans = "") {
			istringstream s(inp);
			Run(name, s, ans);
		}

		void Run(const string &input) { Run("test", input, ""); }
	};
}

int main(int argc, char *argv[])
{
	const char *example[] = {
		"\"the detective questioned his credibility\" Returns: 1",
"\"Server ERRED in Redirecting Spam\" Returns: 2",
"\"  read the RED sign   said fReD\" Returns: 2",
"\"pure delight\" Returns: 0",
"\"re\" Returns: 0"

	};
	int N = sizeof(example) / sizeof(example[0]);

	TesterNS::Tester tester;

	if (argc <= 1) {
		for (int i = 0; i < N; i++)
			tester.Run(TesterNS::ToString(i), example[i]);
	} else {
		for (int i = 1; i < argc; i++) {
			if (strcmp(argv[i], "-") == 0) {
				tester.Run("stdin", cin);
				continue;
			}

			int cs = 0;
			for (int j = 0; argv[i][j]; j++) {
				if (!isdigit(argv[i][j]) || j > 5) { cs = -1; break; }
				cs = cs * 10 + (argv[i][j] - '0');
			}

			if (0 <= cs && cs < N) {
				tester.Run(argv[i], example[cs]);
				continue;
			}

			fprintf(stderr, "Test \"%s\" is undefined\n", argv[i]);
		}
	}
}
#endif

// END CUT HERE
