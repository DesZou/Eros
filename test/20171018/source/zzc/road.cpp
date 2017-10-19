#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

// const int Inf = -1u >> 1;
const int Mod = 1e9 + 7;
const size_t Size = 5e5 + 5;

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
    T r(0); char c(getchar()); bool n(0);
    while(c > '9' || c < '0') {if(c == '-') n = 1; c = getchar();}
    while(c <= '9' && c >= '0') {r = r * 10 - 48 + c, c = getchar();}
    return n? -r : r;
}

typedef std::vector<int>::iterator viter;
typedef int array[Size];

std::vector<int> e[Size], scc[Size];

bool in_stack[Size];
array dfn, low, stack, belong, que, d;
array to, len;
array f, g, h;
int top, front, back, n, ans, cnt;

void tarjan(int x) {
    static int _Index = 0;
    dfn[x] = low[x] = ++_Index;
    in_stack[x] = true, stack[++top] = x;
    if(to[x] != x) {
        if(!dfn[to[x]]) tarjan(to[x]), chkmin(low[x], low[to[x]]);
        else if(in_stack[to[x]]) chkmin(low[x], dfn[to[x]]);
    }
    if(low[x] == dfn[x]) {
        ++cnt;
        for(int now = -1; now != x;) {
            now = stack[top--];
            scc[cnt].push_back(now);
            belong[now] = x;
            in_stack[now] = false;
            ++g[x];
        } ans = (ans + (long long)g[x] * (g[x] - 1)) % Mod;
    }
}

void toposort() {
    for(int i = 1; i <= n; ++i) if(belong[to[i]] != belong[i]) ++d[belong[to[i]]];
    for(int i = 1; i <= n; ++i) if(belong[i] == i && !d[i]) que[back++] = i;
    while(front < back) {
        int now = que[front++];
        if(belong[to[now]] != belong[now] && ! --d[belong[to[now]]])
            que[back++] = belong[to[now]];
    }
}

void fig() {
    for(int i = 1; i <= n; ++i) if(belong[to[i]] != belong[i])
        e[belong[to[i]]].push_back(belong[i]);
    for(int i = back - 1, x; i >= 0; --i)
        for(viter it = e[x = que[i]].begin(); it != e[x].end(); ++it)
            g[*it] += g[x];
    for(int i = 0, x; i < back; ++i) if(belong[(x = que[i])] != belong[to[x]]) {
        ++f[x];
        ans = (ans + (long long)f[x] * g[belong[to[x]]] % Mod * len[x] % Mod) % Mod;
        ans = (ans + g[belong[to[x]]]) % Mod;
        (f[belong[to[x]]] += f[x]) %= Mod;
        if(belong[to[to[x]]] == belong[to[x]]) h[to[x]] += f[x];
    }
    for(int i = 1, x, y, z, sz, tmp; i <= cnt; ++i) if(scc[i].size() > 1) {
        x = y = tmp = 0, sz = scc[i].size(), z = *scc[i].begin();
        do {
            ++h[z], x = (x + len[z]) % Mod;
            y = (y + (long long)(sz - tmp - 1) * len[z]) % Mod;
            z = to[z], ++tmp;
        } while(z != *scc[i].begin());
        do {
            ans = (ans + (long long)y * h[z]) % Mod;
            y = (y + x - (long long)sz * len[z] % Mod + Mod) % Mod;
            z = to[z];
        } while(z != *scc[i].begin());
    } ans = (ans - (long long)n * (n - 1) % Mod + Mod) % Mod;
}

int main() {
    freopen("road.in", "r", stdin);
    freopen("road.out", "w", stdout);

    n = input<int>();

    for(int i = 1; i <= n; ++i)
        to[i] = input<int>(), len[i] = input<int>();

    for(int i = 1; i <= n; ++i) if(!dfn[i]) tarjan(i);

    toposort(), fig();

    printf("%d\n", ans);

    return 0;
}
