/**
  luogu2051
  根据题意可知，每行每列最多只能放两个炮。
  那么设f[i][j][k]为当前位于第i行，有j*列*放了一个炮，
  k列放了两个炮的合法状态数。转移方程有六个，分别是
  这行不放新的炮、放一个炮在空列上，放两个炮在空列上、
  放一个炮在有一个炮的列上、放两个炮在有一个炮的列上、
  放两个炮分别在有一个炮的列和空列上。
  最后答案是最后一行的所有状态之和。
 **/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const size_t Size = 100 + 5;
const int Mod = 9999973;

int n, m;
long long ans;

long long f[Size][Size][Size];

inline void add(long long &x, long long y) {
    x = (x + y) % Mod;
}

int main() {
    scanf("%d%d", &n, &m);

    f[0][0][0] = 1;

    for(int i = 1; i <= m; ++i)
        for(int j = 0; j <= n; ++j)
            for(int k = n - j; k >= 0; --k) {
                long long &x = f[i][j][k], y = n - j - k;
                add(x, f[i - 1][j][k]);
                if(k > 0) add(x, f[i - 1][j + 1][k - 1] * (j + 1));
                if(j > 0) add(x, f[i - 1][j - 1][k] * (y + 1));
                if(j > 1) add(x, f[i - 1][j - 2][k] * (y + 2) * (y + 1) / 2);
                if(k > 1) add(x, f[i - 1][j + 2][k - 2] * (j + 2) * (j + 1) / 2);
                if(k > 0) add(x, f[i - 1][j][k - 1] * j * (y + 1));
            }

    for(int k = 0; k <= n; ++k)
        for(int j = 0; j <= n - k; ++j)
            add(ans, f[m][k][j]);

    printf("%lld\n", ans);

    return 0;
}
