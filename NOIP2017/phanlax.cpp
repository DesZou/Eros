#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>

const size_t Size = 3e5 + 5;

template<class T> T max(const T &a, const T &b) {
    return a > b? a : b;
}

template<class T> T min(const T &a, const T &b) {
    return a < b? a : b;
}

template<class T> bool chkmin(T &a, const T &b) {
    return a > b? a = b, 1 : 0;
}

template<class T> bool chkmax(T &a, const T &b) {
    return a < b? a = b, 1 : 0;
}

template<class T> T input() {
    T r(0); char c(getchar()); bool n(false);
    while(c > '9' || c < '0') {if(c == '-') n = true; c = getchar();}
    while(c <= '9' && c >= '0') {r = r * 10 - 48 + c, c = getchar();}
    return n? -r : r;
}

int n, m, q;

namespace splay_tree {

    struct Node {
        long long l, r;
        int size, fa, ch[2];
    } t[Size << 2];

    int root[Size], _Index;

    void pushup(int x) {
        t[x].size = t[t[x].ch[0]].size +
                    t[t[x].ch[1]].size +
                    (t[x].r - t[x].l + 1);
    }

    void rotate(int x) {
        int y, z, B; bool f;
        y = t[x].fa, z = t[y].fa;
        f = (t[y].ch[0] == x);
        B = t[x].ch[f];
        t[x].fa = z, t[y].fa = x;
        if(B) t[B].fa = y;
        t[x].ch[f] = y;
        t[y].ch[f ^ 1] = B;
        if(t[z].ch[0] == y) t[z].ch[0] = x;
        else if(t[z].ch[1] == y) t[z].ch[1] = x;
        pushup(y), pushup(x);
    }

    void splay(int x) {
        for(int y, z; t[x].fa;) {
            y = t[x].fa, z = t[y].fa;
            if(z) rotate(((t[z].ch[0] == y) ^ (t[y].ch[0] == x))? x : y);
            rotate(x);
        }
    }

    int kth(int x, int k) {
        if(t[t[x].ch[0]].size < k && k <= t[x].size - t[t[x].ch[1]].size) {
            long long p = t[x].l + (long long)(k - t[t[x].ch[0]].size - 1);
            if(t[x].l < p) {
                t[++_Index] = (Node){t[x].l, p - 1, 0, x, {t[x].ch[0], 0}};
                t[t[x].ch[0]].fa = _Index;
                t[x].ch[0] = _Index;
                t[x].l = p;
                pushup(_Index);
            } 
            if(p < t[x].r) {
                t[++_Index] = (Node){p + 1, t[x].r, 0, x, {0, t[x].ch[1]}};
                t[t[x].ch[1]].fa = _Index;
                t[x].ch[1] = _Index;
                t[x].r = p;
                pushup(_Index);
            }
            pushup(x);
            return x;
        } else {
           int f = ((k <= t[t[x].ch[0]].size)?
                    kth(t[x].ch[0], k) :
                    kth(t[x].ch[1], k - t[x].size + t[t[x].ch[1]].size));
           pushup(x);
           return f;
        }
    }
    
    void build(int l, int r, int &x) {
        if(!x) x = ++_Index;
        int mid = (l + r) >> 1;
        t[x].l = t[x].r = (long long)m * mid;
        if(l < mid) {
            build(l, mid - 1, t[x].ch[0]);
            t[t[x].ch[0]].fa = x;
        }
        if(r > mid) {
            build(mid + 1, r, t[x].ch[1]);
            t[t[x].ch[1]].fa = x;
        } pushup(x);
    }

    int merge(int x, int y) {
        if(!x || !y) return x | y;
        while(t[x].ch[1]) x = t[x].ch[1];
        splay(x);
        t[x].ch[1] = y;
        t[y].fa = x;
        pushup(x);
        return x;
    }

    int split(int p) {
        int k, j;
        k = t[p].ch[0], j = t[p].ch[1];
        t[p].ch[0] = t[p].ch[1] = 0;
        t[k].fa = t[j].fa = 0;
        pushup(p);
        return merge(k, j);
    }
}

struct Data {
    int e[3];
} d;

int main() {
    // freopen("phanlax.in", "r", stdin);
    // freopen("phanlax.out", "w", stdout);

    using splay_tree::root;
    using splay_tree::t;
    using splay_tree::kth;
    using splay_tree::merge;
    using splay_tree::split;
    using splay_tree::splay;

    n = input<int>(), m = input<int>(), q = input<int>();

    if(m > 1) {
        splay_tree::_Index = n;
        for(int i = 1; i <= n; ++i) {
            root[i] = i;
            t[i].l = (long long)m * (i - 1) + 1;
            t[i].r = (long long)m * i - 1;
            t[i].size = m - 1;
        }
    } splay_tree::build(1, n, root[n + 1]);

    for(int x, y, p, f; q --> 0;) {
        x = input<int>(), y = input<int>();
        if(y == m) {
            p = kth(root[n + 1], x);
            splay(p);
            printf("%lld\n", t[p].l);
            root[n + 1] = merge(split(p), p);
        } else {
            p = kth(root[x], y);
            splay(p);
            printf("%lld\n", t[p].l);
            f = kth(root[n + 1], x);
            splay(f);
            root[x] = split(p);
            root[n + 1] = split(f);
            root[x] = merge(root[x], f);
            root[n + 1] = merge(root[n + 1], p);
        }
    }

    return 0;
}
