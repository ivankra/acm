/**
 *   ////////////////////////
 *   // GEOMETRIC ROUTINES //
 *   ////////////////////////
 *
 * CONTENTS:
 *  - struct P (point)
 *  - struct L (canonical line with integer parameters)
 *  - left turn
 *  - point inside triangle
 *  - polar angle
 *  - point inside polygon
 *  - distance from a point to a line
 *  - distance from a point to a line segment
 *  - line intersection
 *  - line segment intersection
 *  - circle through 3 points
 *  - circle of a given radius through 2 points
 *  - cut polygon (cut a convex polygon by a half-plane)
 *  - triangle area from median lengths
 * 
 * LAST MODIFIED:
 *      November 30, 2004
 *
 * This file is part of my library of algorithms found here:
 *      http://www.palmcommander.com:8081/tools/
 * LICENSE:
 *      http://www.palmcommander.com:8081/tools/LICENSE.html
 * Copyright (c) 2004
 * Contact author:
 *      igor at cs.ubc.ca
 **/

/*********
 * Point *
 *********
 * A simple point class used by some of the routines below.
 * Anything else that supports .x and .y will work just as
 * well. There are 2 variants - double and int.
 **/
struct P { double x, y; P() {}; P( double q, double w ) : x( q ), y( w ) {} };
struct P { int x, y; P() {}; P( int q, int w ) : x( q ), y( w ) {} };

/********************************
 * Line with integer parameters *
 ********************************
 * Represents a line through two lattice points as an
 * implicit equation:
 *      ax + by = c
 * Stores a, b and c in lowest terms with a unique
 * representation (positive a; if a is 0, then positive b).
 * Create a line by giving either (a, b, c) or a pair
 * of points, p and q (p == q is ok, but expect a == b == 0).
 * Perfect for testing whether 3 or more points are collinear -
 * simply compute lines through all pairs of points and store
 * them in a set or a map (see UVA184).
 * REQUIRES:
 * struct P
 * from number.cpp: gcd(int, int)
 * FIELD TESTING:
 *      Passed UVA 184
 **/
struct L
{
    int a, b, c;

    void init( int A, int B, int C )
    {
        if( A < 0 || A == 0 && B < 0 ) { A = -A; B = -B; C = -C; }
        int d = A ?
            gcd( gcd( abs( A ), abs( B ) ), C ) :
            ( B || C ? gcd( abs( B ), C ) : 1 );
        a = A / d;
        b = B / d;
        c = C / d;
    }

    // constructors
    L() {}
    L( int A, int B, int C ) { init( A, B, C ); }
    L( P p, P q ) { init( q.y - p.y, p.x - q.x, p.x * q.y - p.y * q.x ); }

    bool operator<( const L &l ) const
    {
        return a < l.a || a == l.a && ( b < l.b || b == l.b && c < l.c );
    }
};

/************
 * Distance *
 ************
 * Computes the distance between two points a and b.
 * #include <math.h>
 **/
double dist( double ax, double ay, double bx, double by )
{
    return sqrt( ( ax - bx ) * ( ax - bx ) + ( ay - by ) * ( ay - by ) );
}

/********************
 * Squared distance *
 ********************
 * ... between two points.
 */
__typeof( P().x ) dist2( P p, P q )
{
    return ( p.x - q.x ) * ( p.x - q.x ) - ( p.y - q.y ) * ( p.y - q.y );
}

/*************
 * Left turn *
 *************
 * Returns true iff the sequence v1->v2->v3 is a left turn in
 * the plane. Straight line is not a left turn (change to ">= -EPS").
 * #define EPS 1e-7
 **/
bool leftTurn( double x1, double y1, double x2, double y2, double x3, double y3 )
{
    return ( x2 - x1 ) * ( y3 - y1 ) - ( y2 - y1 ) * ( x3 - x1 ) > EPS;
}

/*************
 * Left turn * (this one works with integers)
 *************
 * Returns true iff the sequence v1->v2->v3 is a left turn in
 * the plane. Straight line is not a left turn (change to ">= -C( EPS )").
 * #define EPS ... (1e-7 for doubles, 0 for ints)
 **/
template< class C >
bool leftTurn( C x1, C y1, C x2, C y2, C x3, C y3 )
{
    return ( x2 - x1 ) * ( y3 - y1 ) - ( y2 - y1 ) * ( x3 - x1 ) > C( EPS );
}

/*************
 * Left turn * (for either of the two P (point) structs)
 *************
 * Returns true iff the sequence v1->v2->v3 is a left turn in
 * the plane. Straight line is not a left turn (change to ">= -C( EPS )").
 * #define EPS ...
 **/
bool leftTurn( P a, P b, P c )
{
    return ( b.x - a.x ) * ( c.y - b.y ) - ( b.y - a.y ) * ( c.x - b.x ) > EPS;
}

