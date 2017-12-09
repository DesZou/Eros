#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>

const size_t Size = 3e3 + 5;

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

struct Edge {int next, to, cost;} e[Size];

int f[Size][Size];

int head[Size];

int n, m;

void insert(int u, int v, int w) {
    static int _Index = 0;
    e[++_Index] = (Edge){head[u], v, w};
    head[u] = _Index;
}

int dfs(int x) {
    if(x > n - m) return 1;

    int sum = f[x][0] = 0;

    for(int i = head[x], tmp; i; i = e[i].next) {
        sum += tmp = dfs(e[i].to);
        for(int k = sum; k; --k)
            for(int j = 1; j <= tmp && j <= k; ++j)
                chkmax(f[x][k], f[x][k - j] + f[e[i].to][j] - e[i].cost);
    } return sum;
}

int bin_search(int l, int r) {
    while(l < r) {
        int mid = (l + r) >> 1;
        if(f[1][mid] >= 0) l = mid;
        else r = mid - 1;
    } return l;
}

int main() {
    std::memset(f, -0x3f, sizeof f);

    n = input<int>(), m = input<int>();

    for(int k, a, c, i = 1; i <= n - m; ++i) {
        k = input<int>();
        for(int j = 0; j < k; ++j) {
            a = input<int>(), c = input<int>();
            insert(i, a, c);
        }
    }

    for(int i = n - m + 1; i <= n; ++i)
        f[i][1] = input<int>();
    
    int ans = dfs(1);

    while(f[1][ans] < 0) --ans;

    printf("%d\n", ans);

    return 0;
}
