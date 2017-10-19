#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

// const int Inf = -1u >> 1;
// const size_t Size = 1e5 + 5;

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

template<class T> T multi(T a, T b, const T p) {
    T res = 0;
    while(b) {
        if(b & 1) res = (res + a) % p;
        a = (a << 1) % p, b >>= 1;
    } return res;
}

long long ans, n, p, tmp, a;

int main() {
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);

    n = input<long long>(), p = input<long long>();

    for(int i = 1; i <= n; ++i) {
        a = input<long long>() % p;
        tmp = (multi(tmp, a, p) + a) % p;
        ans = (ans + tmp) % p;
    }

    printf("%lld\n", ans);

    return 0;
}
