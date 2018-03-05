/*
 * luogu3302
 *
 * 主席树，每次连边的时候就暴力遍历一遍小一点的树。
 * 然后加到主席树里去，查询时要从四个地方查，链的两端， lca 和 lca 的父亲。
 * 用前两个减掉后两个就是要求的链上的信息。
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <cmath>

using std::max;
using std::min;
using std::cerr;
using std::endl;
using std::sort;
using std::swap;
using std::unique;
using std::lower_bound;

template<class T>
bool chkmin(T &a, const T &b) { return a > b? a = b, 1 : 0; }

template<class T>
bool chkmax(T &a, const T &b) { return a < b? a = b, 1 : 0; }

struct IM {} getInt;

template<class T> IM& operator>>(IM& im, T &a) {
    a = 0; char c = getchar(); bool n = false;
    for (;!isdigit(c); c = getchar()) if (c == '-') n = true;
    for (; isdigit(c); c = getchar()) a = a * 10 + (c & 0xf);
    if(n) a = -a; return im;
}

const int Size = 8e4 + 5;
const int Log = 17 + 2;

struct Node {
    int val, sum, ch[2];
} c[Size * Log * Log];

bool createNewNode = true; // XXX If I used it, the memory could be smaller, but update() should be changed to fix some problem.

int _Index;

int root[Size];

int copyNode(int i) {
    c[++_Index] = c[i];
    return _Index;
}

void update(int &i, int l, int r, int pos, int key) {
    i = copyNode(i);
    c[i].val += key;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) update(c[i].ch[0], l, mid, pos, key);
    else update(c[i].ch[1], mid + 1, r, pos, key);
}

int query(const int &fst, const int &lst,
          const int &snd, const int &thd, int l, int r, int rank) {
    if (l == r) return l;
    int tmp = (c[c[fst].ch[0]].val + c[c[lst].ch[0]].val
               - c[c[snd].ch[0]].val - c[c[thd].ch[0]].val);
    int mid = (l + r) >> 1;
    return (tmp >= rank)
        ? query(c[fst].ch[0], c[lst].ch[0],
                c[snd].ch[0], c[thd].ch[0], l, mid, rank)
        : query(c[fst].ch[1], c[lst].ch[1],
                c[snd].ch[1], c[thd].ch[1], mid + 1, r, rank - tmp);
}

struct Edge { int next, to; } e[Size * 2];

int head[Size];

void insert(int u, int v) {
    static int _Index = 0;
    e[++_Index] = (Edge){ head[u], v };
    head[u] = _Index;
}

struct Hash {
    int elem[Size];
    int s;

    void init(int *a, int z) {
        memcpy(elem, a, sizeof (int) * (z + 1));
        sort(elem + 1, elem + 1 + z);
        s = unique(elem + 1, elem + 1 + z) - elem - 1;
    }

    int operator[](const int x) {
        return lower_bound(elem + 1, elem + 1 + s, x) - elem;
    }
} hash;

int testCase;

int val[Size];
bool vis[Size];
int size[Size];
int depth[Size];
int fa[Size][Log];

int n, m, t;
int lst;

void dfs(int x, int rt) {
    update(root[x] = root[fa[x][0]], 1, hash.s, hash[val[x]], 1);

    for (int i = 1; i < Log; ++i)
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    vis[x] = true;
    ++size[rt];
    depth[x] = depth[fa[x][0]] + 1;
    for (int i = head[x]; i; i = e[i].next)
        if (e[i].to != fa[x][0]) {
            fa[e[i].to][0] = x;
            dfs(e[i].to, rt);
        }
}

int lca(int x, int y) {
    if (depth[x] < depth[y]) swap(x, y);
    int delta = depth[x] - depth[y];
    for (int i = Log - 1; i >= 0; --i)
        if ((1 << i) & delta) x = fa[x][i];

    if (x == y) return x;

    for (int i = Log - 1; i >= 0; --i)
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i]; y = fa[y][i];
        }
    return fa[x][0];
}

int top(int x) {
    for (int i = Log - 1; i >= 0; --i)
        if (fa[x][i]) x = fa[x][i];
    return x;
}

int main() {
    getInt >> testCase >> n >> m >> t;

    for (int i = 1; i <= n; ++i) {
        getInt >> val[i];
    }

    hash.init(val, n);

    for (int u, v, i = 1; i <= m; ++i) {
        getInt >> u >> v;
        insert(u, v); insert(v, u);
    }

    for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i, i);

    char cmd[3];

    for (int i = 1, x, y, k, l; i <= t; ++i) {
        scanf("%s", cmd);
        getInt >> x >> y;
        x ^= lst; y ^= lst;
        if (*cmd == 'Q') {
            getInt >> k;
            k ^= lst;
            l = lca(x, y);
            printf("%d\n", lst = hash.elem[
                       query(root[x], root[y],
                             root[l], root[fa[l][0]], 1, hash.s, k)]);
        } else {
            insert(x, y);
            insert(y, x);
            k = top(x);
            l = top(y);
            if (size[k] < size[l]) {
                swap(k, l); swap(x, y);
            }
            fa[y][0] = x;
            dfs(y, k);
        }
    }

    return 0;
}
