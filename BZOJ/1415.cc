/*
 * bzoj1415
 *
 * 概率DP，实际上只好记忆化搜索，很难按顺序DP。
 * 首先BFS记当猫在位置i要到位置j应该走的下一个点path[i][j]。
 * 注意当距离一样时，还要考虑标号。
 * 然后设f[i][j]为猫在i，鼠在j时猫抓到鼠的步数的期望。
 * 可知：
 * f[i][i] = 0;
 * f[i][j] = 1, when path[i][j] == j or path[path[i][j]][j] == j;
 * f[i][j] = ∑{i in nxtmouse}f[nxtcat][i] / (degree[j] + 1) + 1;
 * 意义就是猫的走法是已知的，把每个鼠的可能的走法都算进来
 * （包括停在原地），乘以它们的概率。
 * */
#include <cstdio>
#include <queue>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>

const size_t Size = 1000 + 5;

template<class T> T max(const T &a, const T &b) {
    return a > b? a : b;
}

template<class T> T min(const T &a, const T &b) {
    return a < b? a : b;
}

template<class T> bool chkmax(T &a, const T &b) {
    return a < b? a = b, 1 : 0;
}

template<class T> bool chkmin(T &a, const T &b) {
    return a > b? a = b, 1 : 0;
}

template<class T> T input() {
    T r(0); char c(getchar()); bool n(false);
    while(!std::isdigit(c)) {if(c == '-') n = 1; c = getchar();}
    while(std::isdigit(c)) {r = r * 10 - 48 + c, c = getchar();}
    return n? -r : r;
}

struct Edge {int next, to;} e[Size << 1];

int head[Size];
int path[Size][Size];
double f[Size][Size];
int degree[Size];

int _Index;

int cpos, kpos, n, m;

inline void connect(const int &u, const int &v) {
    e[++_Index] = (Edge){head[u], v};
    head[u] = _Index, ++degree[u];
    e[++_Index] = (Edge){head[v], u};
    head[v] = _Index, ++degree[v];
    path[u][v] = v, path[v][u] = u;
}

void bfs(const int &start) {
    static std::queue<int> q;
    static int dis[Size];
    std::memset(dis, 0x3f, sizeof dis);
    for(int i = head[start]; i; i = e[i].next) {
        dis[e[i].to] = 1, path[start][e[i].to] = e[i].to;
        q.push(e[i].to);
    }
    while(!q.empty()) {
        static int now;
        now = q.front(); q.pop();
        for(int i = head[now]; i; i = e[i].next)
            if(chkmin(dis[e[i].to], dis[now] + 1) or
                (dis[now] + 1 == dis[e[i].to] and
                 path[start][now] < path[start][e[i].to])) {
                path[start][e[i].to] = path[start][now];
                q.push(e[i].to);
            }
    }
}

double dfs(const int &s, const int &t) {
    if(s == t) return 0;
    else if(path[s][t] == t or path[path[s][t]][t] == t) return 1;
    else if(f[s][t]) return f[s][t];
    else {
        double &res = f[s][t] = dfs(path[path[s][t]][t], t);

        for(int i = head[t], j = path[path[s][t]][t]; i; i = e[i].next)
            res += dfs(j, e[i].to);

        return res = res / (1.0 + degree[t]) + 1.0;
    }
}

void init() {
    std::memset(head, 0, sizeof head);
    std::memset(path, 0, sizeof path);
    std::memset(degree, 0, sizeof degree);
    std::memset(f, 0, sizeof f);
    _Index = 0;
}

int main() {
    while(std::scanf("%d%d%d%d", &n, &m, &cpos, &kpos) != EOF) {
        init();

        for(int i = 0, u, v; i < m; ++i) {
            std::scanf("%d%d", &u, &v);
            connect(u, v);
        }

        for(int i = 1; i <= n; ++i) bfs(i);

        std::printf("%.3lf\n", dfs(cpos, kpos));
    }

    return 0;
}
