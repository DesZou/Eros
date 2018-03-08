#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>

#define x first
#define y second

using std::min;
using std::max;
using std::cin;
using std::pow;
using std::sqrt;
using std::cout;
using std::cerr;
using std::make_pair;

typedef std::pair<double, double> Point;

const char El = 10;
const int Size = 15 + 5;

template<class T>
bool chkmin(T &a, const T &b) {return a > b? a = b, 1 : 0;}

template<class T>
bool chkmax(T &a, const T &b) {return a < b? a = b, 1 : 0;}

int n;

Point a[Size];

bool vis[Size];

double dist[Size][Size];

double ans = std::numeric_limits<double>::infinity();

void dfs(const int ptr, const double len, const int tot) {
    if (len >= ans) return;
    if (tot == n) {
        chkmin(ans, len);
    } else {
        vis[ptr] = true;
        for (int i = 1; i <= n; ++i)
            if (!vis[i]) dfs(i, len + dist[i][ptr], tot + 1);
        vis[ptr] = false;
    }
}

int main() {
    cin.sync_with_stdio(0);

    cin >> n;

    for (int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].y;

    a[++n] = make_pair(0., 0.);

    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) if (i != j)
        dist[i][j] = dist[j][i] 
            = sqrt(pow(a[i].x - a[j].x, 2) + pow(a[i].y - a[j].y, 2));

    dfs(n, 0., 1);

    cout << std::fixed << std::setprecision(2) << ans << El;

    return 0;
}
