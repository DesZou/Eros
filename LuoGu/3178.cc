#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>

const size_t Size = 1e5 + 5;

typedef int Array[Size];

template<class T> T min(const T &a, const T &b) {
    return a < b? a : b;
}

template<class T> T max(const T &a, const T &b) {
    return a > b? a : b;
}

template<class T> bool chkmin(T &a, const T &b) {
    return a > b? a = b, 1 : 0;
}

template<class T> bool chkmax(T &a, const T &b) {
    return a < b? a = b, 1 : 0;
}

template<class T> T input() {
    T r(0); char c(std::getchar()); bool n(false);
    for(;!std::isdigit(c); c = std::getchar()) if(c == '-') n = 1;
    for(; std::isdigit(c); c = std::getchar()) r = r * 10 - 48 + c;
    return n? -r : r;
}

int n, m;

struct SegmentTree {
    long long c[Size << 2];
    long long tag[Size << 2];

    void pushup(int i) {
        c[i] = c[i << 1] + c[i << 1|1];
    }

    void pushdown(int i, int l, int r) {
        if(tag[i]) {
            int mid = (l + r) >> 1;
            c[i << 1] += tag[i] * (mid - l + 1);
            c[i << 1 | 1] += tag[i] * (r - mid);
            tag[i << 1] += tag[i];
            tag[i << 1|1] += tag[i];
            tag[i] = 0;
        }
    }

    void update(int i, int l, int r, int s, int t, long long key) {
        if(l >= s && r <= t) {
            c[i] += key * (r - l + 1);
            tag[i] += key;
        } else {
            int mid = (l + r) >> 1;
            pushdown(i, l, r);
            if(s <= mid) update(i << 1, l, mid, s, t, key);
            if(t > mid) update(i << 1|1, mid + 1, r, s, t, key);
            pushup(i);
        }
    }

    long long query(int i, int l, int r, int s, int t) {
        if(l >= s && r <= t) {
            return c[i];
        } else {
            int mid = (l + r) >> 1;
            pushdown(i, l, r);
            return (t <= mid)
                ? query(i << 1, l, mid, s, t)
                : (s > mid)
                ? query(i << 1|1, mid + 1, r, s, t)
                : query(i << 1|1, mid + 1, r, mid + 1, t)
                + query(i << 1, l, mid, s, mid);
        }
    }
} T;

struct Edge {int next, to;} e[Size << 1];

Array head, size, fa, son, depth, top, num;

long long val[Size];

void dfs(int x) {
    size[x] = 1;
    depth[x] = depth[fa[x]] + 1;

    for(int i = head[x]; i; i = e[i].next)
        if(e[i].to != fa[x]) {
            fa[e[i].to] = x;
            dfs(e[i].to);
            size[x] += size[e[i].to];
            if(size[e[i].to] > size[son[x]]) son[x] = e[i].to;
        }
}

void dfs(int x, int script) {
    static int _Index = 0;
    num[x] = ++_Index;
    top[x] = script;

    if(son[x]) dfs(son[x], script);

    for(int i = head[x]; i; i = e[i].next)
        if(e[i].to != fa[x] && e[i].to != son[x]) {
            dfs(e[i].to, e[i].to);
        }
}

long long sum(int x, int y) {
    long long res = 0;
    for(int u = top[x], v = top[y]; u != v; x = fa[u], u = top[x]) {
        if(depth[u] < depth[v]) std::swap(x, y), std::swap(u, v);
        res += T.query(1, 1, n, num[u], num[x]);
    } return res + ((depth[x] < depth[y])
                    ? T.query(1, 1, n, num[x], num[y])
                    : T.query(1, 1, n, num[y], num[x]));
}

void insert(int u, int v) {
    static int _Index = 0;
    e[++_Index] = (Edge){head[u], v};
    head[u] = _Index;
}

int main() {
    n = input<int>(), m = input<int>();

    for(int i = 1; i <= n; ++i)
        val[i] = input<int>();

    for(int i = 1, u, v; i < n; ++i) {
        u = input<int>(), v = input<int>();
        insert(u, v), insert(v, u);
    }

    dfs(1), dfs(1, 1);

    for(int i = 1; i <= n; ++i)
        T.update(1, 1, n, num[i], num[i], val[i]);

    for(int i = 1, x, a, c; i <= m; ++i) {
        c = input<int>();
        x = input<int>();
        if(c == 1) {
            a = input<int>();
            T.update(1, 1, n, num[x], num[x], a);
        } else if(c == 2) {
            a = input<int>();
            T.update(1, 1, n, num[x], num[x] + size[x] - 1, a);
        } else {
            std::printf("%lld\n", sum(1, x));
        }
    }

    return 0;
}
