#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

char text[1024][1024];
int text_rows, text_cols;

char pat[128][128];
int pat_rows, pat_cols;

/* Suffix trie. */
#define NODES 1000010
int kid[NODES], sib[NODES], suf[NODES], cnt;
char alpha[NODES];

void trie_clear() {
        cnt = 1;
        kid[0] = sib[0] = suf[0] = 0;
}

/* Inserts string s and all its suffixes into the trie. */
int trie_insert(char *s) {
        int x = 0;
        for (; *s; s++) {
               int y = x, z, w = -1;
               for (;;) {
                        for (z = kid[y]; z != 0 && alpha[z] != *s; z = sib[z]);
                        if (z != 0) {
                                if (w >= 0) suf[w] = z;
                                break;
                        }

                        z = cnt++;
                        kid[z] = 0;
                        sib[z] = kid[y];
                        kid[y] = z;
                        alpha[z] = *s;
                        suf[z] = -1;
                        if (w >= 0) suf[w] = z;
                        w = z;

                        if (y == 0) { suf[z] = 0; break; }
                        y = suf[y];
                }

                for (x = kid[x]; x != 0 && alpha[x] != *s; x = sib[x]);
                assert(x != 0);
        }
        return x;
}



/**

abc   000
bcd   012
cde   120

bc
cd


abab
bbaa
aabb
abab

*/

int solve()
{
        int thePat[128], thePatSuf[128];

        trie_clear();
        for (int i = 0; i < pat_rows; i++) {
                thePat[i] = trie_insert(pat[i]);
                printf("  pat[%d]: %s %d\n", i, pat[i], thePat[i]);
        }

        thePatSuf[0] = thePatSuf[1] = 0;
        for (int i = 2; i <= pat_rows; i++) {
                int s = thePatSuf[i-1];
                while (s > 0 && thePat[s] != thePat[i-1]) s = thePatSuf[s];
                thePatSuf[i] = (thePat[s] == thePat[i-1] ? s+1 : 0);
        }

        printf("patSuf:");
        for(int i = 1; i <= pat_rows; i++) printf(" %d", thePatSuf[i]);
        printf("\n");

        return 42;
}

int main()
{
        int T, c;
        for (scanf("%d", &T); T-- > 0;) {
                scanf("%d %d", &text_rows, &text_cols);
                assert(0 <= text_rows && text_rows <= 1000);
                assert(0 <= text_cols && text_cols <= 1000);
                while ((c = getchar()) != EOF && c != '\n');
                for (int i = 0; i < text_rows; i++) {
                        for (int j = 0; j < text_cols; j++) {
                                while ((c = getchar()) != EOF && (c == '\n' || c == '\r'));
                                text[i][j] = c;
                        }
                }

                scanf("%d %d", &pat_rows, &pat_cols);
                assert(1 <= pat_rows && pat_rows <= 100);
                assert(1 <= pat_cols && pat_cols <= 100);
                memset(pat, 0, sizeof(pat));
                while ((c = getchar()) != EOF && c != '\n');
                for (int i = 0; i < pat_rows; i++) {
                        for (int j = 0; j < pat_cols; j++) {
                                while ((c = getchar()) != EOF && (c == '\n' || c == '\r'));
                                pat[i][j] = c;
                        }
                }

                printf("%d\n", solve());
        }
        return 0;
}
