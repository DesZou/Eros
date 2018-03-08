#include <cstdio>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <limits>

using std::cin;
using std::cout;

template<class T>
bool chkmin(T &a, const T &b) { return a > b? a = b, 1 : 0; }

template<class T>
bool chkmax(T &a, const T &b) { return a < b? a = b, 1 : 0; }

const char el = '\n';
const int SizeN = 1000 + 5;
const int SizeM = 1e5 + 5;
const int Inf = std::numeric_limits<int>::max();
const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

int n, m;

char graph[SizeN][SizeN];
int belong[SizeN][SizeN];

int num[SizeM], _Index;

bool inBound(int x, int y) { return x > 0 && x <= n && y > 0 && y <= n; }

void dfs(int x, int y, int l) {
    ++num[belong[x][y] = l];
    for (int i = 0, nx, ny; i < 4; ++i)
        if (inBound(nx = x + dx[i], ny = y + dy[i])
                && graph[nx][ny] != graph[x][y] && !belong[nx][ny]) {
            dfs(nx, ny, l);
        }
}

int ans(int x, int y) {
    if (!belong[x][y]) dfs(x, y, ++_Index);
    return num[belong[x][y]];
}

int main() {
    cin.sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> graph[i][j];


    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y;
        cout << ans(x, y) << '\n';
    }

    return 0;
}
