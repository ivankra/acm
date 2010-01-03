// WARNING: Mostly untested code. If you can help me test it,
//      I will be very grateful.

/**
 * Balanced binary search tree, implemented using an AVL tree.
 * The template takes two parameters:
 *      - T: the type of value to be stored at each node. T must
 *          have operator<().
 *      - MAXN: the maximum number of nodes. MAXN is ignored if
 *          BST_DYNAMIC2 is set.
 *     The huge array of MAXN nodes can be either allocated dynamically
 * or statically. By default, allocation is static, and you should
 * make your BST static or global to avoid stack overflow. If you
 * want dynamic allocation, uncomment the line defining the
 * BST_DYNAMIC constant. The third option is to dynamically allocate
 * each node. This is enabled with the BST_DYNAMIC2 constant.
 *     The interface basically emulates that of an STL set, with
 * a couple of useful additions. The most notable ones are the
 * count(a, b) method and the iterator +=/-= operators. Both work
 * in O(log n). count(a, b) returns the number of elements in the
 * range [a, b). Combined with erase(), these are useful for doing
 * Josephus in O(n log n) time, as well as lucky numbers and other
 * weird sieves and scanline algorithms.
 *
 * BUGS:
 *      If you find some, please tell me.
 *
 * FIELD TESTING:
 *      10148 - Advertisement
 *
 * COMPATIBILITY:
 *      This class was written for the g++ compiler and uses some
 *      of the g++ extensions (like the ">?=" operator). If you
 *      want to compile this under Micro$oft's "compiler", I don't
 *      want to talk to you.
 *
 * UPDATE LOG:
 *      September 27, 2005: Added iterator ++ and --.
 *      October 6, 2005:    Added erase() and iterator += and -=.
 *      October 10, 2005:   Bug fixes in erase().
 **/

// Uncomment this line to use a dynamic array instead of a static one
//#define BST_DYNAMIC

// Uncomment this instead to use dynamic allocation for each node
#define BST_DYNAMIC2

#ifndef NULL
#define NULL 0
#endif

template< class T, int MAXN = -1 >
class BST
{
  private:

    friend struct Node
    {
        T val;
        int cnt;        // number of elements in this subtree
        char depth;     // measured in nodes
        Node *l, *r, *p;
    };

    // the tree
    Node *root;

  public:

    BST();
    ~BST();

    // iterator
    friend struct iterator
    {
        Node *p;
        const BST< T, MAXN > *bst;
        inline iterator( Node *z, const BST< T, MAXN > &t ) : p( z ), bst( &t ) {}
        inline const T &operator*() const { return p->val; }
        inline const T &operator->() const { return p->val; }
        iterator &operator++();
        iterator &operator--();
        iterator operator++( int );
        iterator operator--( int );
        iterator &operator+=( int i );
        iterator &operator-=( int i );
        inline iterator up() { p = p->p; return *this; }
        inline iterator left() { p = p->l; return *this; }
        inline iterator right() { p = p->r; return *this; }
        inline int count() const { return p->cnt; }
        inline int depth() const { return p->depth; }
        inline operator bool() { return p != NULL; }
        inline bool operator==( const iterator &i ) { return p == i.p && bst == i.bst; }
        inline bool operator!=( const iterator &i ) { return p != i.p || bst != i.bst; }
    };

    iterator insert( const T &x );
    void erase( const T &x );
    void erase( iterator it );
    int count( const T &x ) const;
    int count( const T &a, const T &b ) const;  // count the number of elements in range [a, b)
    iterator find( const T &x ) const;
    inline int size() const { return root ? root->cnt : 0; }
    void clear();

    iterator begin() const;
    inline iterator end() const { return iterator( NULL, *this ); }

    //DEBUG
    void print( int tabs, Node *t = ( Node* )-1 ) const;

  private:

    // huge array of nodes
    #ifdef BST_DYNAMIC
    Node *v;
    #elif defined( BST_DYNAMIC2 )
    // do nothing
    #else
    Node v[MAXN];
    #endif

    // free list
    #ifndef BST_DYNAMIC2
    Node *flist;
    #endif

    Node *allocNode();
    void deallocNode( Node **n );
    #ifdef BST_DYNAMIC2
    void deleteTree( Node *t );
    #endif

    void balance( Node *p );
    void rotateL( Node *p );
    void rotateR( Node *p );
};

