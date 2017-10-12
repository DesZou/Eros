#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--) 
#define Rep(i,a) for(int i = 0; i < a; i++)
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define ab(x) ((x) < 0 ? -(x) : (x))
using namespace std;
typedef long long LL;
typedef map<int, int>::iterator mit;
typedef set<int>::iterator sit;
const int N = 6010;
int n, m, k, x[N], y[N];
LL dis(int a, int b) {
    if (a > b) swap(a, b);
    if (a == k + 1 && b == k + 2) return 1LL * m * m;
    else if (b == k + 1) return 1LL * (m - y[a]) * (m - y[a]);
    else if (b == k + 2) return 1LL * y[a] * y[a];
    else return 1LL * (x[a] - x[b]) * (x[a] - x[b]) + 1LL * (y[a] - y[b]) * (y[a] - y[b]); 
}


int f[N];
inline int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

struct edge{ int to, pre; LL c; } e[N << 1]; int u[N], l = 0;
void ins(int a, int b, int c) { e[++l] = (edge){b, u[a], c}, u[a] = l; }
void insert(int a, int b, int c) { ins(a, b, c), ins(b, a, c); }
#define v e[i].to
#define ec e[i].c
#define reg(i,a) for(int i = u[a]; i; i = e[i].pre)

LL d[N]; int fr[N];

LL ans = 0;
void dfs(int x, int f, LL c) {
    if (x == k + 2) { ans = c; }
    else reg(i,x) if (v != f) dfs(v, x, max(c, ec));
}

int main() {
    scanf("%d%d%d",&n,&m,&k);
    rep(i,1,k) scanf("%d%d",x + i, y + i);
    rep(i,1,k + 2) f[i] = i;
    const LL inf = 1LL * m * m + 10;
    rep(i,1,k + 2) d[i] = inf; d[k + 1] = 0;
    static bool vis[N];
    rep(t,1,k + 2) {
        LL mn = inf; int x = 0;
        rep(i,1,k + 2) if (d[i] < mn && !vis[i]) mn = d[i], x = i;
        if (fr[x]) insert(fr[x], x, d[x]);
        vis[x] = true; 
        rep(i,1,k + 2) if (!vis[i] && dis(x, i) < d[i])
            d[i] = dis(x, i), fr[i] = x;
    }
    dfs(k + 1,0,0);
    printf("%.9lf\n",sqrt(ans) / 2);
    return 0;
}
