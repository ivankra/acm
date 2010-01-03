/**
 *   //////////////////////////////
 *   // Miscellaneous Algorithms //
 *   //////////////////////////////
 *
 * LAST MODIFIED:
 *      June 6, 2004
 *
 * This file is part of my library of algorithms found here:
 *      http://www.palmcommander.com:8081/tools/
 * LICENSE:
 *      http://www.palmcommander.com:8081/tools/LICENSE.html
 * Copyright (c) 2004
 * Contact author:
 *      igor at cs.ubc.ca
 **/

/***********
 * foreach *
 ***********
 * A handy macro for iterating through STL collections.
 */
#define foreach(i, c) for( __typeof( (c).begin() ) i = (c).begin(); i != (c).end(); ++i )

/**********************
 * Print a Polynomial *
 **********************
 * Takes a list of coefficients, a largest power and a variable name
 * And prints the polynomial to stdout in the form of, e.g
 * 4*x^3+8*n-9
 * #include <math.h>
 **/
void printPoly( int coeffs[], int n, const char *var )
{
    bool empty = true;
    while( n-- )
    {
        if( coeffs[n] || empty && !n )
        {
            if( !empty || coeffs[n] < 0 ) printf( "%c", ( coeffs[n] > 0 ? '+' : '-' ) );
            if( abs( coeffs[n] ) > 1 || n == 0 ) printf( "%d", abs( coeffs[n] ) );
            if( n > 0 )
            {
                if( abs( coeffs[n] ) > 1 ) printf( "*" );
                printf( "%s", var );
            }
            if( n > 1 ) printf( "^%d", n );
            empty = false;
        }
    }
}

/***************
 * Maximum sum *
 ***************
 * Given an array of integers on stdin, find the sub-array
 * [i, j] containing the largest sum, favouring longer ranges,
 * then smaller indices. This one only considers non-negative
 * sums. Best sum and range are returned through pointers.
 * #include <stdio.h>
 **/
void maximumSum( int *bestSum, int *first, int *last )
{
    int start = -1; sum = 0; best = -1; besti = -1; bestj = -1;
    scanf( "%d", &n );          // Size of input array
    for( i = 1; i < n; i++ )
    {
        scanf( "%d", &edge );   // ( Input array )[i - 1];
        if( start < 0 ) { if( edge < 0 ) continue; else start = i; }
        if( edge > 0 && sum < 0 ) { start = i; sum = 0; }
        sum += edge;
        if( edge > 0 && sum >= best )
        {
            if( sum > best || i - start > bestj - besti )
            {
                besti = start;
                bestj = i;
                best = sum;
            }
        }
    }

    *bestSum = best;
    if( best >= 0 ) { *first = besti - 1; *last = bestj; }
}

/**********************
 * Fast integer input *
 **********************
 * Reads an integer from standard input.
 * Almost equivalent to scanf( "%d", n ) (must be terminated
 * by a space or a '\n').
 * WARNING:
 * Valladolid now forbids unlocked IO. Remove the "_unlocked"
 * to get a version that is 1.5 - 2 times slower.
 *
 * #include <stdio.h>
 * USED BY: lis
 **/
void readn( register int *n )
{
    int sign = 1;
    register char c;
    *n = 0;
    while( ( c = getc_unlocked( stdin ) ) != '\n' )
    {
        switch( c )
        {
            case '-' : sign = -1;
            case ' ': goto hell;
            case '\n': goto hell;
            default: (*n) *= 10; (*n) += ( c - '0' ); break;
        }
    }
hell:
    (*n)*=sign;
}

/**********************************
 * Longest Increasing Subsequence *
 **********************************
 * Computes the longest increasing subsequence for a number
 * of problem instances, each given as a sequence of non-negative
 * integers, terminated by a -1. The whole input is terminated
 * by a -1.
 *
 * readn( int *n ) reads the next integer in the sequence.
 *
 * #include <vector>
 * #include <algorithm>
 * REQUIRES: readn (suggested)
 * COMPLEXITY: O(nlogn)
 **/