/*************************
 * Point inside triangle *
 *************************
 * Returns true iff point (xx,yy) is inside the counter-clockwise
 * triangle (x[3],y[3])
 * REQUIRES: leftTurn()
 **/
bool pointInsideTriangle( double x[], double y[], double xx, double yy )
{
    return leftTurn( x[0], y[0], x[1], y[1], xx, yy )
        && leftTurn( x[1], y[1], x[2], y[2], xx, yy )
        && leftTurn( x[2], y[2], x[0], y[0], xx, yy );
}

/***************
 * Polar angle *
 ***************
 * Returns an angle in the range [0, 2*Pi) of a given Cartesian point.
 * If the point is (0,0), -1.0 is returned.
 * REQUIRES:
 * #include <math.h>
 * #define EPS 0.000000001 // or your choice
 * P has members x and y.
 **/
double polarAngle( P p )
{
    if( fabs( p.x ) <= EPS && fabs( p.y ) <= EPS ) return -1.0;
    if( fabs( p.x ) <= EPS ) return ( p.y > EPS ? 1.0 : 3.0 ) * acos( 0 );
    double theta = atan( 1.0 * p.y / p.x );
    if( p.x > EPS ) return( p.y >= -EPS ? theta : ( 4 * acos( 0 ) + theta ) );
    return( 2 * acos( 0 ) + theta );
}

/************************
 * Point inside polygon *
 ************************
 * Returns true iff p is inside poly.
 * PRE: The vertices of poly are ordered (either clockwise or
 *      counter-clockwise.
 * POST: Modify code inside to handle the special case of "on an edge".
 * REQUIRES:
 * polarAngle()
 * #include <math.h>
 * #include <vector>
 * #define EPS 0.000000001 // or your choice
 **/
bool pointInPoly( P p, vector< P > &poly )
{
    int n = poly.size();
    double ang = 0.0;
    for( int i = n - 1, j = 0; j < n; i = j++ )
    {
        P v( poly[i].x - p.x, poly[i].y - p.y );
        P w( poly[j].x - p.x, poly[j].y - p.y );
        double va = polarAngle( v );
        double wa = polarAngle( w );
        double xx = wa - va;
        if( va < -0.5 || wa < -0.5 || fabs( fabs( xx ) - 2 * acos( 0 ) ) < EPS )
        {
            // POINT IS ON THE EDGE
            assert( false );
            ang += 2 * acos( 0 );
            continue;
        }
        if( xx < -2 * acos( 0 ) ) ang += xx + 4 * acos( 0 );
        else if( xx > 2 * acos( 0 ) ) ang += xx - 4 * acos( 0 );
        else ang += xx;
    }
    return( ang * ang > 1.0 );
}

/***********************************
 * Distance from a point to a line *
 ***********************************
 * Returns the distance from p to the line defined by {a, b}.
 * The closest point on the line is returned through (cpx, cpy).
 * Does not work for degenerate lines (when answer is undefined).
 * REQUIRES:
 * #include <math.h>
 * #define EPS ...
 * dist()
 **/
double distToLine(
    double ax, double ay,
    double bx, double by,
    double px, double py,
    double *cpx, double *cpy )
{
    //Formula: cp = a + (p-a).(b-a) / |b-a| * (b-a)
    double proj = ( ( px - ax ) * ( bx - ax ) + ( py - ay ) * ( by - ay ) ) /
                  ( ( bx - ax ) * ( bx - ax ) + ( by - ay ) * ( by - ay ) );
    *cpx = ax + proj * ( bx - ax );
    *cpy = ay + proj * ( by - ay );
    return dist( px, py, *cpx, *cpy );
}

/*******************************************
 * Distance from a point to a line segment *
 *******************************************
 * Returns the distance from p to the line segment ab.
 * The closest point on ab is returned through (cpx, cpy).
 * Works correctly for degenerate line segments (a == b).
 * REQUIRES:
 * #include <math.h>
 * #define EPS ...
 * dist()
 * distToLine()
 **/
double distToLineSegment(
    double ax, double ay,
    double bx, double by,
    double px, double py,
    double *cpx, double *cpy )
{
    if( ( bx - ax ) * ( px - ax ) + ( by - ay ) * ( py - ay ) < EPS )
    {
        *cpx = ax;
        *cpy = ay;
        return dist( ax, ay, px, py );
    }

    if( ( ax - bx ) * ( px - bx ) + ( ay - by ) * ( py - by ) < EPS )
    {
        *cpx = bx;
        *cpy = by;
        return dist( bx, by, px, py );
    }

    return distToLine( ax, ay, bx, by, px, py, cpx, cpy );
}

