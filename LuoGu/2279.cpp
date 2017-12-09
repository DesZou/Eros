#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

const size_t Size = 1000 + 5;
const int Inf = -1u >> 1;

int n, ans;

struct Edge {int next, to;} e[Size << 1];

int head[Size], fa[Size], d[Size];

bool vis[Size];

std::priority_queue<std::pair<int, int> > q;

void dfs(int x) {
    q.push(std::make_pair(d[x] = d[fa[x]] + 1, x));
    for(int i = head[x]; i; i = e[i].next)
        if(e[i].to != fa[x]) dfs(e[i].to);
}

void cover(int x, int b = 2) {
    vis[x] = true;
    if(b) for(int i = head[x]; i; i = e[i].next)
        cover(e[i].to, b - 1);
}

void insert(int u, int v) {
    static int _Index = 0;
    e[++_Index] = (Edge){head[u], v};
    head[u] = _Index;
}

int main() {
    scanf("%d", &n);

    for(int i = 2; i <= n; ++i) {
        scanf("%d", fa + i);
        insert(i, fa[i]);
        insert(fa[i], i);
    }

    dfs(1);

    while(!q.empty()) {
        int now = q.top().second; q.pop();
        if(!vis[now]) {
            if(fa[fa[now]]) cover(fa[fa[now]]), ++ans;
            else if(!vis[1]) cover(1), ++ans;
        }
    }

    printf("%d\n", ans);

    return 0;
}
