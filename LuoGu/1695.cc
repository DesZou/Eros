#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using std::max;
using std::min;
using std::cerr;
using std::endl;
using std::swap;

template<class T> bool chkmin(T &a, const T &b) {
    return a > b? a = b, 1 : 0;
}

template<class T> bool chkmax(T &a, const T &b) {
    return a < b? a = b, 1 : 0;
}

const int Size = 1e5 + 5;

int prime[Size];
bool np[Size];
int mu[Size];
int sumMu[Size];

void eulerSieve() {
    mu[1] = 1;
    for(int i = 2; i < Size; ++i) {
        if(!np[i]) prime[++(*prime)] = i, mu[i] = -1;
        for(int j = 1, k; j <= *prime && (k = i * prime[j]) < Size; ++j) {
            np[k] = true;
            if(i % prime[j] == 0) { mu[k] = 0; break; }
            mu[k] = -mu[i];
        }
    }
}

int b, d, k;

int main() {
    int T;
    scanf("%d", &T);

    eulerSieve();

    for(int i = 1; i < Size; ++i) {
        sumMu[i] = sumMu[i - 1] + mu[i];
    }

    for(int i = 1; i <= T; ++i) {
        scanf("%d%d%d", &b, &d, &k);

        b /= k, d /= k;
        if(b > d) swap(b, d);

        long long sum = 0;

        for(int j = 1, l; j <= b; j = l + 1) {
            l = min(b / (b / j), d / (d / j));
            sum += (long long)(sumMu[l] - sumMu[j - 1]) * (b / j) * (d / j);
        }

        printf("%lld\n", sum);
    }

    return 0;
}
