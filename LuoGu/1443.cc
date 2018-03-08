#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <algorithm>

using std::max;
using std::min;
using std::cerr;
using std::cin;
using std::cout;
using std::make_pair;

typedef std::pair<int, int> Point;
typedef std::pair<std::pair<int, int>, int> Data;

const int Size = 400 + 5;
const int Inf = 0x7f7f7f7f;
const int dx[] = { -2, -2, -1, -1, 1, 1, 2, 2 };
const int dy[] = { 1, -1, 2, -2, 2, -2, 1, -1 };

int n, m, s, t;

Data q[Size * Size * 2];
int front, back;
int ans[Size][Size];

bool inBound(int x, int y) {
    return x > 0 && x <= n && y > 0 && y <= m;
}

void bfs(Point st) {
    q[front = 0] = make_pair(st, 0); back = 1;

    Data tmp;
    Point &now = tmp.first;

    while (front < back) {
        tmp = q[front++];
        ans[now.first][now.second] = tmp.second;
        for (int i = 0, nx, ny; i < 8; ++i) if (inBound(nx = now.first + dx[i], ny = now.second + dy[i])
                    && ans[nx][ny] == Inf) {
                q[back++] = make_pair(make_pair(nx, ny), tmp.second + 1);
                ans[nx][ny] = tmp.second + 1;
            }
    }
}

int main() {
    cin.sync_with_stdio(false);
    memset(ans, 0x7f, sizeof ans);
    cin >> n >> m >> s >> t;

    bfs(make_pair(s, t));

    for (int i = 1; i <= n; ++i, cout << '\n')
        for (int j = 1; j <= m; ++j)
            cout << std::left << std::setw(5)
                << (ans[i][j] == Inf? -1 : ans[i][j]);

    return 0;
}
