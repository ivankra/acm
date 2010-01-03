/*
The Primes
Jozef Tvarozek of Slovakia

First of all, we need to pre-compute all 5-digit primes given the digit sum we're interested in. This can be done in several ways, the way we choose depends on conditions. When solving the problem on a time-limited (5 hours) competition, we choose the simplest way (KISS Principle): for every number ranging from 10000 to 99999 we check whether is properly divisible by any number I (I ranges from 2 to sqrt(99999)); if so the number is definitely not a prime; otherwise a prime number is found. The first simple extension is to check only odd numbers since we're interested in 5-digit numbers (and the only even prime is 2).

When the running time is crucial, we extend the previous idea even more - we check whether the numbers 6x+1, 6x-1 that are in the range from 10000 to 99999 are properly divisible by any prime P ranging from 5 to sqrt(99999) (namely primes: 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313).

Since all solutions (given the digit sum and the top-left digit) have to be found, we must perform an exhaustive search. The "stupidest" idea is to fill the prime square row-by-row with 5-digit primes and when the entire square is filled we just test whether the columns and both diagonals are primes. This obviously does not lead to a low running time since (for the worst test case: digit sum 23, and top-left digit 3) there are (at most) 757 prime numbers to be filled-in each row, which results to 757^5 (rough estimate: 250 x 10^12) operations - impossible even on today's 1Ghz processors.

The obvious way to fill the numbers in the square is to fill them in such way that as much as possible is known in advance about the filling prime - thus reducing the number of possibilities. One of the best ways to do so is given below.

Note: All further complexity estimates will be done on the "worst possible" test case: digit sum 23, top-left digit 3; I wonder why this test case was not used in the RECORD section).

Before all computation is done, we pre-compute so-called prime-patterns. This means that wherever we need to fill a prime whose any digits are know in advance, we pre-compute the primes when the given digits are arbitrary.

First, fill-up the main diagonal (from top-left corner to the bottom-right). Since we know only the first digit we have about 90 possible primes to be filled.

Second, (for all selections of the main diagonal) fill up the other diagonal. Since we know the middle digit in advance we have about 90 possibilities but we also know that the first digit is definitely not even (because the first column must be also a prime) - thus halving the number of primes - we have 45 possibilities.

Third, (for all possible previous selections) fill-up the first row - we have about 20 possibilities, then fill the second and fourth columns, and compute the middle digit in the last row (we know all other digits and the digit sum) and verify that last row is prime. From this point on only a small number of selections will pass, since it is not very common that the last row will be prime. The filling process continues filling the third column, second and fourth row and final verification. The table below shows the order in which the single digits are filled-in.

 1  3  3  3  2
 8  1  7  2  8
10  4  1  5 10
 9  2  7  1  9
 2  4  6  5  1

Finally the solutions need to be sorted because we need to output them in a sorted order - of course we use the built-in QSORT function.

The total operations required (worst test case) are 90*45*20*5*5*5*5*5 - which is only theoretical, since number of possibilities drastically lowers the final fives.

The idea of this approach can be extended to use symmetry to lower the running time eve more. (When square filled) when rows are exchanged by columns the main diagonal remains the same, rows are columns, columns are rows (all are valid primes) and the other diagonal reverts itself, thus if the reverted diagonal is prime we have another valid solution. For the worst test case 23,3 there are 79 (from total of 152 solutions) solutions with the other diagonal as a "double prime" - some of them are symmetric by the main diagonal and the others (about 70) form "pairs" where one member could be obtained from the another one by exchanging rows by columns since the second diagonal is "double-prime". To lower the running time, when filling the square in the STEP 2, when a double-prime is about to be inserted, we insert it only the one way and to get solutions for the second way we perform the operation of exchanging the rows by columns (e.g., 1. row <-> 1. column, 2.row <-> 2.column, etc.). Thus reducing the total running time. 

*/

