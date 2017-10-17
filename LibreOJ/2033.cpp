#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>

// const int Inf = -1u >> 1;
const size_t Size = 2e5 + 5;

std::map<int, int> chl[Size];

int fa[Size], maxl[Size];

long long ans;

int top = 1, last = 1, root = 1;

void push(int x) {
    int p = last, np = ++top; maxl[np] = maxl[p] + 1;
    while(p && !chl[p][x]) chl[p][x] = np, p = fa[p];
    if(!p) fa[np] = root, ans += maxl[np] - maxl[fa[np]];
    else {
        int q = chl[p][x];
        if(maxl[q] == maxl[p] + 1) fa[np] = q, ans += maxl[np] - maxl[fa[np]];
        else {
            int nq = ++top; maxl[nq] = maxl[p] + 1, chl[nq] = chl[q];
            ans -= maxl[q] - maxl[fa[q]];
            fa[nq] = fa[q], fa[q] = fa[np] = nq;
            ans += maxl[nq] - maxl[fa[nq]];
            ans += maxl[q] - maxl[fa[q]];
            ans += maxl[np] - maxl[fa[np]];
            while(p && chl[p][x] == q) chl[p][x] = nq, p = fa[p];
        }
    } last = np;
}

int main() {
    int n, x;
    for(scanf("%d", &n); n; --n) {
        scanf("%d", &x);
        push(x);
        printf("%lld\n", ans);
    }

    return 0;
}
