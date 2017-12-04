#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
#include <iostream>

const size_t EdgeSize = 2e5 + 5;
const size_t VertexSize = 1e5 + 5;
const size_t Scale = 50 + 5;

template<class T> T max(const T &a, const T &b) {
    return a > b? a : b;
}

template<class T> T min(const T &a, const T &b) {
    return a < b? a : b;
}

template<class T> bool chkmin(T &a, const T &b) {
    return a > b? a = b, 1 : 0;
}

template<class T> bool chkmax(T &a, const T &b) {
    return a < b? a = b, 1 : 0;
}

template<class T> T input() {
    T r(0); char c(getchar()); bool n(false);
    while(c > '9' || c < '0') {if(c == '-') n = true; c = getchar();}
    while(c <= '9' && c >= '0') {r = r * 10 - 48 + c, c = getchar();}
    return n? -r : r;
}

struct Edge {int next, to, dis;} e[EdgeSize], re[EdgeSize];

int n, m, k, p;

int rhead[VertexSize], head[VertexSize];

int f[VertexSize][Scale];
bool vis[VertexSize][Scale];

int dis[VertexSize];

void reversed_spfa(int start) {
    static bool inque[VertexSize];
    static std::queue<int> q;
    std::memset(dis, 0x3f, sizeof dis);
    q.push(start); dis[start] = 0;
    while(!q.empty()) {
        int now = q.front(); q.pop(); inque[now] = false;
        for(int i = rhead[now]; i; i = re[i].next)
            if(chkmin(dis[re[i].to], dis[now] + re[i].dis))
                if(!inque[re[i].to]) q.push(re[i].to), inque[re[i].to] = 1;
    }
}

bool cirext;

int dfs(int x, int dt) {
    if(vis[x][dt]) {cirext = true; return 0;}
    if(f[x][dt]) return f[x][dt];

    int &res = f[x][dt];
    vis[x][dt] = true;

    for(int i = head[x], tmp; i; i = e[i].next) {
        tmp = dt - (dis[e[i].to] - (dis[x] - e[i].dis));
        if(tmp > k || tmp < 0) continue;
        res = (res + dfs(e[i].to, tmp)) % p;
        if(cirext) return 0;
    }

    vis[x][dt] = false;

    if(x == n && dt == 0) ++res;
    return res;
}

int _Index, _Rindex;

void insert(int u, int v, int w) {
    e[++_Index] = (Edge){head[u], v, w};
    head[u] = _Index;
}

void rinsert(int u, int v, int w) {
    re[++_Rindex] = (Edge){rhead[u], v, w};
    rhead[u] = _Rindex;
}

int main() {
    // freopen("park.in", "r", stdin);
    // freopen("park.out", "w", stdout);

    for(int T = input<int>(); T --> 0;) {
        std::memset(head, 0, sizeof head);
        std::memset(rhead, 0, sizeof rhead);
        std::memset(vis, 0, sizeof vis);
        std::memset(f, 0, sizeof f);
        _Index = _Rindex = cirext = 0;

        n = input<int>(), m = input<int>();
        k = input<int>(), p = input<int>();

        for(int i = 0, u, v, w; i < m; ++i) {
            u = input<int>(), v = input<int>(), w = input<int>();
            insert(u, v, w), rinsert(v, u, w);
        }

        reversed_spfa(n);
        
        int ans = 0;

        for(int i = 0; i <= k && !cirext; ++i)
            ans = (ans + dfs(1, i)) % p;

        printf("%d\n", cirext? -1 : ans);
    }

    return 0;
}
