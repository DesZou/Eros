/*
 *  luogu2057
 *
 *  luogu1646 减弱版，除了边权固定没什么区别。
 * */
#include <cstdio>
using std::scanf;
using std::printf;

#include <cstring>
using std::memcpy;
using std::memset;

#include <iostream>
using std::cerr;
using std::endl;

#include <algorithm>
using std::min;

const size_t Size = 300 + 5;
const int Inf = -1u >> 1;

namespace Dinic {
    struct Curve {
        int next, to, cap;
    } c[Size * Size * 2];

    int source, sink;

    int level[Size], head[Size], cur[Size];

    void insert(int u, int v, int w) {
        static int _Index = 1;
        c[++_Index] = (Curve){head[u], v, w};
        head[u] = _Index;
    }

    void add(int u, int v, int w) {
        insert(u, v, w);
        insert(v, u, 0);
    }

    bool bfs() {
        static int q[Size], front, back;
        memset(level, -1, sizeof level);
        level[q[front = 0] = source] = 0, back = 1;
        while(front < back)
            for(int now, i = head[now = q[front++]]; i; i = c[i].next)
                if(c[i].cap && level[c[i].to] == -1)
                    level[q[back++] = c[i].to] = level[now] + 1;
        return level[sink] != -1;
    }

    int dfs(int x, int f) {
        if(!f || x == sink) return f;
        for(int flow, &i = cur[x]; i; i = c[i].next)
            if(c[i].cap && level[c[i].to] == level[x] + 1)
                if((flow = dfs(c[i].to, min(f, c[i].cap))))
                    return c[i].cap -= flow, c[i ^ 1].cap += flow, flow;
        return 0;
    }

    int run(int res = 0) {
        for(int x; bfs();) {
            memcpy(cur, head, sizeof cur);
            while((x = dfs(source, Inf))) res += x;
        } return res;
    }
} using namespace Dinic;

int n, m;

int main() {
    scanf("%d%d", &n, &m);

    source = n + 1, sink = n + 2;

    for(int i = 1, j; i <= n; ++i) {
        scanf("%d", &j);
        if(j) add(source, i, 1);
        else add(i, sink, 1);
    }

    while(m --> 0) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y, 1);
        add(y, x, 1);
    }

    printf("%d\n", run());

    return 0;
}
