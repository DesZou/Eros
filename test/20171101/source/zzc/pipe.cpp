#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const size_t Size = 2e5 + 5;
const int Log = 18;

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
    T r(0); char c(getchar()); bool n(false);
    while(c > '9' || c < '0') {if(c == '-') n = true; c = getchar();}
    while(c <= '9' && c >= '0') {r = r * 10 - 48 + c, c = getchar();}
    return n? -r : r;
}

struct Pipe {
    int u, v, w, id;
    bool vis;
} p[Size];

bool operator<(const Pipe &a, const Pipe &b) {
    return a.w < b.w;
}

struct Edge {
    int next, to, val;
} e[Size << 1];

struct Union_find_set {
    int elem[Size];

    Union_find_set(int n) {
        for(int i = 1; i <= n; ++i) elem[i] = i;
    }

    int find(int x) {
        return x == elem[x]? x : elem[x] = find(elem[x]);
    }

    void union_fa(int x, int y) {
        elem[elem[x]] = elem[y];
    }
};

int n, m;

int head[Size], depth[Size];

void insert(int u, int v, int w) {
    static int _Index = 0;
    e[++_Index] = (Edge){head[u], v, w};
    head[u] = _Index;
}

int fa[Size][Log + 2], val[Size][Log + 2];

long long ans[Size];

void dfs(int x) {
    depth[x] = depth[fa[x][0]] + 1;
    for(int i = 1; i < Log; ++i) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
        val[x][i] = max(val[x][i - 1], val[fa[x][i - 1]][i - 1]);
    }

    for(int i = head[x]; i; i = e[i].next) if(e[i].to != fa[x][0]) {
        fa[e[i].to][0] = x, val[e[i].to][0] = e[i].val;
        dfs(e[i].to);
    }
}

int lca_maxans(int x, int y) {
    if(depth[x] < depth[y]) std::swap(x, y);
    int ans = 0, delta = depth[x] - depth[y];
    for(int i = 0; i < Log && i <= delta; ++i)
        if((1 << i) & delta) chkmax(ans, val[x][i]), x = fa[x][i];

    if(x == y) return ans;

    for(int i = Log - 1; i >= 0; --i) if(fa[x][i] != fa[y][i]) {
        chkmax(ans, max(val[x][i], val[y][i]));
        x = fa[x][i], y = fa[y][i];
    }

    return max(ans, max(val[x][0], val[y][0]));
}

int main() {
    freopen("pipe.in", "r", stdin);
    freopen("pipe.out", "w", stdout);

    n = input<int>(), m = input<int>();

    static Union_find_set fset(n);

    for(int i = 1; i <= m; ++i) {
        p[i].u = input<int>();
        p[i].v = input<int>();
        p[i].w = input<int>();
        p[i].id = i;
    }

    std::sort(p + 1, p + 1 + m);

    long long sum = 0;

    for(int i = 1, total = 0, x, y; i <= m && total < n - 1; ++i) {
        x = fset.find(p[i].u), y = fset.find(p[i].v);
        if(x == y) continue;
        ++total, fset.union_fa(x, y);
        sum += p[i].w, p[i].vis = true;
        insert(p[i].u, p[i].v, p[i].w);
        insert(p[i].v, p[i].u, p[i].w);
    }

    dfs(1);

    for(int i = 1; i <= m; ++i) {
        if(p[i].vis) ans[p[i].id] = sum;
        else ans[p[i].id] = sum - lca_maxans(p[i].u, p[i].v) + p[i].w;
    }

    for(int i = 1; i <= m; ++i)
        printf("%lld\n", ans[i]);

    return 0;
}
