/**
 * Rational number class template by igor
 * Stores and manipulates rational numbers represented by a pair
 * of integers of any type. This means that you can create
 * instances of Rational like this:
 *      - Rational< int > ri;
 *      - Rational< long long > rll;
 *      - Rational< BigInt > rbi;
 *
 * REQUIREMENTS on type T:
 *  - 0 and 1 must be valid parameters to T's constructor
 *  - all basic arithmetic operators must be defined for T
 *  - % (modulo operator) must be defined for T
 *
 * INVARIANTS:
 *      - the number is always stored in lowest terms
 *      - the denominator is always positive (###)
 *
 * (###) The denominator becomes 0 after dividing by zero
 *
 * FIELD TESTING:
 *      Passed these problems on Valladolid: 10113
 *
 * This file is part of my library of algorithms found here:
 *      http://www.palmcommander.com:8081/tools/
 * LICENSE:
 *      http://www.palmcommander.com:8081/tools/LICENSE.html
 * Copyright (c) 2004
 * Last modified: February 25, 2004
 * Contact author:
 *      igor at cs.ubc.ca
 **/

#include <string>
#include <iostream>
#include <math.h>
#include <sstream>

#ifndef min
#define min(x,y) ((x) < (y) ? (x) : (y))
#endif

#ifndef max
#define max(x,y) ((x) > (y) ? (x) : (y))
#endif

template< class T >
class Rational
{
    private:
        /** Greatest Common Divisor. **/
        static T gcd( const T &a, const T &b ) { return( a == T( 0 ) ? b : gcd( b % a, a ) ); }

        /** Reduces to lowest terms. **/
        inline void norm() { T g = gcd( n, d ); n /= g; d /= g; if( d < T( 0 ) ) { n = -n; d = -d; } }

        /** Creates a Rational without calling norm(). **/
        static inline Rational makeRat( const T &num, const T &denom )
        {
            Rational r( num );
            r.d = denom;
            return r;
        }

    public:
        /** Numerator and denominator. **/
        T n, d;

        /** Creates a new Rational number with value zero. **/
        Rational(): n( 0 ), d( 1 ) {}

        /** Creates a new Rational number with denominator 1. **/
        Rational( const T &num ): n( num ), d( 1 ) {}

        /** Creates a new Rational number with a given value. **/
        Rational( const T &num, const T &denom ): n( num ), d( denom ) { norm(); }

        /** Arithmetic. **/
        Rational< T > &operator++();
        Rational< T > &operator++( int );
        Rational< T > &operator--();
        Rational< T > &operator--( int );
        Rational< T >  operator- ();
        Rational< T >  operator+ ( const T &t    ) const;
        Rational< T >  operator+ ( const Rational< T > &r ) const;
        Rational< T > &operator+=( const T &t    );
        Rational< T > &operator+=( const Rational< T > &r );
        Rational< T >  operator- ( const T &t    ) const;
        Rational< T >  operator- ( const Rational< T > &r ) const;
        Rational< T > &operator-=( const T &t    );
        Rational< T > &operator-=( const Rational< T > &r );
        Rational< T >  operator* ( const T &t    ) const;
        Rational< T >  operator* ( const Rational< T > &r ) const;
        Rational< T > &operator*=( const T &t    );
        Rational< T > &operator*=( const Rational< T > &r );
        Rational< T >  operator/ ( const T &t    ) const;
        Rational< T >  operator/ ( const Rational< T > &r ) const;
        Rational< T > &operator/=( const T &t    );
        Rational< T > &operator/=( const Rational< T > &r );

        /** Comparision. **/
        bool operator< ( const Rational< T > &r ) const;
        bool operator> ( const Rational< T > &r ) const;
        bool operator<=( const Rational< T > &r ) const;
        bool operator>=( const Rational< T > &r ) const;
        bool operator==( const Rational< T > &r ) const;

        /** Casting and type conversion **/
        bool operator!() const;
        operator string() const;
        string toString() const;

        /** Outputs value to stdout **/
        void print() const;

        /** I/O Friends **/
        friend istream &operator>><>( istream &in, const Rational< T > &n );
        friend ostream &operator<<<>( ostream &out, const Rational< T > &n );
};

template< class T > istream &operator>>( istream &in, const Rational< T > &n );
template< class T > ostream &operator<<( ostream &out, const Rational< T > &n );

template< class T >
Rational< T > &Rational< T >::operator++()
{
    Rational old = *this;
    n += d;
    return old;
}

template< class T >
Rational< T > &Rational< T >::operator++( int )
{
    n += d;
    return *this;
}

template< class T >
Rational< T > &Rational< T >::operator--()
{
    Rational old = *this;
    n -= d;
    return old;
}

template< class T >
Rational< T > &Rational< T >::operator--( int )
{
    n -= d;
    return *this;
}

template< class T >
Rational< T > Rational< T >::operator-()
{
    return makeRat( -n, d );
}

template< class T >
Rational< T > Rational< T >::operator+( const T &t ) const
{
    return makeRat( n + t * d, d );
}

template< class T >
Rational< T > Rational< T >::operator+( const Rational< T > &r ) const
{
    //FIXME: Can make this potentially slower but more robust against overflow
    return Rational< T >( n * r.d + d * r.n, d * r.d );
}

template< class T >
Rational< T > &Rational< T >::operator+=( const T &t )
{
    n += t * d;
    return *this;
}

template< class T >
Rational< T > &Rational< T >::operator+=( const Rational< T > &r )
{
    n *= r.d;
    n += d * r.n;
    d *= r.d;
    norm();
    return *this;
}

template< class T >
Rational< T > Rational< T >::operator-( const T &t ) const
{
    return makeRat( n - t * d, d );
}

