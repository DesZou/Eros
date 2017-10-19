#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define DEBUG(args...) fprintf(stderr, args)

#define FOR(i, l, r) for(int i=(l), i##_end=(r); i<=i##_end; ++i)
#define REP(i, l, r) for(int i=(l), i##_end=(r); i< i##_end; ++i)
#define DFR(i, l, r) for(int i=(l), i##_end=(r); i>=i##_end; --i)
#define DRP(i, l, r) for(int i=(l), i##_end=(r); i> i##_end; --i)

typedef long long LL;

template<class T>T Min(const T &a, const T &b) {return a < b ? a : b;}
template<class T>T Max(const T &a, const T &b) {return a > b ? a : b;}
template<class T>bool Chkmin(T &a, const T &b) {return a > b ? a=b, 1 : 0;}
template<class T>bool Chkmax(T &a, const T &b) {return a < b ? a=b, 1 : 0;}

namespace FI {
	const int SIZE = 1 << 15 | 1;
	char buf[SIZE], *front, *back;
	void NextChar(char &c) {
		if(front == back) back = (front=buf) + fread(buf, 1, SIZE, stdin);
		c = front==back ? (char)EOF : *front++;
	}
	void NextInt(int &x) {
		char c;
		for(NextChar(c); c>'9'||c<'0'; NextChar(c)) ;
		for(x=0; c>='0'&&c<='9'; NextChar(c)) x = (x<<3)+(x<<1)+c-'0';
	}
}

const int SN = 500000 + 47;
const int MOD = 1000000007;

std::vector<int> edge[SN], scc[SN];
std::vector<int>::iterator it;
int dfn[SN], low[SN], stack[SN], bel[SN], top, rank;
bool vis[SN];
int que[SN], front, back, d[SN];
int t[SN], len[SN], n, cnt;
int f[SN], g[SN], h[SN], ans, all;

void Tarjan(int);
void TopoSort();
void DP();

int main() {

	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);

	int x, y, z;

	FI::NextInt(n);
	FOR(i, 1, n) FI::NextInt(t[i]), FI::NextInt(len[i]);

	FOR(i, 1, n) if(!dfn[i]) Tarjan(i);

	TopoSort(), DP();

	printf("%d\n", ans);

	return 0;

}

void Tarjan(int x) {
	dfn[x] = low[x] = ++rank, vis[x] = true, stack[++top] = x;
	if(t[x] != x)
		if(!dfn[t[x]]) Tarjan(t[x]), Chkmin(low[x], low[t[x]]);
		else if(vis[t[x]]) Chkmin(low[x], dfn[t[x]]); // 蛇皮鼠。
	if(low[x] == dfn[x]) {
		++cnt;
		while(stack[top] != x) {
			scc[cnt].push_back(stack[top]), bel[stack[top]] = x;
			vis[stack[top]] = false, ++g[x], --top;
		}
		++g[x], scc[cnt].push_back(x), --top, vis[x] = false, bel[x] = x;
		all = (all + 1LL * g[x] * (g[x] - 1)) % MOD;
	}
}

void TopoSort() {
	FOR(i, 1, n) if(bel[t[i]] != bel[i]) ++d[bel[t[i]]];
	FOR(i, 1, n) if(bel[i] == i && !d[i]) que[back++] = i;
	while(front < back) {
		int now = que[front++];
		if(bel[t[now]] != bel[now] && !--d[bel[t[now]]])
			que[back++] = bel[t[now]];
	}
}

void DP() {
	int x, y, z, sz, tmp;
	FOR(i, 1, n) if(bel[t[i]] != bel[i]) edge[bel[t[i]]].push_back(bel[i]);
	DFR(i, back - 1, 0)
		for(it = edge[x = que[i]].begin(); it != edge[x].end(); ++it)
			g[*it] += g[x];
	REP(i, 0, back) {
		x = que[i];
		if(bel[t[x]] != bel[x]) {
			++f[x];
			ans = (ans + 1LL * f[x] * g[bel[t[x]]] % MOD * len[x]) % MOD;
			all = (all + g[bel[t[x]]]) % MOD;
			(f[bel[t[x]]] += f[x]) %= MOD;
			if(bel[t[t[x]]] == bel[t[x]]) h[t[x]] += f[x];
		}
	}
	FOR(i, 1, cnt) if(scc[i].size() > 1) {
		x = y = z = 0, sz = scc[i].size();
		z = *scc[i].begin(), tmp = 0;
		do {
			++h[z], x = (x + len[z]) % MOD;
			y = (y + 1LL * (sz - tmp - 1) * len[z]) % MOD;
			z = t[z], ++tmp;
		}while(z != *scc[i].begin());
		z = *scc[i].begin();
		do {
			ans = (ans + 1LL * y * h[z]) % MOD;
			y = (y + x - 1LL * sz * len[z] % MOD + MOD) % MOD;
			z = t[z];
		}while(z != *scc[i].begin());
	}
	ans = (ans - 1LL * n * (n - 1) % MOD + all + MOD) % MOD;
}
