// An implementation of a very simple memory-mapped B-tree in C++.
// Features an STL-like container with O(log n) random access iterators,
// find(), lower_bound(), insert().
// No deletion. No multi-threading. No ACID. No warranty whatsoever.
// A recent Linux version required. (Cygwin is okay with minor changes.)
// Code released into public domain by the original author.
//
#define _LARGEFILE64_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>   // for mmap()

#include <algorithm>
#include <numeric>
#include <iterator>

typedef uint32_t enum_t;   // for element indices
typedef uint32_t pnum_t;   // for page indices

// both on-disk and in-memory B-tree page structure
struct  __attribute__((__packed__)) Page {
    typedef double key_type;
    enum { MAXK = 63 };        // number of elements per page, should be odd.
                               // remember to update BTree::PAGE_SIZE.

    int32_t size;              // number of keys in this page
    enum_t total_size;         // total number of elements in subtree
    pnum_t kids[MAXK+1];       // children indices, 0=N/A
    enum_t kids_size[MAXK+1];  // total number of elements in each kid
    key_type keys[MAXK];       // keys
};

// special structure of the very first page in file
struct SuperPage {
    char magic[32];
    pnum_t num_pages;  // number of used pages (numbered 0..num_pages-1)
                       // TODO: replace by a freelist
    pnum_t max_pages;
    int height;        // just stats
};

// B-Tree
class BTree {
  public:
    enum { PAGE_SIZE = 1024, ROOT_PAGE = 1, SPLIT_SIZE = Page::MAXK};
    enum { MAX_DEPTH = 15 };   // "should be enough for anyone"
    typedef Page::key_type key_type;

    // tree iterator
    class Iterator : public std::iterator<std::random_access_iterator_tag, key_type, ssize_t> {
        // iterator needs to keep the entire path to key, because we don't have "parent" field
        Page *p[MAX_DEPTH];
        int e[MAX_DEPTH];   // indices in Page::kids;
        int d;              // depth-1
        ssize_t index_;
        const BTree *tree;
        friend class BTree;

        Iterator(const BTree *tree_) {  // constructs end(), which is cheap
            tree = tree_;
            d = 0;
            p[0] = tree->get_page(ROOT_PAGE);
            e[0] = p[0]->size;
            index_ = p[0]->total_size;
        }

        void normalize() {
            while (e[d] == p[d]->size && d != 0) d--;
        }

      public:
        key_type &operator *() { return p[d]->keys[e[d]]; }
        const key_type &operator *() const { return p[d]->keys[e[d]]; }
        key_type &operator[](ssize_t n) { return *(*this + n); }
        const key_type &operator[](ssize_t n) const { return *(*this + n); }
        bool operator ==(const Iterator &it) const { return index() == it.index(); }
        bool operator !=(const Iterator &it) const { return index() != it.index(); }
        bool operator <(const Iterator &it) const { return index() < it.index(); }
        ssize_t operator -(const Iterator &it) const { return index() - it.index(); }
        Iterator &operator ++() { return *this += (ssize_t)1; }
        Iterator &operator --() { return *this += (ssize_t)-1; }
        Iterator operator ++(int) const { return *this + 1; }
        Iterator operator --(int) const { return *this - 1; }
        Iterator operator +(ssize_t n) const { Iterator it(*this); it += n; return it; }
        Iterator operator -(ssize_t n) const { Iterator it(*this); it -= n; return it; }
        Iterator &operator -=(ssize_t n) { return *this += -n; }

        // Returns 0-based index of this entry in the tree.
        ssize_t index() const { return index_; }

        Iterator &operator +=(ssize_t n) {
            index_ += n;
            while (n != 0) {
                if (n > 0) {                              // right &
                    assert(e[d] < p[d]->size);
                    if (n <= (ssize_t)p[d]->kids_size[e[d]+1]) {  // down
                        p[d+1] = tree->get_page(p[d]->kids[++e[d]]);
                        e[d+1] = 0;
                        n -= 1 + (ssize_t)p[++d]->kids_size[0];
                    } else {  // up
                        n -= 1 + (ssize_t)p[d]->kids_size[++e[d]];
                        normalize();
                    }
                } else {                                   // left &
                    if (-n <= (ssize_t)p[d]->kids_size[e[d]]) {   // down
                        p[d+1] = tree->get_page(p[d]->kids[e[d]]);
                        e[d+1] = p[d+1]->size - 1;
                        d++;
                        n += 1 + (ssize_t)p[d]->kids_size[p[d]->size];
                    } else {                                      // up
                        n += 1 + (ssize_t)p[d]->kids_size[e[d]];
                        while (e[d] == 0) { assert(d != 0); d--; }
                        e[d]--;
                    }
                }
            }
            return *this;
        }
    };

    Iterator begin() const { return end() - size(); }
    Iterator end() const { return Iterator(this); }
    ssize_t size() const { return get_page(ROOT_PAGE)->total_size; }
    int height() const { return super->height; }

    // Opens an existing B-tree file. Aborts program on failure.
    static BTree *open_or_die(const char *filename);

