/*
 * luogu3396
 *
 * 只预处理前根号个模数，
 * 对于后面的模数暴力求答案，也不会超过根号个数。
 * 修改也只用修改前根号个数，总时间复杂度O(√n)
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <typeinfo>

const size_t Size = 150000 + 5;
const size_t Scale = 400;

int n, m, x, y;

char cmd;

int value[Size];

int ans[Scale][Scale];

int query(const int x, const int y) {
    if(x < Scale) {
        return ans[x][y];
    } else {
        int res = 0;
        for(int i = y; i <= n; i += x) res += value[i];
        return res;
    }
}

void modify(const int x, const int y) {
    for(int p = 1; p < Scale; ++p)
        ans[p][x % p] += y - value[x];
    value[x] = y;
}

void init() {
    for(int i = 1; i <= n; ++i)
        for(int p = 1; p < Scale; ++p)
            ans[p][i % p] += value[i];
}

int main() {
    std::scanf("%d%d", &n, &m);

    for(int i = 1; i <= n; ++i) std::scanf("%d", value + i);

    init();

    for(int i = 1; i <= m; ++i) {
        std::scanf(" %c%d%d", &cmd, &x, &y);
        if(cmd == 'A') {
            std::printf("%d\n", query(x, y));
        } else {
            modify(x, y);
        }
    }

    return 0;
}
