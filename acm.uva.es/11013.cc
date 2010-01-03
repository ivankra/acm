#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char *vals = "A23456789TJQK";

int eval(int ccc[]) {
        int c[5], ret=0;
        for (int i = 0; i < 5; i++) c[i] = ccc[i];

        sort(c, c+5);
        do {
                if ((c[0]+1)%13!=c[1]) continue;

                if ((c[0]+2)%13==c[2] && (c[0]+3)%13==c[3]) {
                        ret >?= 10;
                        if ((c[0]+4)%13==c[4]) return 100;
                }

                if ((c[0]+2)%13==c[2]) {
                        ret >?= 3;
                        if ((c[3]+1)%13==c[4]) ret >?= 5;
                }

                if ((c[2]+1)%13==c[3]) ret >?= 1;
        } while (next_permutation(c, c+5));

        return ret;
}

int main()
{
        int card[5], got[13];
        char name[5][16];

        for (;;) {
                for (int i = 0; i < 13; i++) got[i] = 0;
                for (int i = 0; i < 5; i++) {
                        if (scanf(" %s", name[i]) != 1) return 0;
                        if (name[i][0] == '#') return 0;
                        card[i] = strchr(vals, name[i][0]) - vals;
                        got[card[i]]++;
                }

                int best = 47*eval(card), what = -1;
                for (int i = 0; i < 5; i++) {
                        int e = -47;
                        for (int ch = 0; ch < 52; ch++) {
                                if (4-got[ch/4] <= ch%4) continue;
                                int t = card[i];
                                card[i] = ch/4;
                                e += eval(card);
                                card[i] = t;
                        }
                        if (e > best) { best = e; what = i; }
                }

                if (what < 0) printf("Stay\n");
                else printf("Exchange %s\n", name[what]);
        }
}
