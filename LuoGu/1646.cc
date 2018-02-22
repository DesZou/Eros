/*
 *  luogu1646
 *
 *  最小割。给每个同学建一个点，原点连向它，流量为选文科的喜悦值。
 *  它再连向汇点，流量为选理科的喜悦值。再建一些辅助点，从原点连出或连向汇点，
 *  流量为两个同学同时选文或选理的喜悦值。
 *  再连向配对的两个同学，这里的流量可以设为无穷大。
 *  这时的最小割就是能产生的最小喜悦值，用所有可能的喜悦值之和减去就得到了答案。
 *  我们可以发现，这种非此即彼的选择可以用最小割来解释。
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

const size_t Size = 100 * 4 + 5;
const int Inf = -1u >> 1;

namespace Dinic {
    struct Curve {
        int next, to;
        long long cap;
    } c[Size * Size * 4];

    int source, sink;

    int level[Size * Size], head[Size * Size], cur[Size * Size];

    void insert(int u, int v, long long w) {
        static int _Index = 1;
        c[++_Index] = (Curve){head[u], v, w};
        head[u] = _Index;
    }

    void add(int u, int v, long long w) {
        insert(u, v, w);
        insert(v, u, 0);
    }

    bool bfs() {
        static int q[Size * Size], front, back;
        memset(level, -1, sizeof level);
        level[q[front = 0] = source] = 0, back = 1;
        while(front < back)
            for(int now, i = head[now = q[front++]]; i; i = c[i].next)
                if(c[i].cap && level[c[i].to] == -1)
                    level[q[back++] = c[i].to] = level[now] + 1;
        return level[sink] != -1;
    }

    long long dfs(int x, long long f) {
        if(!f || x == sink) return f;
        long long flow;
        for(int &i = cur[x]; i; i = c[i].next)
            if(c[i].cap && level[c[i].to] == level[x] + 1)
                if((flow = dfs(c[i].to, min(f, c[i].cap))))
                    return c[i].cap -= flow, c[i ^ 1].cap += flow, flow;
        return 0;
    }

    long long run(long long res = 0) {
        for(long long x; bfs();) {
            memcpy(cur, head, sizeof cur);
            while((x = dfs(source, Inf))) res += x;
        } return res;
    }
} using namespace Dinic;

int n, m;

int num[Size][Size], idx;

long long total;

int main() {
    scanf("%d%d", &n, &m);

    source = ++idx, sink = ++idx;

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) num[i][j] = ++idx;

    for(int i = 1, k; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            scanf("%d", &k);
            add(source, num[i][j], k);
            total += k;
        }

    for(int i = 1, k; i <= n; ++i)
        for(int j = 1; j <= m; ++j) {
            scanf("%d", &k);
            add(num[i][j], sink, k);
            total += k;
        }

    for(int i = 1, k, p; i < n; ++i)
        for(int j = 1; j <= m; ++j) {
            scanf("%d", &k);
            p = ++idx;
            total += k;
            add(source, p, k);
            add(p, num[i][j], Inf);
            add(p, num[i + 1][j], Inf);
        }

    for(int i = 1, k, p; i < n; ++i)
        for(int j = 1; j <= m; ++j) {
            scanf("%d", &k);
            p = ++idx;
            total += k;
            add(p, sink, k);
            add(num[i][j], p, Inf);
            add(num[i + 1][j], p, Inf);
        }

    for(int i = 1, k, p; i <= n; ++i)
        for(int j = 1; j < m; ++j) {
            scanf("%d", &k);
            p = ++idx;
            total += k;
            add(source, p, k);
            add(p, num[i][j], Inf);
            add(p, num[i][j + 1], Inf);
        }

    for(int i = 1, k, p; i <= n; ++i)
        for(int j = 1; j < m; ++j) {
            scanf("%d", &k);
            p = ++idx;
            total += k;
            add(p, sink, k);
            add(num[i][j], p, Inf);
            add(num[i][j + 1], p, Inf);
        }

    printf("%lld\n", total - run());

    return 0;
}
