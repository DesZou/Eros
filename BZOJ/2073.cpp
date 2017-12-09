/***************
  **BZOJ2073**
  设f[s]为集合s全部过桥的最短时间。
  枚举s的子集q，当q的总重满足要求时
  f[s] = min(f[s], f[s - q] + t[q])
  其中t[q]代表集合q一次性过河所花的时间。
***************/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>

const int Bit = 16 + 1;
const size_t Size = 1 << Bit;

template<class T> bool chkmax(T &a, const T &b) {
    return a < b? a = b, 1 : 0;
}

template<class T> bool chkmin(T &a, const T &b) {
    return a > b? a = b, 1 : 0;
}

int w, n;

int f[Size], t[Size], d[Size];

int main() {
    scanf("%d%d", &w, &n);

    int lim = 1 << n;

    for(int i = 0, x, y; i < n; ++i) {
        scanf("%d%d", &x, &y);
        for(int u = (1 << i); u < lim; ++u)
            if(u & (1 << i)) chkmax(t[u], x), d[u] += y;
    }

    std::memset(f, 0x3f, sizeof f);

    f[0] = 0;

    for(int u = 1; u < lim; ++u)
        for(int v = u; v; v = (v - 1) & u)
            if(d[v] <= w) chkmin(f[u], f[u ^ v] + t[v]);

    printf("%d\n", f[lim - 1]);

    return 0;
}
