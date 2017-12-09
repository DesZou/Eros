#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

const size_t Size = 800 + 5;
const size_t Num = 15 + 5;
const int Mod = 1e9 + 7;

int n, m, k;

int a[Size][Size];

int f[Size][Size][Num][2];

inline int add(int x, int y) {
    return ((x + y) % k + k) % k;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);

    k = k + 1;

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
            f[i][j][a[i][j] %= k][0] = 1;
        }

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            for(int d = 0; d < k; ++d) {
                f[i][j][d][0] += f[i - 1][j][add(d, -a[i][j])][1];
                f[i][j][d][0] += f[i][j - 1][add(d, -a[i][j])][1];
                f[i][j][d][1] += f[i - 1][j][add(d, a[i][j])][0];
                f[i][j][d][1] += f[i][j - 1][add(d, a[i][j])][0];
                f[i][j][d][0] %= Mod;
                f[i][j][d][1] %= Mod;
            }

    int ans = 0;

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            ans = (ans + f[i][j][0][1]) % Mod;

    printf("%d\n", ans);

    return 0;
}