template< class T, int MAXN >
BST< T, MAXN >::BST()
{
    root = NULL;

    #ifdef BST_DYNAMIC
    v = new Node[MAXN];
    #endif
    #ifndef BST_DYNAMIC2
    v[MAXN - 1].l = NULL;
    for( int i = MAXN - 1; i > 0; i-- ) v[i - 1].l = v + i;
    flist = v;
    #endif
}

template< class T, int MAXN >
BST< T, MAXN >::~BST()
{
    #ifdef BST_DYNAMIC
    delete [] v;
    #elif defined( BST_DYNAMIC2 )
    clear();
    #endif
}

template< class T, int MAXN >
typename BST< T, MAXN >::Node *BST< T, MAXN >::allocNode()
{
    Node *n;
    #ifdef BST_DYNAMIC2
    n = new Node();
    #else
    n = flist;
    flist = flist->l;
    #endif
    n->l = n->r = n->p = NULL;
    n->cnt = n->depth = 1;
    return n;
}

template< class T, int MAXN >
void BST< T, MAXN >::deallocNode( BST< T, MAXN >::Node **n )
{
    #ifdef BST_DYNAMIC2
    delete *n;
    *n = NULL;
    #else
    (*n)->l = flist;
    flist = *n;
    #endif
}

#ifdef BST_DYNAMIC2
template< class T, int MAXN >
void BST< T, MAXN >::deleteTree( BST< T, MAXN >::Node *t )
{
    if( t->l ) deleteTree( t->l );
    if( t->r ) deleteTree( t->r );
    delete t;
}
#endif

template< class T, int MAXN >
typename BST< T, MAXN >::iterator BST< T, MAXN >::insert( const T &x )
{
    // find the place to add the node and create it
    Node **p = &root, *par = NULL;
    while( *p )
    {
        par = *p;
        if( x < par->val ) p = &par->l;
        else if( par->val < x ) p = &par->r;
        else return iterator( par, *this );
    }
    *p = allocNode();
    (*p)->val = x;
    (*p)->p = par;

    // update depth and balance the tree
    if( par ) balance( par );

    return iterator( *p, *this );
}

template< class T, int MAXN >
void BST< T, MAXN >::erase( const T &x )
{
    iterator it = find( x );
    if( it ) erase( it );
}

template< class T, int MAXN >
void BST< T, MAXN >::erase( BST< T, MAXN >::iterator it )
{
    Node *x = it.p;
    if( !x ) throw;

    // Get a double pointer to x
    Node **px = ( x == root ? &root : ( x->p->r == x ? &x->p->r : &x->p->l ) );
    Node *bal = x;

    // Have fewer that 2 children?
    if( !x->l ) { *px = x->r; if( x->r ) x->r->p = x->p; }
    else
    if( !x->r ) { *px = x->l; if( x->l ) x->l->p = x->p; }
    else
    {
        // have both children - get the smallest one in the right subtree
        Node *so = x->r;
        while( so->l ) so = so->l;

        // is it x's right child?
        if( x->r == so )
        {
            *px = so;
            bal = so;
            so->p = x->p;
            so->l = x->l; so->l->p = so;
            bal = so;
        }
        else
        {
            // does it have a right subtree?
            if( so->r ) so->r->p = so->p;

            // remove the node
            so->p->l = so->r;

            // add it in place of x
            *px = so;
            bal = so->p;
            so->p = x->p;
            so->l = x->l; so->l->p = so;
            so->r = x->r; so->r->p = so;
        }
    }

    // update counts and depths
    balance( bal );

    // erase the node
    deallocNode( &x );
}

template< class T, int MAXN >
int BST< T, MAXN >::count( const T &x ) const
{
    return find( x ) ? 1 : 0;
}

template< class T, int MAXN >
int BST< T, MAXN >::count( const T &a, const T &b ) const
{
    int ans = 0;
    if( !( a < b ) ) return ans;

    // find the fork
    Node *f = root;
    while( f )
    {
        char sa = 'F', sb = 'F';
        if( a < f->val ) sa = 'L';
        else if( f->val < a ) sa = 'R';
        if( b < f->val ) sb = 'L';
        else if( f->val < b ) sb = 'R';
        if( sa != sb || sa == 'F' ) break;
        f = ( sa == 'L' ? f->l : f->r );
    }
    if( !f ) return ans;

    // count nodes on the left
    Node *x = NULL;
    if( a < f->val ) x = f->l;
    while( x )
    {
        if( x->val < a ) x = x->r;
        else
        {
            ans++;
            if( x->r ) ans += x->r->cnt;
            if( a < x->val ) x = x->l;
            else break;
        }
    }

    // count nodes on the right
    x = f;
    while( x )
    {
        if( b < x->val ) x = x->l;
        else
        {
            if( x->l && x != f ) ans += x->l->cnt;
            if( x->val < b )
            {
                ans++;
                x = x->r;
            }
            else break;
        }
    }

    return ans;
}