int lis()
{
    int n, prob = 0;
    vector< int > table;
    while( true )
    {
        table.clear();
        while( true )
        {
            readn( &n );        // "cin >> n;" might be too slow
            if( n < 0 ) break;
            vector< int >::iterator i =
                upper_bound( table.begin(), table.end(), n );
            if( i == table.end() )
                table.push_back( n );
            else
                *i = n;
        }
        if( table.empty() ) break;
        printf( "Test #%d:\n  maximum possible interceptions: %d\n\n",
            ++prob, table.size() );
    }
    return 0;
}

/*****************
 * Lex k-subsets *
 *****************
 * Given a set of n elements, prints all subsets of size k in
 * lexicographic order. Each one is displayed as a string of
 * 0's and 1's. For example, when n = 4, k = 2, the
 * routine prints
 *      0011
 *      0101
 *      0110
 *      1001
 *      1010
 *      1100
 * COMPLEXITY: O(n*2^n)
 **/
void lexKSubsets( int n, int k )
{
    for( int i = 0; i < ( 1 << n ); i++ )
    {
        int bits = 0;
        for( int j = 0; j < n; j++ ) if( i & ( 1 << j ) ) bits++;
        if( bits != k ) continue;
        for( int j = n - 1; j >= 0; j-- )
            printf( "%c", ( ( i & ( 1 << j ) ) ? '1' : '0' ) );
        printf( "\n" );
    }
}

/***************
 * fill string *
 ***************
 * Creates a string of n identical characters, c
 * #include <string>
 * USED BY: toRoman()
 **/
string fill( char c, int n )
{
    string s;
    while( n-- ) s += c;
    return s;
}

/******************
 * Roman numerals *
 ******************
 * Converts an integer in the range [1, 4000) to a lower case Roman numeral
 * #include <string>
 * REQUIRES: fill()
 **/
string toRoman( int n )
{
    if( n < 4 ) return fill( 'i', n );
    if( n < 6 ) return fill( 'i', 5 - n ) + "v";
    if( n < 9 ) return string( "v" ) + fill( 'i', n - 5 );
    if( n < 11 ) return fill( 'i', 10 - n ) + "x";
    if( n < 40 ) return fill( 'x', n / 10 ) + toRoman( n % 10 );
    if( n < 60 ) return fill( 'x', 5 - n / 10 ) + 'l' + toRoman( n % 10 );
    if( n < 90 ) return string( "l" ) + fill( 'x', n / 10 - 5 ) + toRoman( n % 10 );
    if( n < 110 ) return fill( 'x', 10 - n / 10 ) + "c" + toRoman( n % 10 );
    if( n < 400 ) return fill( 'c', n / 100 ) + toRoman( n % 100 );
    if( n < 600 ) return fill( 'c', 5 - n / 100 ) + 'd' + toRoman( n % 100 );
    if( n < 900 ) return string( "d" ) + fill( 'c', n / 100 - 5 ) + toRoman( n % 100 );
    if( n < 1100 ) return fill( 'c', 10 - n / 100 ) + "m" + toRoman( n % 100 );
    if( n < 4000 ) return fill( 'm', n / 1000 ) + toRoman( n % 1000 );
    return "?";
}

/***************************
 * Milk Judge (Valladolid) *
 ***************************
 * Stop the program in one of 8 possible ways, essentially
 * giving back the 3 lowest bits of 'n', whatever n is.
 **/
void milkJudge( int n )
{
    switch( n & 7 )
    {
        case 0: exit( 0 );                              // Wrong Answer
        case 1: assert( false );                        // SIGABRT
        case 2: *( int* )( n - n ) = 0;                 // SIGSEGV
        case 3: n /= ( n - 3 );                         // SIGFPE
        case 4: while( 1 );                             // Time Limit Exceeded
        case 5: while( 1 ) malloc( 1024 * 1024 );       // Memory Limit Exceeded
        case 6: malloc( 32 * 1024 * 1024 ); while(1);   // 32MB + TLE
        case 7: while( 1 ) printf( "." );               // Output Limit Exceeded
    }
}
