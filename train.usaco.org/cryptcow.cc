/*
ID: infnty1
PROB: cryptcow
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

#define HDIV 533879
#define HSIZE (300*1024)

char plain[] = "Begin the Escape execution at the Break of Dawn";
char enc[128], buffers[128][128];
int isCOW[256], isCOWZ[256];

/* Hashtable - helps detecting repeated states */
int htab[HDIV], hnext[HSIZE], hcount=1;
int cmap[256], cmapn;
char *hstr[HSIZE], hashbuf[5*1048576], *hashptr;

void hinit() {
        memset(htab, 0, sizeof(htab));
        hcount = 1;

        memset(cmap, 0, sizeof(cmap));
        for (int i = 0; plain[i]; i++)
                cmap[plain[i]] = 1;
        cmap['C'] = cmap['O'] = cmap['W'] = 1;

        cmapn = 0;
        for (int i = 0; i < 256; i++)
                if (cmap[i] > 0) cmap[i] = cmapn++;

        hashptr = hashbuf;
}

static int hseen(char *str) {
        int hash = 0;
        for (int i = 0; str[i]; i++) {
                hash = hash * cmapn + cmap[str[i]];
                if (hash >= HDIV) hash %= HDIV;
        }

        for (int i = htab[hash]; i != 0; i = hnext[i])
                if (strcmp(hstr[i], str) == 0) return 1;

        if (hcount+5 > HSIZE || hashptr+128 > hashbuf+sizeof(hashbuf)) return 0;

        int x = hcount++;
        hnext[x] = htab[hash];
        htab[hash] = x;
        hstr[x] = hashptr;
        while (*str) *hashptr++ = *str++;
        *hashptr++ = 0;

        return 0;
}


/* Suffix trie for plain text */
int tnext[1100][128], tsize;

void tinsert(char *p) {
        for (int x = 0; *p; x = tnext[x][*p++])
                if (tnext[x][*p] == 0) tnext[x][*p] = tsize++;
}

void tinit() {
        tsize = 1;
        memset(tnext, 0, sizeof(tnext));
        for (int i = 0; plain[i]; i++) tinsert(plain+i);
}

/* Main backtracking routine */

static int tryit(int pa, int pb, char *text, int ntext) {
        if (ntext <= pb-pa+1) {
                if (ntext != pb-pa+1) return 0;
                return strncmp(text, plain+pa, ntext) == 0;
        }

        while (ntext > 0 && text[0] != 'C') {
                if (plain[pa] != text[0]) return 0;
                pa++; ntext--; text++;
        }

        while (ntext > 0 && text[ntext-1] != 'W') {
                if (plain[pb] != text[ntext-1]) return 0;
                pb--; ntext--;
        }

        if (ntext == 0) return 1;

        for (int i = 0; text[i];) {
                if (isCOW[text[i]]) { i++; continue; }
                for (int x = 0; !isCOWZ[text[i]]; i++) {
                        x = tnext[x][text[i]];
                        if (x == 0) return 0;
                }
        }

        text[ntext] = 0;
        if (hseen(text)) return 0;

//printf("%.*s\n", ntext, text);

        char *p = buffers[ntext];
        for (int c = 0; c < ntext; *p++ = text[c++]) if (text[c]=='C')
        for (int o = c+1; o < ntext; o++) if (text[o]=='O')
//        for (int w = o+1; w < ntext; w++) if (text[w]=='W') {
        for (int w = ntext-1; w > o; w--) if (text[w]=='W') {
                char *q = p;
                for (int i = o+1; i < w; i++) *q++ = text[i];
                for (int i = c+1; i < o; i++) *q++ = text[i];
                for (int i = w+1; i < ntext; i++) *q++ = text[i];
                *q = '\0';
                if (tryit(pa, pb, buffers[ntext], ntext-3)) return 1;
        }

        return 0;
}

int solve() {
        int nenc = strlen(enc), nplain = strlen(plain);

        if (nenc == nplain) return (strcmp(plain, enc) == 0);
        for (int k = 1;; k++) {
                if (k > 9) return 0;
                if (nplain + 3*k == nenc) break;
        }

        int cnt[256];
        memset(cnt, 0, sizeof(cnt));
        cnt['C'] = cnt['O'] = cnt['W'] = (nenc - nplain) / 3;
        for (int i = 0; i < nplain; i++) cnt[plain[i]]++;
        for (int i = 0; i < nenc; i++) cnt[enc[i]]--;
        for (int i = 0; i < 256; i++) if (cnt[i] != 0) return 0;

        memset(isCOW, 0, sizeof(isCOW));
        isCOW['C'] = isCOW['O'] = isCOW['W'] = 1;

        memset(isCOWZ, 0, sizeof(isCOWZ));
        isCOWZ['C'] = isCOWZ['O'] = isCOWZ['W'] = isCOWZ[0] = 1;

        tinit();
        hinit();

        char tmp[256];
        strcpy(tmp, enc);
        return tryit(0, nplain-1, tmp, nenc);
}

int main()
{
        freopen("cryptcow.in", "r", stdin);
        freopen("cryptcow.out", "w", stdout);

        gets(enc);
        for (int n = strlen(enc); n > 0 && strchr("\r\n", enc[n-1]);)
                enc[--n] = 0;

        if (solve())
                printf("1 %d\n", (strlen(enc) - strlen(plain))/3);
        else
                printf("0 0\n");
//printf("hcount=%d hptr=%d\n", hcount, hashptr-hashbuf);
        return 0;
}
