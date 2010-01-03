/**
 *  ///////////////////////////////
 *  // LINE SEGMENT INTERSECTION //
 *  ///////////////////////////////
 *
 * MAIN FUNCTION: lineSegIntersect( E, E, E* )
 *      Takes two line segments in the plane and returns either
 *      true or false, depending on whether they intersect or not. If
 *      they do, also returns the line segment that is the intersection
 *      of the two given line segments.
 * TYPES:
 *      - P: point in 2D
 *      - E: edge (line segment)
 * WARNING:
 *      This code is too long, too slow and too ugly, but it seems
 *      to work. Use at your own risk.
 * FIELD TESTING:
 *      - UVa 10709: Intersection is not that Easy
 *
 * LAST MODIFIED:
 *      October 24, 2005
 *
 * This file is part of my library of algorithms found here:
 *      http://shygypsy.com/tools/
 * LICENSE:
 *      http://shygypsy.com/tools/LICENSE.html
 * Copyright (c) 2005
 **/
#include <math.h>

struct P { double x, y; };
struct E
{
    P a, b;
    E(){}
    E( P x, P y ) { a = x; b = y; }
};

#define EPS 1e-7

inline double dist2( P p, P q )
{
    return ( p.x - q.x ) * ( p.x - q.x ) + ( p.y - q.y ) * ( p.y - q.y );
}

inline double dist( P p, P q )
{
    return sqrt( dist2( p, q ) );
}

inline bool lineIntersect( P a, P b, P c, P d, P &r )
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

inline bool lineIntersect( E e, E f, P *r = NULL )
{
    return lineIntersect( e.a, e.b, f.a, f.b, *r );
}

inline double cross( P a, P b, P c )
{
    return ( b.x - a.x ) * ( c.y - b.y ) - ( b.y - a.y ) * ( c.x - b.x );
}

bool lineSegIntersect( E e, E f, E *r = NULL )
{
    E blah; if( !r ) r = &blah;

    double c1 = cross( e.a, e.b, f.a );
    double c2 = cross( e.b, e.a, f.b );
    double c3 = cross( f.a, f.b, e.a );
    double c4 = cross( f.b, f.a, e.b );
    if( c1 * c2 < -EPS || c3 * c4 < -EPS ) return false;
    if( fabs( c1 ) > EPS || fabs( c2 ) > EPS || fabs( c3 ) > EPS || fabs( c4 ) > EPS )
    {
        lineIntersect( e, f, &r->a );
        r->b = r->a;
        return dist( e.a, r->b ) + dist( r->b, e.b ) - dist( e.a, e.b ) <= EPS
            && dist( f.a, r->b ) + dist( r->b, f.b ) - dist( f.a, f.b ) <= EPS;
    }
    else
    {
        // degenerate line segments?
        if( dist2( e.a, e.b ) <= EPS && dist2( f.a, f.b ) <= EPS && dist2( f.a, e.a ) > EPS )
            return false;

        // Collinear case
        bool fa = dist( e.a, e.b ) >= dist( e.a, f.a ) + dist( e.b, f.a ) - EPS;
        bool fb = dist( e.a, e.b ) >= dist( e.a, f.b ) + dist( e.b, f.b ) - EPS;
        switch( ( fa ? 10 : 0 ) + ( fb ? 1 : 0 ) )
        {
            case 11:        // f is inside e
                r->a = f.a;
                r->b = f.b;
                return true;

            case 10:        // only f.a is inside e
                r->a = ( dist2( e.a, f.b ) <= dist2( e.b, f.b ) ? e.a : e.b );
                r->b = f.a;
                return true;

            case 1:         // only f.b is inside e
                r->a = ( dist2( e.a, f.a ) <= dist2( e.b, f.a ) ? e.a : e.b );
                r->b = f.b;
                return true;

            case 0:         // both outside of e
                if( dist( f.a, e.a ) + dist( e.a, f.b ) <= dist( f.a, f.b ) + EPS &&
                    dist( f.a, e.b ) + dist( e.b, f.b ) <= dist( f.a, f.b ) + EPS )
                {
                    // e is inside f
                    r->a = e.a;
                    r->b = e.b;
                    return true;
                }
                return false;
        }
    }
    return false;       // Will never get here
}