/*********************
 * Line intersection *
 *********************
 * Returns the point of intersection of two lines:
 * (x[0],y[0])-(x[1],y[1]) and (x[2],y[2])-(x[3],y[3]).
 * Puts the result (x, y) into (r[0], r[1]) and returns true.
 * If there is no intersection, return false;
 * USED BY: circle3pts
 * #include <math.h>
 * #define EPS ...
 **/
bool lineIntersect( double x[], double y[], double r[] )
{
    double n[2]; n[0] = y[3] - y[2]; n[1] = x[2] - x[3];
    double denom = n[0] * ( x[1] - x[0] ) + n[1] * ( y[1] - y[0] );
    if( fabs( denom ) < EPS ) return false;
    double num = n[0] * ( x[0] - x[2] ) + n[1] * ( y[0] - y[2] );
    double t = -num / denom;
    r[0] = x[0] + t * ( x[1] - x[0] );
    r[1] = y[0] + t * ( y[1] - y[0] );
    return true;
}

/*********************
 * Line intersection * (P version)
 *********************
 * Returns the point of intersection of two lines:
 * (x[0],y[0])-(x[1],y[1]) and (x[2],y[2])-(x[3],y[3]).
 * Puts the result (x, y) into (r[0], r[1]) and returns true.
 * If there is no intersection, return false;
 * #include <math.h>
 * #define EPS ...
 **/
bool lineIntersect( P a, P b, P c, P d, P &r )
{
    P n; n.x = d.y - c.y; n.y = c.x - d.x;
    double denom = n.x * ( b.x - a.x ) + n.y * ( b.y - a.y );
    if( fabs( denom ) < EPS ) return false;
    double num = n.x * ( a.x - c.x ) + n.y * ( a.y - c.y );
    double t = -num / denom;
    r.x = a.x + t * ( b.x - a.x );
    r.y = a.y + t * ( b.y - a.y );
    return true;
}

/*****************************
 * Line segment intersection *
 *****************************
 * Returns true iff two line segments:
 * (x[0],y[0])-(x[1],y[1]) and (x[2],y[2])-(x[3],y[3])
 * intersect. Call lineIntersect( x, y ) to get the point of intersection.
 * WARNING: Does not work for collinear line segments!
 * #include <vector>
 **/
template< class T >
bool lineSegIntersect( vector< T > &x, vector< T > &y )
{
    double ucrossv1 = ( x[1] - x[0] ) * ( y[2] - y[0] ) - ( y[1] - y[0] ) * ( x[2] - x[0] );
    double ucrossv2 = ( x[1] - x[0] ) * ( y[3] - y[0] ) - ( y[1] - y[0] ) * ( x[3] - x[0] );
    if( ucrossv1 * ucrossv2 > 0 ) return false;
    double vcrossu1 = ( x[3] - x[2] ) * ( y[0] - y[2] ) - ( y[3] - y[2] ) * ( x[0] - x[2] );
    double vcrossu2 = ( x[3] - x[2] ) * ( y[1] - y[2] ) - ( y[3] - y[2] ) * ( x[1] - x[2] );
    return( vcrossu1 * vcrossu2 <= 0 );
}

/***************************
 * Circle through 3 points *
 ***************************
 * Computes the circle containing the 3 given points.
 * The 3 points are
 *      (x[0], y[0]), (x[1], y[1]) and (x[2], y[2]).
 * The centre of the circle is returned as (r[0], r[1]).
 * The radius is returned normally. If the circle is
 * undefined (the points are collinear), -1.0 is returned.
 * #include <math.h>
 * REQUIRES: lineIntersect
 * FIELD TESTING: Passed UVA 190
 **/
double circle3pts( double x[], double y[], double r[] )
{
    double lix[4], liy[4];
    lix[0] = 0.5 * ( x[0] + x[1] ); liy[0] = 0.5 * ( y[0] + y[1] );
    lix[1] = lix[0] + y[1] - y[0];  liy[1] = liy[0] + x[0] - x[1];
    lix[2] = 0.5 * ( x[1] + x[2] ); liy[2] = 0.5 * ( y[1] + y[2] );
    lix[3] = lix[2] + y[2] - y[1];  liy[3] = liy[2] + x[1] - x[2];
    if( !lineIntersect( lix, liy, r ) ) return -1.0;
    return sqrt(
        ( r[0] - x[0] ) * ( r[0] - x[0] ) +
        ( r[1] - y[0] ) * ( r[1] - y[0] ) );
}

/*********************************************
 * Circle of a given radius through 2 points *
 *********************************************
 * Computes the center of a circle containing the 2 given
 * points. The circle has the given radius. The returned
 * center is never to the right of the vector
 * (x1, y1)-->(x2, y2).
 * If this is possible, returns true and passes the center
 * through the ctr array. Otherwise, returns false.
 * #include <math.h>
 * FIELD TESTING:
 *      - Valladolid 10136: Chocolate Chip Cookies
 **/
