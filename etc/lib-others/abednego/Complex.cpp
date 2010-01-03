/**
 * Complex number class template by igor
 * Stores and manipulates complex numbers represented by a pair
 * of numbers of any type.
 *
 * REQUIREMENTS on type T:
 *  - -1, 0 and 1 must be valid parameters to T's constructor
 *  - all basic arithmetic operators must be defined for T
 *
 * INVARIANTS:
 *      - capacity is never smaller than 16
 *      - capacity is not the smallest it can be because every
 *         modifying member function first grows digits as much as
 *         it needs and then does its job.
 *
 * This file is part of my library of algorithms found here:
 *      http://www.palmcommander.com:8081/tools/
 * LICENSE:
 *      http://www.palmcommander.com:8081/tools/LICENSE.html
 * Copyright (c) 2004
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
class Complex
{
    public:
        /** Real and Imaginary parts. **/
        T re, im;

        /** Creates a new Complex number with value zero. **/
        Complex();

        /** Creates a new Complex number "re + i*0". **/
        Complex( T re );

        /** Creates a new Complex number "re + i*im". **/
        Complex( T re, T im );

        /** Arithmetic **/
        Complex< T > &operator++();
        Complex< T > &operator++( int );
        Complex< T > &operator--();
        Complex< T > &operator--( int );
        Complex< T >  operator- ();
        Complex< T >  operator+ ( const T &n    ) const;
        Complex< T >  operator+ ( const Complex< T > &n ) const;
        Complex< T > &operator+=( const T &n    );
        Complex< T > &operator+=( const Complex< T > &n );
        Complex< T >  operator- ( const T &n    ) const;
        Complex< T >  operator- ( const Complex< T > &n ) const;
        Complex< T > &operator-=( const T &n    );
        Complex< T > &operator-=( const Complex< T > &n );
        Complex< T >  operator* ( const T &n    ) const;
        Complex< T >  operator* ( const Complex< T > &n ) const;
        Complex< T > &operator*=( const T &n    );
        Complex< T > &operator*=( const Complex< T > &n );
        Complex< T >  operator/ ( const T &n    ) const;
        Complex< T >  operator/ ( const Complex< T > &n ) const;
        Complex< T > &operator/=( const T &n    );
        Complex< T > &operator/=( const Complex< T > &n );

        /** Casting and type conversion **/
        bool operator!() const;
        //operator bool();
        //operator T();
        operator string() const;
        string toString() const;

        /** Outputs decimal value to stdout **/
        void print() const;

        /** I/O Friends **/
        friend istream &operator>><>( istream &in, const Complex< T > &n );
        friend ostream &operator<<<>( ostream &out, const Complex< T > &n );

        /** Math **/
        friend T abs2<>( const Complex< T > &n );
        friend T abs<>( const Complex< T > &n );

        /*
        friend long double log2( Complex x, long double epsilon = 0.000000000000001 );
        inline friend long double log( Complex x, long double epsilon = 0.000000000000001 );
        inline friend long double log10( Complex x, long double epsilon = 0.000000000000001 );
        inline friend long double lg( Complex x, long double epsilon = 0.000000000000001 );
        inline friend long double ln( Complex x, long double epsilon = 0.000000000000001 );
        */
};
template< class T > istream &operator>>( istream &in, const Complex< T > &n );
template< class T > ostream &operator<<( ostream &out, const Complex< T > &n );
template< class T > T abs2( const Complex< T > &n );
template< class T > T abs( const Complex< T > &n );

template< class T >
Complex< T >::Complex()
{
    re = im = T( 0 );
}

template< class T >
Complex< T >::Complex( T re )
{
    this->re = re;
    this->im = T( 0 );
}

template< class T >
Complex< T >::Complex( T re, T im )
{
    this->re = re;
    this->im = im;
}

template< class T >
Complex< T > &Complex< T >::operator++()
{
    Complex old = *this;
    this->re += T( 1 );
    return old;
}

template< class T >
Complex< T > &Complex< T >::operator++( int )
{
    this->re += T( 1 );
    return *this;
}

template< class T >
Complex< T > &Complex< T >::operator--()
{
    Complex old = *this;
    this->re -= T( 1 );
    return old;
}

template< class T >
Complex< T > &Complex< T >::operator--( int )
{
    this->re -= T( 1 );
    return *this;
}

template< class T >
Complex< T > Complex< T >::operator-()
{
    return Complex< T >( -re, -im );
}

template< class T >
Complex< T > Complex< T >::operator+( const T &n ) const
{
    return Complex< T >( re + n, im );
}

template< class T >
Complex< T > Complex< T >::operator+( const Complex< T > &n ) const
{
    return Complex< T >( re + n.re, im + n.im );
}

template< class T >
Complex< T > &Complex< T >::operator+=( const T &n )
{
    re += n;
    return *this;
}

