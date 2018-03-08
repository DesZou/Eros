/*
 * luogu3332
 *
 * *真正* 的线段树套线段树，不开 O2 过不了。
 * 碰到这种题，一定要想着换换顺序维护，不要死死地跟着题面来。
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::cerr;

const char El = 10;
const int Size = 5e4 + 5;
const int Log = 17;

char getChar() {
    static char buf[1 << 15], *s, *t = s;
    if (s == t) t = (s = buf) + fread(buf, 1, 1 << 15, stdin);
    return s == t? EOF : *s++;
}

struct IM {} getInt;

template<class T> IM& operator>>(IM& im, T& a) {
    a = 0; char c = getChar(); bool n = false;
    for (;!isdigit(c); c = getChar()) if (c == '-') n = true;
    for (; isdigit(c); c = getChar()) a = a * 10 + (c & 0xf);
    if (n) a = -a; return im;
}

struct Node { int ch[2]; long long val, tag; } c[Size * Log * Log];
struct Data { int id, a, b, c; } d[Size];

struct Hash {
    int elem[Size];
    int len;

    void init(int* a, int x) {
        memcpy(elem, a, sizeof (int) * (x + 1));
        std::sort(elem + 1, elem + 1 + x);
        len = std::unique(elem + 1, elem + 1 + x) - elem - 1;
    }

    int operator[](const int x) {
        return std::lower_bound(elem + 1, elem + 1 + len, x) - elem;
    }
} hash;

int _Index = 0;

int n, m, lim;

int val[Size];

int root[Size << 2];

inline void pushdown(int i, int l, int r) {
    if (c[i].tag) {
        int mid = (l + r) >> 1;
        if (!c[i].ch[0]) c[i].ch[0] = ++_Index;
        if (!c[i].ch[1]) c[i].ch[1] = ++_Index;
        c[c[i].ch[0]].val += c[i].tag * (mid - l + 1);
        c[c[i].ch[0]].tag += c[i].tag;
        c[c[i].ch[1]].val += c[i].tag * (r - mid);
        c[c[i].ch[1]].tag += c[i].tag;
        c[i].tag = 0;
    }
}

inline void pushup(int i) { c[i].val = c[c[i].ch[0]].val + c[c[i].ch[1]].val; }

void update(int& i, int l, int r, int s, int t, long long key) {
    if (!i) i = ++_Index;
    if (l >= s && r <= t) {
        c[i].val += key * (r - l + 1);
        c[i].tag += key;
    } else {
        int mid = (l + r) >> 1;
        if (c[i].tag) pushdown(i, l, r);
        if (s <= mid) update(c[i].ch[0], l, mid, s, t, key);
        if (t > mid) update(c[i].ch[1], mid + 1, r, s, t, key);
        pushup(i);
    }
}

long long query(const int& i, int l, int r, const int& s, const int& t) {
    if (!i) return 0;
    else if (l >= s && r <= t) {
        return c[i].val;
    } else {
        int mid = (l + r) >> 1;
        if (c[i].tag) pushdown(i, l, r);
        return (t <= mid)
            ? query(c[i].ch[0], l, mid, s, t)
            : (s > mid)
            ? query(c[i].ch[1], mid + 1, r, s, t)
            : query(c[i].ch[0], l, mid, s, mid)
            + query(c[i].ch[1], mid + 1, r, mid + 1, t);
    }
}

void modify(const int& i, int l, int r, int pos, int key, int s, int t) {
    update(root[i], 1, n, s, t, key);
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) modify(i << 1, l, mid, pos, key, s, t);
    else modify(i << 1 | 1, mid + 1, r, pos, key, s, t);
}

int query(const int& i, int l, int r, int s, int t, long long rank) {
    if (l == r) return hash.elem[l];
    int mid = (l + r) >> 1;
    long long tmp = query(root[i << 1 | 1], 1, n, s, t);
    return (tmp >= rank)
        ? query(i << 1 | 1, mid + 1, r, s, t, rank)
        : query(i << 1, l, mid, s, t, rank - tmp);
}

int main() {
    cout.sync_with_stdio(0);
    getInt >> n >> m;

    for (int i = 1; i <= m; ++i) {
        getInt >> d[i].id >> d[i].a >> d[i].b >> d[i].c;
        if (d[i].id == 1) val[++lim] = d[i].c;
    }

    hash.init(val, lim);

    for (int i = 1; i <= m; ++i) {
        if (d[i].id == 1) {
            modify(1, 1, hash.len, hash[d[i].c], 1, d[i].a, d[i].b);
        } else {
            cout << query(1, 1, hash.len, d[i].a, d[i].b, d[i].c) << El;
        }
    }

    return 0;
}