template< class T, int MAXN >
typename BST< T, MAXN >::iterator BST< T, MAXN >::find( const T &x ) const
{
    Node *p = root;
    while( p )
    {
        if( x < p->val ) p = p->l;
        else if( p->val < x ) p = p->r;
        else break;
    }
    return iterator( p, *this );
}

template< class T, int MAXN >
void BST< T, MAXN >::clear()
{
    #ifdef BST_DYNAMIC2
    if( root ) deleteTree( root );
    #else
    Node *x = root;
    while( x )
    {
        if( x->l ) x = x->l;
        else if( x->r ) x = x->r;
        else
        {
            Node *next = x->p;
            if( next ) ( next->l == x ? next->l : next->r ) = NULL;
            deallocNode( x );
            x = next;
        }
    }
    #endif

    root = NULL;
}

template< class T, int MAXN >
typename BST< T, MAXN >::iterator BST< T, MAXN >::begin() const
{
    Node *p = root;
    while( p && p->l ) p = p->l;
    return iterator( p, *this );
}

template< class T, int MAXN >
typename BST< T, MAXN >::iterator &BST< T, MAXN >::iterator::operator++()
{
    if( !p ) throw;

    // have a right child?
    if( p->r )
    {
        p = p->r;
        while( p->l ) p = p->l;
        return *this;
    }

    // no - have to go up until we come from the left
    Node *x = p;
    p = p->p;
    while( p && p->r == x )
    {
        x = p;
        p = p->p;
    }
    return *this;
}

template< class T, int MAXN >
typename BST< T, MAXN >::iterator &BST< T, MAXN >::iterator::operator--()
{
    if( !p )
    {
        // find the max element
        p = bst->root;
        while( p && p->r ) p = p->r;
        return *this;
    }
    
    // have a left child?
    if( p->l )
    {
        p = p->l;
        while( p->r ) p = p->r;
        return *this;
    }

    // no - have to go up until we come from the right
    Node *x = p;
    p = p->p;
    while( p && p->l == x )
    {
        x = p;
        p = p->p;
    }
    return *this;
}

template< class T, int MAXN >
typename BST< T, MAXN >::iterator BST< T, MAXN >::iterator::operator++( int )
{
    typename BST< T, MAXN >::iterator x = *this;
    operator++();
    return x;
}

template< class T, int MAXN >
typename BST< T, MAXN >::iterator BST< T, MAXN >::iterator::operator--( int )
{
    typename BST< T, MAXN >::iterator x = *this;
    operator--();
    return x;
}

template< class T, int MAXN >
typename BST< T, MAXN >::iterator &BST< T, MAXN >::iterator::operator+=( int n )
{
    if( !p && n < 0 ) { n++; operator--(); }

    while( n && p )
    {
        // should we go into the left subtree?
        if( n < 0 && p->l && p->l->cnt >= -n )
        {
            p = p->l;
            n++;
            if( p->r ) n += p->r->cnt;
        }

        // should we go into the right subtree?
        else if( n > 0 && p->r && p->r->cnt >= n )
        {
            p = p->r;
            n--;
            if( p->l ) n -= p->l->cnt;
        }

        // no? we must go up
        else
        {
            // coming from the left?
            if( p->p && p->p->l == p )
            {
                n--;
                if( p->r ) n -= p->r->cnt;
            }

            // coming from the right?
            else if( p->p )
            {
                n++;
                if( p->l ) n += p->l->cnt;
            }

            p = p->p;
        }
    }

    return *this;
}

template< class T, int MAXN >
typename BST< T, MAXN >::iterator &BST< T, MAXN >::iterator::operator-=( int n )
{
    return operator+=( -n );
}

