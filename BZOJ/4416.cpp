/**
    bzoj4416
    设f[s]为存在s集合中的元素的全排列的结尾位置。
    g[i][j]为i位置之后最近的一个j字母的位置。
    f[s] = max{ g[f[s - p][p] }，其中p是枚举的s中的每一个字母。
    如果f[all]的值大于给定序列的长度则不是阶乘字符串，否则就是。
    另外，当n>21时必定不是。大概证明：当C(n, len)<n!时，肯定是
    凑不出全排列的。
 **/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <iostream>

const int Bit = 21 + 1;
const size_t Size = 1 << Bit;
const size_t Length = 450 + 5;

template<class T> bool chkmax(T &a, const T &b) {
    return a < b? a = b, 1 : 0;
}

template<class T> bool chkmin(T &a, const T &b) {
    return a > b? a = b, 1 : 0;
}

int n, len, T, lim;

char s[Length];

int f[Size], g[Length][Bit];

inline int k(const int &x) {
    return __builtin_ctz(x);
}

int main() {
    for(scanf("%d", &T); T --> 0;) {
        std::memset(f, 0, sizeof f);

        scanf("%d%s", &n, s + 1);
        if(n > 21) {puts("NO"); continue;}
        
        len = std::strlen(s + 1);
        lim = 1 << n;

        for(int i = 1; i <= len; ++i) s[i] -= 'a';
        s[len + 1] = n;
        
        std::fill(g[len], g[len] + n, len + 1);
        std::fill(g[len + 1], g[len + 1] + n, len + 1);

        for(int i = len - 1; i >= 0; --i) {
            std::memcpy(g[i], g[i + 1], sizeof g[i]);
            g[i][(int)s[i + 1]] = i + 1;
        }

        for(int u = 1; u < lim; ++u)
            for(int v = u, p = v & -v; v; v -= p, p = v & -v)
                chkmax(f[u], g[f[u ^ p]][k(p)]);

        puts(f[lim - 1] <= len? "YES" : "NO");
    }
    return 0;
}
