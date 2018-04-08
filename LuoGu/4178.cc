/*
 *  luogu4178
 *
 *  点分治，考虑计算每个点到当前重心的距离。
 *  每次把距离求出来，然后排序，可以用尺取法在线性时间内求出满足条件的点对数。
 *  但是有可能两个点来自同一棵子树，那样会算重，需要在分治下去的时候减掉。
 *  复杂度 O(n log^2 n)
 * */
#include <iostream>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <vector>

using std::cin;
using std::cout;
using std::cerr;

template<class T>
bool chkmin(T &a, const T &b) { return a > b? a = b, 1 : 0; }

template<class T>
bool chkmax(T &a, const T &b) { return a < b? a = b, 1 : 0; }

const char El = 10;
const int Size = 4e4 + 5;

struct Edge { int to, len; };
std::vector<Edge> e[Size];
std::vector<int> tmp;
int n, k, ans, center;
int sum, cenSum;
int size[Size];
bool vis[Size];

void dfs(const int x, const int len) {
    vis[x] = true;
    tmp.push_back(len);
    for (std::vector<Edge>::iterator
         i = e[x].begin(); i != e[x].end(); ++i)
        if (!vis[i->to]) dfs(i->to, len + i->len);
    vis[x] = false;
}

int calc(const int x, const int initVal) {
    tmp.clear();
    dfs(x, initVal);
    std::sort(tmp.begin(), tmp.end());

    int res = 0;
    for (int l = 0, r = tmp.size() - 1; l < r;)
        (tmp[l] + tmp[r] <= k)? res += r - l++ : --r;
    return res;
}

void getCenter(const int x) {
    int cnt = 0;
    size[x] = 1;
    vis[x] = true;
    for (std::vector<Edge>::iterator
         i = e[x].begin(); i != e[x].end(); ++i)
        if (!vis[i->to]) {
            getCenter(i->to);
            size[x] += size[i->to];
            chkmax(cnt, size[i->to]);
        }
    vis[x] = false;
    chkmax(cnt, sum - size[x]);
    if (chkmin(cenSum, cnt)) center = x;
}

void partialSolve(const int x) {
    ans += calc(x, 0);
    vis[x] = true;
    for (std::vector<Edge>::iterator
         i = e[x].begin(); i != e[x].end(); ++i)
        if (!vis[i->to]) {
            ans -= calc(i->to, i->len);
            sum = cenSum = size[i->to];
            getCenter(i->to);
            partialSolve(center);
        }
}

int main() {
    cin.sync_with_stdio(0);

    cin >> n;

    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w;
        e[u].push_back((Edge){ v, w });
        e[v].push_back((Edge){ u, w });
    }

    cin >> k;

    sum = cenSum = n;
    getCenter(1);
    partialSolve(center);

    cout << ans << El;

    return 0;
}
