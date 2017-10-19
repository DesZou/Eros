#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

template <typename ty> void read(ty &x) {
	x = 0; int f = 1; char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x*10 + ch - '0'; ch = getchar(); }
	x *= f;
}
template <typename ty> ty Max(ty a, ty b) { return a > b ? a : b; }
template <typename ty> ty Min(ty a, ty b) { return a < b ? a : b; }

typedef long long LL;
typedef double db;

const int MOD = 1e9 + 7;
const int N = 5e5 + 5;

int T[N], L[N], CNT[N], ANS[N];
int VIS[N], NOW_VIS[N], D[N];
int n;

void dfs(int x, int cnt) {
	if (T[x] == x) {
		CNT[x] = 0;
		ANS[x] = 0;
		VIS[x] = 1;
		return;
	}
	if (VIS[x]) return;
	if (NOW_VIS[x]) {
		int j, k, t = cnt - D[x] - 1;
		LL tmp = 0, tot = 0;
		for (j = x, k = 0; k < t; j = T[j]) {
			k ++;
			tmp = (L[j] + tmp) % MOD;
			tot = (tmp + tot) % MOD;
		}
		tmp = (L[j] + tmp) % MOD;
		CNT[x] = t; ANS[x] = tot; VIS[x] = 1;
		for (int i = T[x], pre = x; i != x; i = T[i]) {
			VIS[i] = 1; CNT[i] = t;
			ANS[i] = (((LL) ANS[pre] - 1ll * t * L[pre] + tmp - L[pre]) % MOD + MOD) % MOD;
			pre = i;
		}
		return;
	}
	D[x] = cnt;
	NOW_VIS[x] = 1;
	dfs(T[x], cnt + 1);
	NOW_VIS[x] = 0;
	if (VIS[x]) return;
	VIS[x] = 1;
	CNT[x] = CNT[T[x]] + 1;
	ANS[x] = ((LL)ANS[T[x]] + 1ll * CNT[x] * L[x]) % MOD;
	return;
}

int main() {
	
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
	
	read(n);
	for (int i = 1; i <= n; ++ i) {
		read(T[i]); read(L[i]);
	}
	
	for (int i = 1; i <= n; ++ i) {
		if (!VIS[i])
			dfs(i, 1);
	}
	
	LL ans = 0;
	for (int i = 1; i <= n; ++ i) {
		ans += (ANS[i] - (n - CNT[i] - 1));
		ans = (ans % MOD + MOD) % MOD;
	}
	
	printf("%lld\n", ans);
	
	return 0;
	
}
