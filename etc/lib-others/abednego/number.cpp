/**
 *   /////////////////////////////////
 *   // Number Theoretic Algorithms //
 *   /////////////////////////////////
 *
 * Contents:
 *      - GCD (Euclidean algorithm)
 *      - extended GCD
 *      - modular linear equation solver
 *      - linear Diophantine equation solver
 *      - modular inverse
 *      - successive squaring (modular powers)
 *      - sieve of Erastosthenes
 *      - simple primality testing algorithm
 *      - simple factoring algorithm
 *      - Euler phi (totient) function
 *      - number of divisors
 *      - continued fractions of rationals
 * Most functions are templates and will work with BigInt.
 *
 * This file is part of my library of algorithms found here:
 *      http://www.lexansoft.com:8081/tools/
 * Copyright (c) 2002-2005
 * Contact author:
 *      igor at cs.ubc.ca
 * Last modified:
 *      January 21, 2005
 **/

/*******
 * GCD *
 *******
 * Euclidean algorithm. Works on non-negative integers.
 **/
int gcd( int a, int b ) { return( b == 0 ? a : gcd( b, a % b ) ); }
long long gcd( long long a, long long b ) { return( b == 0 ? a : gcd( b, a % b ) ); }
template< Int > Int gcd( Int a, Int b ) { return( b == 0 ? a : gcd( b, a % b ); }

/************************
 * A triple of integers *
 ************************
 * USED BY: egcd, msolve, inverse, ldioph
 **/
template< class Int >
struct Triple
{
    Int d, x, y;
    Triple( Int q, Int w, Int e ) : d( q ), x( w ), y( e ) {}
};

/****************
 * Extended GCD *
 ****************
 * Given nonnegative a and b, computes d = gcd( a, b )
 * along with integers x and y, such that d = ax + by
 * and returns the triple (d, x, y).
 * WARNING: needs a small modification to work on
 *      negative integers (operator% fails).
 * REQUIRES: struct Triple
 * USED BY: msolve, inverse, ldioph
 **/
template< class Int >
Triple< Int > egcd( Int a, Int b )
{
    if( !b ) return Triple< Int >( a, Int( 1 ), Int( 0 ) );
    Triple< Int > q = egcd( b, a % b );
    return Triple< Int >( q.d, q.y, q.x - a / b * q.y );
}

/**********************************
 * Modular Linear Equation Solver *
 **********************************
 * Given a, b and n, solves the equation ax = b (mod n)
 * for x. Returns the vector of solutions, all smaller
 * than n and sorted in increasing order. The vector is
 * empty if there are no solutions.
 * #include <vector>
 * REQUIRES: struct Triple, egcd
 **/
template< class Int >
vector< Int > msolve( Int a, Int b, Int n )
{
    if( n < 0 ) n = -n;
    Triple< Int > t = egcd( a, n );
    vector< Int > r;
    if( b % t.d ) return r;
    Int x = ( b / t.d * t.x ) % n;
    if( x < Int( 0 ) ) x += n;
    for( Int i = 0; i < t.d; i++ )
        r.push_back( ( x + i * n / t.d ) % n );
    return r;
}

/**************************************
 * Linear Diophantine Equation Solver *
 **************************************
 * Solves integer equations of the form ax + by = c
 * for integers x and y. Returns a triple containing
 * the answer (in .x and .y) and a flag (in .d).
 * If the returned flag is zero, then there are no
 * solutions. Otherwise, there is an infinite number
 * of solutions of the form
 *          x = t.x + k * b / t.d,
 *          y = t.y - k * a / t.d;
 * where t is the returned triple, and k is any
 * integer.
 * REQUIRES: struct Triple, egcd
 **/
template< class Int >
Triple< Int > ldioph( Int a, Int b, Int c )
{
    Triple< Int > t = egcd( a, b );
    if( c % t.d ) return Triple< Int >( 0, 0, 0 );
    t.x *= c / t.d; t.y *= c / t.d;
    return t;
}

/*******************
 * Modular Inverse *
 *******************
 * Given a and n, solves ax = 1 (mod n).
 * Returns 0 if there is no solution.
 * REQUIRES: struct Triple, egcd
 **/
template< class Int >
Int inverse( Int a, Int n )
{
    Triple< Int > t = egcd( a, n );
    if( t.d > Int( 1 ) ) return Int( 0 );
    Int r = t.x % n;
    return( r < Int( 0 ) ? r + n : r );
}

/***********************
 * Successive Squaring * (for int powers and moduli)
 ***********************
 * Computes b^p mod m. Wants b >= 0, p >= 0, m >= 1.
 **/
int powmod( long long b, int p, int m )
{
    long long r = 1;
    for( int i = ( 1 << 30 ); i; i >>= 1 )
    {
        r *= r; r %= m;
        if( p & i ) { r *= b; r %= m; }
    }
    return ( int )r;
}

/***********************
 * Successive Squaring * (for long long powers)
 ***********************
 * Computes b^p mod m. Wants p >= 0, m >= 1.
 * If m is 0 (which it is by default), no modding is
 * done - expect the full power!
 **/
template< class Int >
Int powmod( Int b, long long p, Int m = 0 )
{
    Int r = 1;
    for( long long i = ( 1LL << 62 ); i; i >>= 1 )
    {
        r *= r; if( m > 0 ) r %= m;
        if( p & i ) { r *= b; if( m > 0 ) r %= m; }
    }
    return r;
}

/***********************
 * Successive Squaring * (for arbitrary powers)
 ***********************
 * Computes b^p mod m. Wants p >= 0, m >= 1.
 * If m is 0 (which it is by default), no modding is
 * done - expect the full power!
 **/
template< class Int >
Int powmod( Int b, Int p, Int m = 0 )
{
    vector< bool > bits;
    while( p > 0 )
    {
        Int np = p / 2;
        bits.push_back( np + np != p );
        p = np;
    }

    Int r = 1;
    for( int i = bits.size() - 1; i >= 0; i-- )
    {
        r *= r; if( m > 0 ) r %= m;
        if( bits[i] ) { r *= b; if( m > 0 ) r %= m; }
    }
    return r;
}

/**************************
 * Sieve of Erastosthenes * (simple, slow version)
 **************************
 * Given a bool array, fills it in such a way that
 * prime[i] is true iff i is prime. This variant
 * requires about 2NlogN operations (under 1 second
 * for N = 100M).
 * #include <string.h>
 * #include <math.h>
 **/
void sieve( bool prime[], int N )
{
    memset( prime, -1, N * sizeof( prime[0] ) );
    prime[0] = prime[1] = false;
    int sqrtN = ( int )sqrt( ( double )N );
    for( int i = 2; i <= sqrtN; i++ ) if( prime[i] )
    {
        for( int j = i * i; j < N; j += i )
            prime[j] = false;
    }
}

/**************************
 * Sieve of Erastosthenes * (fast, memory efficient version)
 **************************
 * Does some magic, after which gP(n) is non-zero iff n is
 * prime. N is the value of the largest prime you will need.
 * Requires N / 16 bytes of memory.
 * WARNING! Only works for odd numbers; deal with even numbers 
 * yourself!
 * If that is unacceptable, add "n==2||(n&1)&&" after the
 * first bracket in the gP() macro.
 * #include <string.h>
 * #include <math.h>
 **/
#define N 51000000
unsigned int prime[N / 64];
#define gP(n) (prime[n>>6]&(1<<((n>>1)&31)))
#define rP(n) (prime[n>>6]&=~(1<<((n>>1)&31)))
void sieve()
{
    memset( prime, -1, sizeof( prime ) );

    unsigned int i;
    unsigned int sqrtN = ( unsigned int )sqrt( ( double )N ) + 1;
    for( i = 3; i < sqrtN; i += 2 ) if( gP( i ) )
    {
        unsigned int i2 = i + i;
        for( unsigned int j = i * i; j < N; j += i2 ) rP( j );
    }
}

/*************
 * Primality * (simple)
 *************
 * A very crude O(sqrt(n)) (sort of) primality tester.
 * #include <math.h>
 * REQUIRES: the constructor Int::Int( double ).
 **/
template< class Int >
bool isPrime( Int n )
{
    if( n < 2 ) return false;
    Int sq = Int( sqrt( n ) );
    for( Int i = 2; i <= sq; i++ )
        if( !( n % i ) ) return false;
    return true;
}

/*************
 * Factoring *
 *************
 * A primitive factoring algorithm. n is the number
 * to factor. v is a vector that will be filled with
 * with the factors. Example: factoring 24 adds
 * (2, 2, 2, 3) to v. Complexity: O(sqrt(n)) (sort of).
 * #include <vector>
 * #include <math.h>
 * REQUIRES: sqrt() must work on Int.
 * REQUIRES: the constructor Int::Int( double ).
 * REQUIRES: the casting operator Int::operator double()
 **/
template< class Int >
void factor( Int n, vector< Int > &v )
{
    Int sq = Int( sqrt( ( double )n ) );
    for( Int i = 2; i <= sq; i++ )
    {
        if( n % i ) continue;
        v.push_back( i );
        n /= i--;
	sq = Int( sqrt( ( double )n ) );
    }
    if( n > 1 ) v.push_back( n );
}

/**************************
 * Euler totient function *
 **************************
 * Returns the number of positive integers that are
 * relatively prime to n. As efficient as factor().
 * #include <vector>
 * REQUIRES: factor()
 * REQUIRES: sqrt() must work on Int.
 * REQUIRES: the constructor Int::Int( double ).
 **/
int phi( int n )
{
    vector< int > p;
    factor( n, p );
    for( int i = 0; i < ( int )p.size(); i++ )
    {
        if( i && p[i] == p[i - 1] ) continue;
        n /= p[i];
        n *= p[i] - 1;
    }
    return n;
}

/**********************
 * Number of divisors *
 **********************
 * Returns the number of positive divisors of n.
 * Complexity: about O(sqrt(n)).
 * #include <math.h>
 * #include <vector>
 * REQUIRES: factor()
 * REQUIRES: sqrt() must work on Int.
 * REQUIRES: the constructor Int::Int( double ).
 **/
template< class Int >
Int divisors( Int n )
{
    vector< Int > f;
    factor( n, f );
    int k = f.size();
    vector< Int > table( k + 1, Int( 0 ) );
    table[k] = Int( 1 );

    for( int i = k - 1; i >= 0; i-- )
    {
        table[i] = table[i + 1];
        for( int j = i + 1; ; j++ )
            if( j == k || f[j] != f[i] )
                { table[i] += table[j]; break; }
    }

    return table[0];
}

/************************************
 * Continued Fractions of Rationals *
 ************************************
 * Returns the continued fraction of the rational
 * number m/n. The resulting finite sequence of
 * integers is pushed to the end of 'ans'.
 * Complexity: O( log n )
 * #include <vector>
 **/
template< class Int >
void contFract( Int m, Int n, vector< Int > &ans )
{
    while( n )
    {
        ans.push_back( m / n );
        m %= n;
        m ^= n ^= m ^= n;
    }
}
