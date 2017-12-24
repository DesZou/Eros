/*
 * luogu2736
 *
 * DP DP DP
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

const size_t Size = 20 + 5;

int f[Size][Size][Size];

int l[Size];

int main()
{
    int n, m, t;

    std::cin >> n >> t >> m;

    for(int i = 1; i <= n; ++i) std::cin >> l[i];

    int ans = 0;

    for(int j = 1; j <= m; ++j)
        for(int k = 1; k <= t; ++k)
            for(int i = 1; i <= n; ++i)
            {
                f[i][j][k] = std::max(f[i][j][k - 1], f[i - 1][j][k]);
                f[i][j][k] = std::max(f[i][j][k], f[i][j - 1][t]);
                if(k >= l[i])
                {
                    f[i][j][k] = std::max(f[i][j][k], f[i - 1][j][k - l[i]] + 1);
                    f[i][j][k] = std::max(f[i][j][k], f[i - 1][j - 1][t] + 1);
                }
                ans = std::max(ans, f[i][j][k]);
            }

    std::cout << ans << std::endl;

    return 0;
}
