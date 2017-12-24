/*
 * libreoj124
 *
 * 线性筛求积性函数的前缀和。
 * */
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>

const long long Mod = 1e9 + 7;
const size_t Size = 1e7 + 5;

template<class T> T power(T a, T b, T p) {
    T res = 1;
    for(; b; a = (a * a) % p, b >>= 1)
        if(b & 1) res = (res * a) % p;
    return res;
}

bool vis[Size];

long long sigma[Size], g[Size], f[Size], prime[Size], p[Size];

int num;

int main() {
    long long n, k, ans = sigma[1] = 1;
    std::scanf("%lld%lld", &n, &k);

    for(long long i = 2; i <= n; ++i) {
        if(!vis[i]) {
           p[++num] = power(i, k, Mod);
           g[i] = 1;
           f[i] = sigma[i] = 1 + p[num];
           prime[num] = i;
        } ans = (ans + sigma[i]) % Mod;
        for(long long j = 1, u = n / i, v; j <= num && prime[j] <= u; ++j) {
            vis[v = i * prime[j]] = true;
            if(i % prime[j] == 0) {
                g[v] = g[i];
                f[v] = (f[i] * p[j] + 1ll) % Mod;
                sigma[v] = g[v] * f[v] % Mod;
                break;
            } else {
                g[v] = sigma[i];
                f[v] = 1 + p[j];
                sigma[v] = sigma[i] * (p[j] + 1) % Mod;
            }
        }
        std::cerr << i << " " << g[i] << " " << f[i] << " " << sigma[i] << std::endl;
    }

    std::printf("%lld\n", ans);

    return 0;
}
