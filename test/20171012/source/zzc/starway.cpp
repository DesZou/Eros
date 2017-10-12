#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>

const int Inf = -1u >> 1;
const int size = 6e3 + 5;

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

struct Data {int x, y;} s[size];

int fa[size];

bool vis[size];

double mindist[size];

int n, m, k, upbound, lowbound;

inline double dis(const Data &a, const Data &b) {
    double dx = std::abs(a.x - b.x);
    double dy = std::abs(a.y - b.y);
    return std::hypot(dx, dy);
}

inline double dis(const int &a, const int &b) {
    if(a > n && b > n) return m;
    else if(a == upbound) return s[b].y;
    else if(a == lowbound) return m - s[b].y;
    else if(b == upbound) return s[a].y;
    else if(b == lowbound) return m - s[a].y;
    else return dis(s[a], s[b]);
}

int find(int x) {
    while(fa[x] != fa[fa[x]]) fa[x] = fa[fa[x]];
    return fa[x];
}

void add(int x) {
    fa[find(x)] = find(upbound), vis[x] = true;
    for(int i = k; i; --i) if(!vis[i]) chkmin(mindist[i], dis(i, x));
}

double prim() {
    double res = 0;

    std::fill(mindist, mindist + k + 1, Inf);

    add(upbound);

    while(find(upbound) != find(lowbound)) {
        int temp = 0;
        for(int i = k; i; --i) {
            if(!vis[i] && mindist[temp] > mindist[i]) temp = i;
        }
        add(temp);
        chkmax(res, mindist[temp]);
    } return res / 2;
}

int main() {
    freopen("starway.in", "r", stdin);
    freopen("starway.out", "w", stdout);

    n = input<int>(), m = input<int>(), k = input<int>();

    for(int i = 1; i <= k; ++i)
        s[i].x = input<int>(), s[i].y = input<int>();

    upbound = ++k, lowbound = ++k;

    int a, b;

    for(int i = 1; i <= k; ++i) fa[i] = i;

    printf("%.8lf", prim());

    return 0;
}
