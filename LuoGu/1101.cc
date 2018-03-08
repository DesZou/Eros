#include <cstdio>
#include <cctype>
#include <cstring>
#include <cmath>
#include <algorithm>

using std::max;
using std::min;

const char str[] = "yizhong";
const int dx[] = { 0, 0, 1, 1, 1, -1, -1, -1 };
const int dy[] = { 1, -1, 0, -1, 1, 0, -1, 1 };
const int Size = 100 + 5;

int n;

char m[Size][Size];
bool vis[Size][Size];

bool dfs(int x, int y, int d, int l) {
    if (m[x][y] == str[l]) {
        if (l == 6) {
            return vis[x][y] = true;
        } else {
            bool res = dfs(x + dx[d], y + dy[d], d, l + 1);
            vis[x][y] |= res;
            return res;
        }
    } else return false;
}

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            do { m[i][j] = getchar(); }
            while (!isalpha(m[i][j]));

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (m[i][j] == 'y')
                for (int k = 0; k < 8; ++k)
                    dfs(i, j, k, 0);

    for (int i = 1; i <= n; ++i, putchar(10))
        for (int j = 1; j <= n; ++j)
            printf("%c", vis[i][j]? m[i][j] : '*');

    return 0;
}