/*
ID: tvaroze001
PROG: prime3
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctime>

#define MAXP 1000
#define MAXS 200

typedef struct
{
    int d[5];           // decimal digits - for quick lookup
    int val;            // prime decimal value
} PRIME;

// records for storing primes as "prime patterns"

typedef struct {
    int n,r[200];
} RECORD200;

typedef struct {
    int n,r[50];
} RECORD50;

typedef struct {
    int n,r[20];
} RECORD20;

typedef struct {
    char s[5*5+1];
} SOLUTION;

PRIME p[MAXP];
int np;
int prime[10][10][10][10][10];// whether number (given its digits) is prime
int dg_sum;                   // digit sum
int sq_a,sq_b,sq_c,sq_d,sq_e,           // prime square
    sq_f,sq_g,sq_h,sq_i,sq_j,
    sq_k,sq_l,sq_m,sq_n,sq_o,
    sq_p,sq_q,sq_r,sq_s,sq_t,
    sq_u,sq_v,sq_w,sq_x,sq_y;
                // '.' = unknown, '_' = 1,3,7,9, '-' = non-zero

RECORD200 pat1[10];     // prime pattern #1: X..._
RECORD200 pat2[10];     // prime pattern #2: _.X._
RECORD50  pat3[10][10]; // prime pattern #3: X---Y
RECORD20  pat4[10][10][10]; // prime pattern #4: XY.Z_
RECORD20  pat7[10][10][10]; // prime pattern #7: X.Y.Z
RECORD20  pat8[10][10][10]; // prime pattern #8: .XYZ_
SOLUTION sol[MAXS];

int nsolution;

void solution(void) {
    sol[nsolution].s[0] = sq_a; sol[nsolution].s[1] = sq_b; 
    sol[nsolution].s[2] = sq_c; sol[nsolution].s[3] = sq_d; 
    sol[nsolution].s[4] = sq_e; sol[nsolution].s[5] = sq_f; 
    sol[nsolution].s[6] = sq_g; sol[nsolution].s[7] = sq_h; 
    sol[nsolution].s[8] = sq_i; sol[nsolution].s[9] = sq_j; 
    sol[nsolution].s[10] = sq_k;sol[nsolution].s[11] = sq_l;    
    sol[nsolution].s[12] = sq_m;sol[nsolution].s[13] = sq_n;    
    sol[nsolution].s[14] = sq_o;sol[nsolution].s[15] = sq_p;    
    sol[nsolution].s[16] = sq_q;sol[nsolution].s[17] = sq_r;    
    sol[nsolution].s[18] = sq_s;sol[nsolution].s[19] = sq_t;    
    sol[nsolution].s[20] = sq_u;sol[nsolution].s[21] = sq_v;    
    sol[nsolution].s[22] = sq_w;sol[nsolution].s[23] = sq_x;    
    sol[nsolution].s[24] = sq_y;sol[nsolution].s[25] = 0;
    nsolution++;
}

void fill(void) {
    int i,j,k,l,m,n,o,q, ii,ij,ik,il,im,in,io,iq,wi,wj,wk,wl,wm,wn,wo,wq;
    ii = pat1[sq_a].n;
    for (i = 0; i < ii; i++) {
        wi = pat1[sq_a].r[i];
        sq_g = p[wi].d[1];
        sq_m = p[wi].d[2];
        sq_s = p[wi].d[3];
        sq_y = p[wi].d[4];
        ij = pat2[ sq_m ].n;
        for (j = 0; j < ij; j++) {
            wj = pat2[ sq_m ].r[j];
            sq_u = p[wj].d[0];
            sq_q = p[wj].d[1];
            sq_i = p[wj].d[3];
            sq_e = p[wj].d[4];
            ik = pat3[ sq_a ][ sq_e ].n;
            for (k = 0; k < ik; k++) {
                wk = pat3[ sq_a ][ sq_e ].r[k];
                sq_b = p[wk].d[1];
                sq_c = p[wk].d[2];
                sq_d = p[wk].d[3];
                il = pat4[ sq_b ][ sq_g ][ sq_q ].n;
                for (l = 0; l < il; l++) {
                    wl = pat4[ sq_b ][ sq_g ][ sq_q ].r[l];
                    sq_l = p[wl].d[2];
                    sq_v = p[wl].d[4];
                    im = pat4[ sq_d ][ sq_i ][ sq_s ].n;
                    for (m = 0; m < im; m++) {
                        wm = pat4[ sq_d ][ sq_i ][ sq_s ].r[m];
                        sq_n = p[wm].d[2];
                        sq_x = p[wm].d[4];
                        sq_w = dg_sum - sq_u - sq_v - sq_x - sq_y;
                        if ( sq_w != 1 && sq_w != 3 &&
                                      sq_w != 7 && sq_w != 9 )
                            continue;
                        if (prime[sq_u][sq_v][sq_w][sq_x][sq_y] == 0)
                            continue;
                        in = pat7[ sq_c ][ sq_m ][ sq_w ].n;
                        for (n = 0; n < in; n++) {
                            wn = pat7[ sq_c ][ sq_m ][ sq_w ].r[n];
                            sq_h = p[wn].d[1];
                            sq_r = p[wn].d[3];
                            io = pat8[ sq_g ][ sq_h ][ sq_i ].n;
                            for (o = 0; o < io; o++) {
                                wo = pat8[ sq_g ][ sq_h ][ sq_i ].r[o];
                                sq_f = p[wo].d[0];
                                sq_j = p[wo].d[4];
                                iq = pat8[ sq_q ][ sq_r ][ sq_s ].n;
                                for (q = 0; q < iq; q++) {
                                    wq = pat8[ sq_q ][ sq_r ][ sq_s ].r[q];
                                    sq_p = p[wq].d[0];
                                    sq_t = p[wq].d[4];
                                    sq_k = dg_sum - sq_a-sq_f-sq_p-sq_u;
                                    if ( sq_k < 0 || sq_k > 9 )
                                        continue;
                                    sq_o = dg_sum - sq_e-sq_j-sq_t-sq_y;
                                    if ( sq_o != 1 && sq_o != 3
                                             && sq_o != 7 && sq_o != 9 )
                                        continue;
                                    if (prime[sq_a][sq_f][sq_k][sq_p][sq_u])
                                    if (prime[sq_k][sq_l][sq_m][sq_n][sq_o])
                                    if (prime[sq_e][sq_j][sq_o][sq_t][sq_y])
                                        solution();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int sol_cmp( const void *va, const void *vb ) {
    int i;
    SOLUTION *sa = (SOLUTION*)va, *sb = (SOLUTION*)vb;
    for (i = 0; i < 25; i++)
    {   if (sa->s[i] > sb->s[i]) return 1;
        if (sa->s[i] < sb->s[i]) return -1;
    }
    return 0;
}

int main(void) {
    FILE *fin,*fout;
    int i,j,k,sum,d0,d1,d2,d3,d4,pp,rt;
    fin = fopen("prime3.in","rt");
    fout = fopen("prime3.out","wt");
    fscanf(fin,"%d %d",&dg_sum,&sq_a);
int tmr=clock();
    // generate all 5-digit primes given the digit sum
    for ( rt = (int)sqrt(99999), pp = 10008; pp < 99999; pp += 6 )
        for (i = pp-1; i <= pp+1; i += 2) {
            j = i; sum = 0; k = 0;
            while ( j > 0 ) {
                p[np].d[4-k++] = j % 10;
                sum += p[np].d[5-k];
                j /= 10;
            }
            if (sum != dg_sum)
                continue;
            for (j = 5; j <= rt; j++)
                if ( i % j == 0 )
                    break;
            if ( j == rt+1 ) {
                if ( sum == dg_sum )
                {
                d0 = p[np].d[0]; d1 = p[np].d[1]; d2 = p[np].d[2];
                d3 = p[np].d[3]; d4 = p[np].d[4];
                // indicate the primes (as digits) for constant lookup
                prime[ d0 ][ d1 ][ d2 ][ d3 ][ d4 ] = 1;
    
            // fill-up lookup patterns
                pat1[ d0 ].r[pat1[ d0 ].n++ ] = np;
                if ( d0 == 1 || d0 == 3 || d0 == 7 || d0 == 9 )
                    pat2[ d2 ].r[pat2[ d2 ].n++ ] = np;
                if ( d1 != 0 && d2 != 0 && d3 != 0 )
                    pat3[ d0 ][ d4 ].r[pat3[ d0 ][ d4 ].n++] = np;
                pat4[ d0 ][ d1 ][ d3 ].r[pat4[ d0 ][ d1 ][ d3 ].n++] = np;
                pat7[ d0 ][ d2 ][ d4 ].r[pat7[ d0 ][ d2 ][ d4 ].n++] = np;
                pat8[ d1 ][ d2 ][ d3 ].r[pat8[ d1 ][ d2 ][ d3 ].n++] = np;
                // store the actual prime value - what a waste
                p[np++].val = i;
                }
            }
        }
    // recursively fill the entire square (backtrack)
    fill();
    // printout the solutions
    if (nsolution == 0)
        fprintf(fout,"NONE\n");
    else {
        // sort
        qsort( &sol, nsolution, sizeof(SOLUTION), sol_cmp);
        for (i = 0; i < nsolution; i++) {
            for (j = 0; j < 5; j++) {
                for ( k = 0; k < 5; k++ )
                    fprintf(fout,"%d",sol[i].s[j*5+k]);
                fprintf(fout,"\n");
            }
            if (i+1 < nsolution)
                fprintf(fout,"\n");
        }
    }
fprintf(stderr, "[%d]\n", (int)(clock()-tmr));
    return 0;
}