template< class T >
Rational< T > Rational< T >::operator-( const Rational< T > &r ) const
{
    return Rational< T >( n * r.d - d * r.n, d * r.d );
}

template< class T >
Rational< T > &Rational< T >::operator-=( const T &t )
{
    n -= t * d;
    return *this;
}

template< class T >
Rational< T > &Rational< T >::operator-=( const Rational< T > &r )
{
    n *= r.d;
    n -= d * r.n;
    d *= r.d;
    norm();
    return *this;
}

template< class T >
Rational< T > Rational< T >::operator*( const T &t ) const
{
    T bc = gcd( t, d );
    return makeRat( n * ( t / bc ), d / bc );
}

template< class T >
Rational< T > Rational< T >::operator*( const Rational< T > &r ) const
{
    T ad = gcd( n, r.d ), bc = gcd( r.n, d );
    return makeRat( ( n / ad ) * ( r.n / bc ), ( d / bc ) * ( r.d / ad ) );
}

template< class T >
Rational< T > &Rational< T >::operator*=( const T &t )
{
    T bc = gcd( t, d );
    n *= t / bc;
    d /= bc;
    return *this;
}

template< class T >
Rational< T > &Rational< T >::operator*=( const Rational< T > &r )
{
    T ad = gcd( n, r.d ), bc = gcd( r.n, d );
    n /= ad;
    n *= r.n / bc;
    d /= bc;
    d *= r.d / ad;
    return *this;
}

template< class T >
Rational< T > Rational< T >::operator/( const T &t ) const
{
    T ac = gcd( n, t );
    return makeRat( n / ac, d * ( t / ac ) );
}

template< class T >
Rational< T > Rational< T >::operator/( const Rational< T > &r ) const
{
    T ac = gcd( n, r.n ), bd = gcd( d, r.d );
    return makeRat( ( n / ac ) * ( r.d / bd ), ( d / bd ) * ( r.n / ac ) );
}

template< class T >
Rational< T > &Rational< T >::operator/=( const T &t )
{
    T ac = gcd( n, t );
    n /= ac;
    d *= t / ac;
    return *this;
}

template< class T >
Rational< T > &Rational< T >::operator/=( const Rational< T > &r )
{
    T ac = gcd( n, r.n ), bd = gcd( d, r.d );
    n /= ac;
    n *= r.d / bd;
    d /= bd;
    d *= r.n / ac;
    return *this;
}

/** Comparison. **/
template< class T >
inline bool Rational< T >::operator< ( const Rational< T > &r ) const
{
    return n * r.d < d * r.n;
}

template< class T >
inline bool Rational< T >::operator> ( const Rational< T > &r ) const
{
    return n * r.d > d * r.n;
}

template< class T >
inline bool Rational< T >::operator<=( const Rational< T > &r ) const
{
    return n * r.d <= d * r.n;
}

template< class T >
inline bool Rational< T >::operator>=( const Rational< T > &r ) const
{
    return n * r.d >= d * r.n;
}

template< class T >
inline bool Rational< T >::operator==( const Rational< T > &r ) const
{
    return n == r.n && d == r.d;
}

/** Casting and type conversion **/
template< class T >
bool Rational< T >::operator!() const
{
    return n == T( 0 );
}

template< class T >
Rational< T >::operator string() const
{
    ostringstream out;
    out << n << " / " << d;
    return out.str();
}

template< class T >
string Rational< T >::toString() const
{
    return *this;
}

/** Outputs value to stdout **/
template< class T >
void Rational< T >::print() const
{
    cout << *this;
}

/** I/O Friends **/
template< class T >
istream &operator>>( istream &in, const Rational< T > &r )
{
    char slash;
    in >> r.n >> slash >> r.d;
    return in;
}

template< class T >
ostream &operator<<( ostream &out, const Rational< T > &r )
{
    return( out << ( string )r );
}

/** TESTING and DEBUGGING **/
typedef Rational< int > RI;
int main()
{
    cout << "Constructors and printing" << endl;
    cout << "0 = " << RI().toString() << endl;
    cout << "1 = " << RI( 1 ).toString() << endl;
    cout << "0 = " << ( string )RI( 0, 1 ) << endl;
    cout << "5 / 3 = " << RI( -15, -9 ) << endl;
    cout << "-6 / 7 = " << RI( -60, 70 ) << " = " << RI( 60, -70 ) << endl;
    cout << "-7 / 6 = " << RI( -70, 60 ) << " = " << RI( 70, -60 ) << endl;
    cout << endl;
    cout << "Algebra" << endl;
    cout << "0 + 1 = "          << RI()             + RI( 1 )           << endl;
    cout << "8/7 + 6/7 = "      << RI( 8, 7 )       + RI( 6, 7 )        << endl;
    cout << "1/2 + 1/3 = "      << RI( 100, 200 )   + RI( 222, 666 )    << endl;
    cout << "3/11 - 3/10 = "    << RI( 3, 11 )      - RI( 3, 10 )       << endl;
    cout << "3/8 * 4/9 = "      << RI( 3, 8 )       * RI( 4, 9 )        << endl;
    cout << "3/8 / 9/2 = "      << RI( 3, 8 )       / RI( 9, 2 )        << endl;
    cout << "1/0 / 0/1 = "      << RI(1)            / RI()              << endl;
    cout << endl;
    cout << "Comparisons" << endl;
    cout << "5/6 > 9/12 ? "     << ( RI( 5, 6 )     > RI( 9, 12 )     ) << endl;
    cout << "3/2 == 9/6 ? "     << ( RI( 3, 2 )    == RI( 9, 6 )      ) << endl;
    cout << endl;
    return 0;
}
