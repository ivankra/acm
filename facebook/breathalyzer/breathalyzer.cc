#include <cstdio>
#include <cctype>
#include <cassert>
#include <cstring>
#include <algorithm>
using namespace std;

const int LEN = 15;
char words[200000][LEN+1], query[100000];
int nwords;

int levensh(const char *s, const char *t)
{
    int f[LEN+1], n = strlen(s);

    for (int i = 0; i <= n; i++)
        f[i] = i;

    for (; *t; t++) {
        int next = f[0], old;
        f[0]++;
        for (int i = 1; i <= n; i++) {
            old = next;
            next = f[i];
            if (s[i-1] == *t)
                f[i] = old;
            else
                f[i] = min(old+1, min(f[i]+1, f[i-1]+1));
        }
    }

    return f[n];
}

int main(int argc, char *argv[])
{
    assert(argc >= 2 && freopen(argv[1], "r", stdin) != NULL);

    FILE *fp = fopen("/var/tmp/twl06.txt", "r");
    if (fp == NULL) fp = fopen("./twl06.txt", "r");
    assert(fp != NULL);
    for (nwords = 0; fscanf(fp, "%s", words[nwords]) == 1;) nwords++;
    fclose(fp);

    int sum = 0;
    while (scanf("%s", query) == 1) {
        for (int i = 0; query[i]; i++)
            query[i] = toupper(query[i]);

        int score = strlen(query);
        for (int i = 0; i < nwords; i++)
            score = min(score, levensh(words[i], query));
        sum += score;
    }
    printf("%d\n", sum);
}
