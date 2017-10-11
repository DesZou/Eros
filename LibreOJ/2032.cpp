#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>

const long long Inf = LONG_MAX;
const long long initInt = 123456789123456789;
const size_t Size = 1e5 + 5;

template<class T> T max(const T &a, const T &b) {
    return a > b? a : b;
}

template<class T> T min(const T &a, const T &b) {
    return a < b? a : b;
}

template<class T> bool chkmax(T &a, const T &b) {
    return a < b? a = b, 1 : 0;
}

template<class T> bool chkmin(T &a, const T &b) {
    return a > b? a = b, 1 : 0;
}

template<class T> T input() {
    T res = 0; char c = getchar(); bool nega = 0;
    while(c > '9' || c < '0') {if(c == '-') nega = 1; c = getchar();}
    while(c <= '9' && c >= '0') {res = res * 10 - 48 + c, c = getchar();}
    return nega? -res : res;
}

template<class Tp> void nextInt(Tp &var) {
    var = input<Tp>();
}

template<class T, class ...Tp> void nextInt(T &var, Tp &...args) {
    var = input<T>();
    nextInt(args...);
}

typedef Array int[Size];
typedef Larray long long[size];

struct Edge {int next, to;} e[Size << 1];

Array head, fa, son, depth, size, top, num, sig;
Larray val;

int n, m;

struct IntervalTree {
    struct Tag {int a, b; bool e;} tag[Size << 2];

    long long elem[Size << 2];

    void pushUp(int i) {
        elem[i] = min(elem[i << 1], elem[i << 1|1]);
    }

    void pushDown(int i, int l, int r) {
        
    }

    void build(int i, int l, int r) {
        elem[i] = initInt;
        if(l == r) continue;
        int mid = (l + r) >> 1;
        build(i << 1, l, mid);
        build(i << 1|1, mid + 1, r);
    }
} T;

void insert(int u, int v, int w) {
    static int _Index = 0;
    e[++_Index] = (Edge){head[u], v, w};
    head[u] = _Index;
}

void dfs(int x) {
    depth[x] = depth[fa[x]] + 1;
    val[x] = initInt;
    for(int i = head[x]; i; i = e[i].next) if(e[i].to != fa[x]) {
        fa[e[i].to] = x; dfs(e[i].to);
        size[x] += size[e[i].to];
        if(size[e[i].to] > size[son[x]]) son[x] = e[i].to;
    }
}

void dfs(int x, int script) {
    static int _Index = 0;
    sig[num[x] = ++_Index] = x;
    top[x] = script;

    if(son[x]) dfs(son[x], script);

    for(int i = head[x]; i; i = e[i].next)
        if(e[i].to != son[x] && e[i].to != fa[x]) dfs(e[i].to, e[i].to);
}

int main() {
    nextInt(n, m);

    for(int i = 1, u, v, w; i < n; ++i) {
        nextInt(u, v, w);
        insert(u, v, w);
        insert(v, u, w);
    }

    dfs(1), dfs(1, 1);

    return 0;
}
