/**
 * Matrix class
 *      by igor
 *
 * Requires the template parameter to support all of these:
 *  - constructor T( int )
 *  - constructor T( double )
 *  - operator=( T, const T& )
 *  - bool operator<( const T&, const T& )
 *  - T operator-( const T& )
 *  - T operator-=( const T&, const T& )
 *  - T operator*( const T&, const T& )
 *  - T operator/( const T&, const T& )
 *  - operator>>( istream, T )
 *  - operator<<( ostream, const T& )
 *
 * Has
 *  - LU-decomposition: Matrix::lu()
 *  - Determinant:      Matrix::det()
 *
 * This file is part of my library of algorithms found here:
 *      http://www.palmcommander.com:8081/tools/
 * LICENSE:
 *      http://www.palmcommander.com:8081/tools/LICENSE.html
 * Copyright (c) 2003
 * Contact author:
 *      igor at cs.ubc.ca
 **/

#include <iostream>

template< class T >
class Matrix
{
    private:
        int m, n;
        T *data;
        T *LU;
        int *P, Psgn;

        // What is considered a zero
        static const T EPS = T( 0.0000001 );

        inline T &at( T *v, int i, int j ) { return v[i * n + j]; }
        inline T &at( int i, int j ) { return data[i * n + j]; }
        inline T myabs( const T &t ) { return( t < T( 0 ) ? -t : t ); }

    public:
        Matrix( int m, int n );
        Matrix( int m, int n, T deflt );
        Matrix( const Matrix< T > &mtx );
        const Matrix< T > &operator=( const Matrix< T > &mtx );
        ~Matrix();

        T *operator[]( int i );

        /**
         * The PLU-decomposition is stored in two companion arrays
         * P and LU. They are allocated by lu() and become obsolete
         * whenever the original matrix is modified. It is the user's
         * responsibility to call lu() again when that happens. The
         * () operator is used to access the LU matrix, just like []
         * is used for the matrix data. p() accesses the permutation
         * vector P.
         **/
        void lu();
        T &operator()( int i, int j );
        T &p( int i );

    // I/O Friends
    friend istream &operator>><>( istream &in, Matrix< T > &mtx );
    friend ostream &operator<<<>( ostream &out, const Matrix< T > &mtx );

    // Other friends
    friend T det<>( Matrix< T > &mtx );

    // DEBUG
    void printLU()
    {
        for( int i = 0; i < m; i++ )
        {
            for( int j = 0; j < n; j++ )
            {
                if( j ) cout << " ";
                cout << at( LU, i, j );
            }
            cout << endl;
        }
    }
};
template< class T > istream &operator>>( istream &in, Matrix< T > &mtx );
template< class T > ostream &operator<<( ostream &out, const Matrix< T > &mtx );
template< class T > T det( Matrix< T > &mtx );

//------------------ Implementation ---------------------//
template< class T >
Matrix< T >::Matrix( int m, int n )
{
    this->m = m;
    this->n = n;
    data = new T[m * n];
    LU = NULL;
    P = NULL;
}

template< class T >
Matrix< T >::Matrix( int m, int n, T deflt ) : Matrix( m, n )
{
    for( int i = 0; i < m * n; i++ )
        data[i] = deflt;
}

template< class T > Matrix< T >::Matrix( const Matrix< T > &mtx ) : Matrix( mtx.m, mtx.n )
{
    for( int i = 0; i < m * n; i++ )
        data[i] = mtx.data[i];
}

template< class T >
const Matrix< T > &Matrix< T >::operator=( const Matrix< T > &mtx )
{
    if( &mtx != this )
    {
        delete [] data;
        m = mtx.m;
        n = mtx.n;
        data = new T[m * n];
        for( int i = 0; i < m * n; i++ )
            data[i] = mtx.data[i];
    }
    return *this;
}

template< class T >
Matrix< T >::~Matrix()
{
    delete [] data;
}

template< class T >
T *Matrix< T >::operator[]( int i )
{
    return data + i * n;
}

template< class T >
void Matrix< T >::lu()
{
    if( LU ) delete [] LU;
    if( P ) delete [] P;
    LU = new T[m * n];
    P = new int[m];
    memcpy( LU, data, m * n * sizeof( T ) );
    for( int i = 0; i < m; i++ ) P[i] = i;
    Psgn = 1;

    for( int r = 0, c = 0; r < m && c < n; r++, c++ )        // For each row
    {
        // Find largest pivot in this column
        int pr = r;
        for( int i = r + 1; i < m; i++ )
            if( myabs( at( LU, i, c ) ) > myabs( at( LU, pr, c ) ) )
                pr = i;
        if( myabs( at( LU, pr, c ) ) <= EPS )
        {
            // Singular matrix; skip column
            r--;
            continue;
        }

        if( pr != r )
        {
            // Swap rows r and pr
            P[r] ^= P[pr] ^= P[r] ^= P[pr];
            Psgn = -Psgn;
            for( int i = 0; i < n; i++ )
            {
                T tmp = at( LU, r, i );
                at( LU, r, i ) = at( LU, pr, i );
                at( LU, pr, i ) = tmp;
            }
        }

        // Subtract row r from rows below it
        for( int s = r + 1; s < m; s++ )
        {
            at( LU, s, c ) = at( LU, s, c ) / at( LU, r, c );
            for( int d = c + 1; d < n; d++ )
                at( LU, s, d ) -= at( LU, s, c ) * at( LU, r, d );
        }
    }
}

template< class T >
T &Matrix< T >::operator()( int i, int j )
{
    return LU[i * n + j];
}

template< class T >
T &Matrix< T >::p( int i )
{
    return P[i];
}

template< class T >
istream &operator>>( istream &in, Matrix< T > &mtx )
{
    for( int i = 0; i < mtx.m * mtx.n; i++ )
        in >> mtx.data[i];
    return in;
}

template< class T >
ostream &operator<<( ostream &out, const Matrix< T > &mtx )
{
    for( int i = 0; i < mtx.m; i++ )
    {
        for( int j = 0; j < mtx.n; j++ )
        {
            if( j ) out << " ";
            out << mtx.at( i, j );
        }
        out << endl;
    }
    return out;
}

template< class T >
T det( Matrix< T > &mtx )
{
    if( mtx.m != mtx.n ) throw "Not a square matrix";
    mtx.lu();
    T ans = 1;
    for( int i = 0; i < mtx.n; i++ )
        ans *= mtx.at( mtx.LU, i, i );
    return( mtx.Psgn > 0 ? ans : -ans );
}

//------------------- DEBUG and Testing ------------------//
int main()
{
    int x, y;
    cin >> x >> y;
    Matrix< double > m( x, y );
    cin >> m;
    cout << "det(M) = " << det( m ) << endl;
    return 0;
}