template< class T, int MAXN >
void BST< T, MAXN >::balance( Node *p )
{
    while( p )
    {
        p->cnt = ( p->l ? p->l->cnt : 0 ) + ( p->r ? p->r->cnt : 0 ) + 1;

        int ldepth = p->l ? p->l->depth : 0;
        int rdepth = p->r ? p->r->depth : 0;
        p->depth = 1 + ( ldepth >? rdepth );

        if( ldepth - rdepth > 1 )
        {
            int lldepth = p->l->l ? p->l->l->depth : 0;
            int lrdepth = p->l->r ? p->l->r->depth : 0;
            if( lrdepth > lldepth ) rotateL( p->l );
            rotateR( p );
        }

        if( rdepth - ldepth > 1 )
        {
            int rldepth = p->r->l ? p->r->l->depth : 0;
            int rrdepth = p->r->r ? p->r->r->depth : 0;
            if( rldepth > rrdepth ) rotateR( p->r );
            rotateL( p );
        }

        // go up
        p = p->p;
    }
}

template< class T, int MAXN >
void BST< T, MAXN >::rotateL( Node *p )
{
    Node *q = p->r;
    p->r = q->l;
    if( q->l ) q->l->p = p;
    q->p = p->p;
    p->p = q;
    q->l = p;
    p->cnt = 1 + ( p->l ? p->l->cnt : 0 ) + ( p->r ? p->r->cnt : 0 );
    p->depth = 1 + ( ( p->l ? p->l->depth : 0 ) >? ( p->r ? p->r->depth : 0 ) );
    q->cnt = 1 + ( q->l ? q->l->cnt : 0 ) + ( q->r ? q->r->cnt : 0 );
    q->depth = 1 + ( ( q->l ? q->l->depth : 0 ) >? ( q->r ? q->r->depth : 0 ) );
    if( q->p ) { if( q->p->l == p ) q->p->l = q; else q->p->r = q; }
    if( p == root ) root = q;
}

template< class T, int MAXN >
void BST< T, MAXN >::rotateR( Node *p )
{
    Node *q = p->l;
    p->l = q->r;
    if( q->r ) q->r->p = p;
    q->p = p->p;
    p->p = q;
    q->r = p;
    p->cnt = 1 + ( p->l ? p->l->cnt : 0 ) + ( p->r ? p->r->cnt : 0 );
    p->depth = 1 + ( ( p->l ? p->l->depth : 0 ) >? ( p->r ? p->r->depth : 0 ) );
    q->cnt = 1 + ( q->l ? q->l->cnt : 0 ) + ( q->r ? q->r->cnt : 0 );
    q->depth = 1 + ( ( q->l ? q->l->depth : 0 ) >? ( q->r ? q->r->depth : 0 ) );
    if( q->p ) { if( q->p->l == p ) q->p->l = q; else q->p->r = q; }
    if( p == root ) root = q;
}

// DEBUG
#include <stdio.h>
#include <iostream>
using namespace std;
template< class T, int MAXN >
void BST< T, MAXN >::print( int tabs, Node *t ) const
{
    if( t == ( Node* )-1 ) t = root;
    for( int i = 0; i < tabs; i++ ) printf( "  " );
    if( !t ) printf( "null\n" );
    else
    {
        cout << t->val;
        printf( " [size %d depth %d] at %X [parent at %X]\n",
            t->cnt, t->depth, ( int )t, ( int )t->p );
        if( t->l || t->r )
        {
            print( tabs + 1, t->l );
            print( tabs + 1, t->r );
        }

        if( t->l && t->l->p != t ) printf( "--- Left child fuck-up at %d\n", t->val );
        if( t->r && t->r->p != t ) printf( "--- Right child fuck-up at %d\n", t->val );
    }
}

