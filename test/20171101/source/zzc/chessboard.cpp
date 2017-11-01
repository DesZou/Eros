#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const size_t Size = 8 + 2;
const int Mod = 1e9 + 7;

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
    T r(0); char c(getchar()); bool n(false);
    while(c > '9' || c < '0') {if(c == '-') n = true; c = getchar();}
    while(c <= '9' && c >= '0') {r = r * 10 - 48 + c, c = getchar();}
    return n? -r : r;
}

long long f[Size][1 << Size];

int graph[Size], bit[Size], n;

long long ans[Size];

int main() {
    freopen("chessboard.in", "r", stdin);
    freopen("chessboard.out", "w", stdout);

    n = input<int>();
    
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) {
            static char c;
            do {c = getchar();} while(c != 'o' && c != '*');
            if(c == '*') graph[i] |= (1 << (j - 1));
        }

    ans[1] = 1, bit[0] = 1;
    
    for(int upper = 2, lim; upper < n + 2; ++upper) {
        std::memset(f, 0, sizeof f);
        for(int i = 1; i <= n; ++i) bit[i] = bit[i - 1] * upper;
        lim = 0, f[0][0] = 1;
        for(int i = 1; i + upper - 1 <= n; ++i) 
            lim = lim * upper + (upper - 1);

        for(int i = 0; i < n; ++i) {
            for(int status = 0; status <= lim; ++status) if(f[i][status]) {
                for(int k = 0; k < (1 << n); ++k) {
                    if(graph[i + 1] & k) continue;
                    int nxtsta = 0; bool flag = false;

                    for(int j = 1; j + upper - 1 <= n; ++j) {
                        int choice = (k >> (j - 1));
                        int now = status / bit[j - 1] % upper;

                        now = ((choice & (1 << upper) - 1) == ((1 << upper) - 1))? ++now : 0;
                        if(now >= upper) {flag = true; break;}

                        nxtsta += now * bit[j - 1];
                    }
                    if(!flag) {
                        f[i + 1][nxtsta] = (f[i + 1][nxtsta] + f[i][status]) % Mod;
                    }
                }
            }
        }
        for(int status = 0; status <= lim; ++status)
            ans[upper] = (ans[upper] + f[n][status]) % Mod;
    }

    for(int i = 1; i <= n + 1; ++i)
        printf("%lld\n", (ans[i] - ans[i - 1] + Mod) % Mod);

    return 0;
}
