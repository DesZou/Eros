/*
  luogu2473

  概率DP+状压，考虑逆推出解。
  设f[i][U]第1到i-1轮已经有集合U所表示的宝物被取到过，第i到最后一轮能得到的最大收益。
  则f[i][U] = max{f[i + 1][U], f[i + 1][U + k] + p[k]}
  其中k是我们枚举的点，表示第i轮抽到了k。而我们也可以选择放弃该轮。
  并且要满足U包含了k的所有前提条件，不然只能选择放弃。
  每次从n个点等概率转移，每转移一轮，f就要除掉n。
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const size_t Bit = 15 + 1;
const size_t Size = 1 << Bit;
const size_t Round = 100 + 5;
const int Inf = 0x3f3f3f3f;

double f[Round][Size];
int p[Bit];
int s[Bit];
int n, k, lim;

int main(void) {
    std::scanf("%d%d", &k, &n);

    lim = (1 << n);

    for(int i = 1, j; i <= n; ++i) {
        std::scanf("%d", p + i);
        while(std::scanf("%d", &j), j)
            s[i] |= (1 << (j - 1));
    }

    for(int i = k; i > 0; --i)
        for(int u = 0; u < lim; ++u) {
            for(int k = 1; k <= n; ++k)
                f[i][u] += std::max(f[i + 1][u],
                                    ((s[k] & u) == s[k])?
                                    f[i + 1][u | (1 << (k - 1))] + p[k] :
                                    -Inf);
            f[i][u] /= n;
        }

    std::printf("%.6lf\n", f[1][0]);

    return 0;
}
