#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

// const int Inf = -1u >> 1;
const size_t size = 2e5 + 5;

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

int n;

struct Data {int p, c, id;} d[size];

bool operator<(const Data &a, const Data &b) {
    return a.c < b.c;
}

bool vis[size];

int main() {
    freopen("knows.in", "r", stdin);
    freopen("knows.out", "w", stdout);

    n = input<int>();

    for(int i = 1; i <= n; ++i) d[i].p = input<int>();
    for(int i = 1; i <= n; ++i) d[i].c = input<int>();
    for(int i = 1; i <= n; ++i) d[i].id = i;

    std::sort(d + 1, d + 1 + n);
    
    int ans = 0, total = 0;

    for(int i = 1; i <= n && total < n; ++i) if(!vis[d[i].id]) {
        ans += d[i].c, vis[d[i].id] = true, ++total;
        for(int j = 1; j <= n; ++j) {
            if((d[j].id > d[i].id) ^ (d[j].p > d[i].p))
                vis[d[j].id] = true, ++total;
        }
    }

    printf("%d\n", ans);

    return 0;
}
