
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

#include <ctime>
#include <stdarg.h>

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

$IODECL$

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
$EXAMPLES$
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
// vim: ts=4 sts=4 sw=4 noet
// }}}
// END CUT HERE