bool circle2ptsRad( double x1, double y1, double x2, double y2, double r, double ctr[2] )
{
    double d2 = ( x1 - x2 ) * ( x1 - x2 ) + ( y1 - y2 ) * ( y1 - y2 );
    double det = r * r / d2 - 0.25;
    if( det < 0.0 ) return false;
    double h = sqrt( det );
    ctr[0] = ( x1 + x2 ) * 0.5 + ( y1 - y2 ) * h;
    ctr[1] = ( y1 + y2 ) * 0.5 + ( x2 - x1 ) * h;
    return true;
}

/***************
 * Cut Polygon *
 ***************
 * Intersects a given convex polygon with a half-plane. The
 * half-plane is defined as the one on the left side of the
 * directed line a-->b. The polygon 'poly' is modified.
 * The half-plane is considered open, so if only one vertex
 * of the polygon remains after the cut, it is eliminated.
 * REQUIRES:
 *      - Pt must have members x and y.
 *      - lineIntersect( Pt, Pt, Pt, Pt )
 *      - dist2( Pt, Pt )
 * FIELD TESTING:
 *      - Valladolid 137: Polygon
 *      - Valladolid 10117: Nice Milk
 **/
template< class Pt >
void cutPoly( list< Pt > &poly, Pt a, Pt b )
{
    if( !poly.size() ) return;
    
    // see if the last point of the polygon is inside
    bool lastin = leftTurn( a, b, poly.back() );
    
    // find the boundary points
    __typeof( poly.begin() ) fi = poly.end(), la = fi, fip = fi, lan = fi;
    for( __typeof( fi ) i = --poly.end(), j = poly.begin(); 
        j != poly.end(); i = j++ )
    {
        int thisin = leftTurn( a, b, *j );
        
        if( lastin && !thisin ) { la = i; lan = j; }
        if( !lastin && thisin ) { fi = j; fip = i; }
        
        lastin = thisin;
    }

    // see if we have crossed the line at all
    if( fi == poly.end() )
    {
        if( !lastin ) poly.clear();
        return;
    }
    
    // if we cut off a corner, insert a new point
    if( lan == fip )
    {
        poly.insert( lan, *lan );
        --lan;
    }
    
    // compute intersection points
    Pt r;
    lineIntersect( *la, *lan, a, b, r );
    *lan = r;
    lineIntersect( *fip, *fi, a, b, r );
    *fip = r;
    
    // erase the part that disappears
    __typeof( fi ) i = lan; ++i;
    while( i != fip )
    {
        if( i == poly.end() ) { i = poly.begin(); if( i == fip ) break; }
        poly.erase( i++ );
    }
    
    // clean up duplicate points
    if( dist2( *lan, *fip ) < EPS ) poly.erase( fip );
}

/******************************
 * Triangle Area from Medians *
 ******************************
 * Given the lengths of the 3 medians of a triangle,
 * returns the triangle's area, or -1 if it impossible.
 * WARNING: Deal with the case of zero area carefully.
 * #include <math.h>
 * FIELD TESTING:
 *      - Valladolid 10347: Medians
 **/
double triAreaFromMedians( double ma, double mb, double mc )
{
    double x = 0.5 * ( ma + mb + mc );
    double a = x * ( x - ma ) * ( x - mb ) * ( x - mc );
    if( a < 0.0 ) return -1.0;
    else return sqrt( a ) * 4.0 / 3.0;
}

/****************
 * Great Circle *
 ****************
 * Given two pairs of (latitude, longitude), returns the
 * great circle distance between them.
 * FIELD TESTING
 *      - Valladolid 535: Globetrotter
 **/
double greatCircle( double laa, double loa, double lab, double lob )
{
    double PI = acos( -1.0 ), R = 6378.0;
    double u[3] = { cos( laa ) * sin( loa ), cos( laa ) * cos( loa ), sin( laa ) };
    double v[3] = { cos( lab ) * sin( lob ), cos( lab ) * cos( lob ), sin( lab ) };
    double dot = u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
    bool flip = false;
    if( dot < 0.0 )
    {
        flip = true;
        for( int i = 0; i < 3; i++ ) v[i] = -v[i];
    }
    double cr[3] = { u[1]*v[2] - u[2]*v[1], u[2]*v[0] - u[0]*v[2], u[0]*v[1] - u[1]*v[0] };
    double theta = asin( sqrt( cr[0]*cr[0] + cr[1]*cr[1] + cr[2]*cr[2] ) );
    double len = theta * R;
    if( flip ) len = PI * R - len;
    return len;
}
