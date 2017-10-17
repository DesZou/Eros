#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

const int Inf = 0x3f3f3f3f;
const size_t Size = 5e5 + 5;

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

struct Data {int x, y;} d[Size];

bool operator<(const Data &a, const Data &b) {
    return a.x < b.x;
}

double fig(const Data &a, const Data &b) {
    return (double)(b.y - a.y) / (b.x - a.x);
}

int n;

double ans = -Inf;

int main() {
    freopen("slope.in", "r", stdin);
    freopen("slope.out", "w", stdout);

    n = input<int>();

    for(int i = 1; i <= n; ++i)
        d[i].x = input<int>(), d[i].y = input<int>();

    std::sort(d + 1, d + 1 + n);

    for(int i = 1; i < n; ++i)
        chkmax(ans, fig(d[i], d[i + 1]));

    printf("%.3lf", ans);

    return 0;
}
