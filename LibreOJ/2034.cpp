#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>


const long long Mod = 1e9 + 7;
const size_t Size = 1e6 + 5;

template<class T> T input() {
    T res = 0; char c = getchar(); bool nega = 0;
    while(c > '9' || c < '0') {if(c == '-') nega = 1; c = getchar();}
    while(c >= '0' && c <= '9') {res = res * 10 - 48 + c, c = getchar();}
    return nega? -res : res;
}

template<class T> T multi(T a, T b) {
    T res = 0;
    while(b) {
        if(b & 1) res = (res + a) % Mod;
        a = (a << 1) % Mod, b >>= 1;
    } return res;
}

template<class T> T power(T a, T b) {
    T res = 1;
    while(b) {
        if(b & 1) res = (res * a) % Mod;
        a = (a * a) % Mod, b >>= 1;
    } return res;
}

int T, n, m;

long long d[Size], inv[Size];

long long C(long long y, long long x) {
    return inv[y] * power(inv[x], Mod - 2) % Mod * power(inv[y - x], Mod - 2) % Mod;
}

long long D(int x) {
    return d[x];
}

inline void init() {
    d[1] = 0, d[0] = d[2] = 1; // caution: d[0] must be 1.
    for(int i = 3; i < Size; ++i)
        d[i] = (i - 1) * ((d[i - 1] + d[i - 2]) % Mod) % Mod;
    inv[0] = inv[1] = 1;
    for(int i = 2; i < Size; ++i)
        inv[i] = inv[i - 1] * i % Mod;
}

int main() {
    init();

    for(scanf("%d", &T); T; --T) {
        n = input<int>(), m = input<int>();
        printf("%lld\n", C(n, m) * D(n - m) % Mod);
    }

    return 0;
}
