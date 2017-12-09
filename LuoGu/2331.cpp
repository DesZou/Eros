/**
  luogu2331
  一开始没注意到宽度最大只有二。
  注意数组初始化为负无穷即可。
 **/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>

const size_t Size = 100 + 5;
// const int Inf = -1u >> 1;

template<class T> T max(const T &a, const T &b) {
    return a > b? a : b;
}

template<class T> T min(const T &a, const T &b) {
    return a < b? a : b;
}

template<class T> bool chkmin(T &a, const T &b) {
    return a > b? a = b, 1 : 0;
}

template<class T> bool chkmax(T &a, const T &b) {
    return a < b? a = b, 1 : 0;
}

template<class T> T input() {
    T r(0); char c(getchar()); bool n(false);
    while(c > '9' || c < '0') {if(c == '-') n = true; c = getchar();}
    while(c <= '9' && c >= '0') {r = r * 10 - 48 + c, c = getchar();}
    return n? -r : r;
}

int n, m, k;

int a[Size][3];

int f[Size][11][2][2][2];

int g[Size][11][2];

int main() {
    n = input<int>(), m = input<int>(), k = input<int>();
    
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            a[i][j] = input<int>();
            
    if(m == 1) {
        int ans = 0;
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= k; ++j) {
                chkmax(g[i][j][0], max(g[i - 1][j][0], g[i - 1][j][1]));
                chkmax(g[i][j][1], max(g[i - 1][j][1], g[i - 1][j - 1][0]) + a[i][1]);
                chkmax(ans, max(g[i][j][0], g[i][j][1]));
            }
        printf("%d\n", ans);
        return 0;
    }
            
    std::memset(f, -0x7f, sizeof f);

    f[1][0][1][0][0] = 0;
    f[1][1][0][1][0] = a[1][1];
    f[1][1][0][0][1] = a[1][2];

    for(int i = 2; i <= n; ++i)
        for(int j = 1; j <= k; ++j) {
            f[i][j][1][0][0] = max(f[i - 1][j][0][1][0],
                               max(f[i - 1][j][0][0][1],
                               max(f[i - 1][j][0][1][1],
                               max(f[i - 1][j][1][0][0],
                               max(f[i - 1][j][1][1][0],
                               max(f[i - 1][j][1][1][1], f[i - 1][j][1][0][1]))))));
            f[i][j][1][1][0] = max(f[i - 1][j][1][1][0], f[i - 1][j - 1][1][1][1]) + a[i][1];
            f[i][j][1][0][1] = max(f[i - 1][j][1][0][1], f[i - 1][j - 1][1][1][1]) + a[i][2];
            f[i][j][1][1][1] = max(f[i - 1][j - 1][1][0][0], f[i - 1][j][1][1][1]) + a[i][1] + a[i][2];
            f[i][j][0][1][0] = max(f[i - 1][j][0][1][0],
                               max(f[i - 1][j - 1][1][0][0],
                               max(f[i - 1][j][0][1][1],
                               max(f[i - 1][j - 1][1][0][1], f[i - 1][j - 1][0][0][1])))) + a[i][1];
            f[i][j][0][0][1] = max(f[i - 1][j][0][0][1],
                               max(f[i - 1][j - 1][1][0][0],
                               max(f[i - 1][j][0][1][1],
                               max(f[i - 1][j - 1][1][1][0], f[i - 1][j - 1][0][1][0])))) + a[i][2];
            f[i][j][0][1][1] = max(f[i - 1][j][0][1][1],
                               max(f[i - 1][j - 1][1][1][0],
                               max(f[i - 1][j - 1][1][0][1],
                               max(f[i - 1][j - 1][0][1][0], f[i - 1][j - 1][0][0][1])))) + a[i][1] + a[i][2];
                             /*  
            std::cerr << f[i][j][1][0][0] << " "
                      << f[i][j][1][1][0] << " "
                      << f[i][j][1][0][1] << " "
                      << f[i][j][1][1][1] << " "
                      << f[i][j][0][1][0] << " "
                      << f[i][j][0][0][1] << " "
                      << f[i][j][0][1][1] << std::endl;
                      */
    }
    
    int ans = 0;
    for(int i = 1; i <= k; ++i) {
        chkmax(ans, max(f[n][i][1][0][0],
                    max(f[n][i][1][1][0],
                    max(f[n][i][1][0][1],
                    max(f[n][i][1][1][1],
                    max(f[n][i][0][1][0],
                    max(f[n][i][0][0][1], f[n][i][0][1][1])))))));
    }

    printf("%d\n", ans);

    return 0;
}
