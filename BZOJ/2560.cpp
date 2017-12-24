/*
 * bzoj2560
 *
 * 枚举子集，要注意的是每次分成两边。
 * 一边包括所有边的状况，一边只能是合法状况。
 * 至于为什么，我不知道。。。
 * */
#include <cstdio>
#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>

const size_t Size = 16 + 1;
const int Mod = 1e9 + 7;

int n, lim;

long long f[1 << Size];
long long g[1 << Size];

long long c[Size][Size];

int main() {
    scanf("%d", &n);

    lim = 1 << n;

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            scanf("%lld", &c[i][j]);

    for(int u = 1; u < lim; ++u) {
        for(int i = g[u] = 1; i <= n; ++i) if((1 << (i - 1)) & u)
            for(int j = i + 1; j <= n; ++j) if((1 << (j - 1)) & u)
                g[u] = (g[u] * (c[i][j] + 1)) % Mod;
        f[u] = g[u];
        int xk = u - (u & -u);
        for(int v = xk; v; v = xk & (v - 1))
            std::cerr << "subset: " << std::bitset<3>(v) << std::endl,
            f[u] = (f[u] - (g[v] * f[u ^ v] % Mod)) % Mod;
        std::cerr << "set[" << std::bitset<3>(u)
                  << "] f := " << f[u] << " g := " << g[u] << std::endl;
    }

    printf("%lld\n", (f[lim - 1] % Mod + Mod) % Mod);

    return 0;
}
