#include <cstdio>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <cstring>

// const size_t Size = 1e3 + 5;
const int Log = 12 + 1;
const int Inf = 0x3f3f3f3f;

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

int n, m;

int h[Log][1 << Log];
int f[Log][1 << Log];
int graph[Log][Log];

int main() {
    // freopen("treasure.in", "r", stdin);
    // freopen("treasure.out", "w", stdout);

    std::memset(graph, 0x3f, sizeof graph);
    std::memset(h, 0x3f, sizeof h);
    std::memset(f, 0x3f, sizeof f);

    n = input<int>(), m = input<int>();

    for(int i = 0, u, v; i < m; ++i) {
        u = input<int>(), v = input<int>();
        if(chkmin(graph[v][u], input<int>()))
            graph[u][v] = graph[v][u];
    }

    int lim = 1 << n;

    for(int i = 1; i <= n; ++i)
        for(int u = 1; u < lim; ++u) {
            if(!(u & (u - 1))) f[1][u] = 0;
            if(!(u & (1 << (i - 1)))) for(int j = 1; j <= n; ++j)
                    if(u & (1 << (j - 1))) chkmin(h[i][u], graph[i][j]);
        }

    for(int u = 1, v, cost; u < lim; ++u)
        for(v = u - 1; v; v = u & (v - 1)) {
            cost = 0;
            for(int i = 1; i <= n; ++i) if((1 << (i - 1)) & v) {
                if(h[i][u ^ v] >= Inf) {cost = -1; break;}
                cost += h[i][u ^ v];
            } if(cost == -1) continue;

            for(int d = 2; d <= n; ++d)
                chkmin(f[d][u], f[d - 1][u ^ v] + cost * (d - 1));
        }


    int ans = Inf;
    for(int i = 1; i <= n; ++i) chkmin(ans, f[i][lim - 1]);

    printf("%d\n", ans);

    return 0;
}
