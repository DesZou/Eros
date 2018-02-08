/*
  luogu 2292

  trie 树
 */
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>

const size_t Size = 5e5 + 5;

int n, m;

struct Node {
    int ch[2], sum, end;
} c[Size];

int _Index = 1;

int main() {
    std::scanf("%d%d", &m, &n);

    for(int i = 1, k, now; i <= m; ++i) {
        std::scanf("%d", &k);

        for(int j = now = 1, tmp; j <= k; ++j) {
            std::scanf("%1d", &tmp);
            if(c[now].ch[tmp]) now = c[now].ch[tmp];
            else now = c[now].ch[tmp] = ++_Index;
            ++c[now].sum;
        } ++c[now].end;
    }

    for(int i = 1, k, now, ans; i <= n; ++i) {
        std::scanf("%d", &k);

        ans = 0;
        for(int j = now = 1, tmp; j <= k; ++j) {
            std::scanf("%1d", &tmp);
            now = c[now].ch[tmp]? c[now].ch[tmp] : 0; // maybe touch the end
            ans += c[now].end;
        }
        std::printf("%d\n", ans + c[now].sum - c[now].end);
    }

    return 0;
}