template< class T >
Complex< T > &Complex< T >::operator+=( const Complex< T > &n )
{
    re += n.re;
    im += n.im;
    return *this;
}

template< class T >
Complex< T > Complex< T >::operator-( const T &n ) const
{
    return Complex< T >( re - n, im );
}

template< class T >
Complex< T > Complex< T >::operator-( const Complex< T > &n ) const
{
    return Complex< T >( re - n.re, im - n.im );
}

template< class T >
Complex< T > &Complex< T >::operator-=( const T &n )
{
    re -= n;
    return *this;
}

template< class T >
Complex< T > &Complex< T >::operator-=( const Complex< T > &n )
{
    re -= n.re;
    im -= n.im;
    return *this;
}

template< class T >
Complex< T > Complex< T >::operator*( const T &n ) const
{
    return Complex< T >( re * n, im * n );
}

template< class T >
Complex< T > Complex< T >::operator*( const Complex< T > &n ) const
{
    return Complex< T >( re * n.re - im * n.im, re * n.im + im * n.re );
}

template< class T >
Complex< T > &Complex< T >::operator*=( const T &n )
{
    re *= n;
    im *= n;
    return *this;
}

template< class T >
Complex< T > &Complex< T >::operator*=( const Complex< T > &n )
{
    return *this = operator*( n );
}

template< class T >
Complex< T > Complex< T >::operator/( const T &n ) const
{
    return Complex< T >( re / n, im / n );
}

template< class T >
Complex< T > Complex< T >::operator/( const Complex< T > &n ) const
{
    T f = T( 1 ) / abs2( n );
    return Complex< T >( f * ( re * n.re + im * n.im ), f * ( im * n.re - re * n.im ) );
}

template< class T >
Complex< T > &Complex< T >::operator/=( const T &n )
{
    re /= n;
    im /= n;
    return *this;
}

template< class T >
Complex< T > &Complex< T >::operator/=( const Complex< T > &n )
{
    return *this = operator/( n );
}

/** Casting **/
template< class T >
bool Complex< T >::operator!() const
{
    return !abs2< T >( *this );
}

/** Overloaded casting operators and templates don't mix!
template< class T >
Complex< T >::operator bool()
{
    return abs2< T >( *this );
}
**/

/** Returns the real part only!
template< class T >
Complex< T >::operator T()
{
    return re;
}
**/

template< class T >
Complex< T >::operator string() const
{
    return toString();
}

template< class T >
string Complex< T >::toString() const
{
    ostringstream out;
    out << re << ( im < T( 0 ) ? " - I*" : " + I*" ) << im * ( im < T( 0 ) ? T( -1 ) : T( 1 ) );
    return out.str();
}

/** Outputs decimal value to stdout **/
template< class T >
void Complex< T >::print() const
{
    cout << *this;
}

/** I/O Friends **/
template< class T >
istream &operator>>( istream &in, const Complex< T > &n )
{
    in >> n.re;
    char sig; in >> sig;
    if( sig != '+' & sig != '-' )
    {
        in.clear( ios::failbit );
        return;
    }
    char i; in >> i;
    if( i != 'I' && i != 'i' )
    {
        in.clear( ios::failbit );
        return;
    }
    in >> n.im;
    if( sig == '-' ) n.im *= T( -1 );
    return in;
}

template< class T >
ostream &operator<<( ostream &out, const Complex< T > &n )
{
    return( out << ( string )n );
}

/** Math **/
template< class T >
T abs2( const Complex< T > &x )
{
    return x.re * x.re + x.im * x.im;
}

template< class T >
T abs( const Complex< T > &x )
{
    return sqrt( abs2( x ) );
}

/** TESTING and DEBUGGING **/
typedef Complex< double > CD;
int main()
{
    cout << "Constructors and printing" << endl;
    cout << "0 = " << CD().toString() << endl;
    cout << "1 = " << CD( 1. ).toString() << endl;
    cout << "i = " << ( string )CD( 0., 1. ) << endl;
    cout << "1.5 + I*(-3.4) = " << ( string )CD( 1.5, -3.4 ) << endl;
    cout << endl;
    cout << "Algebra" << endl;
    cout << "0 + i = " << ( CD() + CD( 0., 1. ) ).toString() << endl;
    cout << "(1 + i) + (2 - i) = " << ( string )( CD( CD(1., 1.) + CD(2., -1.) )) << endl;
    cout << "(5 + i) - (5 - i) = " << ( string )( CD(5., 1.) - CD(5., -1.) ) << endl;
    cout << "(2 + 3i)*(3 - 3i) = " << ( string )( CD(2., 3.) * CD(3., -3.) ) << endl;
    cout << "(-1 + 5i)/(2 + 3i) = " << ( string )( CD(-1., 5.) / CD(2., 3.) ) << endl;
    cout << "(0 + 0i)/(0 + 0i) = " << (CD() / CD()) << endl;
    cout << endl;
    return 0;
}
