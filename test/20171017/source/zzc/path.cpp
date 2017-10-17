#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <climits>

const int Inf = -1u >> 1;
const size_t Size = 500 + 5;

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
    T r(0); char c(getchar()); bool n(0);
    while(c > '9' || c < '0') {if(c == '-') n = 1; c = getchar();}
    while(c <= '9' && c >= '0') {r = r * 10 - 48 + c, c = getchar();}
    return n? -r : r;
}

int f[Size][Size];
int g[Size][Size];

long long ans[Size][Size];

struct Data {int id, val;} d[Size];

bool operator<(const Data &a, const Data &b) {
    return a.val < b.val;
}

inline long long fig(const int a, const int b) {
    return (long long)f[a][b] * g[a][b];
}

inline long long fig(const int a, const int b, const int c) {
    return (long long)max(f[a][b], f[b][c]) * max(g[a][b], g[b][c]);
}

int n, m;

int main() {
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);

    std::memset(f, 0x7f, sizeof f);
    std::memset(g, 0x7f, sizeof g);

    n = input<int>(), m = input<int>();

    for(int i = 1; i <= n; ++i) {
        d[i].val = input<int>(), d[i].id = i;
        f[i][i] = d[i].val, g[i][i] = 0;
    }

    for(int i = 0, u, v, w; i < m; ++i) {
        u = input<int>(), v = input<int>(), w = input<int>();
        f[u][v] = f[v][u] = w, g[u][v] = g[v][u] = max(d[v].val, d[u].val);
    }

    std::sort(d + 1, d + 1 + n);

    for(int k = 1; k <= n; ++k)
    for(int i = n; i; --i) if(i != k)
    for(int j = n; j; --j) if(j != i && j != k)
        if(fig(d[i].id, d[j].id) > fig(d[i].id, d[k].id, d[j].id)) {
            f[d[i].id][d[j].id] = max(f[d[i].id][d[k].id], f[d[k].id][d[j].id]);
            g[d[i].id][d[j].id] = max(g[d[i].id][d[k].id], g[d[k].id][d[j].id]);
        }

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            if(f[d[i].id][d[j].id] >= Inf ||
               g[d[i].id][d[j].id] >= Inf) ans[d[i].id][d[j].id] = -1;
            else ans[d[i].id][d[j].id] = fig(d[i].id, d[j].id);

    for(int i = 1; i <= n; ++i, putchar(10))
        for(int j = 1; j <= n; ++j)
            printf("%lld ", ans[i][j]);

    return 0;
}
