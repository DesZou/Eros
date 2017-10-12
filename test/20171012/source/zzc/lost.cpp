#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
#include <vector>
#include <queue>

const int Inf = -1u >> 1;
const double Eps = 1e-8;
const int Log = 20;
const size_t size = 5e5 + 5;

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
    while(c >= '0' && c <= '9') {res = res * 10 - 48 + c, c = getchar();}
    return nega? -res : res;
}
int fa[size];

int c[size];

int l[size];

int depth[size];

double ans[size];

std::vector<int> ch[size];

std::queue<int> q;

int n;

int f[size][Log];

inline double fig(const int x, const int y) {
    return (double)(c[x] - c[y]) / (depth[x] - depth[y]);
}

void bfs() {
    q.push(1);

    while(!q.empty()) {
        int x = q.front(); q.pop();
        int y = x;
        depth[x] = depth[fa[x]] + 1;
        l[x] = f[x][0] = fa[x];

        for(int i = 1; i <= 16; ++i) f[x][i] = f[f[x][i - 1]][i - 1];

        for(int i = 16; i >= 0; --i) {
            int z = f[y][i];
            if(!l[z]) continue;
            if(fig(l[z], z) > fig(z, x)) y = z;
        }

        y = l[y], l[x] = f[x][0] = y, ans[x] = -fig(x, y);

        for(int i = 1; i <= 16; ++i) f[x][i] = f[f[x][i - 1]][i - 1];
        for(int i = ch[x].size() - 1; i >= 0; --i) q.push(ch[x][i]);
    }
}

int main() {
    freopen("lost.in", "r", stdin);
    freopen("lost.out", "w", stdout);

    n = input<int>();

    for(int i = 1; i <= n; ++i) c[i] = input<int>();

    for(int i = 2; i <= n; ++i) {
        fa[i] = input<int>();
        ch[fa[i]].push_back(i);
    }

    bfs();

    for(int i = 2; i <= n; ++i) printf("%.8lf\n", std::fabs(ans[i]) < Eps?
            std::fabs(ans[i]) : ans[i]);

    return 0;
}