// TESTING and DEBUGGING
#include <stdio.h>
#include <stdlib.h>
int main()
{
    /*
    // insert 11 integers into the set
    #define N 11
    BST< int, N > t;
    for( int i = 0; i < N; i++ ) t.insert( i * 3 % N );
    //t.print( 0 );

    // test the count( a, b ) method
    for( int i = -1; i < 12; i++ )
    for( int j = i; j <= 13; j++ )
        if( t.count( i, j ) != 0>?((j<?11) - (0>?i))<?11 )
            printf( "ERROR: count( [%d, %d) ) returned %d\n", i, j, t.count( i, j ) );
    */

    BST< int > t;

    printf( "--- inserting -1, -2, -3, -4, -5\n" );
    t.insert( -1 );
    t.insert( -2 );
    t.insert( -3 );
    t.insert( -4 );
    t.insert( -5 );
    t.print( 0 );

    printf( "--- [-3, 0] has %d\n", t.count( -3, 1 ) );
    printf( "--- inserting 0\n" );
    t.insert( 0 );
    t.print( 0 );

    printf( "--- [2, 8] has %d\n", t.count( 2, 9 ) );
    printf( "--- inserting 8, 7, 6, 5, 4\n" );
    t.insert( 8 );
    t.print( 4 );
    t.insert( 7 );
    t.print( 4 );
    t.insert( 6 );
    t.print( 4 );
    t.insert( 5 );
    t.print( 4 );
    t.insert( 4 );
    t.print( 0 );

    printf( "--- [2, 9] has %d\n", t.count( 2, 10 ) );
    printf( "--- [1, 10] has %d\n", t.count( 1, 11 ) );
    printf( "--- [15, 15] has %d\n", t.count( 15, 16 ) );
    printf( "--- inserting 15\n" );
    t.insert( 15 );
    t.print( 0 );

    printf( "--- [14, 21] has %d\n", t.count( 14, 22 ) );
    printf( "--- inserting 21, 20, 19, 18, 17\n" );
    t.insert( 21 );
    t.insert( 20 );
    t.print( 7 );
    t.insert( 19 );
    t.insert( 18 );
    t.insert( 17 );
    t.print( 0 );

    printf( "--- [20, 27] has %d\n", t.count( 20, 28 ) );
    printf( "--- inserting 27, 26, 25\n" );
    t.insert( 27 );
    t.insert( 26 );
    t.insert( 25 );
    t.print( 0 );

    printf( "--- [20, 27] has %d\n", t.count( 20, 28 ) );
    printf( "--- [7, 30] has %d\n", t.count( 7, 30 ) );
    
    printf( "------------- Testing ++ -------------\n" );
    #define foreach(it,x)for(__typeof(x.end())it=x.begin();it!=x.end();++it)
    t.print( 0 );
    printf( "Traversal:" ); foreach( it, t ) printf( " %d", *it ); printf( "\n" );

    printf( "------------- Testing erase() -------------\n" );
    printf( "Erasing 25\n" );
    t.erase( 25 );
    printf( "Traversal:" ); foreach( it, t ) printf( " %d", *it ); printf( "\n" );
    printf( "Erasing 5\n" );
    t.erase( 5 );
    printf( "Traversal:" ); foreach( it, t ) printf( " %d", *it ); printf( "\n" );
    printf( "Erasing 20\n" );
    t.erase( 20 );
    printf( "Traversal:" ); foreach( it, t ) printf( " %d", *it ); printf( "\n" );
    printf( "Erasing 15\n" );
    t.erase( 15 );
    printf( "Traversal:" ); foreach( it, t ) printf( " %d", *it ); printf( "\n" );
    printf( "Jumpersal:" );
    for( int i = 0; i < t.size(); i++ )
    {
        __typeof( t.end() ) it = t.begin();
        it += i;
        printf( " %d", *it );
    }
    printf( "\n" );
    t.print( 0 );
    while( t.size() )
    {
        __typeof( t.begin() ) it = t.begin();
        int i = rand() % t.size();
        printf( "%dth element: ", i );
        it += i % t.size();
        printf( "Erasing %d:", *it ); foreach( it, t ) printf( " %d", *it ); printf( "\n" );
        t.erase( it );
        t.print( 0 );
    }

    printf( "------------- Testing += and -= -------------\n" );
    t.clear();
    for( int i = 0; i < 128; i++ ) t.insert( i );
    printf( "Even traversal:" );
    for( __typeof( t.end() ) it = t.begin(); it != t.end(); it += 2 )
        printf( " %d", *it );
    printf( "\n" );
    printf( "Odd traversal:" );
    for( __typeof( t.end() ) it = ++t.begin(); it != t.end(); it += 2 )
        printf( " %d", *it );
    printf( "\n" );
    printf( "Triangular traversal:" );
    int di = 1;
    for( __typeof( t.end() ) it = t.begin(); it != t.end(); it += di++ )
        printf( " %d", *it );
    printf( "\n" );
    printf( "Power-of-2 traversal:" );
    di = 1;
    for( __typeof( t.end() ) it = ++t.begin(); it != t.end(); it += di, di += di )
        printf( " %d", *it );
    printf( "\n" );
    return 0;
}