    // Creates a new B-tree file with `npages' pages. Aborts program on failure.
    static BTree *create_or_die(const char *filename, pnum_t npages);

    // Destructor closes file and frees resources.
    ~BTree();

    // Inserts key into the tree, returns iterator to its new location.
    // This invalidates existing iterators.
    Iterator insert(const key_type &key);

    // Returns iterator to the first element that does not compare less than key.
    Iterator lower_bound(const key_type &key) const;

    // Returns an iterator to the first instance of `key', or end() if not found.
    Iterator find(const key_type &key) const {
        Iterator it = lower_bound(key);  // *it >= key
        return (it == end() || key < *it) ? end() : it;
    }

  private:
    BTree(const BTree &) {}
    void operator =(const BTree &) {}

    BTree(int fd_, uint64_t grow_pages, int init);
    void split_node(int id, key_type &key, pnum_t &l_id, pnum_t &r_id);
    void insert_now(pnum_t id, int e, const key_type &key, pnum_t l, pnum_t r);

    pnum_t alloc_page() {
        assert(super->num_pages < super->max_pages);
        return super->num_pages++;
    }

    Page *get_page(pnum_t id) const {
        assert(1 <= id && id < super->num_pages);
        return &pages[id];
    }

    int fd;             // file descriptor
    Page *pages;        // memory-mapped contents of fd
    SuperPage *super;   // = &pages[0]
};

BTree *BTree::open_or_die(const char *filename) {
    int fd = open(filename, O_RDWR|O_LARGEFILE);
    if (fd == -1) { perror("open"); abort(); }
    return new BTree(fd, 1, 1);
}

BTree *BTree::create_or_die(const char *filename, pnum_t npages) {
    int fd = ::open(filename, O_RDWR|O_CREAT|O_TRUNC|O_LARGEFILE, 0666);
    if (fd == -1) { perror("open"); abort(); }
    return new BTree(fd, npages, 1);
}

BTree::BTree(int fd_, uint64_t grow_pages, int init) {
    assert(sizeof(Page) == PAGE_SIZE);
    assert(SPLIT_SIZE % 2 == 1 && int(SPLIT_SIZE) <= int(Page::MAXK));

    fd = fd_;
    pages = NULL;

    // compute file size, sanity check
    uint64_t fsize = lseek64(fd, 0, SEEK_END);
    assert(fsize % sizeof(Page) == 0 && (init || fsize >= 2*sizeof(Page)));
    uint64_t max_pages = fsize / sizeof(Page);

    // grow file if requested
    if (grow_pages < 2) grow_pages = 2;
    if (grow_pages > max_pages) {
        int64_t offs = grow_pages * sizeof(Page) - 1;
        assert(offs == lseek64(fd, offs, SEEK_END));
        assert(1 == write(fd, "", 1));
        max_pages = grow_pages;
        fsize = max_pages * (uint64_t)sizeof(Page);
    }

    // map file into address space
    assert(fsize == (size_t)fsize);
    pages = (Page *)mmap(NULL, fsize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    assert(pages != NULL);

    // check superblock
    assert(sizeof(SuperPage) <= sizeof(Page));
    super = (SuperPage *)&pages[0];
    const char *magic = "BTREE-6B1D9F22";
    if (init) {
        strcpy(super->magic, magic);
        super->num_pages = 2;
        super->height = 1;
        memset(&pages[ROOT_PAGE], 0, sizeof(Page));
    } else {
        assert(strcmp(super->magic, magic) == 0);
        assert(super->num_pages >= 2);
    }
    super->max_pages = max_pages;
}

BTree::~BTree() {
    if (pages != NULL) munmap(pages, (size_t)(super->max_pages * 4096ULL));
    if (fd != -1) close(fd);
}

// Splits a page into two, returns median key and subpages' indices
void BTree::split_node(int id, key_type &key, pnum_t &l_id, pnum_t &r_id) {
    l_id = id;
    r_id = alloc_page();
    Page *L = get_page(l_id), *R = get_page(r_id);
    int mid = L->size / 2;
    key = L->keys[mid];
    R->size = L->size - mid - 1;
    memcpy(R->keys, &L->keys[mid+1], sizeof(R->keys[0]) * R->size);
    memcpy(R->kids, &L->kids[mid+1], sizeof(R->kids[0]) * (R->size + 1));
    memcpy(R->kids_size, &L->kids_size[mid+1], sizeof(R->kids_size[0]) * (R->size + 1));
    L->size = mid;
    L->total_size = L->size + std::accumulate(L->kids_size, L->kids_size + 1 + L->size, (enum_t)0);
    R->total_size = R->size + std::accumulate(R->kids_size, R->kids_size + 1 + R->size, (enum_t)0);
}

// Inserts key into an *incomplete* page at given position, does some fix-up
void BTree::insert_now(pnum_t id, int e, const key_type &key, pnum_t l, pnum_t r) {
    Page *p = get_page(id);
    assert(p->size + 1 <= SPLIT_SIZE);
    if (p->size > 0) {
        memmove(&p->keys[e+1], &p->keys[e], (p->size-e) * sizeof(p->keys[0]));
        memmove(&p->kids[e+2], &p->kids[e+1], (p->size-e) * sizeof(p->kids[0]));
        memmove(&p->kids_size[e+2], &p->kids_size[e+1], (p->size-e) * sizeof(p->kids_size[0]));
        p->total_size -= p->kids_size[e];
    }
    p->keys[e] = key;
    p->kids[e] = l;
    p->kids_size[e] = l == 0 ? 0 : get_page(l)->total_size;
    p->kids[e+1] = r;
    p->kids_size[e+1] = r == 0 ? 0 : get_page(r)->total_size;
    p->size++;
    p->total_size += p->kids_size[e] + p->kids_size[e+1] + 1;
}

BTree::Iterator BTree::insert(const key_type &key) {
    pnum_t path[MAX_DEPTH] = { ROOT_PAGE };
    enum_t lindex[MAX_DEPTH];
    Iterator it(this);
    it.d = 0;

    assert(super->num_pages + MAX_DEPTH + 2 <= super->max_pages);

    while (true) {
        Page *p = get_page(path[it.d]);

        if (p->size == SPLIT_SIZE) {
            // это однопроходный алгоритм, сразу разбиваем полные страницы по пути вниз
            key_type up_key;
            pnum_t l, r;

            assert(it.d <= MAX_DEPTH);
            split_node(path[it.d], up_key, l, r);

            if (it.d > 0) {
                insert_now(path[it.d-1], it.e[it.d-1], up_key, l, r);
                it.d--;
            } else {
                // ой-ой, разбили корень, чиним
                pnum_t rootcopy = alloc_page();
                assert(l == ROOT_PAGE);
                memcpy(get_page(rootcopy), get_page(l), sizeof(Page));
                l = rootcopy;
                memset(get_page(ROOT_PAGE), 0, sizeof(Page));
                insert_now(ROOT_PAGE, 0, up_key, l, r);
            }
            continue;
        }

        int c = std::lower_bound(p->keys, p->keys + p->size, key) - p->keys;
        it.e[it.d] = c;
        lindex[it.d] = c + std::accumulate(p->kids_size, p->kids_size + c, (ssize_t)0);

        if (p->kids[c] == 0) {  // leaf
            insert_now(path[it.d], c, key, 0, 0);
            if (it.d + 1 > super->height) super->height = it.d + 1;
            break;
        } else {
            p->total_size++;
            p->kids_size[c]++;
            path[++it.d] = p->kids[c];
        }
    }

    for (int i = 0; i <= it.d; i++) it.p[i] = get_page(path[i]);
    it.index_ = std::accumulate(lindex, lindex + it.d + 1, (enum_t)0);
    return it;
}

BTree::Iterator BTree::lower_bound(const key_type &key) const {
    Iterator it(this);
    it.d = 0;
    it.p[0] = get_page(ROOT_PAGE);
    it.index_ = 0;
    while (true) {
        Page *p = it.p[it.d];
        int c = std::lower_bound(p->keys, p->keys + p->size, key) - p->keys;
        it.e[it.d] = c;
        it.index_ += c + std::accumulate(p->kids_size, p->kids_size + c, (ssize_t)0);
        if (p->kids[c] == 0) {
            it.normalize();  // may need to go a few steps up 
            return it;
        } else {
            it.p[++it.d] = get_page(p->kids[c]);
        }
    }
}


// test
#include <vector>
#include <set>
using namespace std;
int main()
{
    BTree *tree = BTree::create_or_die("/tmp/btree", 10000);
    srand(12049645);
    set<double> seen;
    for (int sz = 1; sz <= 1000000; sz++) {
        double x = (double)rand();
        if (seen.count(x) != 0) { sz--; continue; }
        seen.insert(x);

        printf("===== h=%d n=%d, inserting %.0lf\n", tree->height(), (int)tree->size(), x);
        BTree::Iterator it = tree->insert(x);

        assert(tree->size() == sz);
        vector<double> v(seen.begin(), seen.end());
        vector<double> w(tree->begin(), tree->end());
        assert(v == w);
        assert(it != tree->end());
        assert(0 <= it.index() && it.index() < (int)v.size() && v[it.index()] == *it);
        assert(tree->lower_bound(v[0] - 1) == tree->begin());
        assert(tree->lower_bound(v.back() + 1) == tree->end());

        for (int z = 0; z <= sz; z++) {
            BTree::Iterator i = it + (z - it.index());
            assert(i.index() == z);
            if (z == sz) {
                assert(i == tree->end());
            } else {
                assert(*i == v[z]);
                assert(tree->lower_bound(v[z]) == i);
            }
            assert(tree->begin() + z == i);
            assert(tree->end() - (sz - z) == i);
            if (z+1 < sz && v[z]+1 < v[z+1])
                assert(tree->lower_bound(v[z]+1) == tree->begin()+(z+1));
        }
    }

    delete tree;
}
